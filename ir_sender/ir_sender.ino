#include <boarddefs.h>
#include <IRremote.h>
#include <IRremoteInt.h>
#include <ir_Lego_PF_BitStreamEncoder.h>

IRsend irsend;

void setup() {
  Serial.begin(9600);
}

void loop() {
  irsend.sendNEC(0x8C03F, 32);
  delay(250); 
}
