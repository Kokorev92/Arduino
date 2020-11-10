#define a 5
#define b 6
#define c 7
#define d 8
#define e 9
#define f 10
#define g 11
#define dp 12

#define d1 A1
#define d2 A2
#define d3 A3
#define d4 A4

void setup() {
  for(int i = 5; i < 13; i++) {
    pinMode(i, OUTPUT);
    digitalWrite(i, HIGH);
  }

  pinMode(d1, OUTPUT);
  digitalWrite(d1, LOW);
  pinMode(d2, OUTPUT);
  digitalWrite(d2, LOW);
  pinMode(d3, OUTPUT);
  digitalWrite(d3, LOW);
  pinMode(d4, OUTPUT);
  digitalWrite(d4, LOW);
}

void changeDigit(int dg) {
  digitalWrite(d1, LOW);
  digitalWrite(d2, LOW);
  digitalWrite(d3, LOW);
  digitalWrite(d4, LOW);
  switch(dg) {
    case 1: digitalWrite(d4, HIGH); break;
    case 2: digitalWrite(d3, HIGH); break;
    case 3: digitalWrite(d2, HIGH); break;
    case 4: digitalWrite(d1, HIGH); break;
  }
}

void one() {
  digitalWrite(a, HIGH);
  digitalWrite(b, LOW);
  digitalWrite(c, LOW);
  digitalWrite(d, HIGH);
  digitalWrite(e, HIGH);
  digitalWrite(f, HIGH);
  digitalWrite(g, HIGH);
}

void two() {
  digitalWrite(a, LOW);
  digitalWrite(b, LOW);
  digitalWrite(c, HIGH);
  digitalWrite(d, LOW);
  digitalWrite(e, LOW);
  digitalWrite(f, HIGH);
  digitalWrite(g, LOW);
}

void loop() {
  changeDigit(3);
  one();
  delay(5);
  changeDigit(4);
  two();
  delay(5);
}
