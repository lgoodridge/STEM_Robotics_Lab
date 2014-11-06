/****  Double Motor Example  ****/

#define FORWARD HIGH
#define REVERSE LOW

#define START_BUTTON A7  //This pin controls which button will start the program

#define LEFT_MOTOR_DIR_PIN 4     //This pin controls the left motor direction
#define LEFT_MOTOR_POWER_PIN 5   //This pin controls the left motor power
#define RIGHT_MOTOR_DIR_PIN 7    //This pin controls the right motor direction
#define RIGHT_MOTOR_POWER_PIN 6  //This pin controls the right motor power

int leftMotorDirection = FORWARD;   //Controls whether the left motor runs forward or in reverse
int leftMotorPower = 125;           //Controls how fast the left motor runs (from 0 - 255)
int rightMotorDirection = FORWARD;  //Controls whether the right motor runs forward or in reverse
int rightMotorPower = 125;          //Controls how fast the right motor runs (from 0 - 255)

void setup() {
  Serial.begin(9600);
  pinMode(LEFT_MOTOR_DIR_PIN, OUTPUT);
  pinMode(LEFT_MOTOR_POWER_PIN, OUTPUT);
  pinMode(RIGHT_MOTOR_DIR_PIN, OUTPUT);
  pinMode(RIGHT_MOTOR_POWER_PIN, OUTPUT);
  waitUntilButtonIsPressed();
}

void loop() {
  //Run each of the motors
  runLeftMotor(leftMotorDirection, leftMotorPower);
  runRightMotor(rightMotorDirection, rightMotorPower);
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

/* Waits until the start button is pressed
 * to continue */
void waitUntilButtonIsPressed() {
  while (analogRead(START_BUTTON) > 500) {
    delay(100);
  }
}
