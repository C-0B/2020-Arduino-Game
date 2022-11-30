#include <EEPROM.h>
#include <Wire.h>
#include <Adafruit_RGBLCDShield.h>
#include <utility/Adafruit_MCP23017.h>

Adafruit_RGBLCDShield lcd = Adafruit_RGBLCDShield();

void setup(){
  Serial.begin(9600);
  Serial.println("Hello, World!");
  lcd.begin(16, 2);
  lcd.setCursor(0, 0);


  int a[] = {5, 17, 23, 42, 99, 123};
  int *p = a;
  for (int i=0; i<6; i++) {
      Serial.print(*(p + i));
      Serial.print("  ");
      sprint(p);
  }
}

void loop(){

}
