static const uint8_t led = 13;

static uint32_t blink_len = 5000; // In ms
static const uint32_t max_blink = 5;
static uint32_t t = blink_len / max_blink;
static uint32_t start_time = 0;
static uint32_t n = 3;

void setup() {
  pinMode(led, OUTPUT);
  digitalWrite(led, LOW);
  start_time = millis();
}

void loop() {
  uint32_t current_time = millis();
  uint32_t delta_time = current_time - start_time;

  auto pos = delta_time / (t / 2);

  if((pos < n*2) && (pos % 2 == 0)){
    digitalWrite(led, HIGH);
  } else {
    digitalWrite(led, LOW);
  }

  if(delta_time >= blink_len){
    start_time = millis();
  }
}
