static constexpr uint8_t msg[6] = {0x41, 0x42, 0x43, 0x44, 0x0D, 0x0A};

void setup() {
  pinMode(2, OUTPUT);
  digitalWrite(2, LOW);
  Serial.begin(19200);
}

void loop() {
  digitalWrite(2, HIGH);
  for(int i = 0; i < sizeof(msg); i++) {
    Serial.write(msg[i]);
  }

  delay(500);
}
