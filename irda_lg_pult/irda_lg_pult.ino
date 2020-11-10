#include "IRremote.h"
#include "Servo.h"

IRrecv irrecv(10);
decode_results results;
Servo servoMain;

 
int servPoz = 90; //Начальное положение сервы
int lastPoz = 0;
 
void setup()
{
  Serial.begin(9600);
  irrecv.enableIRIn();
  servoMain.attach(12); // Servo присоединен к 12 выводу
  servoMain.write(servPoz);
}
 
void loop() {
  if (irrecv.decode(&results)) 
  {
    int res = results.value;
    Serial.println(res, HEX);
    if(res==0x40BF)// Если нажата кнопка "+"
    {
      lastPoz=res;
      servPoz=servPoz+5;  
      servoMain.write(servPoz);
    }
    else if(res==0xC03F)// Если нажата кнопка "-" 
    {
      servPoz=servPoz-5;
      lastPoz=res;
      servoMain.write(servPoz);
    }
    else if(res==0xFFFFFFFF)// Если кнопку удерживают
    {
      if(lastPoz==0x40BF) servPoz=servPoz+5;// Удерживают "+"
      if(lastPoz==0xC03F) servPoz=servPoz-5;// Удерживают "-"   
      servoMain.write(servPoz);
    }
    else if(res==0x10EF) {
      servPoz = 90; 
      lastPoz = 0;
      servoMain.write(servPoz);
    }
 
    irrecv.resume();
    delay(100);
  }
}
