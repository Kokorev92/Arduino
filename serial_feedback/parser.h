#pragma once

#include <stdint.h>
#include <unistd.h>
#include <string.h>

enum class STATE {
  IDLE = 0,
  GOT_HEADER,
  GOT_PAYLOAD_SIZE,
  GOT_PAYLOAD,
  GOT_FOOTER,
  GOT_PACKET
};

class Parser {
  public:
    void add_byte(uint8_t bt);

    uint8_t get_data(uint8_t* data);

  private:
    uint8_t crc_ = 0;
    uint8_t buffer_[256];
    uint8_t payload_length_ = 0;
    uint8_t data_counter_   = 0;

    STATE parser_state_ = STATE::IDLE;

    void calc_crc(uint8_t bt) {
      crc_ += bt;
    }
};
