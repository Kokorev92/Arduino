#include <TimerOne.h>

TimerOne timer;

void setup() {
  timer.initialize(0.5);
  timer.pwm(9, 512);
}

void loop() {

}
