#include <Keypad.h>
#include <LiquidCrystal.h>

// LCD setup
LiquidCrystal lcd(12, 11, 10, 9, 8, 7);

// Keypad setup
const byte ROWS = 4;
const byte COLS = 4;
char keys[ROWS][COLS] = {
  {'1','2','3','+'},
  {'4','5','6','-'},
  {'7','8','9','*'},
  {'C','0','=','/'}
};
byte rowPins[ROWS] = {5, 4, 3, 2};
byte colPins[COLS] = {A3, A2, A1, A0};
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

// Variables
String input = "";
char operation;
float num1, num2;

void setup() {
  lcd.begin(16, 2);
  lcd.print("Arduino Calc");
  delay(1000);
  lcd.clear();
}

void loop() {
  char key = keypad.getKey();
  if (key) {
    if (key >= '0' && key <= '9') {
      input += key;
      lcd.print(key);
    } else if (key == '+' || key == '-' || key == '*' || key == '/') {
      num1 = input.toFloat();
      operation = key;
      input = "";
      lcd.setCursor(0, 1);
      lcd.print(operation);
    } else if (key == '=') {
      num2 = input.toFloat();
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Result:");
      lcd.setCursor(0, 1);
      switch (operation) {
        case '+': lcd.print(num1 + num2); break;
        case '-': lcd.print(num1 - num2); break;
        case '*': lcd.print(num1 * num2); break;
        case '/': 
          if (num2 != 0) lcd.print(num1 / num2);
          else lcd.print("Err: Div0");
          break;
      }
      input = "";
    } else if (key == 'C') {
      input = "";
      lcd.clear();
    }
  }
}
