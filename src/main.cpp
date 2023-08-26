#include <SPI.h>
#include "Monitor.h"
#include "config.h"
#include "CAN_driver.h"


void setup(void) {
    MONITOR_setup();
    CAN_setup();
    send(MOTOR_RESET);
    delay(5000);
}

void loop(void ) {

    int i;
    for(i=0; i<=180;i++){
      requestMoveMotor(i);
    }

}

