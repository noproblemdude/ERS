// demo: CAN-BUS Shield, receive data with interrupt mode
// when in interrupt mode, the data coming can't be too fast, must >20ms, or else you can use check mode
// loovee, 2014-6-13

#include <SPI.h>

#include <CAN_driver.h>

void setup() {
    CAN_setup();
}



void loop() {
    init_transmission();
}

/*********************************************************************************************************
    END FILE
*********************************************************************************************************/
