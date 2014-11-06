/****  Single Motor Example  ****/

#define FORWARD HIGH  //Tells motors to go forward
#define REVERSE LOW   //Tells motors to go in reverse

#define START_BUTTON A7  //This pin controls which button will start the program

#define MOTOR_DIRECTION_PIN 4  //This pin controls the motor direction
#define MOTOR_POWER_PIN 5      //This pin controls the motor power

int motorDirection = FORWARD;  //Controls whether the motor runs forward or in reverse
int motorPower = 125;          //Controls how fast the motor runs (from 0 - 255)

void setup() {
  Serial.begin(9600);
  pinMode(MOTOR_DIRECTION_PIN, OUTPUT);
  pinMode(MOTOR_POWER_PIN, OUTPUT);
  waitUntilButtonIsPressed();
}

void loop() {
  runMotor(motorDirection, motorPower);
}

/* Runs the motor in the direction given,
 * at the specified power */
void runMotor(int direction, int power) {
  digitalWrite(MOTOR_DIRECTION_PIN, direction);
  analogWrite(MOTOR_POWER_PIN, power);
}

/* Waits until the start button is pressed
 * to continue */
void waitUntilButtonIsPressed() {
  while (analogRead(START_BUTTON) > 500) {
    delay(100);
  }
}
