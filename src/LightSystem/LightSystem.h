/*
 * Timekeeper.h
 *
 * Created: 18.05.2021 18:58:27
 *  Author: merke
 */ 


#ifndef LIGHTSYSTEM_H_
#define LIGHTSYSTEM_H_

#pragma once
#include <avr/io.h>
#include <stdbool.h>
// #include "FreeRTOS.h"
// #include "task.h"
// #include "queue.h"

void Anzeige_cyclic(void *pvParameters);

void Anzeige_mult(void *pvParameters);



#endif /* TIMEKEEPER_H_ */