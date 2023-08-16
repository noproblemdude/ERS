
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
    recvmsg[0] = 0;    
    CAN_listen(recvmsg);
    distribute();
}


void distribute(){

    SERIAL_PORT_MONITOR.println(recvmsg[0]);

    switch((PROCESS_IDS)recvmsg[0]) {
        case MOTOR_MOVE:
            moveMotor(recvmsg[7]);
            send(MONITOR_MOTORFEEDBACK);
            break;
        case MOTOR_RESET:
            SERIAL_PORT_MONITOR.println("Motor wird zurückgesetzt");
            moveMotor(0);
            break;
        default:
            SERIAL_PORT_MONITOR.println("Keine gültige processid");
        }
}

void moveMotor(unsigned char angle){
    SERIAL_PORT_MONITOR.print("Motor wird auf folgende position bewegt:");
    SERIAL_PORT_MONITOR.println(angle);
    myServo.write(180-angle);
    delay(abs(angle-position)*10);
    position = angle;
}

void send(PROCESS_IDS Pid){
    sntmsg[0] = (char)Pid;
    CAN_transmit(sntmsg);
}
