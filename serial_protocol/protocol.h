#pragma once
#include "HardwareSerial.h"

class Serial_protocol {
public:
  Serial_protocol(HardwareSerial& serial) : serial_(serial) {}
  ~Serial_protocol() = default;
private:
  HardwareSerial& serial_;
};
