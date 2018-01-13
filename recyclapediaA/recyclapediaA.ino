#include <Adafruit_LEDBackpack.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SPITFT.h>
#include <Adafruit_SPITFT_Macros.h>
#include <gfxfont.h>
#include "Adafruit_LEDBackpack.h"
#include <Time.h>

Adafruit_AlphaNum4 alpha4 = Adafruit_AlphaNum4(); 

//***********************LEDS********************************
const int startLED = 11;
#define LED_G 11
#define LED_R 12
#define LED_B 13

//**********************BUTTONS****************************
#define BUTTON_YES 4
#define BUTTON_NO 3
#define BUTTON_UNSURE 2

//*********************CONSTANTS****************************
const short optionNO = 0;
const short optionYES = 1;
const short optionUNSURE = 2;

//**********************GLOBALS*****************************
long debounceDelay = 1500;
long lastDebounceTime = 0;
short valO = 0; // One's place
short valD = 0; // Ten's place
short valC = 0; // Hundred's place
short valK = 0; // Thousand's place
short statusIO = -1; // < 0 means reading, > 0 means writing
short buttonState[] = {0, 0, 0}; // green, red, blue
time_t curTime = 0;

void buttonPress(int buttonState, char letter){
  if((millis() - lastDebounceTime) > debounceDelay){
    if(buttonState == HIGH){
      Serial.println(letter);
      lastDebounceTime = millis();  
    }
  }
}

void incrementCounter(){
  valO++;
  valD += (int)(valO/10);
  valO = valO % 10;
  valC += (int)(valD/10);
  valD = valD % 10;
  valK += (int)(valC/10);
  valC = valC % 10;

  alpha4.writeDigitAscii(3, '0' + valO);
  alpha4.writeDigitAscii(2, '0' + valD);
  alpha4.writeDigitAscii(1, '0' + valC);
  alpha4.writeDigitAscii(0, '0' + valK);
  alpha4.writeDisplay();
}

//1:red, 2:green, 3:blue, 0:powerOff, 1:powerOn
void controlLED(const int LED, const int power){
  if(LED == 1 && power == 0){
    digitalWrite(LED_R, LOW); 
  } else {
    digitalWrite(LED_R, HIGH);
  }
  if(LED == 2 && power == 0){
    digitalWrite(LED_G, LOW);  
  } else {
    digitalWrite(LED_G, HIGH);
  }
  if(LED == 3 && power == 0){
    digitalWrite(LED_B, LOW);  
  } else {
    digitalWrite(LED_B, HIGH);  
  }
}

//Return 1 if read a button, return 0 if no button read
int buttonRead(){
  int result = 2;

  buttonState[0] = digitalRead(BUTTON_YES);
  buttonState[1] = digitalRead(BUTTON_NO);
  buttonState[2] = digitalRead(BUTTON_UNSURE);

  buttonPress(buttonState[0], 'G');
  buttonPress(buttonState[1], 'R');
  buttonPress(buttonState[2], 'B');

  if(buttonState[0] == HIGH) {
    result = 0;  
  } else if (buttonState[1] == HIGH) {
    result = 1;
  } else if (buttonState[2] == HIGH) {
    result = 2;
  }
  return result; 
}

void setup() {
  // put your setup code here, to run once:
  pinMode(LED_G, OUTPUT);
  pinMode(LED_B, OUTPUT);
  pinMode(LED_R, OUTPUT);

  pinMode(BUTTON_YES, INPUT);
  pinMode(BUTTON_NO, INPUT);
  pinMode(BUTTON_UNSURE, INPUT);
  
  Serial.begin(9600);
  alpha4.begin(0x70); //pass in the address for the display

  //Signal that the signal is ready 
  digitalWrite(LED_G, HIGH);
  delay(500);
  digitalWrite(LED_R, HIGH);
  delay(500);
  digitalWrite(LED_B, HIGH);
  delay(500);
  digitalWrite(LED_G, LOW);
  digitalWrite(LED_R, LOW);
  digitalWrite(LED_B, LOW);

  alpha4.writeDigitAscii(0, '0');
  alpha4.writeDigitAscii(1, '0');
  alpha4.writeDigitAscii(2, '0');
  alpha4.writeDigitAscii(3, '0');
  alpha4.writeDisplay();
}

void loop() {
  short input = -1:
  if (statusIO < 0) { // reading
    if (Serial.available()) {
      char inChar = Serial.read();
      if (inChar != '\0') { // should be '0', '1', or '2'
        input = inChar - '0';
        processInput();
      }
    }
  } else { // statusIO > 0 -> writing
    if (now() - curTime > 10000) { // 10 seconds passed
      statusIO *= -1;
      blinkLED(2);
    }
    input = buttonRead();
    processInput();    
  }
}

void processInput() {
  if (input != -1) {
    if (input == 0) {
      incrementCounter();
    } else if (input == 2) {
      if (!statusIO) { // true when reading
        curTime = now();
      }
      statusIO *= -1;
    }
    blinkLED(input);
  }
}

void blinkLED(int n) {
  switch(LED) {
    case 0:
      controlLED(LED_R, HIGH);
      delay(500);
      controlLED(LED_R, LOW);
      break;
    case 1:
      controlLED(LED_G, HIGH);
      delay(500);
      controlLED(LED_G, LOW); 
      break;
    case 2:
      controlLED(LED_B, HIGH);
      delay(500);
      controlLED(LED_B, LOW);
      break;
    default:
      break;
  }
}
