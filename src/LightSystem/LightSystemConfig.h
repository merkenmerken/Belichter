/*
 * TimekeeperConfig.h
 *
 * Created: 18.05.2021 18:58:50
 *  Author: merke
 */ 
#ifndef LIGHTSYSTEMCONFIG_H_
#define LIGHTSYSTEMCONFIG_H_

#include <avr/io.h>

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


typedef enum{
    LS_entry,
    LS_idle,
    LS_active,
    LS_up,
    LS_up2,
    LS_down,
    LS_down2,
    LS_save1,
    LS_save1_2,
    LS_save2,
    LS_save2_2,
    LS_save3,
    LS_save3_2
} tStates;


const uint8_t vBtnThreshold[BTN_MAX];



#endif
