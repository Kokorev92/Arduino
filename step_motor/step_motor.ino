const int direction_pin = 4;
const int step_pin = 5;
const int enable_pin = 6;

const int ms_pins[] = {10, 11, 11};
bool ms_state[] = {false, false, false};

void setup() {
  pinMode(direction_pin, OUTPUT);
  pinMode(step_pin, OUTPUT);
  pinMode(enable_pin, OUTPUT);

  for (int i = 0; i < 3; i++) {
    pinMode(ms_pins[i], OUTPUT);
    digitalWrite(ms_pins[i], ms_state[i] ? HIGH:LOW);
  }

  digitalWrite(enable_pin, HIGH);
  digitalWrite(direction_pin, LOW);

  Serial.begin(9600);
}

void loop() {
  if (Serial.available() > 0) {
    char comm = Serial.read();
    
    switch (comm) {
      case 's':
        step_motor();
        Serial.println("Do step");
        break;
      case 'e':
        digitalWrite(enable_pin, LOW);
        Serial.println("Enabled");
        break;
      case 'd':
        digitalWrite(enable_pin, HIGH);
        Serial.println("Disabled");
        break;
      case 'l':
        digitalWrite(direction_pin, HIGH);
        Serial.println("Direction to left");
        break;
      case 'r':
        digitalWrite(direction_pin, LOW);
        Serial.println("Direction to right");
        break;
    }
  }
}

void step_motor() {
  digitalWrite(step_pin, HIGH);
  delayMicroseconds(500);
  digitalWrite(step_pin, LOW);
  delayMicroseconds(500);
}
