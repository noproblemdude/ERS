
#include "Sensor.h"


const int pingPin = 7; // Trigger Pin of Ultrasonic Sensor
const int echoPin = 6; // Echo Pin of Ultrasonic Sensor

unsigned int range;
unsigned char degree;
unsigned char recvmsg[8];
unsigned char sntmsg[8];



void standby(){
    CAN_listen(recvmsg);
    distribute();
}



void measureRange(){
    int measurements[10];
    long duration;
    for(int i =0;i<=9;i++){
        pinMode(pingPin, OUTPUT);
        digitalWrite(pingPin, LOW);
        delayMicroseconds(2);
        digitalWrite(pingPin, HIGH);
        delayMicroseconds(10);
        digitalWrite(pingPin, LOW);
        pinMode(echoPin, INPUT);
        duration = pulseIn(echoPin, HIGH);
        measurements[i] = duration / 29 / 2;
        SERIAL_PORT_MONITOR.print(measurements[i]);
        SERIAL_PORT_MONITOR.print("cm");
        SERIAL_PORT_MONITOR.println();
        delay(10);
    }
    range = round(calculateAverage(measurements,10));
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