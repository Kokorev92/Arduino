#include <IRremote.h>


IRrecv ir(10);
decode_results result;

int r = 0;
int g = 0;
int b = 0;
int redPin = 8;
int greenPin = 7;
int bluePin = 6;

void setup() {
  ir.enableIRIn();
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
}

void loop() {
  if(ir.decode(&result)) {
    if(result.value == 0x8C03F) {
      r = !r;
      digitalWrite(redPin, r ? HIGH : LOW);
    }
    if(result.value == 0x820DF) {
      g = !g;
      digitalWrite(greenPin, g ? HIGH : LOW);
    }
    if(result.value == 0x8A05F) {
      b = !b;
      digitalWrite(bluePin, b ? HIGH : LOW);
    }
    ir.resume();
  }
}
