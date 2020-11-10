#include <IRremote.h>
#include <IRremoteInt.h>

const int IR_PIN = 7;
const int RELAY_PIN = 10;

IRrecv resv(IR_PIN);
decode_results result;

void setup() {
  Serial.begin(9600);
  resv.enableIRIn();
  pinMode(RELAY_PIN, OUTPUT);
}
int on = 0;
void loop() {
  if(resv.decode(&result)) {
    Serial.println(result.value, HEX);
    if(result.value == 0x20DF10EF) {
      on = !on;
      digitalWrite(RELAY_PIN,  on ? HIGH : LOW);
    }
    resv.resume();
  }
}
