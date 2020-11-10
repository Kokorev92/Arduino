/**
\file
\brief Файл с определением функций cobs

Данный файл содержит в себе определение namespace cobs, который включает функции
для кодирования и декодирования массива данных в формат cobs.
 */

#pragma once

#include <stddef.h>
#include <stdint.h>

#include "ring_buffer.h"

namespace cobs {

/// max размер данных для енкода COBS пакета
static constexpr uint16_t MAX_DATA_SIZE = 128;

static constexpr uint16_t MAX_PACKET_SIZE = 131;  ///< max размер COBS пакета

/// при кодировании cobs-ом размер данных увеличивается на ADD_BYTES
static constexpr uint16_t ADD_BYTES = 3;

/**
\brief Функция преобразования в формат cobs.

\param[in] *input_buffer Указатель на входной буфер.\n
\param[in] length input Длина входного буфера (должна быть в интервале [1,254]).\n
\param[in] *output_buffer Указатель на выходной буфер \n 
\param[in] length_output Длина выходного буфер (должна быть в интервале [length_input + 3, +inf]) 
\return Фактическая длина выходного буфера в случае успешного выполнения\n 
\retval	0 - в случае неуспешного выполнения
 */
size_t cobs_encode(const uint8_t* input_buffer, size_t length_input,
                   uint8_t* output_buffer, size_t length_output);

/**
\brief Функция преобразования в формат cobs.

\param[in] *input_buffer Указатель на входной буфер.\n
\param[in] length input Длина входного буфера (должна быть в интервале [4,257]). \n 
\param[in] *output_buffer Указатель на выходной буфер \n 
\param[in] length_output Длина выходного буфер (должна быть в интервале [length_input - 3,+inf]) 
\return Фактическая длина выходного буфера в случае успешного выполнения \n 
\retval	0 - в случае неуспешного выполнения
 */
size_t cobs_decode(const uint8_t* input_buffer, size_t length_input,
                   uint8_t* output_buffer, size_t length_output);

/**
\brief Специальные символы протокола cobs.
 */
enum class COBS_SPEC_CHAR : uint8_t {
    END     = 0x00,  ///< Граница кадра.
};

/**
\brief Максимальный размер cobs-пакета.
 */
static constexpr uint16_t cobs_packet_max_size_c = 131;

/**
\brief Количество байт, которые добавляются при кодировании пакета.

0x00 в начале и конце (2 байта) + смещение первого нулевого символа
в кодируемом пакете (1 байт).
 */
static constexpr uint8_t cobs_overhead_bytes_c = 3;

/**
\brief Максимальный размер полезных данных в cobs-пакете.
 */
static constexpr uint16_t cobs_data_max_size_c =
    cobs_packet_max_size_c - cobs_overhead_bytes_c;

/**
\brief Размер кольцевого буфера в парсере.

\warning Должен быть степенью двойки!
\warning Должен быть >= cobs_packet_max_size_c!
 */
static constexpr uint16_t cobs_parser_buf_size_c = 256;

/**
\brief Структура для хранения полезных данных из cobs-пакета.
 */
struct cobs_packet_t {
    uint8_t data[cobs_data_max_size_c];
    uint16_t data_size;
} __attribute__((packed));

/**
\brief Парсер cobs-пакетов.

Границей COBS-кадра является уникальный флаг END (0x00).
Уникальность этого флага поддерживается следующим образом:
алгоритм кодирования данных заменяет каждый нулевой байт
исходных данных на байт положения следующего нуля. 
Последним нулевым байтом последовательности является нагрузочный
байт - разделитель (END). Разделительный байт остаётся неизменным.

Содержит кольцевой буфер байтов, в который добавляются
приходящие байты.

При запросе пакета возвращает первый найденный готовый пакет и
затирает его.
 */
class Cobs_parser : Ring_buffer<cobs_parser_buf_size_c> {
public:
    /**
    \brief Конструктор объекта Cobs_parser.
     */
    Cobs_parser()
        : packet_size_(0),
          state_(COBS_PARSER_STATE::NONE) {
        static_assert(cobs_parser_buf_size_c >= cobs_packet_max_size_c,
                      "cobs_parser_buf_size_c < cobs_packet_max_size_c");
    }

    /**
    \brief Добавление байтов для считывания.

    \param buf - Указатель на буфер байтов.
    \param size - Количество байт, которые нужно считыть.

    \retval true - Все данные успешно добавлены.
    \retval false - Добавить данные не удалось, слишком много данных.
    */
    bool add_bytes(uint8_t* buf, uint16_t size);

    /**
    \brief Проверяет, есть ли в парсере готовые пакеты.

    Заполняет текущий пакет, который будет возвращён функцией get_packet.
    При этом если check() будет вызвана несколько раз подряд,
    при вызове get_packet будет возвращён первый валидный пакет.
    Т.е. пока первый найденный готовый пакет не будет возвращён функцией
    get_packet, дальнейший парсинг производиться не будет
    (cм. тест cobs_tests:double_check).

    Если буфер парсера заполнен невалидными пакетами, вызов
    check удаляет весь мусор из буфера парсера до первого валидного пакета
    или до начала предположительно валидного пакета.
    Если валидных и начатых пакетов в буфере нет, то удаляются все данные из
    буфера парсера
    (см. тест cobs_tests:add_few_invalid_packet_with_overflow).

    \retval true - Пакеты есть.
    \retval false - Пакетов нет.
     */
    bool check();

    /**
    \brief Возвращает первый готовый пакет.

    \warning Перед использованием get_packet необходимо вызвать
    функцию check, так как именно она заполняет структуру, которая будет
    возвращена.

    \note Если у возвращённого пакета data_size > cobs_data_max_size_c, то
    пакет невалидный.
     */
    cobs_packet_t get_packet();

private:
    /**
    \brief Пытается дабавить байт к текущему пакету.

    \retval true - Байт добавлен.
    \retval false - Байт не добавлен (найден готовый пакет
    или нет данных в буфере).
     */
    bool check_byte();

    /**
    \brief Действия совершаемые при завершении считывания пакета.

    Вызывается, когда был успешно считан валидный пакет
    или был считан невалидный пакет и надо сбросить состояние в NONE.

    \note Зависит от текущего значения packet_size. Т.к. смещает
    индекс текущего начала буфера и изменяет текущий размер буфера
    на эту величину.
     */
    void end_packet() {
        remove_bytes(packet_size_);
        packet_size_ = 0;
    }

    /**
    \brief Проверяет, является ли байт граничным символом пакета.

    \param byte - Проверяемый байт.

    \retval true - Является граничным символом пакета.
    \return false - не вляется граничным символом пакета.
     */
    bool is_end(uint8_t byte) {
        return byte == static_cast<uint8_t>(COBS_SPEC_CHAR::END);
    }

    /**
    \brief Декодирование cobs-пакета.

    \note Считается, что пакет ограничен символами END,
    дополнительная проверка не проводится.

    \retval true - Пакет успешно декодирован.
    \retval false - При декодировании пакета возникли ошибки.
     */
    bool decode();

    /// Размер текущего пакета.
    uint16_t packet_size_;

    /// Возможные состояния парсера.
    enum class COBS_PARSER_STATE {
        NONE,    ///< Не было начала пакета.
        PACKET,  ///< Было встречено начало пакета.
        HAS_PACKET,  ///< В буфере есть минимум 1 готовый пакет.
    };


    /// Состояние парсера.
    COBS_PARSER_STATE state_;

    /// Текущий готовый пакет
    cobs_packet_t tmp_packet_;
};

}  // namespace cobs
