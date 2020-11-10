const uint8_t header_byte = 0x0F;
const uint8_t footer_byte = 0x00;
const uint8_t digital_channels = 0xF0;

uint8_t buff[25];

void setup() {
  buff[0] = header_byte;
  buff[23] = digital_channels;
  buff[24] = footer_byte;

  for(int i = 1; i < 23; i ++){
    buff[i] = 0xA0 + i;
  }

  Serial.begin(100000, SERIAL_8E2);
}

void loop() {
  Serial.write(buff, sizeof(buff));
  delay(500);
}
