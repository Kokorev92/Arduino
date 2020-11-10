void setup() {
  pinMode(PB0, OUTPUT);
  pinMode(A1, INPUT);
}

void loop() {
  int pwm = 0;
  pwm = analogRead(A1);
  if(pwm > 512) {
    digitalWrite(PB0, HIGH);
  } else {
    digitalWrite(PB0, LOW);
  }
  delay(100);
}
