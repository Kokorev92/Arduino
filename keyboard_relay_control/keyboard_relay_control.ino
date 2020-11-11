#include <Keypad.h>
#include <Key.h>

const byte ROWS = 4;
const byte COLS = 4;
const int OUT_PINS[] = {A0, A1, A2, A3, A4};
bool out_pins_state[5];

const char keys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

const byte row_pins[ROWS] = {9, 8, 7, 6};
const byte col_pins[COLS] = {5, 4, 3 , 2};

Keypad keypad = Keypad(makeKeymap(keys), row_pins, col_pins, ROWS, COLS);

void setup() {
  Serial.begin(9600);
  for (int i = 0; i < 5; i++) {
    pinMode(OUT_PINS[i], OUTPUT);
    digitalWrite(OUT_PINS[i], LOW);
    out_pins_state[i] = false;
  }
}

void loop() {
  char key = keypad.getKey();

  if (key) {
    Serial.println(key);
    switch (key) {
      case '1' :
        pin_toggle(0);
        break;
      case '2' :
        pin_toggle(1);
        break;
      case '3' :
        pin_toggle(2);
        break;
      case '4' :
        pin_toggle(3);
        break;
      case '5' :
        pin_toggle(4);
        break;
      case 'C' :
        pins_reset();
        break;
      case 'A' :
        pins_on();
        break;
    }
  }
}

void pin_toggle(int pin) {
  out_pins_state[pin] = !out_pins_state[pin];
  digitalWrite(OUT_PINS[pin], out_pins_state[pin] ? HIGH : LOW);
  Serial.println(pin);
}

void pins_reset() {
  for (int i = 0; i < 5; i++) {
    digitalWrite(OUT_PINS[i], LOW);
    out_pins_state[i] = false;
  }
}

void pins_on() {
  for (int i = 0; i < 5; i++) {
    digitalWrite(OUT_PINS[i], HIGH);
    out_pins_state[i] = true;
  }
}
