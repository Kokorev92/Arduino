//Цветной графический дисплей 2.8 TFT 320x240 UNO http://iarduino.ru/shop/Displei/cvetnoy-graficheskiy-displey-2-8-tft-320x240-uno-sensornyy.html

#include <UTFT.h>                              // подключаем библиотеку UTFT
UTFT myGLCD(TFT28UNO,A2,A1,A3,A4,A0);          // объявляем объект myGLCD класса библиотеки UTFT указывая тип дисплея TFT28UNO и номера выводов Arduino к которым подключён дисплей: RS, WR, CS, RST, SER. Выводы параллельной шины данных не указываются
                                               //
void setup(){                                  //
   myGLCD.InitLCD();                           // инициируем дисплей
}                                              //
                                               //
void loop(){                                   //
   myGLCD.clrScr();                            // стираем всю информацию с дисплея
                                               //
   myGLCD.setColor(VGA_RED);                   // Устанавливаем красный цвет
   myGLCD.drawLine(10,10,150,10);              // Рисуем линию (через точки с координатами 10x10 - 150x10)
                                               //
   myGLCD.setColor(VGA_GREEN);                 // Устанавливаем зелёный цвет
   myGLCD.drawRect(10,20,150,80);              // Рисуем прямоугольник (с противоположными углами в координатах 10x20 - 150x80)
                                               //
   myGLCD.setColor(VGA_BLUE);                  // Устанавливаем синий цвет
   myGLCD.drawRoundRect(10,90,150,160);        // Рисуем прямоугольник со скруглёнными углами (с противоположными углами в координатах 10x90 - 150x160)
                                               //
   myGLCD.setColor(VGA_LIME);                  // Устанавливаем лаймовый цвет
   myGLCD.fillRect(10,170,150,230);            // Рисуем закрашенный прямоугольник (с противоположными углами в координатах 10x170 - 150x230)
                                               //
   myGLCD.setColor(VGA_PURPLE);                // Устанавливаем фиолетовый цвет
   myGLCD.drawCircle(260,60,40);               // Рисуем окружность (с центром в точке 260x60 и радиусом 40)
   myGLCD.fillCircle(260,160,40);              // Рисуем закрашенную окружность (с центром в точке 260x160 и радиусом 40)
                                               //
   delay(20000);                               // ждём 20 секунд
}                                              //
