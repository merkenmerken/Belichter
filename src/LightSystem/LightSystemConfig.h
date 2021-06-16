/*
 * TimekeeperConfig.h
 *
 * Created: 18.05.2021 18:58:50
 *  Author: merke
 */ 
#ifndef LIGHTSYSTEMCONFIG_H_
#define LIGHTSYSTEMCONFIG_H_

#include "Std_Types.h"

#define LIGHTSYSTEM_TICK_RATE 10U
#define LIGHTSYSTEM_SEC_TO_TICKS(sec) (sec*1000UL/10UL)
#define LIGHTSYSTEM_100MS_TO_TICKS (100UL/10UL)
#define LIGHTSYSTEM_STATE_NEXT_MULT (LIGHTSYSTEM_SEC_TO_TICKS(1U))
#define LIGHTSYSTEM_STATE_NEXT_MULT_PHASE2 (LIGHTSYSTEM_SEC_TO_TICKS(6U))

typedef enum{
    BTN_off,
    BTN_save1,
    BTN_save2,
    BTN_save3,
    BTN_down,
    BTN_start,
    BTN_up,
    BTN_MAX_VALUE,
    BTN_MAX
}tBTN;

typedef struct{
    uint16_t vLastSetTime;
    uint16_t vCurrentTimer;
    uint8_t vActiveBtn;
}tTimeKeeper;

typedef enum{
    EeprLastSetTime,
    EeprSave1,
    EeprSave2,
    EeprSave3,
    EeprMaxSavedValues
}tSaveSpot;



const uint8_t vBtnThreshold[BTN_MAX];

const uint8_t vCountUnit[2];



#endif
