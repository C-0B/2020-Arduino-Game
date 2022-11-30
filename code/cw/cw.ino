#include <EEPROM.h>
#include <Wire.h>
#include <Adafruit_RGBLCDShield.h>
#include <utility/Adafruit_MCP23017.h>
Adafruit_RGBLCDShield lcd = Adafruit_RGBLCDShield();

// Arrow Characters
byte upArrow[] = {
    B00100,
    B01110,
    B11111,
    B00100,
    B00100,
    B00100,
    B00100,
    B00100
};
byte downArrow[] = {
    B00100,
    B00100,
    B00100,
    B00100,
    B00100,
    B11111,
    B01110,
    B00100
};
byte rightArrow[] = {
    B00000,
    B00100,
    B00110,
    B11111,
    B00110,
    B00100,
    B00000,
    B00000
};
byte leftArrow[] = {
    B00000,
    B00100,
    B01100,
    B11111,
    B01100,
    B00100,
    B00000,
    B00000
};
#define RED 0x1
#define GREEN 0x2
#define YELLOW 0x3
#define BLUE 0x4
#define VIOLET 0x5
#define TEAL 0x6
#define WHITE 0x7

//#define BUTTON_NONE 0b00000000
#define BUTTON_SELECT 0b00000001
#define BUTTON_RIGHT 0b00000010
#define BUTTON_DOWN 0b00000100
#define BUTTON_UP 0b00001000
#define BUTTON_LEFT 0b00010000
//#define BUTTON_ALL 0b11111111


// Custom characters
#define UP_ARROW 0
#define DOWN_ARROW 1
#define LEFT_ARROW 2
#define RIGHT_ARROW 3

#define MODE_SELECT 5// Choose story or practice mode
#define MENU_SEQ_LEN 0 // Sequence Length Menu
#define MENU_SYMBOLS 1 // Character Option Menu
#define PRACTICE 2 // Where the practice game is played
#define STORY 3 // Where the stroy mode is played
#define HIGHSCORE 4 // Where the highscore is viewed

int state = MODE_SELECT;
int sequenceLen = 4;
int noOfSymbols = 2;
int buttonPress; // Stores the value for lcd.readButtons()
int modeSelected = 2; // 2: prac, 3: story, 4: highscore

// Current sequence
int SEQ[16];
// User reply 
int REPLY[16];


void setup(){
  Serial.begin(9600);
  lcd.begin(16, 2);
  
  lcd.createChar(UP_ARROW, upArrow);
  lcd.createChar(DOWN_ARROW, downArrow);
  lcd.createChar(LEFT_ARROW, leftArrow);
  lcd.createChar(RIGHT_ARROW, rightArrow);

  // Makes the randomness more random
  randomSeed(analogRead(0));

  lcd.setCursor(0, 0);
  lcd.print("Memory Game");
  lcd.setCursor(0, 1);
  lcd.print("Press any button");
  buttonPress = lcd.readButtons();
  anyButtonPressRelease();
  lcd.clear();  
}

void loop() {
  // Main switch statement to change states
  switch(state){
    // State for mode select from thge main menu
    case(MODE_SELECT):
      selectMenu();
      break;

    // 1. States for the practice mode
    case(MENU_SEQ_LEN):
      menuSeqLen();
      break;
    case(MENU_SYMBOLS):
      menuSymbols();
      break;
    case(PRACTICE):
      practice();
      state = MODE_SELECT;
      break;

    // 2. State for story mode
    case(STORY): 
      story();
      state = MODE_SELECT;
      break;

    // 3. State to show the user the current highscore
    case(HIGHSCORE):
      showHighScore();
      state = MODE_SELECT;
      break;
    }
}
/*----------------------- MENU SELECTOR -----------------------
  Function to display the menu for the user to select between
  Practice mode, Story Mode, and Viewing the current highscore
*/
void selectMenu(){
  buttonPress = lcd.readButtons();
  while(!(buttonPress & BUTTON_SELECT)){
    buttonPress = lcd.readButtons();
    if(buttonPress & BUTTON_UP){
      buttonPressRelease(BUTTON_UP); // Wait for Up to be released
      modeSelected++;
    }
    if(buttonPress & BUTTON_DOWN){
      buttonPressRelease(BUTTON_DOWN); // Wait for down to be released
      modeSelected--;
    }
    if(modeSelected < 2){modeSelected = 2;}
    else if(modeSelected > 4){modeSelected = 4;}
    lcd.setCursor(0, 0);
    switch(modeSelected){
      case(PRACTICE):
        lcd.print("1. PRACTICE     ");
        state = MENU_SEQ_LEN;
        break;
      case(STORY):
        lcd.print("2. STORY        ");
        state = STORY;
        break;
      case(HIGHSCORE):
        lcd.print("3. HI-SCORE     ");
        state = HIGHSCORE;
        break;
    }
  } 
  buttonPressRelease(BUTTON_SELECT);
}

/* ------------ MENU SEQ LEN ---------------
   Menu to select the length of the sequence
   in practice mode
 */
void menuSeqLen(){
  // Menu to select the sequence length
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Sequence Length");

  setSequence(sequenceLen);
  buttonPress = lcd.readButtons();

  // Loop unitl select is pressed
  // Up, down choose difficulty, until select pressed
  while(!(buttonPress & BUTTON_SELECT)){
    buttonPress = lcd.readButtons();
    if(buttonPress & BUTTON_UP){
      buttonPressRelease(BUTTON_UP);
      sequenceLen++;    
    }
    if(buttonPress & BUTTON_DOWN){
      buttonPressRelease(BUTTON_DOWN);
      sequenceLen--;
    }
    setSequence(sequenceLen);
  }
  // Wait for select to be released
  buttonPressRelease(BUTTON_SELECT);
  
  // End of Sequence Length Menu
  state = MENU_SYMBOLS;// Next Menu
}

/* Function to keep the value of the sequence length chosen
   by the user between 4 and 10, and chnages the lcd as selected  M */
void setSequence(int seqLen){
  // Displaying the length of the sequence selected
  // Must be between 4 and 10 inclusive
  if(seqLen < 4){sequenceLen = 4;}
  if(seqLen > 16){sequenceLen = 16;}
  
  lcd.setCursor(7, 1);
  switch(sequenceLen){
    case(4):
      lcd.print("04");
      break;
    case(5):
      lcd.print("05");
      break;
    case(6):
      lcd.print("06");
      break;
    case(7):
      lcd.print("07");
      break;
    case(8):
      lcd.print("08");
      break;
    case(9):
      lcd.print("09");
      break;
    case(10):
      lcd.print("10");
      break;
    case(11):
      lcd.print("11");
      break;
    case(12):
      lcd.print("12");
      break;
    case(13):
      lcd.print("13");
      break;
    case(14):
      lcd.print("14");
      break;
    case(15):
      lcd.print("15");
      break;
    case(16):
      lcd.print("16");
      break;
  }
}

/* 
   ---------------- MENU SYMBOLS ----------------
   Menu to allow the user to select which symbols
   could appear in the sequence
 */
// Menu to select the 
void menuSymbols(){
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Possible Symbols");
  buttonPress = lcd.readButtons();

  // Loop until select is pressed
  while(!(buttonPress & BUTTON_SELECT)){
    buttonPress = lcd.readButtons();
    if(buttonPress & BUTTON_UP){
      buttonPressRelease(BUTTON_UP);
      noOfSymbols++;     
    }
    if(buttonPress & BUTTON_DOWN){
      buttonPressRelease(BUTTON_DOWN);
      noOfSymbols--;     
    }
    setSymbols(noOfSymbols);
  }
  buttonPressRelease(BUTTON_SELECT);
  // End of state
  state = PRACTICE;// Next state
}
/*
   Function to determine the number of possible symbols that could
   appear in the sequence.   
*/
void setSymbols(int numSymbols){
  // Set the number of symbols to be used in the sequence
  if(numSymbols < 2){noOfSymbols = 2;}
  if(numSymbols > 4){noOfSymbols = 4;}

  lcd.setCursor(2,1);
  switch(noOfSymbols){
    case(2):
      lcd.write(UP_ARROW);
      lcd.write(DOWN_ARROW);
      lcd.print("  ");

      lcd.setCursor(12,1);
      lcd.print("2");
      break;
    case(3):
      lcd.write(UP_ARROW);
      lcd.write(DOWN_ARROW);
      lcd.write(LEFT_ARROW);
      lcd.print(" ");
      
      lcd.setCursor(12,1);
      lcd.print("3"); 
      break;
    case(4):
      lcd.write(UP_ARROW);
      lcd.write(DOWN_ARROW);
      lcd.write(LEFT_ARROW);
      lcd.write(RIGHT_ARROW);
      
      lcd.setCursor(12,1);
      lcd.print("4"); 
      break;
  }  
}
/* ---------- PRACTICE GAME ----------
   Main function for the practice mode
*/
void practice(){
  lcd.clear();
  lcd.setCursor(7,0);
  lcd.print("3");
  delay(1000);
  lcd.setCursor(7,0);
  lcd.print("2");
  delay(1000);
  lcd.setCursor(7,0);
  lcd.print("1");
  delay(1000);
  lcd.clear();
  for(int i = 0; i<sequenceLen; i++){
    showChar(i, 1000); // Function to display each symbol
  }
  userReply();
}

/* 
   Function to generate a random character
   store it in an array and display in on the lcd
 */
void showChar(int i, int timeDelay){
  int choice = random(0,noOfSymbols);
  SEQ[i] = choice;
  lcd.setCursor(0,0);
  lcd.write(choice);
  delay(timeDelay); // Time each character is displayed for
  lcd.clear();
  delay(333);// Delay between characters
}
/*
  Interprets the reply of the user 
  and stores thier reply in an array
  to be compared with the actual sequence
 */
bool userReply(){
  int replies = 0;
  lcd.setCursor(0,0);
  lcd.print("Copy the symbols");
  for(replies ; replies < sequenceLen; replies++){
    lcd.setCursor(replies, 1  );
    lcd.write(UP_ARROW); 
    REPLY[replies] = UP_ARROW;

    // Symbol selection
    while(!(buttonPress & BUTTON_SELECT)){
      lcd.setCursor(replies, 1  );
      if(buttonPress & BUTTON_UP){
        buttonPressRelease(BUTTON_UP);
        lcd.write(UP_ARROW);
        REPLY[replies] = UP_ARROW;    
      }
      if(buttonPress & BUTTON_DOWN){
        buttonPressRelease(BUTTON_DOWN);
        lcd.write(DOWN_ARROW); 
        REPLY[replies] = DOWN_ARROW;   
      }
      if(buttonPress & BUTTON_LEFT){
        buttonPressRelease(BUTTON_LEFT);
        lcd.write(LEFT_ARROW);
        REPLY[replies] = LEFT_ARROW;   
      }
      if(buttonPress & BUTTON_RIGHT){
        buttonPressRelease(BUTTON_RIGHT);
        lcd.write(RIGHT_ARROW);
        REPLY[replies] = RIGHT_ARROW; 
      }
      buttonPressRelease(BUTTON_SELECT);
      buttonPress = lcd.readButtons();
    }
    buttonPressRelease(BUTTON_SELECT);
  }
  if(readReply()){
    flashBacklight(GREEN);
    return true;
  }else{
    flashBacklight(RED);
    return false;
  }
}

/* ---------------------- STORY MODE ----------------------
   Main function for the story mode. 3 nested for loops are
   used to make each level harder */
void story(){
  bool isReplyCorrect = true;
  lcd.clear();
  int levelNo = 0;
  for(int seqLen = 4; seqLen<=16; seqLen++){ // Sequence Length
    sequenceLen = seqLen;
    for(int numSymbols = 2; numSymbols<=4; numSymbols++){ // Number of symbols in sequence
      noOfSymbols = numSymbols;
      for(int timeDelay = 1000; timeDelay>= 500; timeDelay-=500){ // Time delay between symbols
        lcd.setCursor(4,0);
        lcd.print("LEVEL: ");
        lcd.print(levelNo, DEC);
        
        delay(1000);
        lcd.clear();

        // Generates the sequence
        for(int index = 0; index < seqLen; index++){
          showChar(index, timeDelay);
        }
        
        // If the user reply is incorrect all the for loops are exited
        if(!userReply()){
          isReplyCorrect = false;
          break;
        }
        levelNo++;
      }
      if(!isReplyCorrect){break;}
    }
    if(!isReplyCorrect){break;}
  }
  lcd.setCursor(0, 0);
  lcd.print("SCORE : ");
  lcd.print(levelNo, DEC);
  lcd.setCursor(0, 1);
  lcd.print("Press any button");
  buttonPress = lcd.readButtons();
  anyButtonPressRelease();
  lcd.clear();

  // If new high score
  if(levelNo > getHighScore()){
    saveScore(levelNo);
  }
  
  
}
// ------------ Key functions used by both story and practice mode ------------

// Compares the user reply to the actual sequence
bool readReply(){
  for(int i = 0; i<sequenceLen; i++){
    if(SEQ[i] != REPLY[i]){return false;}
  }
  return true;
}

void flashBacklight(int colour){
  lcd.setBacklight(colour);
  lcd.clear();
  lcd.setCursor(4,0);
  if(colour == GREEN){
    lcd.print("SUCCESS");
  }else if(colour == RED){
    lcd.print("FAILIURE");
  }
  delay(1000);
  lcd.clear();
  lcd.setBacklight(WHITE);
}

// Function to loop while the a button is held and wait for it to be released
void buttonPressRelease(int button){
  while(buttonPress & button){
    buttonPress = lcd.readButtons();
  }
}

// Waits for all buttons to be released
void anyButtonPressRelease(){
  while(!buttonPress){
    buttonPress = lcd.readButtons();
  }
  while(buttonPress){
    buttonPress = lcd.readButtons();
  }
}

// ---------------------- HIGH SCORE ----------------------
// HIGH SCORE STORED IN LOCATION 10
// 3 CHAR NAME STORED IN 11, 12, 13

void showHighScore(){
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("HIGH SCORE: ");
  lcd.print(getHighScore(), DEC);
  lcd.setCursor(0, 1);
  lcd.print("BY: ");
  lcd.write(getPlyrName(11));
  lcd.write(getPlyrName(12));
  lcd.write(getPlyrName(13));
  buttonPress = lcd.readButtons();
  anyButtonPressRelease();
  lcd.clear();
}
int getHighScore(){
  return EEPROM.read(10);
}

int getPlyrName(int index){
  return EEPROM.read(index);
}

void saveScore(int newScore){
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("ENTER A NAME:");

  int charValue = 65; // Capital A
  for(int index = 0; index <= 2; index++){

    lcd.setCursor(index, 1);
    buttonPress = lcd.readButtons();

    // Character Selection
    while(!(buttonPress == BUTTON_SELECT)){
      if(buttonPress & BUTTON_UP){
        buttonPressRelease(BUTTON_UP);  
        charValue++; 
      }
      if(buttonPress & BUTTON_DOWN){
        buttonPressRelease(BUTTON_DOWN);
        charValue--;
      }
      // Does not loop between characters
      if(charValue < 65){charValue = 65;}// A
      else if(charValue > 90){charValue = 90;}// Z
      
      lcd.setCursor(index, 1);
      lcd.write(charValue);
      buttonPress = lcd.readButtons();
    }
    buttonPressRelease(BUTTON_SELECT);
    EEPROM.update(index+11, charValue);
  }
  EEPROM.update(10, newScore);
  lcd.clear();
  lcd.print("SCORE SAVED");
  delay(1000);
}
