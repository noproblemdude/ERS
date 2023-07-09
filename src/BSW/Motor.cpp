
#include "Motor.h"


Servo myServo;

unsigned char recvmsg[8];
unsigned char sntmsg[8];

int position;

void MOTOR_setup() {
  myServo.attach(10);
  myServo.write(180);
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
            moveMotor(recvmsg[7]);
            send(MONITOR_MOTORFEEDBACK);
            break;
        default:
            SERIAL_PORT_MONITOR.println("Keine gültige processid");
        }
}

void moveMotor(unsigned char angle){
    myServo.write(180-angle);
    delay(abs(angle-position)*10);
    position = angle;
}

void send(PROCESS_IDS Pid){
    sntmsg[0] = Pid;
    CAN_transmit(sntmsg);
}
