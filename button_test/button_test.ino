const int button_pin = 2;
const int led_pin = 13;

void setup() {
  pinMode(button_pin, INPUT);
  pinMode(led_pin, OUTPUT);
  digitalWrite(led_pin, HIGH);
  digitalWrite(button_pin, LOW);
}

void loop() {
  int button_state = digitalRead(button_pin);

  if (button_state == HIGH) {
    digitalWrite(led_pin, HIGH);
  } else {
    digitalWrite(led_pin, LOW);
  }
}
