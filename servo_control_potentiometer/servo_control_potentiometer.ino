#include <Servo.h>
#include "scale.h"

Scale adc_to_degrees(2, 178, 0, 1023);
Servo servo;

void setup()
{
  servo.attach(5);
  pinMode(A0, INPUT);
}

void loop()
{
  int adc = analogRead(A0);
  auto deg = adc_to_degrees.get_on_scale_a(adc);
  servo.write(deg);
  delay(10);
}
