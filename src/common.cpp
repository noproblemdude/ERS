#include "common.h"

unsigned char* intTochar (unsigned int intvalue){
    
    unsigned char output[4];

    output[0] = static_cast<char>((intvalue >> 24) & 0xFF);
    output[1] = static_cast<char>((intvalue >> 16) & 0xFF);
    output[2] = static_cast<char>((intvalue >> 8) & 0xFF);
    output[3] = static_cast<char>(intvalue & 0xFF);

    return output;

}


unsigned int charToint(unsigned char *bytes){
    
    unsigned int number = (static_cast<int>(bytes[0]) << 24) |
                        (static_cast<int>(bytes[1]) << 16) |
                        (static_cast<int>(bytes[2]) << 8) |
                        static_cast<int>(bytes[3]);

    return number;
}


unsigned char* extractRange(unsigned char *msg){

    unsigned char output[4];

    output[0] = msg[4];
    output[1] = msg[5];
    output[2] = msg[6];
    output[3] = msg[7];


}