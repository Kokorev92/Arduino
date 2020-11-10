#include <SPI.h>
#include "nm025_regs.h"

uint8_t req_word[2];

void setup() {
  uint16_t cadr = ((0 | 0x000) << 5 | READ_MODE_2);
  cadr |= PARITY_BIT_NO;
  pinMode(11, OUTPUT);
  digitalWrite(11, LOW);
  pinMode(12, OUTPUT);
  digitalWrite(12, LOW);
  pinMode(13, OUTPUT);
  digitalWrite(13, LOW);

  memcpy(&req_word, &cadr, sizeof(cadr));
  Serial.begin(9600);
  pinMode(10, OUTPUT);
  SPI.begin();
  SPI.setClockDivider(SPI_CLOCK_DIV8);
  SPI.setDataMode(0);

  digitalWrite(10, LOW);
  SPI.transfer(req_word, sizeof(req_word));
//  SPI.transfer(req_word[1]);
//  SPI.transfer(req_word[0]);


  byte a = SPI.transfer(0);
  byte b = SPI.transfer(0);
  digitalWrite(10, HIGH);
//  Serial.println(cadr, HEX);
  Serial.println(req_word[1], HEX);
  Serial.println(req_word[0], HEX);

  Serial.println(a, HEX);
  Serial.println(b, HEX);
}

void loop() {

}
