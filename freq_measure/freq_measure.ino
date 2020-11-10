uint32_t HTime;
uint32_t LTime;
double TTime;
double freq;

void setup() {
  pinMode(8, INPUT);
  Serial.begin(115200);
}

void loop() {
  HTime=pulseIn(8,HIGH);    // прочитать время высокого логического уровня
  LTime=pulseIn(8,LOW);     // прочитать время низкого логического уровня
    
  TTime = HTime+LTime;

  freq=1000000/TTime;  // получение частоты из Ttime в микросекундах
  Serial.write("\r");
  Serial.print((uint32_t)(freq));
//  Serial.write(" ");
//  Serial.print(HTime);
//  Serial.write(" ");
//  Serial.print(LTime);

  delay(100);
  
}
