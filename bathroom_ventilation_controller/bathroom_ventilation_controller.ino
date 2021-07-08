static const float TIME_M = 10;
static const int DELAY_TIME_MS = 1000 * 60 * TIME_M;

static const int START_BUTTON = 2;
static const int STOP_BUTTON = 3;
static const int RELAY = 4;

bool work = false;
uint32_t start_work_time;

auto ON = !HIGH;
auto OFF = !LOW;

void setup() {
  pinMode(RELAY, OUTPUT);
  digitalWrite(RELAY, OFF);
  pinMode(START_BUTTON, INPUT_PULLUP);
  pinMode(STOP_BUTTON, INPUT_PULLUP);
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
    if ((current_time - start_work_time) <= DELAY_TIME_MS) {
      digitalWrite(RELAY, ON);
    } else {
      work = false;
    }
  } else {
    digitalWrite(RELAY, OFF);
  }
}
