#include "EC25.h"
#include <Arduino.h>


namespace EC25
{
    
    LTE::LTE(){
        Serial.begin(9600);
        Serial2.begin(115200, SERIAL_8N1, 16, 17);
    };
    void LTE::test(){

        Serial.println("AT+QGPSCFG");
        Serial.println("AT+QGPS");
        Serial.println("AT+QGPS"); 
        

        Serial.println("AT+CSCS=\"GSM\"");
        Serial.println("AT+CMGS=\"+905535002175\"");
        Serial.println(konum);
        Serial.println("\x1a");

        if (Serial2.available() > 0) {
        // read the incoming byte:
        text = Serial2.readString();
        Serial.println(text);
  }
    };
}