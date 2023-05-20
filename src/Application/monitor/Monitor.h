#ifndef MONITOR_H
#define MONITOR_H


#include "BSW/CAN_driver.h"
#include "BSW/common.h"
#include "config.h"



void standby();

void distribute();

void send();

void requestmeasurement();

void storerange();

void calculaterange();

#endif