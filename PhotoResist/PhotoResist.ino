паvoid setup() {
pinMode(5, OUTPUT);
Serial.begin(9600);
digitalWrite(5, HIGH);
}

void loop() {
int val = analogRead(A0);
Serial.println(val);
delay(250);

}
