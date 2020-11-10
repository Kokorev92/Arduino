#include <boarddefs.h>
#include <IRremote.h>
#include <IRremoteInt.h>
#include <ir_Lego_PF_BitStreamEncoder.h>
#include <Servo.h>

const int relay_pin = 28;
const int servo_pin = 7;
const int ir_pin = 30;

int relay_state = HIGH;

Servo serv1;
IRrecv irrecv(ir_pin);

decode_results results;


void setup() {
  serv1.attach(servo_pin);
  serv1.write(90);
  
  pinMode(relay_pin, OUTPUT);
  digitalWrite(relay_pin, relay_state);
  
  Serial.begin(9600); //DEBUGs
  
  irrecv.enableIRIn();
}

void loop() {
  if ( irrecv.decode( &results )) {
     Serial.println(results.value, HEX);
     
     switch(results.value) {
      case 0xFF10EF: 
        serv1.write(135);
        break;
      case 0xFF5AA5: 
        serv1.write(45);
        break;
      case 0xFF18E7: 
        serv1.write(90);
        break;
      case 0xFF38C7:
        relay_state = !relay_state;
        digitalWrite(relay_pin, relay_state);
        break;
     }
     
     irrecv.resume();
  }

}
