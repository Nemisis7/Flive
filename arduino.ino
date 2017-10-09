// include the library code:
#include <LiquidCrystal.h>

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

int count = 0; // Keep track of character count

void setup() {
  Serial.begin(9600); // Open serial port at 9600
  lcd.begin(16, 2); // Begin LCD which has a 16 digit width and 2 digit height
}

void loop() {
  char character; // Initialise character variable

  while(Serial.available()) { // Begin while loop whilst the Serial port is avilable
    character = Serial.read(); // Read the current character being transmitted
    if(String(character) == "_") { // Check if the character is an underscore
      count = 0; // If it is, reset the character count
      return; // Return from the loop
    }
    if(count < 16) {
      if(count == 0) { // If the count is 0
        lcd.clear(); // Delete everything on the screen.
      }
      if(String(character) == "-") { // If the character is a dash, go to the new line.
        count = 16; // 16 is the width of the screen, so thats when we should go to the new line.
        return;
      } else {
        lcd.setCursor(count, 0); // Set the cursor to the current character count, on the first line.
        lcd.print(character); // Print out the current character
      }
      count++; // Increment the character count
    } else {
      lcd.setCursor(count - 16, 1); // Set cursor to second line
      lcd.print(character); // Print character
      count++; // Increment the character count
    }
  }
}

