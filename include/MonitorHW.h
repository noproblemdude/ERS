/*
Here is the functionality destined to take care of the lower level 
Hardware access of the Monitor ECU.
*/



#ifndef MONITORHW_H
#define MONITORHW_H


#include "CAN_driver.h"
#include "common.h"
#include "config.h"

#include <Elegoo_GFX.h>    
#include <Elegoo_TFTLCD.h> 


#define LCD_CS A3 
#define LCD_CD A2 
#define LCD_WR A1 
#define LCD_RD A0 

#define LCD_RESET A4


#define	BLACK   0x0000
#define	BLUE    0x001F
#define	RED     0xF800
#define	GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF

//wipes all of the data points from the monitor
static void resetScreen(void);

//Draws new data point onto the screen, considering the last datapoint from that direction and if it was on one of the radar lines
static void renderMap(void);

// Configures the Harware on boot
extern void MONITOR_setup(void);

//Waits to receive a message, once message has been received it, it triggers the distributer
static void standby(void);

//Triggers a process depending on the processID of the received message
static void distribute(void);

//Sends the buffered massage with the passed processID
extern void send(PROCESS_IDS Pid);

//Sends a request to the sensor ECU to measure the range in its current position
static void requestMeasureRange(void);

//Sends a request to the Motor ECU to move the motor to the position described by the deg parameter, this is called first in the main.cpp to start the routine.
extern void requestMoveMotor(unsigned char deg);

//Stores the data from the other ECUs into a struct
static void storeRange(unsigned char deg, uint8_t range);

//Draws the base graphics onto the monitor (radar lines)
static void displayMap(void);


#endif
