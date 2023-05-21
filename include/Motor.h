/*

All of the  functions controlling the Motor HW.
Triggering will happen when a can message with the relevant Processid has been received.

*/

#ifndef MOTOR_H
#define MOTOR_H


#include "CAN_driver.h"
#include "common.h"
#include "config.h"


//Waits to receive a message, once message has been received it, it triggers the distributer
void standby();

//Triggers a process depending on the processID of the received message
void distribute();

//Sends the buffered massage with the passed processID
void send(PROCESS_IDS Pid);

//Accesses the feedback motor library to move the motor do desired positing as specified by the "angle" parameter 
void movemotor(unsigned char angle);


#endif