#include "parser.h"

const uint8_t relay_1_pin = 6;
const uint8_t relay_2_pin = 7;

const uint8_t pins[] = {relay_1_pin, relay_2_pin};

struct packet_t {
  bool relay_1 : 1;
  bool relay_2 : 1;
} __attribute__((packed));

packet_t packet;
Parser parser;
uint8_t command = 0;

void setup() {
  for (auto pin : pins) {
    pinMode(pin, OUTPUT);
    digitalWrite(pin, LOW);
  }

  Serial.begin(19200);
}

void loop() {
  if (Serial.available() > 0) {
    byte b = Serial.read();

    parser.add_byte(b);
  }

  if(parser.get_command(command)){
    memcpy(&packet, &command, sizeof(command));
    
  }

  digitalWrite(relay_1_pin, !packet.relay_1);
  digitalWrite(relay_2_pin, !packet.relay_2);
}
