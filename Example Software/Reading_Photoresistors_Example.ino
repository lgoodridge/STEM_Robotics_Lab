/****  Reading the Photoresistors Example  ****/

//Define Photoresistor Pins
#define LEFT_PHOTORESISTOR_PIN A0   //The left light sensor pin
#define RIGHT_PHOTORESISTOR_PIN A1  //The right light sensor pin

//Variables
int leftLight;   //How much light the left sensor sees
int rightLight;  //How much light the right sensor sees

void setup() {
  Serial.begin(9600);
  
  //Remember: We need to set the light sensors as inputs
  pinMode(LEFT_PHOTORESISTOR_PIN, INPUT);
  pinMode(RIGHT_PHOTORESISTOR_PIN, INPUT);
}

void loop() {
  //Read the photoresistors
  leftLight = analogRead(LEFT_PHOTORESISTOR_PIN);
  rightLight = analogRead(RIGHT_PHOTORESISTOR_PIN);
  
  //Report the data
  sendDataToSerialMonitor();
  
  //Wait a little
  delay(500);
}

//Sends the sensor data to the Serial Monitor
void sendDataToSerialMonitor() {
  Serial.print("Left Light: ");
  Serial.print(leftLight);
  Serial.print(" , Right Light: ");
  Serial.println(rightLight);
}
