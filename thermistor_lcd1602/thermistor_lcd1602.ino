#include <DHT.h>

#include <LiquidCrystal.h>

class Average {

  public:
    float add_value(float val) {
      stat_value_ = (stat_value_ * (float)(count_) + val) / ((float)(count_) + 1.0);
      count_++;
      return stat_value_;
    }

    float get_value() {
      return stat_value_;
    }

    void reset() {
      count_ = 0;
      stat_value_ = 0;
    }

  private:
    int count_ = 0;
    float stat_value_ = 0;

};

const int rs_pin = 2;
const int e_pin = 3;
const int data_pins[4] = {4, 5, 6, 7};

const int dht_pin = 8;

LiquidCrystal lcd(2, 3, data_pins[0], data_pins[1], data_pins[2], data_pins[3]);

Average average;

DHT dht(dht_pin, DHT11);

const byte tempPin = A0;
const int B =  3950; // B-коэффициент
const int SERIAL_R = 100000; // сопротивление последовательного резистора, 102 кОм
const int THERMISTOR_R = 100000; // номинальное сопротивления термистора, 100 кОм
const int NOMINAL_T = 25; // номинальная температура (при которой TR = 100 кОм)

void setup() {
  Serial.begin( 9600 );
  pinMode( tempPin, INPUT );
  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  dht.begin();
}

void loop() {
  lcd.setCursor(0, 0);
  for (int i = 0; i < 20; i++) {
    int t = analogRead( tempPin );
    float tr = 1023.0 / t - 1;
    tr = SERIAL_R / tr;

    float result = (1.0 / ((1.0 / (NOMINAL_T + 273.15)) + (1.0 / B) * log(tr / THERMISTOR_R))) - 273.15;
    average.add_value(result);
    delay(5);
  }
  lcd.print("TEMP: ");
  lcd.print(average.get_value());
  average.reset();

  float h = dht.readHumidity();
  float t = dht.readTemperature();

  lcd.setCursor(0, 1);
  lcd.print(h);
  lcd.print("% ");
  lcd.print(t);
  lcd.print("C");

  delay(1000);
}
