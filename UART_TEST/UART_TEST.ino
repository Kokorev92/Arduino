bool relay_1 = false;
bool relay_2 = false;

void setup() {
  Serial.begin(9600);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  digitalWrite(3, LOW);
  digitalWrite(4, LOW);
}

void loop() {

}

void serialEvent() {
  if (Serial.available() > 0) {
    uint8_t b = Serial.read();
    if (b == 0x31) {
      digitalWrite(3, relay_1 ? HIGH : LOW);
      relay_1 = !relay_1;
      return;
    }

    if (b == 0x32) {
      digitalWrite(4, relay_2 ? HIGH : LOW);
      relay_2 = !relay_2;
      return;
    }
  }
}
