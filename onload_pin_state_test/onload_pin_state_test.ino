const int led_pin = 13;
const int button_pin = 2;

int onload_jack_state;

void setup() {
  pinMode(button_pin, INPUT);
  pinMode(led_pin, OUTPUT);

  onload_jack_state = digitalRead(button_pin);
}

void loop() {
  if (onload_jack_state == HIGH) {
    first_load();
  }
  digitalWrite(led_pin, LOW);
  delay(500);
  digitalWrite(led_pin, HIGH);
  delay(500);
}

void first_load() {
  while (1) {
    digitalWrite(led_pin, LOW);
    delay(100);
    digitalWrite(led_pin, HIGH);
    delay(100);
  }
}
