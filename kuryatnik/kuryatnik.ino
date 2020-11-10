#include <EEPROM.h>

const int led_pin = 13;
const int delay_time = 500;

int addres = 0;
int value = 0;

void setup() {
  Serial.begin(115200);
  pinMode(led_pin, OUTPUT);
  digitalWrite(led_pin, HIGH);
  delay(5000);
  while(addres < EEPROM.length()) {
    value = EEPROM.read(addres);
    Serial.print("Addres: ");
    Serial.print(String(addres));
    Serial.print(" value: ");
    Serial.println(String(value));
    addres++;
  }
}

void loop() {
  digitalWrite(led_pin, LOW);
  delay(delay_time);
  digitalWrite(led_pin, HIGH);
  delay(delay_time);
}
