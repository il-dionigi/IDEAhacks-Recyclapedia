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

void writePi(String msg) {
  
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
}

void loop() {
  // put your main code here, to run repeatedly:
  char buttonState[] = {0, 0, 0}; // red, green, blue
  uint8_t stateIncr = 0;

  while (1) {
    for (stateIncr = 0; stateIncr < 3; stateIncr++) {
      char curState = digitalRead(4 - stateIncr);
      if (buttonState[2 - stateIncr] > curState) {
        switch (stateIncr) {
 	  case 0:
	    digitalWrite(LED_R, HIGH);
	    delay(100);
	    digitalWrite(LED_R, HIGH);
  	  case 1:
	    digitalWrite(LED_G, HIGH);
	     delay(100);
	    digitalWrite(LED_G, HIGH);		
	  case 2:
	    digitalWrite(LED_B, HIGH);
	    delay(100);
	    digitalWrite(LED_B, HIGH);
  	  default:
	    break;
        }
      }
    }
  }  
//  digitalWrite(LED_G, HIGH);
//  delay(100);
//  digitalWrite(LED_R, HIGH);
//  delay(100);
//  digitalWrite(LED_B, HIGH);
//  delay(100);

  
  
}
