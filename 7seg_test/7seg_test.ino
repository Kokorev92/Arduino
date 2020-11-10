int firstPin = 2;
int lastPin = 8;
int j = 0;
int buttonPin = 10;
bool buttonPush = false;

byte nums[10] = {
  0b00000110,
  0b01011011,
  0b01001111,
  0b01100110,
  0b01101101,
  0b01111101,
  0b00000111,
  0b01111111,
  0b01101111,
  0b00111111,
};

void button_press(){
  if(j == 10) {
    j = 0;
  }
  for (int i = 0; i < 7; i++){
    bool segment = bitRead(nums[j],i);
    digitalWrite(i+firstPin, segment);
  }
  j++;
}

void setup() {
  for (int i = firstPin; i < lastPin+1; i++){
    pinMode(i, OUTPUT);
    digitalWrite(i, LOW);
  }
  pinMode(buttonPin, INPUT_PULLUP);
  digitalWrite(buttonPin, HIGH);
  pinMode(13, OUTPUT);
  digitalWrite(13, LOW);
}

void loop() {
  if (digitalRead(buttonPin) == HIGH && !buttonPush){
    buttonPush = true;
  }

  if(digitalRead(buttonPin) == LOW && buttonPush){
    buttonPush = false;
    button_press();
  }
  delay(50);
}
