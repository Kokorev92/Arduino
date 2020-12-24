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

Average average;

const byte tempPin = A0;
const int B =  3950; // B-коэффициент
const int SERIAL_R = 100000; // сопротивление последовательного резистора, 102 кОм
const int THERMISTOR_R = 100000; // номинальное сопротивления термистора, 100 кОм
const int NOMINAL_T = 25; // номинальная температура (при которой TR = 100 кОм)

void setup() {
  Serial.begin( 9600 );
  pinMode( tempPin, INPUT );
}

void loop() {
  for (int i = 0; i < 20; i++) {
    int t = analogRead( tempPin );
    float tr = 1023.0 / t - 1;
    tr = SERIAL_R / tr;

    float result = (1.0 / ((1.0 / (NOMINAL_T + 273.15)) + (1.0 / B) * log(tr / THERMISTOR_R))) - 273.15;
    average.add_value(result);
    delay(5);
  }
//  Serial.print("T=");
  Serial.println(average.get_value());
  average.reset();
}
