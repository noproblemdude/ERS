#include "CAN_driver.h"


mcp2515_can CAN(SPI_CS_PIN);
unsigned char flagRecv;
unsigned char len;
unsigned char buf[8];
char str[20];
extern unsigned char stmp[8];


void MCP2515_ISR(void) {
      flagRecv = 1;
}

void CAN_setup(void){
 

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



void CAN_listen(unsigned char *buffer){

    unsigned int time = 0;

    while(time<=1000){
        if(CAN_MSGAVAIL == CAN.checkReceive()){
            SERIAL_PORT_MONITOR.println("Nachricht empfangen");
            CAN.readMsgBuf(&len, buffer);

            for (int i = 0; i < len; i++) {
                SERIAL_PORT_MONITOR.print(buffer[i]); SERIAL_PORT_MONITOR.print("\t");
            }

            break;
        }
        SERIAL_PORT_MONITOR.println("Wartet auf Nachricht");
        delay(100);
        time=time + 100;
    }

    SERIAL_PORT_MONITOR.println("Keine nachricht empfangen");

}



void CAN_transmit(const byte *body){

    for (int i = 0; i < len; i++) {
                SERIAL_PORT_MONITOR.print(body[i]); SERIAL_PORT_MONITOR.print("\t");
            }

    CAN.MCP_CAN::sendMsgBuf(CANid, 0, 8, body);
    SERIAL_PORT_MONITOR.println("Nachricht versendet");
}



