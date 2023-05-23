
#include "Motor.h"


Servo myservo;

unsigned char recvmsg[8];
unsigned char sntmsg[8];

int position;

void MOTOR_setup() {
  myservo.attach(10);
  myservo.write(180);
  delay(1000);
  position = 0;
}

void standby(){    
    CAN_listen(recvmsg);
    distribute();
}


void distribute(){
    switch(recvmsg[0]) {
        case MOTOR_MOVE:
            movemotor(recvmsg[8]);
            send();
            break;
        default:
            SERIAL_PORT_MONITOR.println("Keine gültige processid");
        }
}

void movemotor(unsigned char angle){
    myservo.write(180-angle);
    delay(abs(angle-position)*10);
    position = angle;
}

void send(){
    sntmsg[0] = MONITOR_MOTORFEEDBACK;
    CAN_transmit(sntmsg);
}
