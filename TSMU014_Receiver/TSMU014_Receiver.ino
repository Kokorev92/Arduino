int adc_value = 0;

void setup() {
  Serial.begin(9600);
  pinMode(A1, INPUT);
}

void loop() {
  adc_value = analogRead(A1);
  if(adc_value > 100) {
    Serial.println(adc_value);
  }

  delay(100);
}
