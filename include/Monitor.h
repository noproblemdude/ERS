/*

Here are the functions which take care of the user interfacing with the system.
Most of these functions will be triggered by button presses or something similar

*/

#ifndef MONITOR_H
#define MONITOR_H


#include "MonitorHW.h"



//Will shutdown the Monitor and set all of the hardware into a sleep mode
void shutdown();

//Will turn on the monitor and wake up all of the hardware from sleep mode
void startup();

//Shutdown and Startup
void reset();

//Clear the screen of any scanned objects by clearing the map
void clear();


#endif