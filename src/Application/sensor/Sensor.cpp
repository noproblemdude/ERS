
#include "Sensor.h"



unsigned int range;
unsigned char degree;
unsigned char recvmsg[8];
unsigned char sntmsg[8];



void standby(){    
    CAN_listen(recvmsg);
    distribute();    

}



void measureRange(){
    //TODO: Sensor access through sensorDriver.h for now mock values  
    range = 30;
    degree = 90;
}



void send(){

    sntmsg[0] = MONITOR_STORERANGE;

    unsigned char* byterange = intTochar(range);

    sntmsg[4] = byterange[0];
    sntmsg[5] = byterange[1];
    sntmsg[6] = byterange[2];
    sntmsg[7] = byterange[3];

    CAN_transmit(sntmsg);

}



void distribute(){
    switch(recvmsg[0]) {
        case SENSOR_MEASURE:
            measureRange();
            send();
            break;
        default:
            SERIAL_PORT_MONITOR.println("Keine gültige processid");
        }
}








