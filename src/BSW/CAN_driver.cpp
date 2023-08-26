#include "CAN_driver.h"


mcp2515_can CAN(SPI_CS_PIN);


static void MCP2515_ISR(void) {

    static unsigned char flagRecv;
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



extern void CAN_listen(unsigned char *buffer){

    static unsigned char len;
    bool received = false;
    unsigned int time = 0;

    while(time<=(unsigned int)10000){
        if(CAN_MSGAVAIL == CAN.checkReceive()){
            received = true;
            CAN.readMsgBuf(&len, buffer);
            SERIAL_PORT_MONITOR.println("NACHRICHT ERHALTEN");
            break;
        }
        delay(10);
        time=time + (unsigned int)10;
    }

    if(received == false){ SERIAL_PORT_MONITOR.println("KEINE NACHRICHT IN 10 SEKUNDEN ERHALTEN"); }
}



void CAN_transmit(const byte *body){
    CAN.MCP_CAN::sendMsgBuf(0, 0, 8, body);
}



