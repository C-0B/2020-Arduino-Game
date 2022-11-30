 // 2.3

#include <Wire.h>
#include <Adafruit_RGBLCDShield.h>
#include <utility/Adafruit_MCP23017.h>

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

#define UP 0
#define DOWN 1
#define LEFT 2
#define RIGHT 3
#define SELECT 4

#define RED 0x1
#define GREEN 0x2
#define YELLOW 0x3
#define BLUE 0x4
#define VIOLET 0x5
#define TEAL 0x6
#define WHITE 0x7


Adafruit_RGBLCDShield lcd = Adafruit_RGBLCDShield();

void setup() {
  Serial.begin(9600);
  Serial.println("Hello, World!");
  lcd.begin(16, 2);
  lcd.setCursor(0, 1);
  lcd.setBacklight(WHITE);
  lcd.print("Hello world ");
}

  



void loop() {
  byte up[8] = {
  0b00100,
  0b01110,
  0b11111,
  0b00100,
  0b00100,
  0b00100,
  0b00100,
  0b00100
  };
  byte down[8] = {
    0b00100,
    0b00100,
    0b00100,
    0b00100,
    0b00100,
    0b11111,
    0b01110,
    0b00100
  };
  byte right[8] = {
    0b00000,
    0b00000,
    0b00100,
    0b00110,
    0b11111,
    0b00110,
    0b00100,
    0b00000
  };
  byte left[8] = {
    0b00000,
    0b00000,
    0b00100,
    0b01100,
    0b11111,
    0b01100,
    0b00100,
    0b00000 
  };
  byte select [8] = {
    0b00101,
    0b01010,
    0b10100,
    0b01000,
    0b10100,
    0b01010,
    0b00101,
    0b00010
  };
  lcd.createChar(UP, up);
  lcd.createChar(DOWN, down);
  lcd.createChar(RIGHT, right);
  lcd.createChar(LEFT, left);
  lcd.createChar(SELECT, select);

  int button_state = lcd.readButtons();
  
  lcd.setCursor(0, 0);
  if (button_state & BUTTON_SELECT);
  else{
    lcd.print("                ");
    lcd.setCursor(0, 0);
    lcd.print(millis(), DEC);
    Serial.println(millis(), DEC);
  }
  
  lcd.setCursor(0, 1);
  if (button_state & BUTTON_SELECT){
    lcd.write(SELECT);  
  }
  if (button_state & BUTTON_RIGHT){
    lcd.write(RIGHT);  
  }
  if (button_state & BUTTON_DOWN){
    lcd.write(DOWN);  
  }
  if (button_state & BUTTON_UP){
    lcd.write(UP); 
  }
  if (button_state & BUTTON_LEFT){
    lcd.write(LEFT); 
  }
  if (button_state == BUTTON_NONE){
    lcd.print("                ");  
  }
}
/*
1-
2-   
3-
  lastByte = incomingByte;
  incomingByte = Serial.read();
  if (incomingByte != 10 && incomingByte != -1){ 

    if(incomingByte > 0){
      readByte(incomingByte);
    }
  }

    if (incomingByte == 84){
      Serial.println(incomingByte);
      incomingByte = Serial.read();
      Serial.println(incomingByte);
      if (incomingByte == 58){
        Serial.println(incomingByte);
      }        
    }

    
    if (lastByte == 84 && incomingByte == 58){
      incomingByte = Serial.read();
    }


4-
    lcd.scrollDisplayLeft();
    delay(400);

5-
   int button_state = lcd.readButtons();
   if (button_state & BUTTON_SELECT){
    ;  
  }
  else{
    lcd.clear();
    lcd.println(millis(), DEC);
  }
  
  delay(500);

6-
  lcd.setCursor(0, 1);
  int button_state = lcd.readButtons();
  if (button_state & BUTTON_SELECT){
    lcd.print("SELECT");  
  }
  if (button_state & BUTTON_RIGHT){
    lcd.print("RIGHT");  
  }
  if (button_state & BUTTON_DOWN){
    lcd.print("DOWN");  
  }
  if (button_state & BUTTON_UP){
    lcd.print("UP"); 
  }
  if (button_state & BUTTON_LEFT){
    lcd.print("LEFT"); 
  }
  if (button_state == BUTTON_NONE){
    lcd.clear();  
  }

7-

  
  int button_state = lcd.readButtons();
  
  lcd.setCursor(0, 0);
  if (button_state & BUTTON_SELECT);
  else{
    lcd.print("                ");
    lcd.setCursor(0, 0);
    lcd.print(millis(), DEC);
    Serial.println(millis(), DEC);
  }
  
  lcd.setCursor(0, 1);
  if (button_state & BUTTON_SELECT){
    lcd.print("SELECT");  
  }
  if (button_state & BUTTON_RIGHT){
    lcd.print("RIGHT");  
  }
  if (button_state & BUTTON_DOWN){
    lcd.print("DOWN");  
  }
  if (button_state & BUTTON_UP){
    lcd.print("UP"); 
  }
  if (button_state & BUTTON_LEFT){
    lcd.print("LEFT"); 
  }
  if (button_state == BUTTON_NONE){
    lcd.print("                ");  
  }

8-
  int button_state = lcd.readButtons();
  
  if (button_state & BUTTON_SELECT){
    lcd.setBacklight(VIOLET); 
  }
  if (button_state & BUTTON_RIGHT){
    lcd.setBacklight(BLUE);
  }
  if (button_state & BUTTON_DOWN){
    lcd.setBacklight(TEAL);
  }
  if (button_state & BUTTON_UP){
    lcd.setBacklight(GREEN);
  }
  if (button_state & BUTTON_LEFT){
    lcd.setBacklight(YELLOW);
  }

9-

    byte up[8] = {
  0b00100,
  0b01110,
  0b11111,
  0b00100,
  0b00100,
  0b00100,
  0b00100,
  0b00100
  };
  byte down[8] = {
    0b00100,
    0b00100,
    0b00100,
    0b00100,
    0b00100,
    0b11111,
    0b01110,
    0b00100
  };
  byte right[8] = {
    0b00000,
    0b00000,
    0b00100,
    0b00110,
    0b11111,
    0b00110,
    0b00100,
    0b00000
  };
  byte left[8] = {
    0b00000,
    0b00000,
    0b00100,
    0b01100,
    0b11111,
    0b01100,
    0b00100,
    0b00000 
  };
  byte select [8] = {
    0b00101,
    0b01010,
    0b10100,
    0b01000,
    0b10100,
    0b01010,
    0b00101,
    0b00010
  };
  lcd.createChar(UP, up);
  lcd.createChar(DOWN, down);
  lcd.createChar(RIGHT, right);
  lcd.createChar(LEFT, left);
  lcd.createChar(SELECT, select);

  int button_state = lcd.readButtons();
  
  lcd.setCursor(0, 0);
  if (button_state & BUTTON_SELECT);
  else{
    lcd.print("                ");
    lcd.setCursor(0, 0);
    lcd.print(millis(), DEC);
    Serial.println(millis(), DEC);
  }
  
  lcd.setCursor(0, 1);
  if (button_state & BUTTON_SELECT){
    lcd.write(SELECT);  
  }
  if (button_state & BUTTON_RIGHT){
    lcd.write(RIGHT);  
  }
  if (button_state & BUTTON_DOWN){
    lcd.write(DOWN);  
  }
  if (button_state & BUTTON_UP){
    lcd.write(UP); 
  }
  if (button_state & BUTTON_LEFT){
    lcd.write(LEFT); 
  }
  if (button_state == BUTTON_NONE){
    lcd.print("                ");  
  }

*/
