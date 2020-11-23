void setup() {
  pinMode(8, INPUT_PULLUP);
  pinMode(13, OUTPUT);
}

void loop() {
   digitalWrite(13, !digitalRead(8));
   delay(10);
}
