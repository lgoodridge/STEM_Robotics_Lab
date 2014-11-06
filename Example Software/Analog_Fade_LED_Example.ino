/****  Analog Fade LED Example  ****/

#define LED_PIN 10      //Which pin the LED is plugged into
#define FADE_TIME 5000  //How long each fade takes (in milliseconds)

int brightness;     //The current brightness of the LED
int fadeDirection;  //Determines whether the LED is getting brighter or darker

//Readies the board and software
void setup() {
  Serial.begin(9600);        //Prepare Board to receive data
  pinMode(LED_PIN, OUTPUT);  //Prepare the pin to send values
  brightness = 0;            //Set initial brightness to 0 (off)
  fadeDirection = 1;         //Set initial fade direction to +1 (getting brighter)
}

//This loops continuously
void loop() {
  fadeLED(LED_PIN, FADE_TIME);  //Fade LED
}

//"Fades" the LED
void fadeLED(int pin, int fadeTime) {
  brightness += fadeDirection;                //Increase or decrease brightness, according to fade direction
  if (brightness >= 255) fadeDirection = -1;  //If we've reached the max brightness (255) start getting darker
  if (brightness <= 0) fadeDirection = 1;     //If we've reached the minimum brightness (0, a.k.a off) start getting brighter
  analogWrite(pin, brightness);               //Set the LED at the new brightness
  delay(fadeTime / 255 / 2);                  //Wait
}
