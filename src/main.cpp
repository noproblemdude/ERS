#include <SPI.h>
#include "Monitor.h"
#include "config.h"
#include "CAN_driver.h"
#include "CAN_driver.h"




void setup() {
    //MONITOR_setup();
    CAN_setup();
}


void loop() {

    sendTest();

    /*
    int i;
    for(i=0; i<=180;i++){
      RenderMap();
    }
    */
}

