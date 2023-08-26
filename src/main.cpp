#include <SPI.h>
#include "config.h"
#include "CAN_driver.h"
#include "Motor.h"



void setup(void) {
    CAN_setup();
    MOTOR_setup();
}



void loop(void) {
    standby();
}

