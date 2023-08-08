#include "CAN_driver.h"


tCAN message;

void CAN_setup(){
 
    Serial.begin(9600);
    Serial.println("CAN Write - Testing transmission of CAN Bus messages");
    delay(1000);

    if(Canbus.init(CANSPEED_500))
    //Initialise MCP2515 CAN controller at the specified speed
    Serial.println("CAN Init ok");
    
    else

    Serial.println("Can't init CAN");
    delay(1000);


}



void CAN_listen(unsigned char *buffer){

    mcp2515_bit_modify(CANCTRL, (1<<REQOP2)|(1<<REQOP1)|(1<<REQOP0),0);
    mcp2515_get_message(&message);
    
    for (int i = 0; i < 7; i++) { 
            buffer[i]==message.data[i];
        }

}



void CAN_transmit(const byte *body){
   
message.id = 0; //formatted in HEX
message.header.rtr = 0;
message.header.length = 8; //formatted in DEC

for (int i = 0; i < 7; i++) { 
            message.data[i]==body[i];
        }

mcp2515_bit_modify(CANCTRL, (1<<REQOP2)|(1<<REQOP1)|(1<<REQOP0),0);
mcp2515_send_message(&message);
}




