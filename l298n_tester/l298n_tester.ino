#include <Stepper.h>

Stepper motor(18,2,3,4,5);

void setup() {
  for(int i = 2; i < 6; i++){
    pinMode(i, OUTPUT);
    digitalWrite(i, LOW);
  }
}

void loop() {
  motor.step(1);
  delay(10);
}
