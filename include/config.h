/*

global constants are defined here

*/

#ifndef CONFIG_H
#define CONFIG_H


const unsigned char CANid = 0;


typedef enum {
    MONITOR_RENDERMAP,
    MONITOR_MOTORFEEDBACK,
    MOTOR_MOVE,
    MONITOR_STORERANGE,
    SENSOR_MEASURE
    
} PROCESS_IDS;

#endif