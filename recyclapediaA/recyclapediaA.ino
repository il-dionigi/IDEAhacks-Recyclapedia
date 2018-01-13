#include <Adafruit_LEDBackpack.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SPITFT.h>
#include <Adafruit_SPITFT_Macros.h>
#include <gfxfont.h>
#include "Adafruit_LEDBackpack.h"

Adafruit_AlphaNum4 alpha4 = Adafruit_AlphaNum4(); 

//***********************LEDS********************************
#define LED_R 11
#define LED_G 12
#define LED_B 13

//**********************BUTTONS****************************
#define BUTTON_YES 4
#define BUTTON_NO 3
#define BUTTON_UNSURE 2

//*********************CONSTANTS****************************
long debounceDelay = 1500;
long lastDebounceTime = 0;
int count = 0; 

void readPi(int numByte){
  while(Wire.available()){
    
  }
}

void writePi() {
  
}

void buttonPress(int buttonState, char letter){
  if((millis() - lastDebounceTime) > debounceDelay){
    if(buttonState == HIGH){
      Serial.println(letter);
      lastDebounceTime = millis();  
    }
  }
}

void incrementCounter(){
  short valO = 0; // One's place
  short valD = 0; // Ten's place
  short valC = 0; // Hundred's place
  short valK = 0; // Thousand's place
  
  valO++;
  valD += (int)(valO/10);
  valO = valO % 10;
  valC += (int)(valD/10);
  valD = valD % 10;
  valK += (int)(valC/10);
  valC = valC % 10;

  alpha4.writeDigitAscii(0, '0' + valO);
  alpha4.writeDigitAscii(1, '0' + valD);
  alpha4.writeDigitAscii(2, '0' + valC);
  alpha4.writeDigitAscii(3, '0' + valK);
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
int buttonRead(int buttonState[3]){
  int result = 0;
  if(buttonState[0] == HIGH || buttonState[1] == HIGH || buttonState[2] == HIGH){
    result = 1;  
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
}

void loop() {
  // put your main code here, to run repeatedly:
  int buttonState[] = {0, 0, 0}; // green, red, blue
  uint8_t stateIncr = 0;

  buttonState[0] = digitalRead(BUTTON_YES);
  buttonState[1] = digitalRead(BUTTON_NO);
  buttonState[2] = digitalRead(BUTTON_UNSURE);

  buttonPress(buttonState[0], 'G');
  buttonPress(buttonState[1], 'R');
  buttonPress(buttonState[2], 'B');
 
  
}
