#include "timeout.h"

namespace systools {
Timeout::Timeout() : timeout_(0),
  enable_(false),
  start_time_(0),
  end_time_(0) {}

Timeout::Timeout(uint32_t timeout, bool enabled)
  : timeout_(timeout),
    enable_(enabled),
    start_time_(enabled ? millis() : 0),
    end_time_(start_time_ + timeout) {}

bool Timeout::expired() const {
  if (!enable_) {
    return true;
  }
  return get_remaining() == 0;
}

uint32_t Timeout::get_remaining() const {
  uint32_t current_time = millis();
  bool overflow_ = end_time_ < start_time_;

  if (overflow_) {
    if (end_time_ < current_time && current_time < start_time_) {
      return 0;
    }
  } else {
    if (current_time < start_time_ || end_time_ < current_time) {
      return 0;
    }
  }

  return end_time_ - current_time;
}

void Timeout::start() {
  enable_ = true;
  start_time_ = millis();
  end_time_ = start_time_ + timeout_;
}

void Timeout::stop() {
  enable_ = false;
}

bool Timeout::is_enabled() const {
  return enable_;
}

}
