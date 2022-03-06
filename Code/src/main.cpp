#include <Arduino.h>
#include "EC25.h"

void setup() {
   Serial.begin(9600);
   EC25::LTE EC25Dev(&Serial2,&Serial);
  //Serial2.begin(115200, SERIAL_8N1, 16, 17);
  
  pinMode(5, OUTPUT);
  Serial.println("Setup");
  delay(3000);
  
  String text;
  //EC25Dev.ping("asd");
  delay(1000);
  String addr = "ornekapiadresi.com"; //Verinin gönderileceği adres
  String data = "{ \"asd\" : \"asd\"}"; //Gönderilecek veri
  String path = "/in.json"; //Gönderilecek yol
  
  //Serial.println(*EC25Dev.buildPatchRequest(&addr,&data,&path));

  EC25Dev.sendHttpsReq(addr+path,&data);
}

void loop() {
  

}
