#include <LiquidCrystal_I2C.h>
#include <DHT.h>
#include <SD.h>

const uint8_t dht_pin = 8;
const uint8_t light_pin = A0;
const uint8_t cs_pin = 10;
const uint8_t lcd_width = 16;
const uint8_t lcd_lines = 2;

static uint32_t prev_time = 0;
static uint32_t curr_time = 0;

LiquidCrystal_I2C lcd(0x27, lcd_width, lcd_lines);

DHT dht(dht_pin, DHT11);

void setup() {
  pinMode(light_pin, INPUT);
  pinMode(cs_pin, OUTPUT);

  lcd.init();
  lcd.backlight();
  dht.begin();
  //  Serial.begin(19200);
  SD.begin(cs_pin);

  if (SD.exists("log.csv")) {
    SD.remove("log.csv");
  }

  File log_file = SD.open("log.csv", FILE_WRITE);
  if (log_file) {
    log_file.println("time;temp;humd;light");
    log_file.close();
  }
}

void loop() {
  curr_time = millis();
  uint32_t sec = curr_time / 1000ul;

  auto hours = (sec / 3600ul) % 24;
  auto mins = (sec % 3600ul)  / 60ul;
  auto secs = (sec % 3600ul) % 60ul;

  int temperature = dht.readTemperature();
  int humidity = dht.readHumidity();
  int light = analogRead(light_pin);

  //  Serial.println(curr_time);
  //  Serial.println(prev_time);
  //  Serial.println(curr_time - prev_time);
  //  Serial.println("-------------");
  if ((curr_time - prev_time) >= 10000) {
    String log_string = String(hours) + ':' + String(mins) + ':' + String(secs) + ';' + String(temperature) + ';' + String(humidity) + ';' + String(light);

    File log_file = SD.open("log.csv", FILE_WRITE);
    if (log_file) {
      log_file.println(log_string);
      log_file.close();
    }
    prev_time = curr_time;
  }

  String temp_string = "T:" + String(temperature) + "C";
  String hum_string = "H:" + String(humidity) + "%";
  String light_string = "L:" + String(light);
  String time_string = String(hours) + ':' + String(mins) + ':' + String(secs);

  int hum_str_len = hum_string.length();
  int temp_str_len = temp_string.length();
  int light_str_len = light_string.length();
  int time_str_len = time_string.length();

  int temp_str_pos = (hum_str_len + (lcd_width - (hum_str_len + temp_str_len)));
  int time_str_pos =  (light_str_len + (lcd_width - (light_str_len + time_str_len)));

  lcd.setCursor(0, 0);
  lcd.print(hum_string);
  lcd.setCursor(temp_str_pos, 0);
  lcd.print(temp_string);
  lcd.setCursor(0, 1);
  lcd.print(light_string);
  lcd.setCursor(time_str_pos, 1);
  lcd.print(time_string);

  delay(100);
}
