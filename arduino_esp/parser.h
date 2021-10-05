#pragma once

#include <stdint.h>
#include <unistd.h>

enum class STATE { IDLE = 0, GOT_HEADER, GOT_CMD, GOT_FOOTER, GOT_PACKET };

class Parser {
public:
    void add_byte(uint8_t byte);

    bool get_command(uint8_t& cmd);

private:
    uint8_t crc_          = 0;
    uint8_t cmd_          = 0;
    STATE   parser_state_ = STATE::IDLE;

    void calc_crc(uint8_t byte) {
        crc_ += byte;
    }
};
