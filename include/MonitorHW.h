/*

Here is the functionality destined to take care of the lower level 
Hardware access of the Monitor ECU.

*/

#ifndef MONITORHW_H
#define MONITORHW_H


#include "CAN_driver.h"
#include "common.h"
#include "config.h"


//Waits to receive a message, once message has been received it, it triggers the distributer
void standby();

//Triggers a process depending on the processID of the received message
void distribute();

//Sends the buffered massage with the passed processID
void send(PROCESS_IDS Pid);

//requests a measurement for a given degree, should first trigger the motor and then the sensor
void requestmeasurement(unsigned char deg);

//store the coordinates of the measured object into a map object
void storerange();

//take the received combination of angle and distance and calculate the coordinates of the scanned object
void calculaterange();

//periodically display radar view according to a map object
void displaymap();

#endif