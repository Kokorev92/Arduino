#include <AFMotor.h>

#define get_size(array)(sizeof(array)/sizeof(*array))

AF_DCMotor front_right_motor(1);
AF_DCMotor rear_right_motor(2);
AF_DCMotor front_left_motor(3);
AF_DCMotor rear_left_motor(4);

AF_DCMotor *all_motors[4] = {&front_right_motor, &rear_right_motor, &front_left_motor, &rear_left_motor};
AF_DCMotor *right_motors[2] = {&front_right_motor, &rear_right_motor};
AF_DCMotor *left_motors[2] = {&front_left_motor, &rear_left_motor};

void run_motors(int speed, int direction, AF_DCMotor **motors, uint8_t size_arr);
void forward();
void backward();
void turn_to_left();
void turn_to_right();
void stopped();

void setup() {
  run_motors(0, RELEASE, all_motors, get_size(all_motors));
  Serial.begin(115200);
}

void loop() {
  delay(10);
  if (Serial.available()) {
    uint8_t cmd = Serial.read();
    switch (cmd) {
      case 0x46:
        forward();
        break;
      case 0x53:
        stopped();
        break;
      case 0x4C:
        turn_to_left();
        break;
      case 0x52:
        turn_to_right();
        break;
      case 0x42:
        backward();
        break;
      default:
        break;
    }
  }
}


void run_motors(int speed, int direction, AF_DCMotor **motors, uint8_t size_arr) {
  for (int i = 0; i < size_arr; i++) {
    motors[i]->setSpeed(speed);
    motors[i]->run(direction);
  }
}

void forward() {
  run_motors(0, RELEASE, all_motors, get_size(all_motors));
  run_motors(255, FORWARD, all_motors, get_size(all_motors));
}

void backward() {
  run_motors(0, RELEASE, all_motors, get_size(all_motors));
  run_motors(255, BACKWARD, all_motors, get_size(all_motors));
}

void turn_to_left() {
  run_motors(0, RELEASE, left_motors, get_size(left_motors));
  run_motors(255, FORWARD, right_motors, get_size(right_motors));
}

void turn_to_right() {
  run_motors(255, FORWARD, left_motors, get_size(left_motors));
  run_motors(0, RELEASE, right_motors, get_size(right_motors));
}

void stopped() {
  run_motors(0, RELEASE, all_motors, get_size(all_motors));
}
