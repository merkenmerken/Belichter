
#include "adc.h"
#include <avr/interrupt.h>
#include "uart_custom.h"



xCircularBuffer ADC_buffer;

/**
 * @brief Initialization of the circular buffer
 * 
 * @param pBuffer pointer to the buffer which should be initialized
 */
static void adc_circBufferInit(xCircularBuffer* pBuffer){

    if (pBuffer != 0U)
    {
        pBuffer->nextpos = 0;
        // pBuffer->filteredValue = 0U;
        for (uint8_t i = 0; i < ADC_BUFFER_MAX_CIRCULAR_VALUES; i++)
        {
            pBuffer->buffer[i] = 0U;
        }
    }
    else
    {
        uart0_putErrorMsg();
    }
}



/**
 * @brief ADC Init
 * 
 */
void adc_init(void){

    ADMUX = (0<<REFS1) | (0<<REFS0) | (1<<ADLAR) | ADC4; 
    ADCSRA = (1<<ADEN) | (1<<ADSC) | (0<<ADFR) | (0<<ADIF) | (1<<ADIE) | (0<<ADPS2) | (1<<ADPS1) | (0<<ADPS0);

    adc_circBufferInit( &ADC_buffer);
}



/**
 * @brief Put a new value on the circular buffer of the adc
 * 
 * @param pBuffer pointer to the circular buffer
 * @param vValue new ad value
 */
static void adc_circBufferPutValue(xCircularBuffer* pBuffer, uint8_t vValue){

    if (pBuffer != 0U)
    {
        pBuffer->buffer[pBuffer->nextpos] = vValue;

        pBuffer->nextpos++;

        if (pBuffer->nextpos >= ADC_BUFFER_MAX_CIRCULAR_VALUES)
        {
            pBuffer->nextpos = 0;
        }
    }
    else
    {
        uart0_putErrorMsg();
    }

}

/**
 * @brief This function checks the deviation of the array values. 
 * If the deviation is not greater than ADC_BUFFER_MAX_DEVIATION, the average value will be returned to the pointed variable vValue.
 * If everything was ok, buffer_ok will be returned. Else buffer_nok will be returned.
 * 
 * @param vValue 
 * @return tBufferStatus 
 */
tBufferStatus adc_circBufferGetFilteredValue(uint8_t* vValue){

    tBufferStatus vReturn = buffer_nok;
    xCircularBuffer* pBuffer = &ADC_buffer;

    if ((pBuffer != 0U)&&(vValue != 0U))
    {
        // Stop ad converter to not mess up the result
        ADC_STOP();
        uint16_t vtempBuffer = 0U;
        uint8_t vtempMinValue = pBuffer->buffer[0];
        uint8_t vtempMaxValue = pBuffer->buffer[0];


        // Get min and max values out of the buffer and add up all values to get an average value
        for (uint8_t i = 0; i < ADC_BUFFER_MAX_CIRCULAR_VALUES; i++)
        {
            vtempBuffer +=pBuffer->buffer[i];
            if (vtempMinValue > pBuffer->buffer[i])
            {
                vtempMinValue = pBuffer->buffer[i];
            }
            else if (vtempMaxValue < pBuffer->buffer[i])
            {
                vtempMaxValue = pBuffer->buffer[i];
            }
        }

        // Start ad converter after the last access to the buffer
        ADC_START();
        
        // Check if deviation is ok and calculate the average value.
        if ((vtempMaxValue-vtempMinValue) < ADC_BUFFER_MAX_DEVIATION)
        {
            *vValue = (uint8_t)(vtempBuffer/ADC_BUFFER_MAX_CIRCULAR_VALUES);
            vReturn = buffer_ok;
        }
        else
        {
            *vValue = 0U;
        }
    }
    else
    {
        uart0_putErrorMsg();
    }

    return vReturn;
}



/**
 * @brief Construct a new ISR object
 * ADC Interrupt
 * 
 */
ISR(ADC_vect){

    adc_circBufferPutValue(&ADC_buffer, ADCH);

}