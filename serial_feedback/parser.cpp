#include "parser.h"

void Parser::add_byte(uint8_t bt) {
    switch (parser_state_) {
        case STATE::IDLE: {
            crc_            = 0;
            payload_length_ = 0;
            data_counter_   = 0;

            if (bt == 0x3A) {
                calc_crc(bt);
                parser_state_ = STATE::GOT_HEADER;
            }
            break;
        }

        case STATE::GOT_HEADER: {
            if (bt != 0x00) {
                calc_crc(bt);
                payload_length_ = bt;
                parser_state_   = STATE::GOT_PAYLOAD_SIZE;
            } else {
                parser_state_ = STATE::IDLE;
            }
            break;
        }

        case STATE::GOT_PAYLOAD_SIZE: {
            buffer_[data_counter_++] = bt;
            calc_crc(bt);

            if (data_counter_ == payload_length_) {
                parser_state_ = STATE::GOT_PAYLOAD;
            }
            break;
        }

        case STATE::GOT_PAYLOAD: {
            if (bt == 0x21) {
                calc_crc(bt);
                parser_state_ = STATE::GOT_FOOTER;
            } else {
                parser_state_ = STATE::IDLE;
            }
            break;
        }

        case STATE::GOT_FOOTER: {
            if (bt == crc_) {
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

uint8_t Parser::get_data(uint8_t* data) {
    if (parser_state_ == STATE::GOT_PACKET) {
        memcpy(data, buffer_, payload_length_);
        parser_state_ = STATE::IDLE;
        return payload_length_;
    }

    return 0;
}
