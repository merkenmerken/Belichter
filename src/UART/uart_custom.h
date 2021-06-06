#ifndef UARTH
#define UARTH

#include "uart.h"



/**
 * @brief 
 * Convert an integer to a string.
 * Max planned number is a 16 bit value. 
 * If neccessary it is possible to use a 32 bit number.
 * 
 * @param data Intenger that will be converted to a string and put to the tx buffer
 */
void uart0_putNum(uint16_t data);

/**
 * @brief Put a line feed to the tx buffer
 * 
 */
void uart0_putLF(void);

/**
 * @brief Used for debugging. Shows the location of the error.
 * 
 */
#define uart0_putErrorMsg()  uart0_puts(__FILE__); \
                            uart0_putLF(); \
                            uart0_putNum(__LINE__); \
                            uart0_putLF();

#endif