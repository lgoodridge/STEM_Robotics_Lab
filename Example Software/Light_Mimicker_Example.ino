/****  Light Mimicker Example  ****/

//Define Photoresistor Pins
#define LEFT_PHOTORESISTOR_PIN A0
#define RIGHT_PHOTORESISTOR_PIN A1

//Define LED pins
#define LEFT_LED_PIN 10
#define RIGHT_LED_PIN 11

//Variables
int leftLight;
int rightLight;
int leftLightAnalog;
int rightLightAnalog;

void setup() {
  Serial.begin(9600);
  
  //Set light sensor pins as inputs
  pinMode(LEFT_PHOTORESISTOR_PIN, INPUT);
  pinMode(RIGHT_PHOTORESISTOR_PIN, INPUT);
  
  //Set LED pins as outputs
  pinMode(LEFT_LED_PIN, OUTPUT);
  pinMode(RIGHT_LED_PIN, OUTPUT);
}

void loop() {
  //Read the photoresistors
  leftLight = analogRead(LEFT_PHOTORESISTOR_PIN);
  rightLight = analogRead(RIGHT_PHOTORESISTOR_PIN);
  
  //Convert sensor values to analog values
  leftLightAnalog = convertToAnalog(leftLight);
  rightLightAnalog = convertToAnalog(rightLight);
  
  //Output to LEDs
  analogWrite(LEFT_LED_PIN, leftLightAnalog);
  analogWrite(RIGHT_LED_PIN, rightLightAnalog);
}

/* Convert the number you get from the sensor
 * (0 - 1023) into an analog value the LED can
 * use (0 - 255) */
int convertToAnalog(int sensorValue) {
  return map(sensorValue, 0, 1023, 0, 255);
}
