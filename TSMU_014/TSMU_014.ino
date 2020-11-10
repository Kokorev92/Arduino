#include <LiquidCrystal.h>

int analog_val = 0;
LiquidCrystal lcd(7,6,5,4,3,2);


void setup() {
  analogReference(DEFAULT);
  Serial.begin(9600);
  pinMode(A1, INPUT);
  lcd.begin(16,2);
  lcd.clear();
  lcd.print("Hello world!");
}

void loop() {
  analog_val = analogRead(A1);
  Serial.println(analog_val);
  delay(100);
}
