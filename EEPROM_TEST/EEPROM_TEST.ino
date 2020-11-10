#include <EEPROM.h>

void setup() {
  pinMode(13, OUTPUT);
  digitalWrite(13, HIGH);
  for (int i = 0; i < 1024; i++) {
    EEPROM.write(i, (uint8_t)0xAA);
  }
  digitalWrite(13, LOW);
}

void loop() {
  // put your main code here, to run repeatedly:

}
