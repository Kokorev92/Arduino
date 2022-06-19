static const int data_pin = A0;
static const int clock_pin = A1;
static const int latch_pin = A2;

volatile int a = 0;

void setup() {
  pinMode(data_pin, OUTPUT);
  pinMode(clock_pin, OUTPUT);
  pinMode(latch_pin, OUTPUT);

  Serial.begin(19200);
  Serial.setTimeout(10);
}

void loop() {

  if (Serial.available() > 0) {
    int relay_num = Serial.parseInt();
    if ((relay_num != 0) && (relay_num <= 8)) {
      relay_num--;
      a ^= (1 << relay_num);
      Serial.println(a);
    }
  }

  digitalWrite(latch_pin, LOW);
  shiftOut(data_pin, clock_pin, LSBFIRST, ~a);
  digitalWrite(latch_pin, HIGH);
}
