#include <SD.h>
#include <DHT.h>

static const int CS = 4;
static const int dht_pin = 7;
static const int led_pin = 13;

DHT dht_sensor(dht_pin, DHT11);

void setup() {
  Serial.begin(9600);
  dht_sensor.begin();
  
  pinMode(CS, OUTPUT);

  SD.begin(CS);

  if (SD.exists("LOG.csv")) {
    SD.remove("LOG.csv");
  }
  File log_file = SD.open("LOG.csv", FILE_WRITE);
  if (log_file) {
    log_file.println("time;temperature;humidity");
    log_file.close();
  }
}

void loop() {
  uint32_t sec = millis() / 1000ul;
  auto hours = (sec / 3600ul) % 24;
  auto mins = (sec % 3600ul)  / 60ul;
  auto secs = (sec % 3600ul) % 60ul;
  
  float temp = dht_sensor.readTemperature();
  float humidity = dht_sensor.readHumidity();

  String log_string = String(hours) + ':' + String(mins) + ':' + String(secs) + ';' + String(temp) + ';' + String(humidity);
  File log_file = SD.open("LOG.csv", FILE_WRITE);

  if (log_file) {
    log_file.println(log_string);
    log_file.close();
  }

  delay(1000);
}
