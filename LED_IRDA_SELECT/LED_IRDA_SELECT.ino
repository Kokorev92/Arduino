#include <IRremote.h>
#include <IRremoteInt.h>

const int IR_PIN = 0;

IRrecv resv(IR_PIN);
decode_results result;

void setup() {
  for(int i=1; i<5; i++) {
    pinMode(i, OUTPUT);
    digitalWrite(i, LOW);
  }

  resv.enableIRIn();
}

void loop() {
  if(resv.decode(&result)) {
    if(result.value == 0x8C03F) {
      for(int i=1; i<2; i++){
        digitalWrite(i, HIGH);
      }
      for(int i=2; i<5; i++){
        digitalWrite(i, LOW);
      }
    } else

    if(result.value == 0x820DF) {
      for(int i=1; i<3; i++){
        digitalWrite(i, HIGH);
      }
      for(int i=3; i<5; i++){
        digitalWrite(i, LOW);
      }
    } else

    if(result.value == 0x8A05F) {
      for(int i=1; i<4; i++){
        digitalWrite(i, HIGH);
      }
      for(int i=4; i<5; i++){
        digitalWrite(i, LOW);
      }
    } else

    if(result.value == 0x8609F) {
      for(int i=1; i<5; i++){
        digitalWrite(i, HIGH);
      }
      for(int i=5; i<5; i++){
        digitalWrite(i, LOW);
      }
    } else 
    if(result.value ==0x830CF) {
      for(int i=1; i<5; i++){
        digitalWrite(i, LOW);
      }
    }
    resv.resume();
  }

  delay(50);
}
