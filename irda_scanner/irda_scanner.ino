#include <IRremote.h>
#include <IRremoteInt.h>

IRrecv resv(7);
decode_results result;

void setup() {
  Serial.begin(9600);
  resv.enableIRIn();
}

void loop() {
  if(resv.decode(&result)) {
    Serial.println(result.value, HEX);
    resv.resume();
  }
}
