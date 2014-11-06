/****  Braitenberg Machine Example  ****/

//Define Photoresistor Pins
#define LEFT_PHOTORESISTOR_PIN A0
#define RIGHT_PHOTORESISTOR_PIN A1

//Define LED pins
#define LEFT_LED_PIN 10
#define RIGHT_LED_PIN 11

//Define Motor Pins
#define LEFT_MOTOR_DIR_PIN 4
#define LEFT_MOTOR_POWER_PIN 5
#define RIGHT_MOTOR_DIR_PIN 7
#define RIGHT_MOTOR_POWER_PIN 6

//Define Motor directions
#define FORWARD HIGH
#define REVERSE LOW

//Define start button
#define START_BUTTON A7

//Constants
#define IS_PHOTOPHOBIC false    //Determines whether robot follows or runs away from light
#define LIGHT_SENSITIVITY 50    //How sensitive the robot is to light
#define MOTOR_SENSITIVITY 50    //How much the robot turns in response to light

#define MINIMUM_BASE_MOTOR_POWER 125    //Motor Power when light source is farthest
#define MAXIMUM_BASE_MOTOR_POWER 175    //Motor Power when light source is closest

//Variables
int leftLightValue;     //How much light the left sensor sees
int rightLightValue;    //How much light the right sensor sees
int leftMotorPower;     //Determines power output to the left wheel
int rightMotorPower;    //Determines power output to the right wheel

void setup() {
  //Start communication with Serial Monitor
  Serial.begin(9600);
  
  //Set input pins
  pinMode(LEFT_PHOTORESISTOR_PIN, INPUT);
  pinMode(RIGHT_PHOTORESISTOR_PIN, INPUT);
  
  //Set output pins
  pinMode(LEFT_LED_PIN, OUTPUT);
  pinMode(RIGHT_LED_PIN, OUTPUT);
  pinMode(LEFT_MOTOR_DIR_PIN, OUTPUT);
  pinMode(RIGHT_MOTOR_DIR_PIN, OUTPUT);
  pinMode(LEFT_MOTOR_POWER_PIN, OUTPUT);
  pinMode(RIGHT_MOTOR_POWER_PIN, OUTPUT);
  
  //Set the initial value of variables
  initVars();
  
  //Turn LEDs on
  digitalWrite(LEFT_LED_PIN, HIGH);
  digitalWrite(LEFT_LED_PIN, HIGH);
  
  //Wait until start button is pressed
  waitUntilButtonIsPressed();
}

void loop() {
  //Read Photoresistor Values
  leftLightValue = analogRead(LEFT_PHOTORESISTOR_PIN);
  rightLightValue = analogRead(LEFT_PHOTORESISTOR_PIN);
  
  /* Calculate minimum light for movement using the 
   * light sensitivity constant. */
  int minimumLightForMovement = 400 - map(LIGHT_SENSITIVITY, 0, 100, 0, 400);
  
  /* If the amount of light for both sensors is too low:
   * If its photophobic, stop completely.
   * If its photophilic, swivel and search for light sources. */
  if (leftLightValue < minimumLightForMovement && 
  rightLightValue < minimumLightForMovement) {
    if (IS_PHOTOPHOBIC) {
      //Stop the robot
      runLeftMotor(FORWARD, 0);
      runRightMotor(FORWARD, 0);
    } else {
      //Swivel the robot
      runLeftMotor(FORWARD, 200);
      runRightMotor(REVERSE, 200);
    }
  }
  
  /* Otherwise, there is a notable light 
   * source, and we should go follow it */
  else {
    /* Determine and assign base motor power: More 
     * total light means the robot should move faster */
    int totalLight = leftLightValue + rightLightValue;
    totalLight = min(totalLight, 800);
    int baseMotorPower = map(totalLight, 0, 800, 
    MINIMUM_BASE_MOTOR_POWER, MAXIMUM_BASE_MOTOR_POWER);
    
    /* Caluclate motor difference value using motor sensitivity
     * constant and the difference between the left and right
     * light sensors */
    int difference = leftLightValue - rightLightValue;
    int motorPowerDifference = convertToAnalog(difference) * 
    MOTOR_SENSITIVITY / 50;
    
    //Calculate the final motor powers
    if (IS_PHOTOPHOBIC) {
      leftMotorPower = boundMotorPowers(baseMotorPower + motorPowerDifference);
      rightMotorPower = boundMotorPowers(baseMotorPower - motorPowerDifference);
    } else {
      leftMotorPower = boundMotorPowers(baseMotorPower - motorPowerDifference);
      rightMotorPower = boundMotorPowers(baseMotorPower + motorPowerDifference);
    }
    
    //Write values to the motors
    runLeftMotor(FORWARD, leftMotorPower);
    runRightMotor(FORWARD, rightMotorPower);
    
    //Report values to the Serial Monitor
    sendDataToSerialMonitor();
  }
  
  //Brief delay
  delay(50);
}

//Set the initial value of variables
void initVars() {
  leftLightValue = 0;
  rightLightValue = 0;
  leftMotorPower = 0;
  rightMotorPower = 0;
}

/* Runs the left motor in the direction 
 * given, at the specified power */
void runLeftMotor(int direction, int power){
  digitalWrite(LEFT_MOTOR_DIR_PIN, direction);
  analogWrite(LEFT_MOTOR_POWER_PIN, power);
}

/* Runs the right motor in the direction 
 * given, at the specified power */
void runRightMotor(int direction, int power){
  digitalWrite(RIGHT_MOTOR_DIR_PIN, direction);
  analogWrite(RIGHT_MOTOR_POWER_PIN, power);
}

//Keep Motor Powers within bounds
int boundMotorPowers(int value) {
  return constrain(value, 100, 255);
}

/* Convert the number you get from the sensor
 * (0 - 1023) into an analog value the LED can
 * use (0 - 255) */
int convertToAnalog(int sensorValue) {
  return map(sensorValue, 0, 1023, 0, 255);
}

//Sends out values to the Serial Monitor
void sendDataToSerialMonitor() {
  Serial.print("Left Light: ");
  Serial.print(leftLightValue);
  Serial.print(" , Right Light: ");
  Serial.print(rightLightValue);
  Serial.print(" , Left Motor: ");
  Serial.print(leftMotorPower);
  Serial.print(" , Right Motor: ");
  Serial.println(rightMotorPower);
}

/* Waits until the start button is
 * pressed to continue */
void waitUntilButtonIsPressed() {
  while (analogRead(START_BUTTON) > 500) {
    delay(100);
  }
}
