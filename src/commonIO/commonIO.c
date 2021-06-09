#include "commonIO.h"
#include "uart_custom.h"



/**
 * @brief Specifies the pin number and the direction of the pin
 * 
 */
const PinConfiguration PIN_DefaultConfig[COMMONIO_MAX_PINS] = {
    {   PIN0,  PinDontCare},           /* PINB0 */
    {   PIN1,  PinOutput},          /* PINB1 */
    {   PIN2,  PinDontCare},        /* PINB2 */
    {   PIN3,  PinDontCare},        /* PINB3 */
    {   PIN4,  PinDontCare},        /* PINB4 */
    {   PIN5,  PinDontCare},        /* PINB5 */
    {   PIN6,  PinOutput},          /* PINB6 */
    {   PIN7,  PinOutput},          /* PINB7 */

    {   PIN0,  PinOutput},          /* PINC0 */
    {   PIN1,  PinOutput},          /* PINC1 */
    {   PIN2,  PinOutput},          /* PINC2 */
    {   PIN3,  PinOutput},          /* PINC3 */
    {   PIN4,  PinInput},           /* PINC4 */
    {   PIN5,  PinDontCare},           /* PINC5 */
    {   PIN6,  PinDontCare},        /* PINC6 */
    {   PIN7,  PinDontCare},        /* PINC7 */

    {   PIN0,  PinDontCare},        /* PIND0 */
    {   PIN1,  PinDontCare},        /* PIND1 */
    {   PIN2,  PinOutput},          /* PIND2 */
    {   PIN3,  PinOutput},          /* PIND3 */
    {   PIN4,  PinOutput},          /* PIND4 */
    {   PIN5,  PinOutput},          /* PIND5 */
    {   PIN6,  PinOutput},          /* PIND6 */
    {   PIN7,  PinDontCare}            /* PIND7 */
};

/**
 * @brief Private function to get a handle to the MCU ports
 * 
 * @param vPin 
 * @param pPortHandle Pointer to the porthandlepointer
 */
static void commonIO_getPortHandlePrivate(COMMONIO_PIN vPin, uint8_t **pPortHandle){ 

    if (PIN_MAX > vPin) //Check of input parameters
    {
        if (PORTB_END >= vPin)
        {
            *pPortHandle = ( uint8_t *)&PORTB;
        }
        else if (PORTC_END >= vPin)
        {
            *pPortHandle = ( uint8_t *)&PORTC;
        }
        else if (PORTD_END >= vPin)
        {
            *pPortHandle = ( uint8_t *)&PORTD;
        }
    }
    else
    {
        #ifdef DEBUG_COMMON_IO
            uart0_putErrorMsg();
        #endif
    }
}

/**
 * @brief Private function to get a handle to the MCU ports
 * 
 * @param vPin 
 * @param pPortHandle Pointer to the porthandlepointer
 */
static void commonIO_getDDRxHandlePrivate(COMMONIO_PIN vPin, uint8_t **pDirHandle){

    if (PIN_MAX > vPin) //Check of input parameters
    {
        if (PORTB_END >= vPin){ 
            *pDirHandle = ( uint8_t *)&DDRB;
        }
        else if (PORTC_END >= vPin)
        { 
            *pDirHandle = ( uint8_t *)&DDRC;
        }
        else if (PORTD_END >= vPin)
        { 
            *pDirHandle = ( uint8_t *)&DDRD;
        }
    }
    else
    {
        #ifdef DEBUG_COMMON_IO
            uart0_putErrorMsg();
        #endif
    }
}

/**
 * @brief Private function to get a handle to the MCU ports
 * 
 * @param vPin 
 * @param pPortHandle Pointer to the porthandlepointer
 */
static void commonIO_getPortPinHandlePrivate(COMMONIO_PIN vPin, uint8_t **pPortPinHandle){
    
    if (PIN_MAX > vPin) //Check of input parameters
    {
        if (PORTB_END >= vPin)
        {
            *pPortPinHandle = ( uint8_t *)&PINB;
        }
        else if (PORTC_END >= vPin)
        {
            *pPortPinHandle = ( uint8_t *)&PINC;
        }
        else if (PORTD_END >= vPin)
        {
            *pPortPinHandle = ( uint8_t *)&PIND;
        }
    }
    else
    {
        #ifdef DEBUG_COMMON_IO
            uart0_putErrorMsg();
        #endif
    }
}



void commonIO_setPin(COMMONIO_PIN vPin){
    if (PIN_MAX > vPin)   //Check of input parameters
    {
        uint8_t *pPortHandle;

        commonIO_getPortHandlePrivate(vPin, &pPortHandle);

        *pPortHandle |= (1U << PIN_DefaultConfig[vPin].vPinNum);
    }
    else
    {
        #ifdef DEBUG_COMMON_IO
            uart0_putErrorMsg();
        #endif
    }
}



void commonIO_clearPin(COMMONIO_PIN vPin){
    if (PIN_MAX > vPin)   //Check of input parameters
    {
        uint8_t *pPortHandle;

        commonIO_getPortHandlePrivate(vPin, &pPortHandle);

        *pPortHandle &= ~(1U << PIN_DefaultConfig[vPin].vPinNum);
    }
        else
    {
        #ifdef DEBUG_COMMON_IO
            uart0_putErrorMsg();
        #endif
    }
}



void commonIO_readPin(COMMONIO_PIN vPin, uint8_t* vPinLevel){
    if ((PIN_MAX > vPin)&&(PinInput == PIN_DefaultConfig[vPin].vDir))   //Check of input parameters
    {
        uint8_t *pPortHandle;
        uint8_t vTempLevel = 0U;
        commonIO_getPortPinHandlePrivate(vPin, &pPortHandle);

        vTempLevel = *pPortHandle & (1U << PIN_DefaultConfig[vPin].vPinNum);
        if (0!=vTempLevel)
        {
            vTempLevel = 1U;
        }
        *vPinLevel = vTempLevel;
    }
    else
    {
        #ifdef DEBUG_COMMON_IO
            uart0_putErrorMsg();
        #endif
    }
}



void commonIO_togglePin(COMMONIO_PIN vPin){
    if (PIN_MAX > vPin)   //Check of input parameters
    {
        uint8_t *pPortHandle;

        commonIO_getPortHandlePrivate(vPin, &pPortHandle);

        *pPortHandle ^= (1U << PIN_DefaultConfig[vPin].vPinNum);

    }
    else
    {
        #ifdef DEBUG_COMMON_IO
            uart0_putErrorMsg();
        #endif
    }
    
}



void commonIO_setPinLevel(COMMONIO_PIN vPin, COMMONIO_LEVEL vLevel){
    if ((PIN_MAX > vPin)&&(PinMaxLevel>vLevel))   //Check of input parameters
    {
        if (PinHigh == vLevel)
        {
            commonIO_setPin(vPin);
        }
        else
        {
            commonIO_clearPin(vPin);
        }
    }
    else
    {
        #ifdef DEBUG_COMMON_IO
            uart0_putErrorMsg();
        #endif
    }
    
}



void commonIO_setDir(COMMONIO_PIN vPin ,COMMONIO_DIR vDir){
    if ((PIN_MAX > vPin)&&(dirMaxValue>vDir))   //Check of input parameters
    {
        if (PinDontCare>vDir)
        {
            uint8_t *pPortHandle;
            commonIO_getDDRxHandlePrivate(vPin, &pPortHandle);
            *pPortHandle |= (vDir << PIN_DefaultConfig[vPin].vPinNum);
        }
        else
        {
            // Do nothing
        }        
    }
    else
    {
        #ifdef DEBUG_COMMON_IO
            uart0_putErrorMsg();
        #endif
    }
    
}





void commonIO_init(void){

    DDRB = 0;
    DDRC = 0;
    DDRD = 0;
    PORTB = 0;
    PORTC = 0;
    PORTD = 0;

    for(uint8_t reg = 0; reg < COMMONIO_MAX_PINS; reg++){
        commonIO_setDir(reg, PIN_DefaultConfig[reg].vDir);
    } 
}



