#include <DHT.h>
#include <LiquidCrystal.h>

const int rs_pin = 2;
const int e_pin = 3;
const int data_pins[4] = {4, 5, 6, 7};

const int dht_pin = 8;

DHT dht(dht_pin, DHT11);
LiquidCrystal lcd(2, 3, data_pins[0], data_pins[1], data_pins[2], data_pins[3]);

void setup() {
  Serial.begin(9600);
  dht.begin();
  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
}

void loop() {
  delay(500);
  float temp = dht.readTemperature();
  float h = dht.readHumidity();

  lcd.setCursor(0, 0);
  lcd.print(h);
  lcd.print("% ");
  lcd.setCursor(0, 1);
  lcd.print(temp);
  lcd.print("C");
}
