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
}



int count = 0, incomingByte;
char current[]= {};

void loop(){
  incomingByte = Serial.read();
  if (incomingByte != 10 && incomingByte != -1){
    count++;  
    Serial.println(char(incomingByte));
    char n[] = {'a','b','c', 'd'};
    printArray(n);
    
  }
}
void printArray(char ar[]){
  int len = sizeof(ar) / sizeof(char);
  for(int i = 0; i<len; i++){
    Serial.print(ar[i]);
    Serial.print(", ");
  }
  Serial.println();
}



/*
3-



  bool val = false;
  if(value == 255)val = true;
  

  Serial.print(a);
  Serial.print("\t");
  Serial.print(val);
  Serial.print("\t");
  Serial.print(value);
  Serial.println();

  a++;

  if (a == 101){
    a = 0;

  }
  delay(50);
}





1- 
long sum(int n){
  long result;
  if (n == 0) result = 0;
  else result = n + sum(n-1);
  return result;
}

void loop() {
  // Max Value 
  Serial.println(sum(32767));
  delay(500);
}


2- 

// #pragma GCC push_options
// #pragma GCC optimize ("O0")
long sum(int n)
{
  Serial.println(n);
  long result;
  if (n == 0) result = 0;
  else result = n + sum(n-1);
  Serial.println(result);
  delay(1000);
  return result;
}
// #pragma GCC pop_options

void loop() {
  // Max Value 
  sum(125);
}
 */
