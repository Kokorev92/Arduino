#include <LiquidCrystal_I2C.h>
#include <DS1307RTC.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);
char clsstr[16] = {" "};

void setup() {
  lcd.init();
  lcd.backlight();
}

void loop() {
  tmElements_t tm;

  if (RTC.read(tm)) {
    lcd.setCursor(0, 0);
    lcd.print(clsstr);
    lcd.print(tm.Hour);
    lcd.print(":");
    lcd.print(tm.Minute);
    lcd.print(":");
    lcd.print(tm.Second);
  }

  delay(250);
}
