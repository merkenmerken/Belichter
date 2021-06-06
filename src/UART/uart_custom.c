/**
 * @file uart_custom.c
 * @author your name (you@domain.com)
 * @brief This file is an addon to the uart lib with custom functions
 * @version 0.1
 * @date 2021-06-02
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "uart_custom.h"
#include <stdlib.h>



void uart0_putNum(uint16_t data)
{
	char str[16];
	itoa(data, str, 10);
	uart0_puts(str);
}



void uart0_putLF(void)
{
	uart0_putc('\n');
}

