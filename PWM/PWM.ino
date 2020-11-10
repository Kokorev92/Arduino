void setup() {
  pinMode(10, OUTPUT);
  pinMode(A0, INPUT);
  Serial.begin(9600);
}

void loop() {
  int rot = 0;
  int ang = 0;
  float voltage = 0;
  char* message[50];
  rot = analogRead(A0);
  ang = rot / 4;
  voltage = (5 * (float)rot) / 1024;
  int tmp_volt = voltage;
  float tmp_frac = voltage - tmp_volt;
  int tmp_frac2 = double(tmp_frac * 100);
  snprintf((char*)message, 50, "%hu : %hu : %d.%d V", rot, ang, tmp_volt, tmp_frac2);
  Serial.println((char*)message);
  analogWrite(10, ang);
  delay(250);
}
