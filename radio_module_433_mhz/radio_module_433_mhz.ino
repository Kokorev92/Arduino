#include <RCSwitch.h>

RCSwitch radio = RCSwitch();

bool pin_state = false;

void setup() {
  pinMode(13, OUTPUT);
  digitalWrite(13, LOW);
  radio.enableTransmit(3);
  radio.enableReceive(0);
  Serial.begin(9600);
}

void loop() {
  radio.send(8, 4);

  if(radio.available()){
    int val = radio.getReceivedValue();
    Serial.println(val);
    if( val == 8) {
      digitalWrite(13, pin_state ? HIGH:LOW);
      pin_state != pin_state;
    }
  }

  delay(100);
}
