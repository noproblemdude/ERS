/*

layer on top of the bare can drivers from the Seeed_Arduino_CAN library
functions that are reused by all of the other components to send/receive CAN frames

*/

#ifndef CAN_DRIVER_H
#define CAN_DRIVER_H


#include "config.h"
#include <SPI.h>
#include "mcp2515_can.h"



#define CAN_2515



#if defined(SEEED_WIO_TERMINAL) && defined(CAN_2518FD)
const int SPI_CS_PIN  = BCM8;
const int CAN_INT_PIN = BCM25;
#else
const int SPI_CS_PIN = 9;
const int CAN_INT_PIN = 2;
#endif




//Setup function for the CAN Shield. Has to be called every time the ECU is booted
void CAN_setup();

//Generic listen function. Waits for a message to be broadcated on the CAN bus and stores it in the passed buffer parameter
void CAN_listen(unsigned char *buffer);

//Builds a CAN frame from the CANid, body length and an 8 byte array
void CAN_transmit(const byte *body);


#endif