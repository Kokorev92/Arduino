#include <LiquidCrystal_I2C.h>
#include <DHT.h>

const int dht_pin = 8;

LiquidCrystal_I2C lcd(0x27, 16, 2);

DHT dht(dht_pin, DHT11);

void setup() {
  Serial.begin(9600);
  dht.begin();
  lcd.init();
  lcd.backlight();
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
