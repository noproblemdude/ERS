
#include "Sensor.h"




static unsigned int range;
static unsigned char recvmsg[8];




extern void standby(void){
    CAN_listen(recvmsg);
    distribute();
}



static void measureRange(void){

    static const int pingPin = 7; // Trigger Pin of Ultrasonic Sensor
    static const int echoPin = 6; // Echo Pin of Ultrasonic Sensor

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
    
    SERIAL_PORT_MONITOR.print("Gemessene entfernung:");
    SERIAL_PORT_MONITOR.println(range);
}



static void send(void){

    static unsigned char sntmsg[8];
    
    sntmsg[0] = (char)MONITOR_RENDERMAP;

    unsigned char byterange[4]; 
    
    intTochar(range,byterange);

    sntmsg[4] = byterange[0];
    sntmsg[5] = byterange[1];
    sntmsg[6] = byterange[2];
    sntmsg[7] = byterange[3];
    

    CAN_transmit(sntmsg);

}



static void distribute(void){
    
    switch((PROCESS_IDS)recvmsg[0]) {
        case SENSOR_MEASURE:
            SERIAL_PORT_MONITOR.println("Messanfrage erhalten, wird gemessen");
            measureRange();
            send();
            break;
        default:
            SERIAL_PORT_MONITOR.print("Keine gültige processid:");
            Serial.println(recvmsg[0]);
            break;
        }
    
    recvmsg[0] = 0;
}