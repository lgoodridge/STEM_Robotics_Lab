/****  HEAD  ****/

#include <LiquidCrystal.h>

#define SENSOR_PIN 3
#define LED_PIN 5

#define DELAY_TIME 200

int sensorValue;

/****  BODY  ****/

void setup() {
  Serial.begin(9600);
  
  pinMode(SENSOR_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);
  
  sensorValue = 0;
}

void loop() {
  sensorValue = readSensorPin();
  
  if (sensorValue == HIGH) {
    turnLightOn();
  } else {
    turnLightOff();
  }
  
  delay(DELAY_TIME);
}

/****  DEFINED METHODS  ****/

void turnLightOn() {
  digitalWrite(LED_PIN, HIGH);
}
void turnLightOff() {
  digitalWrite(LED_PIN, LOW);
}

int readSensorPin() {
  return analogRead(SENSOR_PIN);
}
