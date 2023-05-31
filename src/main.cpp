#include <SPI.h>
#include "config.h"
#include "CAN_driver.h"
#include "Sensor.h"


void setup() {
    CAN_setup();
}



void loop() {
    measureRange();
}

