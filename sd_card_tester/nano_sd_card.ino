#include <SD.h>
#include <LiquidCrystal_I2C.h>

static const int cs_pin = 4;
static bool sd_connected = false;
static uint32_t i = 0;
static const String file_name = "log.txt";

LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  lcd.init();
  lcd.backlight();

  pinMode(cs_pin, OUTPUT);

  if (SD.begin(cs_pin)) {
    lcd.print("SD card is open!");
    sd_connected = true;
    if (SD.exists(file_name)) {
      SD.remove(file_name);
    }
  } else {
    lcd.print("No SD card!");
  }
}

void loop() {

  if (i == 200) {
    lcd.setCursor(0, 1);
    lcd.print("Record stopped");
    while (true) {}
  }

  if (sd_connected) {
    File log_file = SD.open(file_name, FILE_WRITE);
    if (log_file) {
      log_file.println(i);
      lcd.setCursor(0, 1);
      lcd.print("Writen: ");
      lcd.print(i);
      log_file.close();
    }
  }

  i++;
  delay(250);
}
