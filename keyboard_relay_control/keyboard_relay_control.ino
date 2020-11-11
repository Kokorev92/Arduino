#include <Keypad.h>
#include <Key.h>

constexpr byte ROWS = 4;
constexpr byte COLS = 4;

constexpr char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

constexpr byte row_pins[ROWS] = {9, 8, 7, 6};
constexpr byte col_pins[COLS] = {5, 4, 3 ,2};

Keypad keypad = Keypad(makeKeymap(keys), row_pins, col_pins, ROWS, COLS);

void setup() {

}

void loop() {

}
