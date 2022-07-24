#include "Keyboard.h"

void setup() {
  Keyboard.begin();
}

void loop() {
  Keyboard.press('A');
  delay(500);
}
