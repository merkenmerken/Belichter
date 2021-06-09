/*
 * TimeKeeper.c
 *
 * Created: 18.05.2021 18:58:14
 *  Author: merke
 */ 
#include "LightSystem.h"
#include "Anzeige.h"
#include "uart_custom.h"	
#include "commonIO.h"	
#include "FreeRTOS.h"
#include "task.h"
#include "adc.h"


tStates Lightsystem_CurrentState = LS_entry;



uint16_t dispNum = 0;
uint8_t stateEntry = 0;
tBTN activeBtn = BTN_off;





void Lightsystem_stateEntry(void){

	if (stateEntry == 0)
	{
		stateEntry = 0;
		Lightsystem_CurrentState = LS_idle;
		Anzeige_setNum(dispNum);
		uart0_puts("LS_entry");
		uart0_putLF();
	}
}



void Lightsystem_stateIdle(void){

	if (stateEntry == 0)
	{
		stateEntry = 1;
		commonIO_clearPin(PIN_B1);
		uart0_puts("LS_idle");
		uart0_putLF();
	}

	if (BTN_up == activeBtn)
	{
		Lightsystem_CurrentState = LS_up;
		stateEntry = 0;
	}
	else if (BTN_down == activeBtn)
	{
		Lightsystem_CurrentState = LS_down;
		stateEntry = 0;
	}	
	else if (BTN_start == activeBtn)
	{
		Lightsystem_CurrentState = LS_active;
		stateEntry = 0;
	}	
}

void Lightsystem_stateActive(void){

	static tBTN vPreviousBTN = BTN_off;
	static uint8_t vStateToggleCount = 0;

	if (stateEntry == 0)
	{
		stateEntry = 1;
		vPreviousBTN = activeBtn;
		vStateToggleCount = 0;
		commonIO_setPin(PIN_B1);
		uart0_puts("LS_active");
		uart0_putLF();
	}

	if (dispNum > 0U)
	{
		dispNum--;
		Anzeige_setNum(dispNum);
	}
	else
	{
		Lightsystem_CurrentState = LS_idle;
		stateEntry = 0;
	}

	if (vPreviousBTN != activeBtn)
	{
		vPreviousBTN = activeBtn;
		vStateToggleCount++;
	}
	
	if ((vStateToggleCount >= 2U)&&(BTN_start != activeBtn))
	{
		Lightsystem_CurrentState = LS_idle;
		stateEntry = 0;
	}
}


#define LIGHTSYSTEM_STATE_UP_COUNTDOWN (1000U / 100U)

void Lightsystem_stateUp(void){

	static uint8_t vLightsystem_stateUpCountdown = 0;

	if (stateEntry == 0)
	{
		stateEntry = 1;
		vLightsystem_stateUpCountdown = LIGHTSYSTEM_STATE_UP_COUNTDOWN;
		
		uart0_puts("LS_up");
		uart0_putLF();
	}
	vLightsystem_stateUpCountdown--;


	if (BTN_up != activeBtn)
	{
		dispNum++;
		Anzeige_setNum(dispNum);
		Lightsystem_CurrentState = LS_idle;
		stateEntry = 0;
	}
	if (0U == vLightsystem_stateUpCountdown)
	{
		Lightsystem_CurrentState = LS_up2;
		stateEntry = 0;
	}
}





#define LIGHTSYSTEM_STATE_UP2_COUNTDOWN (6000U / 100U)

void Lightsystem_stateUp2(void){

	static uint8_t vLightsystem_stateUp2Factor = 1;
	static uint8_t vLightsystem_stateUp2Countdown = 0;

	if (stateEntry == 0)
	{
		stateEntry = 1;
		vLightsystem_stateUp2Factor = 1;
		vLightsystem_stateUp2Countdown = LIGHTSYSTEM_STATE_UP2_COUNTDOWN;
		uart0_puts("LS_up2");
		uart0_putLF();
	}

	if (0 < vLightsystem_stateUp2Countdown)
	{
		vLightsystem_stateUp2Countdown--;
	}
	
	dispNum += 1*vLightsystem_stateUp2Factor;
	Anzeige_setNum(dispNum);


	if (0U == vLightsystem_stateUp2Countdown)
	{
		vLightsystem_stateUp2Factor = 10;
	}

	if (BTN_up != activeBtn)
	{
		Lightsystem_CurrentState = LS_idle;
		stateEntry = 0;
	}
}






void Lightsystem_stateDown(void){
	if (stateEntry == 0)
	{
		stateEntry = 1;
		
		uart0_puts("LS_down");
		uart0_putLF();
	}

	if (BTN_down != activeBtn)
	{
		Lightsystem_CurrentState = LS_idle;
		stateEntry = 0;
		if (dispNum > 0U)
		{
			dispNum--;
		}
		Anzeige_setNum(dispNum);
	}
}









void Lightsystem_cyclic(void *pvParameters){
	(void) pvParameters;
	
	Anzeige_init();

	TickType_t xLastExecutionTime;
	xLastExecutionTime = xTaskGetTickCount();
	
	xTaskCreate( Lightsystem_mult, "Multi", configMINIMAL_STACK_SIZE, NULL, 2, NULL );

	uart0_init(UART_BAUD_SELECT(56000UL,F_CPU));
	commonIO_init();
	adc_init();

	uart0_puts("START\n");
	
	for( ;; )
	{

		vTaskDelayUntil( &xLastExecutionTime, pdMS_TO_TICKS(100UL) );


		switch (Lightsystem_CurrentState)
		{
		case LS_entry:
			Lightsystem_stateEntry();
			break;

		case LS_idle:

			Lightsystem_stateIdle();
			break;

		case LS_active:

			Lightsystem_stateActive();
			break;

		case LS_up:
			Lightsystem_stateUp();

			break;

		case LS_up2:
			Lightsystem_stateUp2();
			break;	

		case LS_down:
			Lightsystem_stateDown();
			break;
		
		default:
			Lightsystem_CurrentState = LS_idle;
			break;
		}
			
	}	
}







/**
 * @brief This function returns the number of the button which is currently active by comparing the ad value with the configuration table
 * 
 * @param vButton pointer to a storage variable
 */
void Lightsystem_getActiveBtnNum(tBTN* vButton){
	if (0U != vButton)
	{
		uint8_t vTempValue;
		if (buffer_ok == adc_circBufferGetFilteredValue(&vTempValue))
		{
			for (tBTN i = BTN_off; i < BTN_MAX; i++)
			{
				if (vBtnThreshold[i] > vTempValue)
				{
					*vButton = i;
					break;
				}
			}
		}
	}
}



#define TICKS_MULTIPLEX 5
#define TICKS_AD (10/TICKS_MULTIPLEX)

uint8_t ticks = 0;

void Lightsystem_mult(void *pvParameters){

	static TickType_t xLastExecutionTime;
	xLastExecutionTime = xTaskGetTickCount();
	(void) pvParameters;
	
	for( ;; )
	{
		vTaskDelayUntil( &xLastExecutionTime, pdMS_TO_TICKS( 5 ) );	
		Anzeige_switchPos();	

		ticks++;

		if (TICKS_AD <= ticks)
		{
			ticks = 0;
			
			// tBTN tempv = 0;
			Lightsystem_getActiveBtnNum(&activeBtn);
			// Anzeige_setNum(tempv);

			if (ADC_READY())
			{
				ADC_START_CONV();
			}
		}
	}
}

