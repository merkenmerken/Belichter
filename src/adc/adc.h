#ifndef ADC_H
#define ADC_H

#include "Std_Types.h"

#define ADC_BUFFER_MAX_CIRCULAR_VALUES 5U
#define ADC_BUFFER_MAX_DEVIATION 5U

#define ADC_START_CONV() (ADCSRA |= (1<<ADSC))
#define ADC_READY() (~(ADCSRA & (1<<ADIF)))

#define ADC_STOP() (ADCSRA &= ~(1U << ADEN))
#define ADC_START() (ADCSRA |= (1U << ADEN))



typedef enum{
    ADC0,
    ADC1,
    ADC2,
    ADC3,
    ADC4,
    ADC5,
    ADC6,
    ADC7,
    Reserved1,
    Reserved2,
    Reserved3,
    Reserved4,
    Reserved5,
    Reserved6,
    VBG,
    NULLVOLT,
    MAX_ADCS
}tAdConverter;

typedef enum{
    buffer_ok,
    buffer_nok,
    buffer_statMax
}tBufferStatus;

typedef struct{
    uint8_t nextpos;
    uint8_t buffer[ADC_BUFFER_MAX_CIRCULAR_VALUES];
}xCircularBuffer;

void adc_init(void);
tBufferStatus adc_circBufferGetFilteredValue(uint8_t* vValue);

#endif