#include "IRremote.h"

#define IR 10
#define relay 12

IRrecv ir(IR);
decode_results result;
int pinState = LOW;
void setup() {
  pinMode(relay, OUTPUT);
  digitalWrite(relay, pinState);
  ir.enableIRIn();
}

void loop() {
  if(ir.decode(&result)){
    int res = result.value;
    if (res==0x10EF) {
      digitalWrite(relay, HIGH);
      delay(100);
    }
  }

}
