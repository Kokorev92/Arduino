#include <Servo.h>
#include "cobs.h"

struct skvt_packet {
    uint32_t current_time_ms = 0;
    uint32_t counter = 0;
    uint16_t coord = 0;
    int16_t speed = 0;
} __attribute__((packed));

byte c[sizeof(skvt_packet) + 3];
uint16_t coord;
uint8_t buff[sizeof(skvt_packet) + 3];
//const uint32_t CIR = 360;

skvt_packet recive_packet_t;

cobs::Cobs_parser parser;
cobs::cobs_packet_t packet;

Servo serv;

void setup() {
  Serial.begin(115200);
  serv.attach(10);
  serv.write(90);
}

void loop() {
  serialEvent();
}

void serialEvent() {
  if(Serial.available() > 0) {
    Serial.readBytes(c,sizeof(c));
    memcpy(&buff, c, sizeof(buff));

    parser.add_bytes(buff, sizeof(buff));

    while(parser.check()) {
      packet = parser.get_packet();
      memcpy(&recive_packet_t, packet.data, sizeof(packet.data));

      
      uint32_t ang = recive_packet_t.coord;
//      ang = constrain(ang, 10, 170);
      if(ang > 10 && ang < 170) {
        serv.write(ang);
      }
    }
    
    
  }
}
