

void setup() {
  Serial.begin(115200);
  Serial1.begin(115200);
}

void loop() {

}

void serialEvent1() {
  if(Serial1.available() > 0) {
    int buff = Serial1.read();
    Serial.write(buff);
  }
}
