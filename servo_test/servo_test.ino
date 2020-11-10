#include <Servo.h>

Servo serv;
void setup() {
  serv.attach(52);
  serv.write(0);
}

void loop() {
  delay(500);
  serv.write(0);
  delay(500);
  serv.write(90);
  delay(500);
  serv.write(180);

}
