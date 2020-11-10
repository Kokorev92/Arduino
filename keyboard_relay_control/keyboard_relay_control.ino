#include <Keypad.h>
#include <Key.h>

const byte ROWS = 4;
const byte COLS = 4;

const char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

const byte row_pins[ROWS] = {14, 15, 16, 17};
const byte col_pins[COLS] = {18, 19, 20, 21};

Keypad keypad = Keypad(makeKeymap(keys), row_pins, col_pins, ROWS, COLS);

void setup() {

}

void loop() {

}
