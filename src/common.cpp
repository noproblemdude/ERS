#include <stdio.h>
#include "common.h"



void intTochar (unsigned int intvalue, unsigned char* output){

    output[0] = static_cast<char>((intvalue >> 24) & 0xFF);
    output[1] = static_cast<char>((intvalue >> 16) & 0xFF);
    output[2] = static_cast<char>((intvalue >> 8) & 0xFF);
    output[3] = static_cast<char>(intvalue & 0xFF);

}


unsigned int charToInt(unsigned char *array){

    unsigned int value = 0;
    value |= array[0] << 24;
    value |= array[1] << 16;
    value |= array[2] << 8;
    value |= array[3];
    return value;
}


unsigned int extractRange(unsigned char *msg){

    unsigned char output[4];

    output[0] = msg[4];
    output[1] = msg[5];
    output[2] = msg[6];
    output[3] = msg[7];

    return charToInt(output);

    

}