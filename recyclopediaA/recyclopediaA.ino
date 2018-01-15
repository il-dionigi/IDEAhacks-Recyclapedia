#include <Adafruit_LEDBackpack.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SPITFT.h>
#include <Adafruit_SPITFT_Macros.h>
#include <gfxfont.h>
#include <TimeLib.h>
#include <Servo.h>

Servo myServo;
Adafruit_AlphaNum4 alpha4 = Adafruit_AlphaNum4(); 

//***********************LEDS********************************
#define LED_R 2
#define LED_G 3
#define LED_B 4

//**********************BUTTONS****************************
#define BUTTON_YES 12
#define BUTTON_NO 11
#define BUTTON_UNSURE 10

//*********************CONSTANTS****************************
const short optionNO = 0;
const short optionYES = 1;
const short optionUNSURE = 2;

//*******************MISCELLANIOUS**************
#define displayPin 9
#define pirPin 6

//**********************GLOBALS*****************************
long debounceDelay = 1500;
long lastDebounceTime = 0;
short counterVals[] = {0, 0, 0, 0};
short statusIO = -1; // < 0 means reading, > 0 means writing
short buttonState[] = {0, 0, 0}; // green, red, blue
short input = -1;
short initCount = 0;
time_t curTime = 0;

//*************HELPER FUNCTIONS FOR DISPENSER***************
void openDispenser(){
  myServo.write(90);    
}

void closeDispenser(){
  myServo.write(0);  
}

void buttonPress(int buttonState){
  if((millis() - lastDebounceTime) > debounceDelay){
    if(buttonState == HIGH){
      lastDebounceTime = millis();  
    }
  }
}

void incrementCounter(){
  counterVals[3]++;
  counterVals[2] += (short)(counterVals[3]/10);
  counterVals[3] = counterVals[3] % 10;
  counterVals[1] += (short)(counterVals[2]/10);
  counterVals[2] = counterVals[2] % 10;
  counterVals[0] += (short)(counterVals[1]/10);
  counterVals[1] = counterVals[1] % 10;

  for (short i = 0; i < 4; i++) {
    alpha4.writeDigitAscii(i, '0' + counterVals[i]);
  }
  alpha4.writeDisplay();
}

//Return 1 if read a button, return 0 if no button read
int buttonRead(){
  int result = -1;

  buttonState[0] = digitalRead(BUTTON_NO);
  buttonState[1] = digitalRead(BUTTON_YES);
  buttonState[2] = digitalRead(BUTTON_UNSURE);

  buttonPress(buttonState[0]);
  buttonPress(buttonState[1]);
  buttonPress(buttonState[2]);

  if(buttonState[0] == HIGH) {
    result = 0;  
  } else if (buttonState[1] == HIGH) {
    result = 1;
  } else if (buttonState[2] == HIGH) {
    result = 2;
  }
  
  return result; 
}

bool motionTriggered(){
  bool result = false;
  if(digitalRead(pirPin) == HIGH){
    result = true;  
  }  
  return result; 
}

void setup() {
  // put your setup code here, to run once:
  pinMode(LED_R, OUTPUT);
  pinMode(LED_G, OUTPUT);
  pinMode(LED_B, OUTPUT);

  pinMode(BUTTON_YES, INPUT);
  pinMode(BUTTON_NO, INPUT);
  pinMode(BUTTON_UNSURE, INPUT);

  pinMode(pirPin, INPUT);
  
  Serial.begin(9600);
  myServo.attach(displayPin); 
  myServo.write(0); 
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

  //Initiate the display as 0
  for (short i = 0; i < 4; i++) {
    alpha4.writeDigitAscii(i, '0');
  }
  alpha4.writeDisplay();
}

void loop() {
  short place = 0;
  while (!initCount) {
    if (Serial.available()) {
      counterVals[place] = Serial.read() - '0';
      alpha4.writeDigitAscii(place, counterVals[place] + '0');
      if (++place == 4) {
        initCount = 1;
        alpha4.writeDisplay();
      }
    }
  }
  input = -1;
  if (statusIO < 0) { // reading
    if (Serial.available()) {
      char inChar = Serial.read();
      if (inChar != '\0') { // should be '0', '1', or '2'
        input = inChar - '0';
        processInput();
      }
    }
  } else { // statusIO > 0 -> writing
    if (now() - curTime > 7000) { // 7 seconds passed
      statusIO *= -1;
      blinkLED(2);
    }
    input = buttonRead();
    processInput();    
  }
}

void processInput() {
  if (input != -1) {
    if (statusIO) { // true when writing)
      Serial.println(input);
    }
    
    blinkLED(input);
    if (input == 1) {
      incrementCounter();
      curTime = now();
      while (now() - curTime < 3000) {
        if (motionTriggered()) {
          openDispenser();
          break;
        }
      }
      delay(3000);
      closeDispenser();
      } else if (input == 2) {
      if (!statusIO) { // true when reading
        curTime = now();
      }
      statusIO *= -1;
    }
  }
}

void blinkLED(int n) {
  switch(n) {
    case 0:
      digitalWrite(LED_R, HIGH);
      delay(1000);
      digitalWrite(LED_R, LOW);
      break;
    case 1:
      digitalWrite(LED_G, HIGH);
      delay(1000);
      digitalWrite(LED_G, LOW); 
      break;
    case 2:
      digitalWrite(LED_B, HIGH);
      delay(1000);
      digitalWrite(LED_B, LOW);
      break;
    default:
      break;
  }
}
