#include <IRremote.h>
#include <IRremoteInt.h>

IRrecv resv(A0);
decode_results result;

void setup() {
  resv.enableIRIn();
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
}
int on2 = 0;
int on3 = 0;
int on4 = 0;

void loop() {
  if(resv.decode(&result)) {
//    Serial.println(result.value, HEX);
    if(result.value == 0x8C03F) {
      on2 = !on2;
      digitalWrite(2,  on2 ? HIGH : LOW);
    }
    if(result.value == 0x820DF) {
      on3 = !on3;
      digitalWrite(3,  on3 ? HIGH : LOW);
    }
    if(result.value == 0x8A05F) {
      on4 = !on4;
      digitalWrite(4,  on4 ? HIGH : LOW);
    }
    resv.resume();
  }
}
