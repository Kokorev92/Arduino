#include "parser.h"

void Parser::add_byte(uint8_t byte) {
    switch (parser_state_) {
        case STATE::IDLE: {
            crc_ = 0;
            if (byte == 0x3A) {
                calc_crc(byte);
                parser_state_ = STATE::GOT_HEADER;
            }
            break;
        }

        case STATE::GOT_HEADER: {
            calc_crc(byte);
            cmd_          = byte;
            parser_state_ = STATE::GOT_CMD;
            break;
        }

        case STATE::GOT_CMD: {
            if (byte == 0x21) {
                calc_crc(byte);
                parser_state_ = STATE::GOT_FOOTER;
            } else {
                parser_state_ = STATE::IDLE;
            }
            break;
        }

        case STATE::GOT_FOOTER: {
            if (byte == crc_) {
                parser_state_ = STATE::GOT_PACKET;
            } else {
                parser_state_ = STATE::IDLE;
            }
            break;
        }

        default:
            break;
    }
}

bool Parser::get_command(uint8_t& cmd) {
    if (parser_state_ == STATE::GOT_PACKET) {
        cmd           = cmd_;
        parser_state_ = STATE::IDLE;
        return true;
    }
    return false;
}
