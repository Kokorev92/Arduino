#include "parser.h"

static volatile uint32_t timer = 0;

uint8_t buf[256];
uint8_t response[] = {0x3a, 0x4, 0x00, 0x00, 0x00, 0x00, 0x21, 0x00};

Parser parser;

void setup() {
  pinMode(13, OUTPUT);
  digitalWrite(13, LOW);
  Serial.begin(19200);
}

void loop() {
  timer = millis();

  if (Serial.available() > 0) {
    byte b = Serial.read();
    parser.add_byte(b);
  }

  uint8_t len = parser.get_data(buf);

  if (len != 0) {
    if (buf[0] == 0x47) {
      digitalWrite(13, HIGH);
    } else if (buf[0] == 0x46) {
      digitalWrite(13, LOW);
    }
  }

}
