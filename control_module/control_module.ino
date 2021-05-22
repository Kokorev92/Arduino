#include <DHT.h>
#include <LiquidCrystal.h>

static const int rs_pin = 2;
static const int e_pin = 3;
static const int data_pins[4] = {4, 5, 6, 7};
static const int RELAY_1 = A3;

const int dht_pin = 8;

DHT dht(dht_pin, DHT11);
LiquidCrystal lcd(2, 3, data_pins[0], data_pins[1], data_pins[2], data_pins[3]);

void setup() {
  pinMode(RELAY_1, OUTPUT);
  digitalWrite(RELAY_1, HIGH);
  Serial.begin(9600);
  dht.begin();
  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
}
uint8_t b;

void loop() {
  if (Serial.available() > 0) {
    b = Serial.read();
  }

  if (b == 0x4F) {
    digitalWrite(RELAY_1, LOW);
  }
  if (b == 0x46) {
    digitalWrite(RELAY_1, HIGH);
  }
  
  float temp = dht.readTemperature();
  float h = dht.readHumidity();
  int relay_state = digitalRead(RELAY_1);

  lcd.setCursor(0, 0);
  lcd.print(h);
  lcd.print("% ");
  lcd.print(relay_state ? "OFF" : "ON ");
  lcd.setCursor(0, 1);
  lcd.print(temp);
  lcd.print("C");

  delay(50);
}
