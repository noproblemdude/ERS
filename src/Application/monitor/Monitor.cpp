
#include "Monitor.h"


unsigned char recvmsg[8];
unsigned char sntmsg[8];

void standby(){
    CAN_listen(recvmsg);
    distribute();
}

void distribute(){
    switch(recvmsg[0]) {
        case MONITOR_STORERANGE:
            storerange();
            break;
        default:
            SERIAL_PORT_MONITOR.println("Keine gültige processid");
        }
}

void send(){
    
    sntmsg[0] = SENSOR_MEASURE;
    CAN_transmit(sntmsg);

}

void calculaterange(){
    //TODO
}

void storerange(){
    //TODO
}





