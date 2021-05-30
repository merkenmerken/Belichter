#ifndef COMMONIO
#define COMMONIO

#ifndef atmega8
#define atmega8
#endif

#include "avr/io.h"

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
    PIN_C0,
    PIN_C1,
    PIN_C2,
    PIN_C3,
    PIN_C4,
    PIN_C5,
    PIN_C6,
    PIN_C7,
    PIN_D0,
    PIN_D1,
    PIN_D2,
    PIN_D3,
    PIN_D4,
    PIN_D5,
    PIN_D6,
    PIN_D7
}COMMONIO_PIN;

typedef enum{
    PinInput,
    PinOutput,
    dirMaxValue
}COMMONIO_DIR;

typedef enum{
    dirB,
    dirC,
    dirD
}COMMONIO_DIR_PORT;

typedef enum{
    Port_B,
    Port_C,
    Port_D
} COMMONIO_PORT;

typedef struct {
    uint8_t vPinNum;
    uint8_t vAvailable;
    COMMONIO_DIR_PORT vDirPort;
    COMMONIO_DIR vDir;
    COMMONIO_PORT vPort;
}PinConfiguration;

void commonIO_init(void);

void setPin(void);

void togglePin(void);

extern void uart_init (void);

// static inline int
// uart_putc (const uint8_t c)
// {
//     // Warten, bis UDR bereit ist für einen neuen Wert 
//     while (!(UCSRA & (1 << UDRE)))
//         ;

//     // UDR Schreiben startet die Übertragung 
//     UDR = c;

//     return 1;
// }

void uart_putc(uint8_t u8Data);
void UART_String_TX(char *command);

#endif