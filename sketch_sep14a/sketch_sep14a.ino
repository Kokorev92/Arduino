bool pin = false;

void setup() {
  pinMode(13, OUTPUT);
  digitalWrite(13, LOW);
}

void loop() {
  digitalWrite(13, pin ? HIGH:LOW);
  pin = !pin;
  delay(500);
}
