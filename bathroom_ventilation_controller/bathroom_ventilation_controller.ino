static const int DELAY_TIME_MS = 5000;
bool work = false;
uint32_t start_work_time;

auto ON = !HIGH;
auto OFF = !LOW;

void setup() {
  pinMode(13, OUTPUT);
  pinMode(4, OUTPUT);
  digitalWrite(4, OFF);
  digitalWrite(13, LOW);
  pinMode(2, INPUT_PULLUP);
  pinMode(3, INPUT_PULLUP);
}

void loop() {
  if (!digitalRead(2)) {
    work = true;
    start_work_time = millis();
  }

  if(!digitalRead(3)){
    work = false;
  }

  if (work) {
    auto current_time = millis();
    if ((current_time - start_work_time) <= DELAY_TIME_MS) {
      digitalWrite(13, HIGH);
      digitalWrite(4, ON);
    } else {
      work = false;
    }
  } else {
    digitalWrite(13, LOW);
    digitalWrite(4, OFF);
  }
}
