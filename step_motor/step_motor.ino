#include <Stepper.h>

Stepper stp(2048,1,2,3,4);

void setup() {
  stp.setSpeed(12);
  stp.step(1024);
}

void loop() {


}
