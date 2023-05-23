/*

global constants are defined here

*/

#ifndef CONFIG_H
#define CONFIG_H


const unsigned char CANid = 0;


typedef enum {
    SENSOR_MEASURE,
    MONITOR_STORERANGE,
    MOTOR_MOVE,
    MONITOR_MOTORFEEDBACK,
} PROCESS_IDS;

#endif