#include "CAN_driver.h"



long unsigned int rxId;
unsigned char len = 0;
unsigned char rxBuf[8];
char msgString[128];
//mcp2515_can CAN(SPI_CS_PIN);
unsigned char flagRecv;
//unsigned char len;
//unsigned char buf[8];
char str[20];
extern unsigned char stmp[8];

MCP_CAN CAN0(49);

/*
void MCP2515_ISR(void) {
      flagRecv = 1;
}
*/
void CAN_setup(void){
 
    Serial.begin(115200);


    // Initialize MCP2515 running at 16MHz with a baudrate of 500kb/s and the masks and filters disabled.
    if(CAN0.begin(MCP_ANY, CAN_500KBPS, MCP_16MHZ) == CAN_OK)
        Serial.println("MCP2515 Initialized Successfully!");
    else
        Serial.println("Error Initializing MCP2515...");
    
    CAN0.setMode(MCP_NORMAL);                     // Set operation mode to normal so the MCP2515 sends acks to received data.

    pinMode(CAN0_INT, INPUT);                            // Configuring pin for /INT input


}

byte data[8] = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07};


void sendTest()
{
  // send data:  ID = 0x100, Standard CAN Frame, Data length = 8 bytes, 'data' = array of data bytes to send
  byte sndStat = CAN0.sendMsgBuf(0x100, 0, 8, data);
  if(sndStat == CAN_OK){
    Serial.println("Message Sent Successfully!");
  } else {
    Serial.println("Error Sending Message...");
  }
  delay(100);   // send data per 100ms
}

/*
void CAN_listen(unsigned char *buffer){

    unsigned int time = 0;

    while(time<=1000){
        if(CAN_MSGAVAIL == CAN.checkReceive()){
            SERIAL_PORT_MONITOR.println("Nachricht empfangen");
            CAN.readMsgBuf(&len, buffer);
            break;
        }
        SERIAL_PORT_MONITOR.println("Wartet auf Nachricht");
        delay(100);
        time=time + 100;
    }

    SERIAL_PORT_MONITOR.println("Keine nachricht empfangen");

}



void CAN_transmit(const byte *body){
    CAN.MCP_CAN::sendMsgBuf(CANid, 0, 8, body);
    SERIAL_PORT_MONITOR.println("Nachricht versendet");
}




*/