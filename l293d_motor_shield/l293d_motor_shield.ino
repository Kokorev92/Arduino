#include <AFMotor.h>

AF_DCMotor front_right_motor(1);
AF_DCMotor rear_right_motor(2);
AF_DCMotor front_left_motor(3);
AF_DCMotor rear_left_motor(4);

AF_DCMotor motors[4] = {front_right_motor, rear_right_motor, front_left_motor, rear_left_motor};

void run_all_motors(int speed);

void setup() {
  run_all_motors(0, RELEASE);
  Serial.begin(115200);
}

void loop() {
  if(Serial.available()) {
    uint8_t cmd = Serial.read();
    switch(cmd) {
      case 0x46:
      run_all_motors(255, FORWARD);
      break;
      case 0x53:
      run_all_motors(0, RELEASE);
      break;
    }
  }
}


void run_all_motors(int speed, int direction){
  for(int i = 0; i < 4; i++) {
    motors[i].setSpeed(speed);
    motors[i].run(direction);
  }
}
