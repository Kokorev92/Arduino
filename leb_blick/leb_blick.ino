void setup() {
  pinMode(5, OUTPUT);
  digitalWrite(5, LOW); 
}

void loop() {
  digitalWrite(5, HIGH);
  delay(250);
  digitalWrite(5, LOW);
  delay(250);
}
