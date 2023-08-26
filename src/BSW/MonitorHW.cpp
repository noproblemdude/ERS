
#include "MonitorHW.h"


static unsigned char recvmsg[8];
static unsigned char sntmsg[8];
static unsigned char degrees = 0;

struct dataPoint
{
    double x;
    double y;
};

static struct dataPoint dataPoints[180];

static Elegoo_TFTLCD tft(LCD_CS, LCD_CD, LCD_WR, LCD_RD, LCD_RESET);


extern void MONITOR_setup(void) {
    Serial.begin(115200);
    Serial.println(F("TFT LCD test"));

#ifdef USE_Elegoo_SHIELD_PINOUT
    Serial.println(F("Using Elegoo 2.8\" TFT Arduino Shield Pinout"));
#else
    Serial.println(F("Using Elegoo 2.8\" TFT Breakout Board Pinout"));
#endif

    Serial.print("TFT size is "); Serial.print(tft.width()); Serial.print("x"); Serial.println(tft.height());
    
    tft.reset();
    
    uint16_t identifier = 0x9341u;

    tft.begin(identifier);

    resetScreen();

    degrees = 0;
}

static void standby(void){
    recvmsg[0] = 0;
    CAN_listen(recvmsg);
    distribute();
}



extern void send(PROCESS_IDS Pid){
    sntmsg[0] = (char)Pid;
    CAN_transmit(sntmsg);
}

extern void requestMoveMotor(unsigned char deg){

    SERIAL_PORT_MONITOR.print("Motorbewegung wird angefragt, pos:");
    SERIAL_PORT_MONITOR.println(deg);

    sntmsg[7] = deg;
    degrees = deg;
    send(MOTOR_MOVE);
    standby();
    
}

static void requestMeasureRange(void){

    SERIAL_PORT_MONITOR.println("messung wird angefragt");
    send(SENSOR_MEASURE);
    standby();
}

static void storerange(unsigned char deg, uint8_t range){
    

    dataPoints[deg].x = range*(cos(degrees * (PI / 180)+PI)) + tft.height()/2;
    dataPoints[deg].y = range*(sin(degrees * (PI / 180)));
    
    Serial.print("das sind die Daten. Deg:");Serial.print(deg);Serial.print(" X :");Serial.print(dataPoints[deg].x);Serial.print(" Y:");Serial.println(dataPoints[deg].y);

}

static  bool checkOnMap(unsigned char deg){

    bool output=false;
     
    unsigned char radiuses[5] = {10,60,110,160,210};

    for(int i = 0; i < 4; i++){

        if(radiuses[i] == deg){output=true;}

    }

    return output;

}


static void RenderMap(void){

    tft.fillCircle(dataPoints[degrees].y,dataPoints[degrees].x,3,BLACK);
    
    if(checkOnMap(degrees)){displayMap();}
    
    storerange(degrees,extractRange(recvmsg));
    Serial.println(extractRange(recvmsg));

    tft.fillCircle(dataPoints[degrees].y,dataPoints[degrees].x,3,RED);

}

static void resetScreen(void){

    tft.fillScreen(BLACK);
    tft.fillCircle(0, tft.height()/2,10,GREEN);
    tft.drawCircle(0,tft.height()/2,60,GREEN);
    tft.drawCircle(0,tft.height()/2,110,GREEN);
    tft.drawCircle(0,tft.height()/2,160,GREEN);
    tft.drawCircle(0,tft.height()/2,210,GREEN);

}

static void displayMap(void){
    
    tft.fillCircle(0, tft.height()/2,10,GREEN);
    tft.drawCircle(0,tft.height()/2,60,GREEN);
    tft.drawCircle(0,tft.height()/2,110,GREEN);
    tft.drawCircle(0,tft.height()/2,160,GREEN);
    tft.drawCircle(0,tft.height()/2,210,GREEN);

}

static void distribute(void){

    SERIAL_PORT_MONITOR.println(recvmsg[0]);
    
    switch((PROCESS_IDS)recvmsg[0]) {
        case MONITOR_RENDERMAP:
            SERIAL_PORT_MONITOR.println("Sensor Nachricht erhalten");
            RenderMap();
            break;
        case MONITOR_MOTORFEEDBACK:
            SERIAL_PORT_MONITOR.println("Motorfeedback erhalten");
            requestMeasureRange();
            break;
        default:
            
            SERIAL_PORT_MONITOR.print("Keine gültige processid: ");
            SERIAL_PORT_MONITOR.println(recvmsg[0]);

           break;
    }
        
}




