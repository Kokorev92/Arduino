
struct packet_t {
  uint8_t prefix = 0xFE;
  uint8_t version = 0x01;
  uint16_t alt = 200;
  uint8_t snr = 0x10;
  uint8_t crc = 0x00;
} __attribute__((packed));

packet_t packet;
uint8_t buffer[6];

void setup() {
  Serial.begin(115200, SERIAL_8N2);
  delay(5000);
}

void loop() {
  delay(20);
  memcpy(buffer, (uint8_t*)&packet, sizeof(buffer));
  buffer[5] = (buffer[0] + buffer[1] + buffer[2] + buffer[3]) & 0xFF;
  Serial.write(buffer, 6);
  packet.alt++;
}
