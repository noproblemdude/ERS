/*

All of the  functions controlling the Motor HW.
Triggering will happen when a can message with the relevant Processid has been received.

*/

#ifndef MOTOR_H
#define MOTOR_H


#include "CAN_driver.h"
#include "common.h"
#include "config.h"
#include <Servo.h>


//Setup function for the CAN Shield. Has to be called every time the ECU is booted
extern void MOTOR_setup(void);

//Waits to receive a message, once message has been received it, it triggers the distributer
extern void standby(void);

//Triggers a process depending on the processID of the received message
static void distribute(void);

//Sends the buffered massage with the passed processID
static void send(PROCESS_IDS Pid);

//Accesses the feedback motor library to move the motor do desired positing as specified by the "angle" parameter 
static void moveMotor(unsigned char angle);


#endif