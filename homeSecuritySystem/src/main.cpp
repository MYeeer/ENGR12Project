#include <Arduino.h>

// Inputs from the logic circuit
const int basement = 0;          // Family in basement
const int basementFailed = 1;    // Family not in basement
const int robberyDetected = 2;   // Robbery detected and cops called
const int robberySuccessful = 3; // House is robbed
const int houseIsSafe = 4;       // All clear

// Outputs
const int houseLEDGreen = 5;
const int houseLEDBlue = 6;
const int houseLEDRed = 7;
const int basementLEDGreen = 8;
const int basementLEDRed = 9;
const int policeRedLED = 10;
const int policeBlueLED = 11;
const int buzzer = 12;

enum HouseState{HOUSE_OFF, HOUSE_ALARM, HOUSE_ROBBED, HOUSE_SAFE};

HouseState houseState = HOUSE_OFF;
HouseState lastHouseState = HOUSE_OFF;

unsigned long lastPoliceToggle = 0;
bool policeToggle = false;

unsigned long lastAlarmToggle = 0;
bool alarmToggle = false;

void basementGreenResponse();
void basementRedResponse();
void policeResponse();
void alarmTriggered();
void houseIsRobbed();
void allClear();
void basementOff();
void policeOff();
void houseOff();
void buzzerOff();

void setup(){
  // IC Chip Setup
  pinMode(basement, INPUT);
  pinMode(basementFailed, INPUT);
  pinMode(robberyDetected, INPUT);
  pinMode(robberySuccessful, INPUT);
  pinMode(houseIsSafe, INPUT);

  // Other Elements
  pinMode(houseLEDGreen, OUTPUT);
  pinMode(houseLEDBlue, OUTPUT);
  pinMode(houseLEDRed, OUTPUT);
  pinMode(basementLEDGreen, OUTPUT);
  pinMode(basementLEDRed, OUTPUT);
  pinMode(policeRedLED, OUTPUT);
  pinMode(policeBlueLED, OUTPUT);
  pinMode(buzzer, OUTPUT);

  basementOff();
  policeOff();
  houseOff();
}

void loop(){
  // Basement group (one color at a time)
  if (digitalRead(basementFailed) == HIGH){
    basementRedResponse();
  }
  else if (digitalRead(basement) == HIGH){
    basementGreenResponse();
  }
  else{
    basementOff();
  }

  // Police group
  if (digitalRead(robberyDetected) == HIGH){
    policeResponse();
  }
  else{
    policeOff();
  }

  // House group (one state at a time)
  if (digitalRead(robberyDetected) == HIGH){
    houseState = HOUSE_ALARM;
  }
  else if (digitalRead(robberySuccessful) == HIGH){
    houseState = HOUSE_ROBBED;
  }
  else if (digitalRead(houseIsSafe) == HIGH){
    houseState = HOUSE_SAFE;
  }
  else{
    houseState = HOUSE_OFF;
  }

  // Clear the house LEDs and buzzer whenever the state changes
  if (houseState != lastHouseState){
    houseOff();
    alarmToggle = false;
    lastAlarmToggle = millis();
    lastHouseState = houseState;
  }

  // Buzzer is only allowed to run during the alarm state
  if (houseState != HOUSE_ALARM){
    buzzerOff();
  }

  switch (houseState){
    case HOUSE_ALARM:
      alarmTriggered();
      break;
    case HOUSE_ROBBED:
      houseIsRobbed();
      break;
    case HOUSE_SAFE:
      allClear();
      break;
    case HOUSE_OFF:
      break;
  }
}

void basementGreenResponse(){
  digitalWrite(basementLEDRed, LOW);
  digitalWrite(basementLEDGreen, HIGH);
}

void basementRedResponse(){
  digitalWrite(basementLEDGreen, LOW);
  digitalWrite(basementLEDRed, HIGH);
}

void policeResponse(){
  unsigned long now = millis();

  // Alternate red/blue every 1250 ms
  if (now - lastPoliceToggle >= 1250){
    lastPoliceToggle = now;
    policeToggle = !policeToggle;
  }

  if (policeToggle){
    digitalWrite(policeRedLED, HIGH);
    digitalWrite(policeBlueLED, LOW);
  }
  else{
    digitalWrite(policeRedLED, LOW);
    digitalWrite(policeBlueLED, HIGH);
  }
}

void alarmTriggered(){
  unsigned long now = millis();

  digitalWrite(buzzer, HIGH);

  // Flash the house red LED every 1000 ms
  if (now - lastAlarmToggle >= 1000){
    lastAlarmToggle = now;
    alarmToggle = !alarmToggle;
  }

  if (alarmToggle){
    digitalWrite(houseLEDRed, HIGH);
  }
  else{
    digitalWrite(houseLEDRed, LOW);
  }
}

void houseIsRobbed(){
  digitalWrite(houseLEDRed, HIGH);
}

void allClear(){
  digitalWrite(houseLEDGreen, HIGH);
}

void basementOff(){
  digitalWrite(basementLEDGreen, LOW);
  digitalWrite(basementLEDRed, LOW);
}

void policeOff(){
  digitalWrite(policeRedLED, LOW);
  digitalWrite(policeBlueLED, LOW);
  policeToggle = false;
  lastPoliceToggle = millis();
}

void buzzerOff(){
  digitalWrite(buzzer, LOW);
}

void houseOff(){
  digitalWrite(houseLEDGreen, LOW);
  digitalWrite(houseLEDBlue, LOW);
  digitalWrite(houseLEDRed, LOW);
  buzzerOff();
}