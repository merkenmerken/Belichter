/*
 * Anzeige.h
 *
 * Created: 15.05.2021 19:47:26
 *  Author: merke
 */ 


#ifndef ANZEIGE_H_
#define ANZEIGE_H_

#pragma once
// #include <avr/io.h>
// #include <stdbool.h>
#include "FreeRTOS.h"
#include "task.h"

#include "AnzeigeConfig.h"



extern t_Anzeige Anzeige;

/**
 * @brief Cycles to the next disp position of the segment displays. 
 * Function has to be called in a cyclic function with the desired frequency. 
 * Frequency has to be MAX_DISPLAY times higher than the desired Frequency.
 * 
 */
void Anzeige_switchPos(void);

/**
 * @brief Initialization of segment display. The initial configuration will turn off the display
 * 
 */
void Anzeige_init();

/**
 * @brief Set Number on segdisplay
 * 
 * @param Display display number
 * @param Num number to be displayed
 */
void Anzeige_setNumDisplay(uint8_t Display, uint8_t Num);

/**
 * @brief Set Number on the whole display
 * 
 * @param Num Number to be displayed
 */
void Anzeige_setNum(uint16_t Num);

/**
 * @brief Function turns off the display
 * 
 */
void Anzeige_off();



void Anzeige_cyclic(void *pvParameters);

void Anzeige_mult(void *pvParameters);




#endif /* ANZEIGE_H_ */
