#include "parser.h"

struct packet_t {
  bool relay_1 : 1;
  bool relay_2 : 1;
} __attribute__((packed));

static const uint8_t relay_1 = 2;
static const uint8_t relay_2 = 3;

Parser parser;
packet_t packet;

void setup() {
  Serial.begin(19200);

  pinMode(relay_1, OUTPUT);
  pinMode(relay_2, OUTPUT);

  digitalWrite(relay_1, HIGH);
  digitalWrite(relay_2, HIGH);
}


void loop() {
  uint8_t command;

  while (Serial.available() > 0) {
    uint8_t _byte = Serial.read();
    parser.add_byte(_byte);
    if (parser.get_command(command)) {
      memcpy(&packet, &command, sizeof(command));
      break;
    }
  }

  digitalWrite(relay_1, packet.relay_1 ? LOW : HIGH);
  digitalWrite(relay_2, packet.relay_2 ? LOW : HIGH);
}
