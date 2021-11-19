#include <Arduino.h>
#include "EC25.h"

  EC25::LTE forci;

void setup() {
  // put your setup code here, to run once:
  pinMode(5, OUTPUT);
}

void loop() {
  forci.test();
  delay(1000);

}