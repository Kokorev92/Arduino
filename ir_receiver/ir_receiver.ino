#include <Servo.h>

#include <boarddefs.h>
#include <IRremote.h>
#include <IRremoteInt.h>
#include <ir_Lego_PF_BitStreamEncoder.h>

IRrecv irrecv(3); // указываем вывод, к которому подключен приемник
Servo serv;

decode_results results;

const uint8_t relay_pin = 10;
int on = HIGH;

void setup() {
  serv.attach(5);
  serv.write(90);
  Serial.begin(9600); // выставляем скорость COM порта
  irrecv.enableIRIn(); // запускаем прием
  pinMode(relay_pin, OUTPUT);
  digitalWrite(relay_pin, on);
}

void loop() {
  if ( irrecv.decode( &results )) { // если данные пришли
    Serial.print( results.value, HEX ); // печатаем данные
    Serial.print( " , type: " );
    Serial.println( results.decode_type, HEX);
    if (results.value == 0xFF10EF) {
      serv.write(180);
    }

    if (results.value == 0xFF5AA5) {
      serv.write(0);
    }

    if (results.value == 0xFF18E7) {
      serv.write(90);
    }

    if (results.value == 0xFF38C7) {
      on = !on;
      digitalWrite(relay_pin, on);
    }
    irrecv.resume(); // принимаем следующую команду
  }
}
