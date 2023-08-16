/*

auxiliary functions are defined here

*/

#ifndef COMMON_H
#define COMMON_H

void intTochar (unsigned int intvalue, unsigned char* output);

unsigned int charToInt(unsigned char* array);

unsigned int extractRange(unsigned char *msg);

double calculateAverage(int arr[], int size);

#endif