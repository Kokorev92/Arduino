#include <LiquidCrystal.h>

LiquidCrystal lcd(7,6,5,4,3,2);

void setup() {
  lcd.begin(16,2);
  Serial.begin(9600);  
}

void loop() {
  if (Serial.available()) {
    delay(100);
    // очистим экран
    lcd.clear();
    // считываем все символы
    while (Serial.available() > 0) {
      // выводим символы на экран
      int c = Serial.read();
      if(c != 0x00) {
        if((c == 0x0A) || (c == 0x0D)) {
          lcd.setCursor(0,1);
          continue;
        }
        lcd.write(c);
      }
    }
  }
}
