/*
  Morse.h - Library for flashing Morse code.
  Created by David A. Mellis, November 2, 2007.
  Released into the public domain.
*/
#ifndef BMS123_h
#define BMS123_h

#include "Arduino.h"

class BMS123{
  public:
    BMS123(int _capacity_mAh);
    void routine();
    void printStatus();
    unsigned int getCapacityLeft_mAh();
    
  private:
    int readCurrent_mA();
    unsigned int totalCapacity_mAh;
    unsigned long capacityLeft_mAs;
    
    int lastRoutineTime_ms;
    int lastCurrent_mA;
};

#endif
