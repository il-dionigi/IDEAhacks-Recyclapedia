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

short directionIO = -1; // -1 reading, 1 writing

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
  if (directionIO < 0) {
    if (Serial.available()) {
      short input = Serial.read();
      blink(input - '0');
    }
    directionIO *= -1; 
  } else {
    Serial.println(input * 2);
  }
}

void blink(int n) {
  for (int i = 0; i < n; i++) {
    digitalWrite(LED_G, HIGH);
    delay(100);
    digitalWrite(LED_G, LOW);
    delay(100);
  }
}
