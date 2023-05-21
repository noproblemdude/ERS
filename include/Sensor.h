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
void standby();

//Triggers a process depending on the processID of the received message
void distribute();

//Sends the buffered massage with the passed processID
void send(PROCESS_IDS Pid);

//access Sensor driver and genetrate the distance of an object, if one is detected
void measureRange(unsigned int *range);

#endif




