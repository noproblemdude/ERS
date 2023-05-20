#ifndef SENSOR_H
#define SENSOR_H


#include "BSW/CAN_driver.h"
#include "BSW/common.h"
#include "config.h"



void standby();

void distribute();

void send();

void measureRange(unsigned int *range);



#endif




