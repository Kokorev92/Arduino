
#include <TFT.h>                 // Подключаем библиотеку TFT  
#include <SPI.h>                 // Подключаем библиотеку SPI

const int cs = 9;                  // Указываем пины cs
const int dc = 8;                   // Указываем пины dc (A0)
const int rst = 7;                   // Указываем пины reset

uint8_t count = 0;

TFT TFTscreen = TFT(cs, dc, rst);

void setup()
{
  TFTscreen.begin();
  TFTscreen.background(0, 0, 0); // Очистим экран дисплея
  TFTscreen.setTextSize(2);      // Устанавливаем размер шрифта
  /*
    Установка цвета фона TFTscreen.background ( r , g , b )
    где, r, g и b являются значениями RGB для заданного цвета
  */
  TFTscreen.background ( 0 , 0 , 0 );
  /*
    Команда установки цвета фона TFTscreen.stroke ( r , g , b )
    где, r, g и b являются значениями RGB для заданного цвета
  */
  TFTscreen.stroke(0, 255, 0);
  /*
     Вывод текста на дисплей TFTscreen.text("Hello, World!", x, y);
     где x и y координаты.
  */
  TFTscreen.text("Test app!", 0, 2);
  int h = TFTscreen.height();
  int w = TFTscreen.width();
  String str = "Height: ";
  str += h;
  char buff[50];
  str.toCharArray(buff, 50);
  TFTscreen.stroke(0, 255, 255);
  TFTscreen.text(buff, 0, 40);
  str = "Width: ";
  str += w;
  str.toCharArray(buff, 50);
  TFTscreen.text(buff, 0, 60);
  delay(5000);
  TFTscreen.fillScreen(TFTscreen.newColor(0, 0, 0));
}

void loop()
{
  uint8_t prev_pos = 0;
  TFTscreen.point(count, 75);
  if (count >= 162) {
    count = 0;
  } else {
    prev_pos = count;
    count++;
  }
  delay(10);
  //  TFTscreen.fillScreen(TFTscreen.newColor(0, 0, 0));
  TFTscreen.stroke(0, 0, 0);
  TFTscreen.point(prev_pos, 75);
  TFTscreen.stroke(0, 255, 255);
}
