

#include "BMS123.h"
#include "TimerOne.h"

BMS123 BMS(1000);

void setup(){
  Timer1.initialize(100 * 1000);  // Setup for 100ms
  Timer1.attachInterrupt(routine);
  
  Serial.begin(9600);
}

void loop(){
  delay(2000);
  BMS.printStatus();
}

void routine(){
  BMS.routine();
}
