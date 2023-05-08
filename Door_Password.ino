
#include<Keypad.h>
#include<LiquidCrystal.h>
#include<EEPROM.h>
#include <Servo.h> 
Servo s1;
#define KEYPAD_ROWS 4
#define KEYPAD_COLS 4
#define BUZZ 10
#define servoPin 9

char keys [KEYPAD_ROWS][KEYPAD_COLS] = {
  {'7', '8', '9', '/'},
  {'4', '5', '6', 'X'},
  {'1', '2', '3', '-'},
  {'C', '0', '=', '+'}
};

byte rowPins[KEYPAD_ROWS] = {2, 3, 4, 5};
byte colPins[KEYPAD_COLS] = {6, 7, 8, 9};
LiquidCrystal lcd(A0, A1, A2, A3, A4, A5);
Keypad keypad = Keypad(makeKeymap(keys),  rowPins,
                       colPins, KEYPAD_ROWS, KEYPAD_COLS);
void setup() {
  pinMode (A0, OUTPUT);
  pinMode (A1, OUTPUT);
  pinMode (A2, OUTPUT);
  pinMode (A3, OUTPUT);
  pinMode (A4, OUTPUT);
  pinMode (A5, OUTPUT);
  pinMode(BUZZ, OUTPUT);
  pinMode(servoPin, OUTPUT)
  s1.attach(servoPin);
  lcd.begin(16, 2);
  lcd.clear();
  EEPROM.write(0, 0);
}
void loop() {

  if (EEPROM.read(0) != 1) {

    lcd.setCursor(0, 0);
    lcd.print("New Password :");
    lcd.setCursor(0, 1);
    lcd.print("=>");
    String password = "";
    while (true) {
      char key = keypad.getKey();
      if (key == '=') {
        EEPROM.write(0, 1);
        EEPROM.write(1, 0);
        WriteStringToEEPROM(2, password);
        break;
      } else if (key) {
        password += String(key);
        lcd.print("*");
      }
    }
    lcd.clear();
    lcd.print("The password is");
    lcd.setCursor(0, 1);
    lcd.print("set successfully");
  } else {
    int noOfTrials = EEPROM.read(1);
    String password = ReadStringFromEEPROM(2);
    bool isCorrectPassword = false;
    for (int i = noOfTrials; i < 3; i++) {
      delay(1000);
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Enter Password:");
      lcd.setCursor(0, 1);
      lcd.print("=>");
      String userPassword = "";
      while (true) {
        char key = keypad.getKey();
        if (key == '=') {
          if (userPassword.equals(password)) {
            isCorrectPassword = true;
            lcd.clear();
            lcd.print("Correct!");
            s1.write(90);
            delay(1000);
            s1.write(0);
          } 
          else {
            isCorrectPassword = false;
            lcd.clear();
            lcd.print("InCorrect!");
          }
          EEPROM.write(1, noOfTrials + 1);
          break;
        } else if (key) {
          userPassword += String(key);
          lcd.print("*");
        }
      }
      if (isCorrectPassword)
      {
        break;
      }
    }
    if (isCorrectPassword) {
      while (true);
      { 
        lcd.clear();
        lcd.print("THANKS!");
      }
    } 
      else {
      lcd.clear();
      lcd.print("ALARM!!");
      digitalWrite(BUZZ, HIGH);
      while (true);
    }
  }
}
void WriteStringToEEPROM(int addrOffset, const String&strTowrite)
{
  byte len = strTowrite.length();
  EEPROM.write(addrOffset, len);
  for (int i = 0; i < len; i++) {
    EEPROM.write(addrOffset + 1 + i, strTowrite[i]);
  }
}
String ReadStringFromEEPROM(int addrOffset) {
  int newStrLen = EEPROM.read(addrOffset);
  char data [newStrLen + 1];
  for (int i = 0; i < newStrLen; i++) {
    data[i] = EEPROM.read(addrOffset + 1 + i);
  }
  data[newStrLen] = '\0';
  return String(data);
}
