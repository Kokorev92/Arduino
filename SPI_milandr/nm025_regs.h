#pragma once

namespace skvt {
// Маски для формирования кадров
#define READ_MODE_1		((uint16_t)1 << 13) // Режим чтения 1
#define READ_MODE_2		((uint16_t)0x3 << 14) // Режим чтения 2
#define PARITY_BIT_YES	((uint16_t)0x01) // Установить бит четности
#define PARITY_BIT_NO	((uint16_t)0x00) // Без бита четности
#define WRITE_MODE		((uint16_t)1 << 15) // Режим записи в регистр

// Регистры настройки 1310нм025
#define PLL_CONFIG		((uint16_t)0x0000) // Регистр настройки режимов тактирования микросхемы
#define AFE_CONFIG		((uint16_t)0x0002) // Регистр настройки аналоговых блоков
#define MODE_STAT		((uint16_t)0x0004) // Регистр общей настройки микросхемы
#define MASK			((uint16_t)0x0006) // Регистр маскирования MODE_STAT
#define Flags_delay		((uint16_t)0x0008)
#define TST_REG			((uint16_t)0x000A)
#define alive_cnt		((uint16_t)0x000C)
#define CMP_lh			((uint16_t)0x000E)

// Регистры преобразователя 1
#define C1Coord 		((uint16_t)0x0010) // Координата 1
#define C1Vel 			((uint16_t)0x0012) // Скорость 1
#define C1Stat 			((uint16_t)0x0014) // Флаги состояния преобразователя 1
#define C1Mask 			((uint16_t)0x0016) // Маска флагов состояния
#define C1Cntrl 		((uint16_t)0x0018) // Регистр режимов работы преобразователя 1
#define C1ResCntrl 		((uint16_t)0x001A)
#define C1Zero			((uint16_t)0x001C)
#define C1EXInc 		((uint16_t)0x001E) // Приращение фазы синусоидального сигнала на каждом такте ЦАП
#define C1KampS 		((uint16_t)0x0020)
#define C1KampC 		((uint16_t)0x0022)
#define C1KbiasS		((uint16_t)0x0024)
#define C1KbiasC 		((uint16_t)0x0026)
#define C1fbias 		((uint16_t)0x0028)
#define C1InDelay		((uint16_t)0x002A)
#define C1ExPhShft 		((uint16_t)0x002C)
#define C1Amp_metric	((uint16_t)0x003A)
#define C1Err_metric	((uint16_t)0x003E)
#define C1Lock_th       ((uint16_t)0x004E)
#define C1Amp_lth       ((uint16_t)0x0040)

// Регистры преобразователя 2
#define C2Coord 		((uint16_t)0x0050) // Координата 2
#define C2Vel 			((uint16_t)0x0052) // Скорость 2
#define C2Stat 			((uint16_t)0x0054) // Флаги состояния преобразователя 2
#define C2Mask 			((uint16_t)0x0056) // Маска флагов состояния
#define C2Cntrl 		((uint16_t)0x0058) // Регистр режимов работы преобразователя 2
#define C2ResCntrl 		((uint16_t)0x005A)
#define C2Zero 			((uint16_t)0x005C)
#define C2EXInc 		((uint16_t)0x005E) // Приращение фазы синусоидального сигнала на каждом такте ЦАП
#define C2KampS 		((uint16_t)0x0060)
#define C2KampC 		((uint16_t)0x0062)
#define C2KbiasS		((uint16_t)0x0064)
#define C2KbiasC 		((uint16_t)0x0066)
#define C2fbias 		((uint16_t)0x0068)
#define C2InDelay		((uint16_t)0x006A)
#define C2ExPhShft 		((uint16_t)0x006C)

// Биты регистра AFE_CONFIG
#define OSC_DIS			((uint16_t)0x8000) // Отключение подачи тактового сигнала на микросхему
#define OSC_BYP			((uint16_t)0x4000) // Отключение тактового генератора
#define ADC_CAL			((uint16_t)0x0400) // Калибровка АЦП
#define EXI2_inv		((uint16_t)0x0200) // Инверсия входа EXI2
#define EXI1_inv		((uint16_t)0x0100) // Инверсия входа EXI1
#define DAC2_en			((uint16_t)0x0080) // Включение ЦАП канал 2
#define DAC1_en			((uint16_t)0x0040) // Включение ЦАП канал 1
#define OPA2_en			((uint16_t)0x0020) // Включение входных операционных усилителей преобразователя 2
#define OPA1_en			((uint16_t)0x0010) // Включение входных операционных усилителей преобразователя 1
#define NDIFF_OFF		((uint16_t)0x0008) // Отключение N-канальной дифференциальной пары операционных усилителей
#define OFFSET_LOW		((uint16_t)0x0004) // Выбора пониженного напряжения выхода VREF1p25
#define EXT_RES_iREF	((uint16_t)0x0002) // Источник опорного тока
#define VREF_en			((uint16_t)0x0001) // Включение источника опорного напряжения

// Биты регистра Mode_stat (младшие 8 бит - флаги готовности)
#define SPI_CRC_en		((uint16_t)0x8000) // Включение бита четности CRC
#define Mode_2			((uint16_t)0x4000) // Выбор режима работы преобразователя 2 бит
#define Mode_1			((uint16_t)0x2000) // Выбор режима работы преобразователя 1 бит
#define Mode_0			((uint16_t)0x1000) // Выбор режима работы преобразователя 0 бит
#define CONV2_en		((uint16_t)0x0800) // Включение преобразователя 2
#define CONV1_en		((uint16_t)0x0400) // Включение преобразователя 1
#define Sample_src_1	((uint16_t)0x0200) // Выбор строба для выборки данных в SPI бит 1
#define Sample_src_0	((uint16_t)0x0100) // Выбор строба для выборки данных в SPI бит 0
#define PLL_not_DRY		((uint16_t)0x0040) // Флаг готовности ФАПЧ тактовой частоты
#define SPI_err			((uint16_t)0x0010) // Флаг ошибки при передаче по SPI
#define ECC_err			((uint16_t)0x0008) // Ошибка контроля четности. Внутренняя ошибка микросхемы
#define Not_equal		((uint16_t)0x0004) // Результаты преобразований не совпадают
#define nReady_2		((uint16_t)0x0002) // Преобразователь 2 готов
#define nReady_1		((uint16_t)0x0001) // Преобразователь 1 готов

// Биты регистра Mask
#define MSK_PLL_not_RDY	((uint16_t)0x0040) // Маска для бита PLL_not_RDY
#define MSK_SPI_err		((uint16_t)0x0010) // Маска для бита SPI_err
#define MSK_ECC_err		((uint16_t)0x0008) // Маска для бита ECC_err
#define MSK_Not_equal	((uint16_t)0x0004) // Маска для бита Not_Equal
#define MSK_nReady2		((uint16_t)0x0002) // Маска для бита nReady2
#define MSK_nReady1		((uint16_t)0x0001) // Маска для бита nReady1

// Структура битовых полей регистра PLL_CONFIG
struct pll_cfg{
    uint16_t PLL_N :7;
    uint16_t PLL_Q :4;
    uint16_t ADC_cycle :5;
} __attribute__((packed));

// Структура регистров общей настройки микросхемы
struct CP_CFG_TypeDef{
    pll_cfg PLL;
    uint16_t AFE;
    uint16_t MODE;
    uint16_t MODE_MASK;
};

// Битовые поля регистра C1Cntrl и C2Cntrl
struct ConCntrl{
    uint16_t LBW :5;
    uint16_t bit_5 :1;
    uint16_t Sensor_mode :2;
    uint16_t bit_8 :1;
    uint16_t DC_correction :1;
    uint16_t DC_carrier :1;
    uint16_t EX_Source :2;
    uint16_t EX_Recovery_en :1;
    uint16_t EX_Amp :1;
    uint16_t EX_on :1;
} __attribute__((packed));

// Структура
struct ConResCntrl{
    uint16_t Coord_resolution :4;
    uint16_t Vel_hist :1;
    uint16_t Dir_out_en :1;
    uint16_t SPI_ext_en :1;
    uint16_t Coord_hist :1;
    uint16_t Vel_resolution :4;
    uint16_t Enc_presc :3;
    uint16_t Enc_en :1;
} __attribute__((packed));

// Структура с регистрами настройки конвертера
struct CONV_CNTRL_TypeDef{
    ConCntrl Cntrl;
    ConResCntrl ResCntrl;
    uint16_t EXInc;
};

// Структура регистра MODE_STAT - младшие 8 бит
struct CHIP_STATUS_TypeDef{
    uint16_t nReady1 :1;
    uint16_t nready2 :1;
    uint16_t Not_Equal :1;
    uint16_t ECC_Err :1;
    uint16_t SPI_Err :1;
    uint16_t not_use_bit :1;
    uint16_t PLL_not_dry :1;
    uint16_t not_use_bit_2 :1;
} __attribute__((packed));

}
