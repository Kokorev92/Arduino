#include <Servo.h>
#include <Keypad.h>

Servo servo; 

const int srvo_pin = 11;
int start_position = 90;

const byte ROWS = 4;
const byte COLS = 4;

char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

byte rowPins[ROWS] = {14,15,16,17};
byte colPins[COLS] = {18,19,20,21};

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

void setup() {
  Serial.begin(9600);
  servo.attach(11);
  servo.write(start_position);
}

void loop() {
  char key = keypad.getKey(); 
  if(key) {
    Serial.println(key);
    switch(key) {
      case '4' :
        servo.write(start_position + 90);
        break;
      case '5' :
        servo.write(start_position);
        break;
      case '6' :
        servo.write(start_position - 90);
        break;
    }
  }                                       
}
