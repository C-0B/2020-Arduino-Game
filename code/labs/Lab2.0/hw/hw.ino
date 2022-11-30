#include <Wire.h>
#include <Adafruit_RGBLCDShield.h>
#include <utility/Adafruit_MCP23017.h>
#include <math.h>
Adafruit_RGBLCDShield lcd = Adafruit_RGBLCDShield();

// Select = 1
// Right = 2
// Down = 4
// Up = 8
// Left = 16

#define BUTTON_NONE 0b00000000
#define BUTTON_SELECT 0b00000001
#define BUTTON_RIGHT 0b00000010
#define BUTTON_DOWN 0b00000100
#define BUTTON_UP 0b00001000
#define BUTTON_LEFT 0b00010000

int hours = 00;
int mins = 00;

void setup() {
  Serial.begin(9600);
  Serial.println("Hello, World!");
  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  lcd.print("00:00");
  lcd.setCursor(0, 1);
  lcd.setBacklight(0b000000110);
}


int nextHour(){
  if (hours < 0){
    int temp = hours % -24;
    temp = sqrt(temp * temp);
    if (temp == 0){
      return 0;
    }
    return 24 - temp;
  }
    hours = hours % 24;
    return hours;
}

int nextMin(){
  if (mins < 0){
    int temp = mins % -60;
    temp = sqrt(temp * temp);
    if (temp == 0){return 0;}
    return 60 - temp;
    }
  mins = mins % 60;
  return mins;  
}
bool select = true;

void printTime(){
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print(nextHour());
  lcd.print(":");
  lcd.print(nextMin());
  lcd.setCursor(0, 1);
  if (select){lcd.print("Changing Hours");}
  else{lcd.print("Changing Minutes");}
}

// True = hours
// False = mins

void loop() {
  uint8_t buttons = lcd.readButtons();
  if (buttons){
    if (buttons & BUTTON_LEFT) {select = true;}
    if (buttons & BUTTON_RIGHT) {select = false;}
    if (select){
      lcd.print("Changing Hours");
      if (buttons & BUTTON_UP) {hours++;} 
      if (buttons & BUTTON_DOWN) {hours--;}
    }
    else{
      if (buttons & BUTTON_UP) {mins++;} 
      if (buttons & BUTTON_DOWN) {mins--;}
    }
    if(buttons & BUTTON_SELECT){
      Serial.print(nextHour());
      Serial.print(":");
      Serial.println(nextMin());
    }
    printTime();
  }
}
