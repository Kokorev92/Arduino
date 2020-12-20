const int trig_pin = 2;
const int echo_pin = 3;

float distance = 0.0;

void setup() {
  pinMode(trig_pin, OUTPUT);
  pinMode(echo_pin, INPUT);
  digitalWrite(trig_pin, LOW);
  Serial.begin(9600);
}

void loop() {
  distance = get_distance(trig_pin, echo_pin);

  Serial.print(distance);
  Serial.println(" sm");
  delay(100);
}

float get_distance(int trig_pin, int echo_pin) {
  digitalWrite(trig_pin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig_pin, LOW);
  int duration = pulseIn(echo_pin, HIGH);

  return static_cast<float>(duration) / 58.0;
}
