#ifndef COMMONIO
#define COMMONIO

#ifndef atmega8
#define atmega8
#endif

#include "avr/io.h"

#define DEBUG_COMMON_IO 1

#define COMMONIO_MAX_PINS 24


typedef enum{
    PIN_B0,
    PIN_B1,
    PIN_B2,
    PIN_B3,
    PIN_B4,
    PIN_B5,
    PIN_B6,
    PIN_B7,
    PORTB_END = PIN_B7,
    PIN_C0,
    PIN_C1,
    PIN_C2,
    PIN_C3,
    PIN_C4,
    PIN_C5,
    PIN_C6,
    PIN_C7,
    PORTC_END = PIN_C7,
    PIN_D0,
    PIN_D1,
    PIN_D2,
    PIN_D3,
    PIN_D4,
    PIN_D5,
    PIN_D6,
    PIN_D7,
    PORTD_END = PIN_D7,
    PIN_MAX
}COMMONIO_PIN;

typedef enum{
    PinInput,
    PinOutput,
    PinDontCare,
    dirMaxValue
}COMMONIO_DIR;

typedef enum{
    PinLow,
    PinHigh,
    PinMaxLevel
}COMMONIO_LEVEL;

typedef struct {
    uint8_t Pin_0 : 1;
    uint8_t Pin_1 : 1;
    uint8_t Pin_2 : 1;
    uint8_t Pin_3 : 1;
    uint8_t Pin_4 : 1;
    uint8_t Pin_5 : 1;
    uint8_t Pin_6 : 1;
    uint8_t Pin_7 : 1;
}Portpacket;

typedef struct {
    uint8_t vPinNum;
    COMMONIO_DIR vDir;
}PinConfiguration;

/**
 * @brief Set pin number of type COMMONIO_PIN instantly
 * 
 * @param vPin 
 */
void commonIO_setPin(COMMONIO_PIN vPin);

/**
 * @brief Clear pin number of type COMMONIO_PIN instantly
 * 
 * @param vPin 
 */
void commonIO_clearPin(COMMONIO_PIN vPin);

/**
 * @brief Read pin level and return it to vPinLevel
 * 
 * @param vPin 
 * @param vPinLevel 
 */
void commonIO_readPin(COMMONIO_PIN vPin, uint8_t* vPinLevel);

/**
 * @brief Toggle pin number of type COMMONIO_PIN instantly
 * 
 * @param vPin 
 */
void commonIO_togglePin(COMMONIO_PIN vPin);

/**
 * @brief Set or clear pin number of type COMMONIO_PIN to instantly
 * 
 * @param vPin Pin number
 * @param vLevel High or Low
 */
void commonIO_setPinLevel(COMMONIO_PIN vPin, COMMONIO_LEVEL vLevel);

/**
 * @brief Set the direction of the pin vPin on the port
 * 
 * @param vPin 
 * @param vDir 
 */
void commonIO_setDir(COMMONIO_PIN vPin ,COMMONIO_DIR vDir);

/**
 * @brief Initialization of this component has to be done before any pinfunction is used.
 * 
 */
void commonIO_init(void);



#endif