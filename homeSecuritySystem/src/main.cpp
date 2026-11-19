#include <Arduino.h>

// Pin Assignments go here
const int basementLED = 0;
const int policeRedLED = 0;
const int policeBlueLED = 0;
const int houseLED = 0;
const int buzzer = 0; 
const int doorSwitch = 0;
const int windowSwitch = 0;
const int dadSwitch = 0;
const int daughterSwitch = 0;
const int systemActiveSwitch = 0;

// put function declarations here:
void basementResponse(){
  // Static Green LED inside basement

}

void policeResponse(){
  // Flashing red & blue LED outside of house
}

void houseIsRobbed(){
  // Static Red LED inside house
}

void alarmTriggered(){
  // Flashing Red LED inside house + Buzzer sound
}

void systemActive(){
  // Static Green LED on
}

void setup() {
  
}

void loop() {
  // put your main code here, to run repeatedly:
}

// put function definitions here:
int myFunction(int x, int y) {
  return x + y;
}