// 4
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

#define BUTTON_UPDOWN 0b0001100


#define RED 0x1
#define GREEN 0x2
#define YELLOW 0x3
#define BLUE 0x4
#define VIOLET 0x5
#define TEAL 0x6
#define WHITE 0x7

int setTime = 0;
void setup() {
  Serial.begin(9600);
  Serial.println("Hello, World!");
  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  lcd.setBacklight(0b000000110);
  
  lcd.print("Hello World");
  
  uint8_t BUTTONS = lcd.readButtons();
  
}

void loop() {
  if (checkLeft()){
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Secret Code");
    lcd.setCursor(0, 1);
    lcd.print("Completed");

    int colour = 0;
    while(true){
      uint8_t BUTTONS = lcd.readButtons();
      if(BUTTONS & BUTTON_UP){
        while(true){  
          BUTTONS = lcd.readButtons();
          if( (BUTTONS & BUTTON_UP) == 0){
            colour++;
            lcd.setBacklight(colour % 7);
            break;  
          }
        }
      }
      if(BUTTONS & BUTTON_DOWN){
        while(true){  
          BUTTONS = lcd.readButtons();
          if( (BUTTONS & BUTTON_DOWN) == 0){
            colour--;
            if(colour < 0){
              int temp = 7 - colour;
            }
            int temp = colour;
            lcd.setBacklight(temp & 7);
            break;  
          }
        }
      }
    }    
  }
}
  




bool checkUpDown(unsigned int setTime){
  while(millis() < setTime){ 
    uint8_t BUTTONS = lcd.readButtons();
    if ((BUTTONS & BUTTON_UPDOWN) == 12){
      Serial.println("Up Down Pressed");
      while(true){
        BUTTONS = lcd.readButtons();
        if( (BUTTONS & BUTTON_UPDOWN) == 0){
          Serial.println("Up Down Released");
          return true;     
        }
      }
    }
  }
  return false;
}

bool checkRight(unsigned int setTime){
  while(millis() < setTime){
    uint8_t BUTTONS = lcd.readButtons();
    if (BUTTONS & BUTTON_RIGHT){
      Serial.println("Right Pressed");
      while(true){
        BUTTONS = lcd.readButtons();
        if((BUTTONS & BUTTON_RIGHT) == 0){
          Serial.println("Right Released");
          if (checkUpDown(millis() + 1000)){return true;}
          return false;        
        }
      }
    }
  }
  return false;
}
bool checkLeft(){
  while(true){
    uint8_t BUTTONS = lcd.readButtons();
    if (BUTTONS & BUTTON_LEFT){
      Serial.println("Left Pressed");
      while(true){
        BUTTONS = lcd.readButtons();
        if((BUTTONS & BUTTON_LEFT) == 0){
          Serial.println("Left Released");
          if (checkRight(millis() + 1000)){return true;}
          return false;    
        }
      }
    }
  }

}
