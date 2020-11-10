#include <TVout.h>
#include <fontALL.h>
TVout TV;

void setup() 
 {
    TV.begin(PAL,120,96);
    TV.select_font(font6x8);
    TV.println("I LOVE YULYA\n");
    TV.draw_line(10,10,50,50,"WHITE");
 }
 
void loop()
 {

 }
