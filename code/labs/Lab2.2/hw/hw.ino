// Header Files 
// 2.2
#include <Wire.h>
#include <Adafruit_RGBLCDShield.h>
#include <utility/Adafruit_MCP23017.h>
Adafruit_RGBLCDShield lcd = Adafruit_RGBLCDShield();

#define BUTTON_UP 0x08
#define BUTTON_DOWN 0x04
#define BUTTON_LEFT 0x02
#define BUTTON_RIGHT 0x01

// int button_state;
// Select = 1
// Right = 2
// Down = 4
// Up = 8
// Left = 16 

void setup() {
  Serial.begin(9600);
  Serial.println("Hello, World!");
  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  lcd.print("text");
  lcd.setBacklight(0b000000110);
}


int tCount = 0;
int bCount = 0;
int incomingByte = 0;
int TvB = 0;

void readByte(){
  if (TvB == 0){
    lcd.setCursor((tCount++ % 16), TvB);
  }else if (TvB == 1){
    lcd.setCursor((bCount++ % 16), TvB);
  }
  lcd.print(char(incomingByte));
  Serial.print(" - I received: ");
  Serial.print(char(incomingByte));
  Serial.println(incomingByte, DEC);
  delay(500);
}

void loop() {
  incomingByte = Serial.read();

  // handling top and bottom lines
  if (incomingByte != 10 && incomingByte != -1){  
    
    // top  
    if (char(incomingByte) == 'T'){
      Serial.println("First Conditional");

      incomingByte = Serial.read();

      if(incomingByte == 58){
        Serial.println("SecondConditional");
        incomingByte = Serial.read();
        TvB = 0;
      }

    } // bottom
    else if (char(incomingByte) == 'B'){
      Serial.println("bottom 1");
      Serial.print(char(incomingByte));
      incomingByte = Serial.read();
      Serial.print("now");
      Serial.print(incomingByte);
      readByte();
      if(incomingByte == 58){
        Serial.println("bottom 2");
        incomingByte = Serial.read();
        TvB = 1;
      }
    }
    
    
    // read all other characters
    else if(incomingByte != 10){
      readByte();
    }
  }
}
