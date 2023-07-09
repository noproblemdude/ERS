#include <SPI.h>
#include "Monitor.h"
#include "config.h"
#include "CAN_driver.h"

unsigned char remsg[8];
unsigned char semsg[8];

void setup() {
    MONITOR_setup();
    CAN_setup();
}


void loop() {
  
    int i;
    for(i=0; i<=180;i++){
      requestMoveMotor(i);
    }
    

}

