
#include "MonitorHW.h"


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

void send(PROCESS_IDS Pid){
    sntmsg[0] = Pid;
    CAN_transmit(sntmsg);

}

void requestmeasurement(unsigned char deg){
    //TODO
}

void calculaterange(){
    //TODO
}

void storerange(){
    //TODO
}

void displaymap(){
    //TODO
}





