#include <SPI.h>
#include "Application/monitor/Monitor.h"
#include "config.h"
#include "BSW/CAN_driver.h"

void setup() {
    CAN_setup();
}

unsigned char MTBR[8];

void loop() {
    send();
    standby();
    delay(5000);
}

