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


void resetScreen(void);

void RenderMap(void);

void MONITOR_setup(void);

//Waits to receive a message, once message has been received it, it triggers the distributer
void standby(void);

//Triggers a process depending on the processID of the received message
void distribute(void);

//Sends the buffered massage with the passed processID
void send(PROCESS_IDS Pid);

//requests a measurement for a given degree, should first trigger the motor and then the sensor
void requestmeasurement(unsigned char deg);

//store the coordinates of the measured object into a map object
void storerange(void);

//take the received combination of angle and distance and calculate the coordinates of the scanned object
void calculaterange(void);

//periodically display radar view according to a map object
void displaymap(void);

#endif
