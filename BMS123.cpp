#include "Arduino.h"
#include "BMS123.h"

#define SERIAL_SPEED 9600



BMS123::BMS123(int _capacity_mAh)
{
  totalCapacity_mAh = _capacity_mAh;
  
  // TODO: Dummy start at 50% SOC
  capacityLeft_mAs = 1800000;  // = 500mAh
}

// Function to read current from the Hardware. No handeling here
int BMS123::readCurrent_mA(){
  return -1000;
  //return 0;
}


void BMS123::routine(){
  int currentNow_mA;
  int time_now;
  int duration_ms;
  int currentCalculated_mA;
  int flownCapacity_mAms;
  
  // First, read the current and Save the time
  currentNow_mA = readCurrent_mA();
  time_now = millis();
  
  // Calculate the duration till last read
  duration_ms = time_now - lastRoutineTime_ms;
  
  // Save the time for next run
  lastRoutineTime_ms = time_now;
  
  // Average the current till last reading
  currentCalculated_mA = (lastCurrent_mA + currentNow_mA) / 2;
  
  // Update lastCurrent
  lastCurrent_mA = currentNow_mA;
  
  // Calculate the capacity over time
  flownCapacity_mAms = currentCalculated_mA * duration_ms;
  
  // Store the value
  // TODO possible problem if we are going negative!
  capacityLeft_mAs = capacityLeft_mAs + (flownCapacity_mAms / 1000);
}

void BMS123::printStatus(){
  Serial.println("##### BMS-Status #####");
  
  Serial.print("\tCapacity:\t");
  Serial.print(totalCapacity_mAh);
  Serial.print("mAh\n");
  
  Serial.print("Awake for:\t");
  Serial.print(millis() / 1000);
  Serial.print(" seconds\n");
  
  Serial.print("Current:\t");
  Serial.print(lastCurrent_mA);
  Serial.print(" mA\n");
  
  Serial.print("Capacity left:\t");
  Serial.print(getCapacityLeft_mAh());
  Serial.print(" mAh\n");
  
  Serial.print("SOC:\t");
  Serial.print(0);
  Serial.print("%\n");
  
  Serial.println("######################");
  Serial.println("");
}

unsigned int BMS123::getCapacityLeft_mAh(){
  return capacityLeft_mAs / 3600; // s to h
}
