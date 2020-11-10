#include "cobs.h"

int analog_value = 0;
int angle = 0;
uint32_t counter = 0;
uint32_t time_ms = 0;

struct skvt_packet {
    uint32_t current_time_ms = 0;
    uint32_t counter = 0;
    uint16_t coord = 0;
    int16_t speed = 0;
} __attribute__((packed));

uint8_t out_buff[sizeof(skvt_packet)+3];

skvt_packet send_packet;

void setup() {
  Serial.begin(115200);
}

void loop() {
  analog_value = analogRead(A0);
  angle = (unsigned long)(360ul * (unsigned long)analog_value) / (unsigned long)1023;
  send_packet.counter = counter;
  send_packet.current_time_ms = time_ms;
  send_packet.coord = angle;
  cobs::cobs_encode((const uint8_t*)(&send_packet), sizeof(send_packet), out_buff, sizeof(out_buff));
  Serial.write(out_buff, sizeof(out_buff));
  counter++;
  time_ms++;
  delay(10);
}
