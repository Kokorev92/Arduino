#include <IRremote.h>
#include <IRremoteInt.h>

const int IR_PIN = 2;
const int RELAY_PIN = 3;

IRrecv resv(IR_PIN);
decode_results result;

void setup() {
  resv.enableIRIn();
  pinMode(RELAY_PIN, OUTPUT);
  digitalWrite(RELAY_PIN, HIGH);
}
int on = 0;
void loop() {
  if (resv.decode(&result)) {
    if (result.value == 0xFF38C7) {
      on = !on;
      digitalWrite(RELAY_PIN,  on ? HIGH : LOW);
    }
    resv.resume();
  }
}
