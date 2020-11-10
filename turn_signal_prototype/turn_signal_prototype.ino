int I = 2;

void setup() {
  for(int i = 2; i < 6; i++) {
    pinMode(i, OUTPUT);
    digitalWrite(i , LOW);
  }

}
bool inv = false;
void loop() {
  if (!inv) {
    digitalWrite(I, HIGH);
    delay(75);
  } else {
    digitalWrite(I, LOW);
    delay(75);
  }


  if(I > 5) {
    I = 2;
    inv = !inv;
  } else {
    I++;
  }

}
