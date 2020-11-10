const int pin = 13;
bool pin_state = false;

void setup() {
  pinMode(pin, OUTPUT);
  digitalWrite(pin, LOW);
}

void loop() {
  digitalWrite(pin, pin_state ? HIGH:LOW);
  pin_state = !pin_state;
  delay(250);
}
