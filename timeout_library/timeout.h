#pragma once

#include <stdint.h>
#include <Arduino.h>

namespace systools {

class Timeout {
  public:
    Timeout();

    Timeout(uint32_t timeout, bool enabled = true);

    bool expired() const;

    uint32_t get_remaining() const;

    void start();
    void stop();

    bool is_enabled() const;

  private:
    uint32_t timeout_;
    bool enable_;
    uint32_t start_time_;
    uint32_t end_time_;
};
}
