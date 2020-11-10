void setup()
{
  for(int i = 0; i < 5; i++){
    pinMode(i, OUTPUT);
  }
}

bool led = true;

void loop()
{
  for(int i = 0; i< 5; i++){
    digitalWrite(i, led ? HIGH : LOW);
    delay(75);
  }
  
  led = !led;
  
  for(int i = 0; i<5; i++){
    digitalWrite(i, LOW);
  }
}
