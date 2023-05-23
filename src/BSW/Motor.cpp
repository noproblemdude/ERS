#include "Motor.h"


Servo myservo;

void MOTOR_setup() {
  myservo.attach(10);
  movemotor(0);
}

void movemotor(unsigned char angle){
    myservo.write(angle-90);
    delay(angle*1);
}
