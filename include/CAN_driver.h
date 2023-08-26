/*

layer on top of the bare can drivers from the Seeed_Arduino_CAN library
functions that are reused by all of the other components to send/receive CAN frames

*/

#ifndef CAN_DRIVER_H
#define CAN_DRIVER_H


#include <Canbus.h>
#include <defaults.h>
#include <global.h>
#include <mcp2515.h>
#include <mcp2515_defs.h>
#include <SPI.h>



//Setup function for the CAN Shield. Has to be called every time the ECU is booted
extern void CAN_setup(void);

//Generic listen function. Waits for a message to be broadcated on the CAN bus and stores it in the passed buffer parameter
extern void CAN_listen(unsigned char *buffer);

//Builds a CAN frame from the CANid, body length and an 8 byte array
extern void CAN_transmit(const byte *body);


#endif