#include <AFMotor.h>

AF_Stepper motor(50, 2);

void setup() {
  motor.setSpeed(20);
}

void loop() {
  motor.step(100, FORWARD, DOUBLE);
  delay(1000);
}
