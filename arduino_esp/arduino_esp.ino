static const int RELAY_1 = A3;

void setup() {
  Serial.begin(9600);
  pinMode(RELAY_1, OUTPUT);
  digitalWrite(RELAY_1, HIGH);
  
}

uint8_t b;

void loop() {
  if(Serial.available() > 0) {
    b = Serial.read();
  }

  if(b == 1) {
    digitalWrite(RELAY_1, LOW);
  }
  if(b == 0) {
    digitalWrite(RELAY_1, HIGH);
  }
}
