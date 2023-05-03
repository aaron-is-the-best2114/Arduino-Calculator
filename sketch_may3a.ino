#include <LiquidCrystal.h>
#include <Keypad.h>

// Initialize the LCD object
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

// Initialize the keypad object
const byte ROWS = 4;
const byte COLS = 4;
char keys[ROWS][COLS] = {
  {'1','2','3','+'},
  {'4','5','6','-'},
  {'7','8','9','*'},
  {'C','0','=','/'}
};
byte rowPins[ROWS] = {9, 8, 7, 6}; // Connect to the row pinouts of the keypad
byte colPins[COLS] = {13, A0, A1, A2}; // Connect to the column pinouts of the keypad
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

void setup() {
  // Set up the LCD display
  lcd.begin(16, 2);
  lcd.print("Calculator");
  lcd.setCursor(0, 1);
  lcd.print("by Arduino");
  delay(2000);
  lcd.clear();
}

void loop() {
  char key = keypad.getKey(); // Read the pressed key

  if (key != NO_KEY) { // If a key is pressed
    switch (key) {
      case 'C': // Clear the LCD display
        lcd.clear();
        break;
      case '=': // Calculate the result
        lcd.setCursor(15, 1);
        lcd.print('=');
        lcd.setCursor(0, 1);
        lcd.print(calculate(lcd));
        break;
      default: // Display the pressed key on the LCD
        lcd.setCursor(lcd.print(key), 1);
        break;
    }
  }
}

float calculate(LiquidCrystal& lcd) {
  String input = ""; // Initialize the input string
  char key = keypad.getKey(); // Read the pressed key

  while (key != '=') { // Read input until the '=' key is pressed
    if (key != NO_KEY) { // If a key is pressed
      lcd.print(key); // Display the pressed key on the LCD
      input += key; // Add the pressed key to the input string
    }
    key = keypad.getKey(); // Read the pressed key
  }

  lcd.setCursor(0, 0); // Set the cursor to the top-left corner of the LCD

  // Split the input string into two operands and an operator
  int operand1_end = input.indexOf(' ');
  int operand2_start = operand1_end + 3;
  char op = input.charAt(operand1_end + 1);

  // Convert the operands from strings to floats
  float operand1 = input.substring(0, operand1_end).toFloat();
  float operand2 = input.substring(operand2_start).toFloat();

  // Calculate the result based on the operator
  float result;
  switch (op) {
    case '+':
      result = operand1 + operand2;
      break;
    case '-':
      result = operand1 - operand2;
      break;
    case '*':
      result = operand1 * operand2;
      break;
    case '/':
      result = operand1 / operand2;
      break;
  }

  return result;
}