#ifndef CAN_SETUP
#define CAN_SETUP

#ifndef CONFIG_H
#define CONFIG_H
#include <config.h>
#endif

#ifndef SPI_H
#define SPI_H
#include <SPI.h>
#endif


#define CAN_2515

// #define CAN_2518FD

// Set SPI CS Pin according to your hardware



#if defined(SEEED_WIO_TERMINAL) && defined(CAN_2518FD)
// For Wio Terminal w/ MCP2518FD RPi Hat：
// Channel 0 SPI_CS Pin: BCM 8
// Channel 1 SPI_CS Pin: BCM 7
// Interupt Pin: BCM25
const int SPI_CS_PIN  = BCM8;
const int CAN_INT_PIN = BCM25;
#else

// For Arduino MCP2515 Hat:
// the cs pin of the version after v1.1 is default to D9
// v0.9b and v1.0 is default D10
const int SPI_CS_PIN = 9;
const int CAN_INT_PIN = 2;
#endif


#ifdef CAN_2518FD
#include "mcp2518fd_can.h"
mcp2518fd CAN(SPI_CS_PIN); // Set CS pin
#endif

#ifdef CAN_2515
#include "mcp2515_can.h"
mcp2515_can CAN(SPI_CS_PIN); // Set CS pin
#endif

#endif


//variables for reception
unsigned char flagRecv = 0;
unsigned char len = 0;
unsigned char buf[8];
char str[20];

//variables for transmission
unsigned char stmp[8] = {0, 0, 0, 0, 0, 0, 0, 0};




void MCP2515_ISR() {
      flagRecv = 1;
}

void CAN_setup(){

      SERIAL_PORT_MONITOR.begin(115200);
    while (!SERIAL_PORT_MONITOR) {
        ; // wait for serial port to connect. Needed for native USB port only
    }
    attachInterrupt(digitalPinToInterrupt(CAN_INT_PIN), MCP2515_ISR, FALLING); // start interrupt
    while (CAN_OK != CAN.begin(CAN_500KBPS)) {             // init can bus : baudrate = 500k
        SERIAL_PORT_MONITOR.println("CAN init fail, retry...");
        delay(100);
    }
    SERIAL_PORT_MONITOR.println("CAN init ok!");

}

void init_reception(){
      if (flagRecv) {
        // check if get data

        flagRecv = 0;                   // clear flag
        SERIAL_PORT_MONITOR.println("into loop");
        // iterate over all pending messages
        // If either the bus is saturated or the MCU is busy,
        // both RX buffers may be in use and reading a single
        // message does not clear the IRQ conditon.
        while (CAN_MSGAVAIL == CAN.checkReceive()) {
            // read data,  len: data length, buf: data buf
            SERIAL_PORT_MONITOR.println("checkReceive");
            CAN.readMsgBuf(&len, buf);

            // print the data
            for (int i = 0; i < len; i++) {
                SERIAL_PORT_MONITOR.print(buf[i]); SERIAL_PORT_MONITOR.print("\t");
            }
            SERIAL_PORT_MONITOR.println();
        }
    }
}


void init_transmission(){
    
    // send data:  id = 0x00, standrad frame, data len = 8, stmp: data buf
    stmp[7] = stmp[7] + 1;
    if (stmp[7] == 100) {
        stmp[7] = 0;
        stmp[6] = stmp[6] + 1;

        if (stmp[6] == 100) {
            stmp[6] = 0;
            stmp[5] = stmp[5] + 1;
        }
    }

    CAN.MCP_CAN::sendMsgBuf(CAN_id, 0, 8, stmp);
    delay(100);                       // send data per 100ms
    SERIAL_PORT_MONITOR.println("CAN BUS sendMsgBuf ok!");

}

void CAN_transmit(const byte *body){

    CAN.MCP_CAN::sendMsgBuf(CAN_id, 0, 8, body);
    SERIAL_PORT_MONITOR.println("CAN BUS sendMsgBuf ok!");

}