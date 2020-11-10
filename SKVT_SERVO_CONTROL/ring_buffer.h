#pragma once

#include <stdint.h>

/**
\brief Кольцевой буфер. 

\tparam N - Размер кольцевого буфера.

\warning Размер кольцевого буфера должен быть степенью двойки.
 */
template <uint32_t N>
class Ring_buffer {
public:
    /**
    \brief Конструктор объекта Ring_buffer
    */

    explicit Ring_buffer() : begin_(0), size_(0) {}
    Ring_buffer(Ring_buffer const&) = delete;
    Ring_buffer& operator=(Ring_buffer const&) = delete;

    /**
    \brief Добавление байтов .

    \param buf - Указатель на буфер байтов.
    \param size - Количество байт, которые нужно добавить.

    \retval true - Все данные успешно добавлены.
    \retval false - Добавить данные не удалось, слишком много данных.
    */
    bool add_bytes(uint8_t* buf, uint16_t size) {
        if (max_size_ - size_ >= size) {
            // В буфере хватает места для записи данных.
            for (int i = 0; i < size; ++i) {
                write_byte(buf[i]);
            }
            // Данные успешно добавлены.
            return true;
        }

        // Данных слишком много.
        return false;
    }

    /**
    \brief Удаляет из буфера первые size байт.
    
    \param size - Количество байт, которые будут удалены из
    буфера.
     */
    void remove_bytes(uint32_t size) {
        begin_ += size;
        size_ -= size;
    }

    uint8_t& operator[](uint32_t index) {
        return ring_buffer(index);
    }

    /**
    \brief Возвращает текущий размер данных в буфере
     */
    uint32_t get_size() {
        return size_;
    }

    /**
    \brief Функция для обращения к кольцевому буферу.

    \param index - Индекс элемента кольцевого буфера
    относительно begin_.

    \return Элемент буфера с нужным индексом.
    */
    uint8_t& ring_buffer(uint32_t index);

private:
    /**
    \brief Записывает байт в кольцевой буфер.

    \param byte - Записываемый байт.
     */
    void write_byte(uint8_t byte) {
        ring_buffer(size_++) = byte;
    }

    /// Размер буфера.
    uint32_t max_size_ = N;

    /**
    \brief Константа для поддержания кольцевого буфера.

    Побитовое И с этой константой позволяет обеспечить пренадлежность 16 -
    битных индексов диапазону от 0 до max_size_ - 1.
    */
    uint32_t ring_ = N - 1;

    /// Кольцевой буфер.
    uint8_t buffer_[N];

    /// Индекс текущего начала буфера.
    uint32_t begin_;

    /// Текущий размер буфера.
    uint32_t size_;
};

template <>
uint8_t& Ring_buffer<256>::ring_buffer(uint32_t index);

template <>
uint8_t& Ring_buffer<65536>::ring_buffer(uint32_t index);

template <uint32_t N>
uint8_t& Ring_buffer<N>::ring_buffer(uint32_t index) {
    return buffer_[ring_ & (begin_ + index)];
}