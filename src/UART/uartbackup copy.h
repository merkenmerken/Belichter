#ifndef UARTH
#define UARTH

#include <avr/io.h>
#include <stdbool.h>
#include <avr/interrupt.h>

/* Possible BAUD rates */
// 50,75,100,110,134.5,150,300,600,900,1200,1800,2400,3600,4800,9600,14400,19200,28800, 33600,38400, 56000,57600,76800,115200,128000,153600,230400,460800,921600,1500000,2000000

#define BAUD 56000UL    //Definition als unsigned long, sonst gibt es Fehler in der Berechnung

#define UBRR_VAL ((F_CPU+BAUD * 8)/(BAUD*16)-1)     //clever round

#define BAUD_REAL (F_CPU/(16*(UBRR_VAL+1)))         //real baud rate

#define BAUD_ERROR ((BAUD_REAL*1000)/BAUD-1000)     //Error per thousand

#if ((BAUD_ERROR<990) || (BAUD_ERROR>1010))
//   #error Systematischer Fehler der Baudrate grösser 1% und damit zu hoch! 
#endif

#endif