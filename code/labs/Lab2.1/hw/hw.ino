// Header Files 
// 2.1
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


int i = 0;
int incomingByte = 0;
int TvB = 0;

void readByte(){
  lcd.setCursor((i % 16), TvB);
  lcd.print(char(incomingByte));
  Serial.print(i++);
  Serial.print(" - I received: ");
  Serial.print(char(incomingByte));
  Serial.println(incomingByte, DEC);
  delay(500);
}

void loop() {
  incomingByte = Serial.read();
  if (incomingByte != 10 && incomingByte != -1){    
    if (char(incomingByte) == 'T'){
      Serial.println("First Conditional");
      readByte();
      incomingByte = Serial.read();
      readByte();
      if(incomingByte == 58){
        Serial.println("SecondConditional");
        incomingByte = Serial.read();
        readByte();
        TvB = 0;
      }
    }else if (char(incomingByte) == 'B'){
      Serial.println("bottom 1");
      readByte();
      incomingByte = Serial.read();
      readByte();
      if(incomingByte == 58){
        Serial.println("bottom 2");
        incomingByte = Serial.read();
        readByte();
        TvB = 1;
      }
    }
    else if(incomingByte != 10){
      readByte();
    }
  }
}
