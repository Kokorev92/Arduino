enum class DIR {FORWARD = 1, BACK};

bool relay_1 = false;
bool relay_2 = false;

DIR direction = DIR::FORWARD;

void rotate_direction(DIR dir);

void setup()
{
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  digitalWrite(2, LOW);
  digitalWrite(3, LOW);
  Serial.begin(9600);
}

void loop()
{
  if (Serial.available() > 0) {
    auto b = Serial.read();

    switch (b) {
      case 'F': {
          rotate_direction(DIR::FORWARD);
          break;
        }
      case 'B': {
          rotate_direction(DIR::BACK);
          break;
        }
      default:
        break;
    }
  }
}

void rotate_direction(DIR dir) {
  if (dir == direction) {
    return;
  }
  switch (dir) {
    case DIR::FORWARD: {
        relay_1 = true;
        relay_2 = true;
        direction = DIR::FORWARD;
        break;
      }
    case DIR::BACK: {
        relay_1 = false;
        relay_2 = false;
        direction = DIR::BACK;
        break;
      }
    default:
      break;
  }

  digitalWrite(2, relay_1 ? LOW : HIGH);
  delay(200);
  digitalWrite(3, relay_2 ? LOW : HIGH);
}
