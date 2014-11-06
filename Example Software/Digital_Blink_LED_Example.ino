/****  Digital Blink LED Example  ****/

#define LED_PIN 10       //Which pin the LED is plugged into
#define BLINK_TIME 1000  //How long each "blink" takes (in milliseconds)

//Readies the board and software
void setup() {
  Serial.begin(9600);        //Prepare Board to receive data
  pinMode(LED_PIN, OUTPUT);  //Prepare the pin to send output values
}

//This loops continuously
void loop() {
  blinkLED(LED_PIN, BLINK_TIME);  //Blink LED
}

//"Blinks" the LED
void blinkLED(int pin, int blinkTime) {
  digitalWrite(pin, HIGH);  //Turn LED on
  delay(blinkTime / 2);     //Wait (leave on for half of the total blink time)
  digitalWrite(pin, LOW);   //Turn LED off
  delay(blinkTime / 2);     //Wait (leave off for half of the blink time)
}
