#include <SPI.h>
#include "Monitor.h"
#include "config.h"
#include "CAN_driver.h"

unsigned char remsg[8];
unsigned char semsg[8] = {5,0,0,0,0,0,0,0};

void setup() {
    MONITOR_setup();
    CAN_setup();
    send(MOTOR_RESET);
    delay(5000);
}


void loop() {

    int i;
    for(i=0; i<=180;i++){
      requestMoveMotor(i);
    }

}

