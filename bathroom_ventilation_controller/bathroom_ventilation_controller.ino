#include "debug_print.h"

static const float TIME_M = 1;

static const int START_BUTTON = 2;
static const int STOP_BUTTON = 3;
static const int RELAY = 4;

bool work = false;
uint32_t start_work_time;
uint32_t delay_time_ms = 0;

auto ON = !HIGH;
auto OFF = !LOW;

void setup() {
  pinMode(RELAY, OUTPUT);
  digitalWrite(RELAY, OFF);
  pinMode(START_BUTTON, INPUT_PULLUP);
  pinMode(STOP_BUTTON, INPUT_PULLUP);
  delay_time_ms = TIME_M * 60 * 1000;
}

void loop() {
  if (!digitalRead(START_BUTTON)) {
    work = true;
    start_work_time = millis();
  }

  if (!digitalRead(STOP_BUTTON)) {
    work = false;
  }

  if (work) {
    auto current_time = millis();
    if ((current_time - start_work_time) <= delay_time_ms) {
      digitalWrite(RELAY, ON);
    } else {
      work = false;
    }
  } else {
    digitalWrite(RELAY, OFF);
  }

  delay(10);
}
