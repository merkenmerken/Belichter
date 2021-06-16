/*
 * Timekeeper.h
 *
 * Created: 18.05.2021 18:58:27
 *  Author: merke
 */ 


#ifndef LIGHTSYSTEM_H_
#define LIGHTSYSTEM_H_

#pragma once
#include "Std_Types.h"
#include <stdbool.h>
#include "LightSystemConfig.h"
// #include "FreeRTOS.h"
// #include "task.h"
// #include "queue.h"

void Lightsystem_cyclic(void *pvParameters);

void Lightsystem_multCyclic(void *pvParameters);

void Lightsystem_getActiveBtnNum(tBTN* vButton);

#endif /* TIMEKEEPER_H_ */
