#include "timeout.h"

systools::Timeout timeout(500, false);

int pin_state = 0;

void setup() {
  pinMode(13, OUTPUT);
  digitalWrite(13, LOW);
  timeout.start();
}

void loop() {
  if(timeout.expired()){
    pin_state = !pin_state;
    digitalWrite(13, pin_state ? LOW : HIGH);
    timeout.start();
  }
}
