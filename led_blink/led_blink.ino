#include <Servo.h>
#include <Arduino_FreeRTOS.h>

void TaskBlink(void *pvParameters);

const int OUT_PIN = 13;
const int servoPin = 11;

Servo servo1;

void setup() {
  pinMode(OUT_PIN, OUTPUT);
  digitalWrite(OUT_PIN, LOW);
  servo1.attach(servoPin);
  xTaskCreate(TaskBlink, (const char*)"Blink", 128, NULL, 2, NULL);
}

void loop() {

}

void TaskBlink(void *pvParameters) {
  (void)pvParameters;

  while(true) {
    digitalWrite(OUT_PIN, HIGH);
    servo1.write(45);
    delay(500);
    digitalWrite(OUT_PIN, LOW);
    servo1.write(90);
    delay(500);
  }
}
