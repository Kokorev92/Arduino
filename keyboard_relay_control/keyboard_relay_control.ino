#include <EEPROM.h>

#include <Keypad.h>
#include <Key.h>

const byte ROWS = 4;
const byte COLS = 4;
const int OUT_PINS[] = {A0, A1, A2, A3, A4};
bool out_pins_state[5];
byte pins_state = 0;

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
  pins_state = EEPROM.read(0);
  
  for (int i = 0; i < 5; i++) {
    pinMode(OUT_PINS[i], OUTPUT);

    out_pins_state[i] = (bool((1 << i) & pins_state));
    digitalWrite(OUT_PINS[i], out_pins_state[i] ? HIGH:LOW);
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

// Функция переключения состояни пина
void pin_toggle(int pin) {
  out_pins_state[pin] = !out_pins_state[pin];
  digitalWrite(OUT_PINS[pin], out_pins_state[pin] ? HIGH : LOW);
  Serial.println(pin);
  eeprom_write();
}

// Функция сброса всех пинов
void pins_reset() {
  for (int i = 0; i < 5; i++) {
    digitalWrite(OUT_PINS[i], LOW);
    out_pins_state[i] = false;
  }
  eeprom_write();
}

// Функция включения всех пинов
void pins_on() {
  for (int i = 0; i < 5; i++) {
    digitalWrite(OUT_PINS[i], HIGH);
    out_pins_state[i] = true;
  }
  eeprom_write();
}

// Функция сохранения состояния пинов в eeprom
// Вызывается каждый раз при изменение состояния пинов
void eeprom_write() {
  for(int i = 0; i < 5; i++) {
    if(out_pins_state[i]) {
      pins_state |= (1 << i);
    } else {
      pins_state &= ~(1 << i);
    }
  }

  EEPROM.update(0, pins_state);
}
