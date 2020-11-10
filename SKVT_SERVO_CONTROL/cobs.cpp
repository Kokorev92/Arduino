#include "cobs.h"

namespace cobs {

size_t cobs_encode(const uint8_t* input_buffer, size_t length_input,
                   uint8_t* output_buffer, size_t length_output) {
    bool in_the_interval =
        (1 <= length_input) && (length_input <= cobs::MAX_DATA_SIZE);
    if (in_the_interval == false) {
        return 0;
    }

    if (length_output < length_input + 3) {
        return 0;
    }

    uint8_t index = 1;
    for (int16_t i = length_input - 1; i >= 0; i--) {
        if (input_buffer[i] != 0x00) {
            output_buffer[i + 2] = input_buffer[i];
        } else {
            output_buffer[i + 2] = index;
            index                = 0;
        }
        index++;
    }
    output_buffer[1] = index;
    output_buffer[0] = output_buffer[length_input + 2] = 0x00;

    return length_input + 3;
}

size_t cobs_decode(const uint8_t* input_buffer, size_t length_input,
                   uint8_t* output_buffer, size_t length_output) {
    bool in_the_interval =
        (4 <= length_input) && (length_input <= cobs::MAX_PACKET_SIZE);
    if (in_the_interval == false) {
        return 0;
    }
    //на ноль
    if (length_output < length_input - 3) {
        return 0;
    }

    if ((input_buffer[0] != 0x00) || (input_buffer[length_input - 1] != 0x00)) {
        return 0;
    }

    for (uint32_t i = 1; i < length_input - 1; i++) {
        if (input_buffer[i] == 0) {
            return 0;
        }
    }

    uint8_t  index = input_buffer[1];
    uint32_t sum   = index + 1;
    while (1) {
        sum += input_buffer[sum];
        if ((sum == length_input - 1)) {
            break;
        }

        if (sum > length_input - 1) {
            return 0;
        }
    }
    // 10 25 0 37 0 61 1 1 0
    // 0 3! 10 25 2! 37 4! 61 1 1 1! 0
    //	l = 12
    //	3 + 2 + 4 + 1 = 10 (l-2) ?
    // 10 25 37 61 1 1 0
    // 0 7! 10 25 37 61 1 1 1! 0
    //	l = 10
    //  7 + 1 = 8 (l - 2)

    for (uint32_t i = 0; i < length_input - 3; i++) {
        index--;
        if (index != 0) {
            output_buffer[i] = input_buffer[i + 2];
        } else {
            index            = input_buffer[i + 2];
            output_buffer[i] = 0x00;
        }
    }

    return length_input - 3;
}

bool Cobs_parser::add_bytes(uint8_t* buf, uint16_t size) {
    return Ring_buffer::add_bytes(buf, size);
}

bool Cobs_parser::check() {
    // Побайтовый парсинг содержимого буфера.
    // Остановится, когда буден найден валидный
    // пакет или закончатся непроверенные данные
    // в буфере.
    while (check_byte())
        ;
    // Возвращаем true, если был найден валидный пакет.
    return state_ == COBS_PARSER_STATE::HAS_PACKET;
}

cobs_packet_t Cobs_parser::get_packet() {
    if (state_ == COBS_PARSER_STATE::HAS_PACKET) {
        // Есть валидный пакет,
        // возвращаем его и переходим в
        // состояние NONE.
        state_ = COBS_PARSER_STATE::NONE;
        return tmp_packet_;
    }

    // Валидного пакета нет, поэтому
    // не меняем состояние и устанавлием
    // data_size пакета максимальным uint16_t
    tmp_packet_.data_size = -1;
    return tmp_packet_;
}

bool Cobs_parser::check_byte() {
    if ((get_size() - packet_size_) == 0) {
        // В буфере больше нет новых данных.
        return false;
    }
    switch (state_) {
        case COBS_PARSER_STATE::NONE:
            // В состоянии NONE считается, что в буфере нет готовых пакетов
            // и запись нового пакета не началась.

            if (is_end(ring_buffer(packet_size_++))) {
                // Если байт END, начинаем запись пакета.
                // Переходим в состояние PACKET.

                state_ = COBS_PARSER_STATE::PACKET;
            } else {
                // Если байт не END, остаёмся в состоянии NONE,
                // так как пакет может начинаться,
                // только с байта END.
                end_packet();
            }

            return true;

        case COBS_PARSER_STATE::PACKET:
            // В состоянии PACKET считается, что в буфере нет готовых пакетов,
            // пакет начался.

            if (is_end(ring_buffer(packet_size_++))) {
                if (decode()) {
                    // Если байт END и пакет валидный,
                    // заканчиваем запись текущего пакета.
                    // Считается, что в буфере теперь есть пакет.
                    // Переходим в HAS_PACKET.
                    end_packet();

                    state_ = COBS_PARSER_STATE::HAS_PACKET;
                    return false;
                } else {
                    // Если байт END и пакет не валидный,
                    // пакет затирается и начинается запись нового
                    // пакета. При этом текущий размер
                    // пакета сбрасывается до 1
                    // (в пакете уже есть байт END)
                    // И остаёмся в состоянии PACKET.
                    remove_bytes(packet_size_ - 1);
                    packet_size_ = 1;
                    return true;
                }
            }

            // Если текущий байт не END и достигнут максимальный размер
            // пакета, считается, что текущий пакет не валидный и он
            // затирается. Переходим в состояние NONE.
            if (packet_size_ == cobs_packet_max_size_c) {
                end_packet();

                state_ = COBS_PARSER_STATE::NONE;
            }

            // Текущий байт не END и не был достигнут максимальный размер
            // пакета, поэтому продолжаем запись текущего пакета.
            // Остаёмся в состоянии PACKET.
            return true;

        case COBS_PARSER_STATE::HAS_PACKET:
            return false;
    }
    return true;
}

bool Cobs_parser::decode() {
    tmp_packet_.data_size = 0;

    // В пакете нет данных
    if (packet_size_ <= cobs_overhead_bytes_c) {
        return false;
    }

    // буфер для декодированного пакета
    uint8_t* tmp_packet = reinterpret_cast<uint8_t*>(&tmp_packet_);

    // Проверим пакет на целостность.

    // 10 25 0 37 0 61 1 1 0
    // 0 3! 10 25 2! 37 4! 61 1 1 1! 0
    //	l = 12
    //	3 + 2 + 4 + 1 = 10 (l-2) ?
    // 10 25 37 61 1 1 0
    // 0 7! 10 25 37 61 1 1 1! 0
    //	l = 10
    //  7 + 1 = 8 (l - 2)

    uint8_t index = ring_buffer(1);
    uint16_t sum  = index + 1;
    while (1) {
        sum += ring_buffer(sum);
        if ((sum == packet_size_ - 1)) {
            break;
        }

        if (sum > packet_size_ - 1) {
            return false;
        }
    }

    // Собственно декодирование пакета.
    for (uint16_t i = 0; i < packet_size_ - cobs_overhead_bytes_c; i++) {
        index--;
        if (index != 0) {
            tmp_packet[i] = ring_buffer(i + 2);
        } else {
            index = ring_buffer(i + 2);
            tmp_packet[i] = 0x00;
        }
    }

    // Пакет успешно декодирован
    tmp_packet_.data_size = packet_size_ - cobs_overhead_bytes_c;
    return true;
}

}  // namespace cobs
