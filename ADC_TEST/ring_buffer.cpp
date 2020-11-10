#include "ring_buffer.h"

template <>
uint8_t& Ring_buffer<256>::ring_buffer(uint32_t index) {
    return buffer_[static_cast<uint8_t>(begin_ + index)];
}

template <>
uint8_t& Ring_buffer<65536>::ring_buffer(uint32_t index) {
    return buffer_[static_cast<uint16_t>(begin_ + index)];
}
