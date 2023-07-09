
#include "MonitorHW.h"


unsigned char recvmsg[8];
unsigned char sntmsg[8];
static unsigned char degrees;

struct dataPoint
{
    uint8_t x;
    uint8_t y;
};

struct dataPoint dataPoints[180];

static Elegoo_TFTLCD tft(LCD_CS, LCD_CD, LCD_WR, LCD_RD, LCD_RESET);


void MONITOR_setup(void) {
    Serial.begin(115200);
    Serial.println(F("TFT LCD test"));

#ifdef USE_Elegoo_SHIELD_PINOUT
    Serial.println(F("Using Elegoo 2.8\" TFT Arduino Shield Pinout"));
#else
    Serial.println(F("Using Elegoo 2.8\" TFT Breakout Board Pinout"));
#endif

    Serial.print("TFT size is "); Serial.print(tft.width()); Serial.print("x"); Serial.println(tft.height());
    
    tft.reset();
    
    uint16_t identifier = 0x9341;

    tft.begin(identifier);

    resetScreen();

    degrees = 0;
}

void standby(void){
    CAN_listen(recvmsg);
    distribute();
}



void send(PROCESS_IDS Pid){
    sntmsg[0] = Pid;
    CAN_transmit(sntmsg);

}

void requestMoveMotor(unsigned char deg){

    sntmsg[7] = deg;
    degrees = deg;
    send(MOTOR_MOVE);
    standby();

}

void requestMeasureRange(){
    send(SENSOR_MEASURE);
    standby();
}

void storerange(unsigned char deg, uint8_t range){
    
    dataPoints[deg].x = range*cos(deg);
    dataPoints[deg].y = range*sin(deg);

}

bool checkOnMap(unsigned char deg){
     
    unsigned char radiuses[5] = {10,60,110,160,210};

    for(int i = 0; i < 4; i++){

        if(radiuses[i] == deg){return true;}

    }

    return false;

}


void RenderMap(void){

    tft.fillCircle(dataPoints[degrees].y,dataPoints[degrees].x,3,BLACK);
    
    if(checkOnMap(degrees)){displayMap();}
    
    storerange(degrees,charToInt(extractRange(recvmsg)));

    tft.fillCircle(dataPoints[degrees].y,dataPoints[degrees].x,3,RED);

}

void resetScreen(void){

    tft.fillScreen(BLACK);
    tft.fillCircle(0, tft.height()/2,10,GREEN);
    tft.drawCircle(0,tft.height()/2,60,GREEN);
    tft.drawCircle(0,tft.height()/2,110,GREEN);
    tft.drawCircle(0,tft.height()/2,160,GREEN);
    tft.drawCircle(0,tft.height()/2,210,GREEN);

}

void displayMap(void){
    
    tft.fillCircle(0, tft.height()/2,10,GREEN);
    tft.drawCircle(0,tft.height()/2,60,GREEN);
    tft.drawCircle(0,tft.height()/2,110,GREEN);
    tft.drawCircle(0,tft.height()/2,160,GREEN);
    tft.drawCircle(0,tft.height()/2,210,GREEN);

}

void distribute(void){
    switch(recvmsg[0]) {
        case MONITOR_RENDERMAP:
            RenderMap();
            break;
        case MONITOR_MOTORFEEDBACK:
            requestMeasureRange();
            break;
        default:
            SERIAL_PORT_MONITOR.println("Keine gültige processid");
        }
}




