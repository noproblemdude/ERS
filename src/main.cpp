#include <SPI.h>
#include "config.h"
#include "CAN_driver.h"
#include "Motor.h"


int positiontmp = 0;


void setup() {
    CAN_setup();
    MOTOR_setup();
}



void loop() {
    standby();
}

