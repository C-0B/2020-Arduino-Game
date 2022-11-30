#include <EEPROM.h>
#include <Wire.h>
#include <Adafruit_RGBLCDShield.h>
#include <utility/Adafruit_MCP23017.h>
Adafruit_RGBLCDShield lcd = Adafruit_RGBLCDShield();

#define BUTTON_NONE 0b00000000
#define BUTTON_SELECT 0b00000001
#define BUTTON_RIGHT 0b00000010
#define BUTTON_DOWN 0b00000100
#define BUTTON_UP 0b00001000
#define BUTTON_LEFT 0b00010000

#define UP_ARROW 0
#define DOWN_ARROW 1
#define LEFT_ARROW 2
#define RIGHT_ARROW 3


void setup() {
  Serial.begin(9600);
  Serial.println("Hello, World!");
  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  lcd.print("Memory Game");
//  lcd.setCursor(0, 1);  
//  lcd.print("Press any button");
}
int buttonPress = lcd.readButtons();
void loop() {
  buttonPress = lcd.readButtons();
  upPressRelease();

}


void upPressRelease(){
  while(buttonPress & BUTTON_UP){
    // wait for button to be released
    buttonPress = lcd.readButtons();
    Serial.println("UP pressed");
  }
  Serial.println("UP released");
}
// Function to loop while the DOWN button is held
void downPressRelease(){
  while(buttonPress & BUTTON_DOWN){
    // wait for button to be released
    buttonPress = lcd.readButtons();
    Serial.println("DOWN pressed");
    }
    Serial.println("DOWN released");
}
// Function to loop while the LEFT button is held
void leftPressRelease(){
  while(buttonPress & BUTTON_LEFT){
    // wait for button to be released
    buttonPress = lcd.readButtons();
    Serial.println("LEFT pressed");
  }
  Serial.println("LEFT released");
}
// Function to loop while the RIGHT button is held
void rightPressRelease(){
  while(buttonPress & BUTTON_RIGHT){
    // wait for button to be released
    buttonPress = lcd.readButtons();
    Serial.println("RIGHT pressed");
  }
  Serial.println("RIGHT released");
}
