#include <Arduino.h>
#include "EC25.h"

  

void setup() {
  // put your setup code here, to run once:
   Serial.begin(9600);
   EC25::LTE forci(&Serial2,&Serial);
  //Serial2.begin(115200, SERIAL_8N1, 16, 17);
  
  pinMode(5, OUTPUT);
  Serial.println("Setup");
  delay(3000);
  
  String text;
  forci.ping("asd");
  delay(1000);
}

void loop() {
  

}