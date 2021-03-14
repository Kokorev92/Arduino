#include <AFMotor.h>

AF_DCMotor front_right_motor(1);
AF_DCMotor rear_right_motor(2);
AF_DCMotor front_left_motor(3);
AF_DCMotor rear_left_motor(4);

AF_DCMotor all_motors[4] = {front_right_motor, rear_right_motor, front_left_motor, rear_left_motor};
AF_DCMotor right_motors[2] = {front_right_motor, rear_right_motor};
AF_DCMotor left_motors[2] = {front_left_motor, rear_left_motor};

void run_motors(int speed, int direction, AF_DCMotor *motors);

void setup() {
  run_motors(0, RELEASE, all_motors);
  Serial.begin(115200);
}

void loop() {
  if (Serial.available()) {
    uint8_t cmd = Serial.read();
    switch (cmd) {
      case 0x46:
        run_motors(255, FORWARD, all_motors);
        break;
      case 0x53:
        run_motors(0, RELEASE, all_motors);
        break;
      case 0x4C:
        run_motors(255, FORWARD, left_motors);
        run_motors(255, BACKWARD, right_motors);
        delay(1000);
        run_motors(0, RELEASE, all_motors);
        break;
    }
  }
}


void run_motors(int speed, int direction, AF_DCMotor *motors) {
  for (int i = 0; i < 4; i++) {
    motors[i].setSpeed(speed);
    motors[i].run(direction);
  }
}
