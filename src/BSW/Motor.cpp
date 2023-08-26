
#include "Motor.h"


static Servo myServo;

static unsigned char recvmsg[8];


static int position;

extern void MOTOR_setup(void) {
  myServo.attach(10);
  myServo.write(180);
  delay(1000);
  position = 0;
}

extern void standby(void){
    recvmsg[0] = 0;    
    CAN_listen(recvmsg);
    distribute();
}


static void distribute(void){

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
            break;
        }
}

static void moveMotor(unsigned char angle){
    SERIAL_PORT_MONITOR.print("Motor wird auf folgende position bewegt:");
    SERIAL_PORT_MONITOR.println(angle);
    myServo.write((unsigned char)180-angle);
    delay(abs(angle-(unsigned char)position)*10);
    position = angle;
}

static void send(PROCESS_IDS Pid){

    static unsigned char sntmsg[8];

    sntmsg[0] = (char)Pid;
    CAN_transmit(sntmsg);
}
