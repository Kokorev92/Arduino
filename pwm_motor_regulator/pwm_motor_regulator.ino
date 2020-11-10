void setup()
{
  pinMode(1, OUTPUT);
  pinMode(A3, INPUT);
}

void loop()
{
  int rot = analogRead(A3);
  int speed = rot / 4;
  analogWrite(1, speed);
  //delay(100);
}
