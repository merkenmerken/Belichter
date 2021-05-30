#include "commonIO.h"

const PinConfiguration PIN_DefaultConfig[COMMONIO_MAX_PINS] = {
    {   PIN0,  1,  dirB,   PinInput,   Port_B},        /* PINB0 */
    {   PIN1,  1,  dirB,   PinOutput,  Port_B},        /* PINB1 */
    {   PIN2,  1,  dirB,   PinInput,   Port_B},        /* PINB2 */
    {   PIN3,  1,  dirB,   PinInput,   Port_B},        /* PINB3 */
    {   PIN4,  0,  dirB,   PinInput,   Port_B},        /* PINB4 */
    {   PIN5,  0,  dirB,   PinInput,   Port_B},        /* PINB5 */
    {   PIN6,  0,  dirB,   PinInput,   Port_B},        /* PINB6 */
    {   PIN7,  0,  dirB,   PinInput,   Port_B},        /* PINB7 */

    {   PIN0,  0,  dirC,   PinOutput,  Port_C},        /* PINC0 */
    {   PIN1,  0,  dirC,   PinOutput,  Port_C},        /* PINC1 */
    {   PIN2,  0,  dirC,   PinOutput,  Port_C},        /* PINC2 */
    {   PIN3,  0,  dirC,   PinOutput,  Port_C},        /* PINC3 */
    {   PIN4,  0,  dirC,   PinInput,   Port_C},        /* PINC4 */
    {   PIN5,  0,  dirC,   PinInput,   Port_C},        /* PINC5 */
    {   PIN6,  0,  dirC,   PinInput,   Port_C},        /* PINC6 */
    {   PIN7,  0,  dirC,   PinInput,   Port_C},        /* PINC7 */

    {   PIN0,  0,  dirD,   PinOutput,  Port_D},        /* PIND0 */
    {   PIN1,  0,  dirD,   PinOutput,  Port_D},        /* PIND1 */
    {   PIN2,  0,  dirD,   PinOutput,  Port_D},        /* PIND2 */
    {   PIN3,  0,  dirD,   PinOutput,  Port_D},        /* PIND3 */
    {   PIN4,  0,  dirD,   PinOutput,  Port_D},        /* PIND4 */
    {   PIN5,  0,  dirD,   PinOutput,  Port_D},        /* PIND5 */
    {   PIN6,  0,  dirD,   PinOutput,  Port_D},        /* PIND6 */
    {   PIN7,  0,  dirD,   PinInput,   Port_D}         /* PIND7 */
};

static PinConfiguration PIN_Config[COMMONIO_MAX_PINS] /* = PIN_DefaultConfig */;

void commonIO_init(void){

    for(uint8_t reg = 0; reg < COMMONIO_MAX_PINS; reg++){
        PIN_Config[reg].vAvailable = PIN_DefaultConfig[reg].vAvailable;
        PIN_Config[reg].vDir = PIN_DefaultConfig[reg].vDir;
        PIN_Config[reg].vDirPort = PIN_DefaultConfig[reg].vDirPort;
        PIN_Config[reg].vPinNum = PIN_DefaultConfig[reg].vPinNum;
        PIN_Config[reg].vPort = PIN_DefaultConfig[reg].vPort;
    }
    setPin();
    uart_init();
}

void setPin(void){

    PORTB = 0xFF;
    DDRB = 0xFF;
    PORTC = 0xFF;
    DDRC = 0xFF;
    PORTD = 0x00;
    DDRD = 0xFF;
    
}

void togglePin(void){

    PORTB ^= 0xFF;
    PORTD ^= 0xFF;

}

// #include "uart.h"

// #define BAUDRATE 38400UL //Definition als unsigned long, sonst gibt es Fehler in der Berechnung


// 50,75,100,110,134.5,150,300,600,900,1200,1800,2400,3600,4800,9600,14400,19200,28800, 33600,38400, 56000,57600,76800,115200,128000,153600,230400,460800,921600,1500000,2000000

#define BAUD 250000UL

#define UBRR_VAL ((F_CPU+BAUD * 8)/(BAUD*16)-1)     //clever round

#define BAUD_REAL (F_CPU/(16*(UBRR_VAL+1)))         //real baud rate

#define BAUD_ERROR ((BAUD_REAL*1000)/BAUD-1000)     //Error per thousand

#if ((BAUD_ERROR<990) || (BAUD_ERROR>1010))
//   #error Systematischer Fehler der Baudrate grösser 1% und damit zu hoch! 
#endif


void uart_init(void)
{

    // Set baud rate

    UBRRH = (unsigned char)(UBRR_VAL>>8);

    UBRRL = (unsigned char)UBRR_VAL;

    // UBRRH = 0U;

    // UBRRL = 51U;

    // Enable Receiver and Transmitter

    UCSRB |= (1<<TXEN); 

    // Set frame format: 8data, 1stop bit

    UCSRC = (1<<URSEL)|(1<<UCSZ1)|(3<<UCSZ0); 

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


