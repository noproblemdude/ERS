/*

All of the  functions controlling the Sensor HW.
Triggering will happen when a can message with the relevant Processid has been received.

*/


#ifndef SENSOR_H
#define SENSOR_H


#include "CAN_driver.h"
#include "common.h"
#include "config.h"


//Waits to receive a message, once message has been received it, it triggers the distributer
extern void standby(void);

//Triggers a process depending on the processID of the received message
static void distribute(void);

//Sends the buffered massage with the passed processID
static void send(void);

//access Sensor driver and genetrate the distance of an object, if one is detected
static void measureRange(void);

#endif




