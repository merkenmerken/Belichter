/**
 * @file uart.c
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2021-06-02
 * 
 * @copyright Copyright (c) 2021
 * 
 */


#include "uart.h"




void uart_init(void)
{

    // Set baud rate

    UBRRH = (unsigned char)(UBRR_VAL>>8);

    UBRRL = (unsigned char)UBRR_VAL;

    // Enable Receiver and Transmitter

    UCSRB = (0<<RXCIE)|(0<<TXCIE)|(0<<UDRIE)(1<<RXEN)|(1<<TXEN)|(0<<UCSZ2)|(0<<RXB8)|(0<<TXB8); 

    // Set frame format: 8data, 1stop bit

    UCSRC = (1<<URSEL)|(0<<UMSEL)|(0<<UPM1)(0<<UPM0)|(0<<USBS)|(1<<UCSZ1)(1<<UCSZ0)|(0<<UCPOL); 
    

}

void uart_putc(uint8_t data)
{

    // Wait for empty transmit buffer

    while ( !( UCSRA & (1<<UDRE)) ){

    }

    // Put data into buffer, sends the data

    UDR = data;


}

// #include<string.h>

void UART_String_TX(char *command){
    
while(*command != 0x00){
    uart_putc(*command);
command++;}
}
