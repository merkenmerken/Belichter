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
#include "CDD_Lightsystem_Fsm.h"


#include <avr/eeprom.h>



tTimeKeeper LightSystemInstance;

#define MINUTE_BASE 60

uint16_t Lightsystem_secToTimer(const uint16_t vTime){
	uint16_t vtempTime = 0;
	if (MINUTE_BASE <= vTime)
	{
		vtempTime = (vTime / MINUTE_BASE) * 100U;
		vtempTime += vTime % MINUTE_BASE;
	}
	else
	{
		vtempTime = vTime;
	}
	return vtempTime;
}



uint16_t ADDRESS_LAST_TIME[EeprMaxSavedValues] EEMEM = { 0, 2, 4, 6};

void Lightsystem_init(void){

	LightSystemInstance.vActiveBtn = BTN_off;
	LightSystemInstance.vCurrentTimer = 200U;
	LightSystemInstance.vLastSetTime = 0U;
	
	LightSystemInstance.vLastSetTime = eeprom_read_word (&ADDRESS_LAST_TIME[EeprLastSetTime]);
	LightSystemInstance.vCurrentTimer = LightSystemInstance.vLastSetTime;
	Anzeige_setNum(Lightsystem_secToTimer(LightSystemInstance.vCurrentTimer));

	commonIO_setPin(PIN_B1);

}


void Lightsystem_cyclic(void *pvParameters){
	(void) pvParameters;
	
	Anzeige_init();

	TickType_t xLastExecutionTime;
	xLastExecutionTime = xTaskGetTickCount();
	
	xTaskCreate( Lightsystem_multCyclic, "Multi", configMINIMAL_STACK_SIZE, NULL, 2, NULL );

	uart0_init(UART_BAUD_SELECT(56000UL,F_CPU));
	commonIO_init();
	adc_init();
	Lightsystem_init();

	(void) Fsm_Init(0U, &LIGHTSYSTEM_FSM_CONFIGURATION, (FSM_StateIdType) Lightsystem_StateIdInit , (FSM_ContextTypePtr) &LightSystemInstance  );

	uart0_puts("START\n");
	
	for( ;; )
	{

		vTaskDelayUntil( &xLastExecutionTime, pdMS_TO_TICKS(LIGHTSYSTEM_TICK_RATE) );

		Fsm_TaskRun(0U);
			
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

void Lightsystem_multCyclic(void *pvParameters){

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
			Lightsystem_getActiveBtnNum(&LightSystemInstance.vActiveBtn);
			// Anzeige_setNum(tempv);

			if (ADC_READY())
			{
				ADC_START_CONV();
			}
		}
	}
}










/*lint -e818 LINT[818:1] */
FSM_StatusType Lightsystem_StateInitOnEntry( FSM_ContextTypePtr context ){
    FSM_StatusType fsmStatus = FSM_ERROR ;
    tTimeKeeper *pLsInstance = (tTimeKeeper*)context;
    
    if( NULL_PTR != pLsInstance){
		uart0_puts("init_entry");
		uart0_putLF();
    }
    return fsmStatus ;
}
/*lint +e818 LINT[818:1] */

/*lint -e818 LINT[818:1] */
FSM_StatusType Lightsystem_StateInitCyclic( FSM_ContextTypePtr context ){
    FSM_StatusType fsmStatus = FSM_ERROR ;
    tTimeKeeper *pLsInstance = (tTimeKeeper*)context;

    if( NULL_PTR != pLsInstance){
        fsmStatus = FSM_STOP ;
		uart0_puts("init_cyclic");
		uart0_putLF();
		(void) Fsm_InternalTransition(0U,Lightsystem_StateIdIdle);
    }
    return fsmStatus ;
}
/*lint +e818 LINT[818:1] */


/*lint -e818 LINT[818:1] */
FSM_StatusType Lightsystem_StateIdleOnEntry( FSM_ContextTypePtr context ){
    FSM_StatusType fsmStatus = FSM_ERROR ;
    tTimeKeeper *pLsInstance = (tTimeKeeper*)context;
    
    if( NULL_PTR != pLsInstance){
		
		uart0_puts("LS_idle_entry");
		uart0_putLF();
    }
    return fsmStatus ;
}
/*lint +e818 LINT[818:1] */

/*lint -e818 LINT[818:1] */
FSM_StatusType Lightsystem_StateIdleCyclic( FSM_ContextTypePtr context ){
    FSM_StatusType fsmStatus = FSM_ERROR ;
    tTimeKeeper *pLsInstance = (tTimeKeeper*)context;

    if( NULL_PTR != pLsInstance){
		if (BTN_up == pLsInstance->vActiveBtn)
		{
			(void) Fsm_InternalTransition(0U,Lightsystem_StateIdUp);
		}
		else if (BTN_down == pLsInstance->vActiveBtn)
		{
			(void) Fsm_InternalTransition(0U,Lightsystem_StateIdDown);
		}	
		else if (BTN_start == pLsInstance->vActiveBtn)
		{
			(void) Fsm_InternalTransition(0U,Lightsystem_StateIdActive);
		}	
		else if (BTN_save1 == pLsInstance->vActiveBtn)
		{
			(void) Fsm_InternalTransition(0U,Lightsystem_StateIdSave1);
		}	
		else if (BTN_save2 == pLsInstance->vActiveBtn)
		{
			(void) Fsm_InternalTransition(0U,Lightsystem_StateIdSave2);
		}	
		else if (BTN_save3 == pLsInstance->vActiveBtn)
		{
			(void) Fsm_InternalTransition(0U,Lightsystem_StateIdSave3);
		}	
    }
    return fsmStatus ;
}
/*lint +e818 LINT[818:1] */

// FSM_StatusType Lightsystem_StateUpOnEntry( FSM_ContextTypePtr context ){
//     FSM_StatusType fsmStatus = FSM_ERROR ;
//     uint8_t *pLsInstance = (uint8_t*)context;
    
//     if( NULL_PTR != pLsInstance){
// 		uart0_puts("LS_Up_entry");
// 		uart0_putLF();
//     }
//     return fsmStatus ;
// }
/*lint +e818 LINT[818:1] */


FSM_StatusType Lightsystem_StateUpCyclic( FSM_ContextTypePtr context ){
    FSM_StatusType fsmStatus = FSM_ERROR ;
	static uint16_t vCountdown = LIGHTSYSTEM_STATE_NEXT_MULT;
	static uint16_t vIncrementTime = LIGHTSYSTEM_100MS_TO_TICKS;
	static uint8_t vCountStep = 1;
	static uint8_t vCountIndex = 0;
	static uint8_t vIncrement = true;
	static uint8_t vStartCyclicIncrement = false;
    tTimeKeeper *pLsInstance = (tTimeKeeper*)context;

	

    if( NULL_PTR != pLsInstance){
		if (BTN_up == pLsInstance->vActiveBtn)
		{
			// If an increment is requested
			if (vIncrement == true)			
			{	

				pLsInstance->vCurrentTimer += vCountStep;
				Anzeige_setNum(Lightsystem_secToTimer(pLsInstance->vCurrentTimer));
				vIncrement = false;
			}
			
			// after LIGHTSYSTEM_STATE_NEXT_MULT time, an cyclic increment is possible
			if ((vIncrementTime > 0U)&&(vStartCyclicIncrement == true))
			{
				vIncrementTime--;
			}
			else if (vIncrementTime == 0U)
			{
				vIncrement = true;
				vIncrementTime = LIGHTSYSTEM_100MS_TO_TICKS;
			}

			// after a waittime of LIGHTSYSTEM_STATE_NEXT_MULT, the time will be count up in a 100ms cycle
			if (vCountdown > 0U)
			{
				vCountdown--;
			}
			else if (vCountdown == 0U)
			{
				vCountStep = vCountUnit[vCountIndex];
				vCountIndex = 1;
				vStartCyclicIncrement = true;
				vIncrement = true;
				vCountdown = LIGHTSYSTEM_STATE_NEXT_MULT_PHASE2;
			}	
		}
		if (BTN_off == pLsInstance->vActiveBtn)
		{
			
			(void) Fsm_InternalTransition(0U,Lightsystem_StateIdIdle);
			vIncrement = true;
			vStartCyclicIncrement = false;
			vCountStep = 1;
			vCountIndex = 0;
			vCountdown = LIGHTSYSTEM_STATE_NEXT_MULT;
			vIncrementTime = LIGHTSYSTEM_100MS_TO_TICKS;
		}
    }
    return fsmStatus ;
}



FSM_StatusType Lightsystem_StateDownCyclic( FSM_ContextTypePtr context ){
    FSM_StatusType fsmStatus = FSM_ERROR ;
	static uint16_t vCountdown = LIGHTSYSTEM_STATE_NEXT_MULT;
	static uint16_t vDecrementTime = LIGHTSYSTEM_100MS_TO_TICKS;
	static uint8_t vCountStep = 1;
	static uint8_t vCountIndex = 0;
	static uint8_t vDecrement = true;
	static uint8_t vStartCyclicDecrement = false;
    tTimeKeeper *pLsInstance = (tTimeKeeper*)context;

    if( NULL_PTR != pLsInstance){
		if (BTN_down == pLsInstance->vActiveBtn)
		{

			// If an increment is requested
			if (vDecrement == true)			
			{	
				if (pLsInstance->vCurrentTimer>vCountStep)
				{
					pLsInstance->vCurrentTimer -= vCountStep;
				}
				else
				{
					pLsInstance->vCurrentTimer = 0;
				}
				
				Anzeige_setNum(Lightsystem_secToTimer(pLsInstance->vCurrentTimer));
				vDecrement = false;
			}
			
			// after LIGHTSYSTEM_STATE_NEXT_MULT time, an cyclic increment is possible
			if ((vDecrementTime > 0U)&&(vStartCyclicDecrement == true))
			{
				vDecrementTime--;
			}
			else if (vDecrementTime == 0U)
			{
				vDecrement = true;
				vDecrementTime = LIGHTSYSTEM_100MS_TO_TICKS;
			}

			// after a waittime of LIGHTSYSTEM_STATE_NEXT_MULT, the time will be count up in a 100ms cycle
			if (vCountdown > 0U)
			{
				vCountdown--;
			}
			else if (vCountdown == 0U)
			{
				vCountStep = vCountUnit[vCountIndex];
				vCountIndex = 1;
				vStartCyclicDecrement = true;
				vDecrement = true;
				vCountdown = LIGHTSYSTEM_STATE_NEXT_MULT_PHASE2;
			}	
		}
		if (BTN_off == pLsInstance->vActiveBtn)
		{
			(void) Fsm_InternalTransition(0U,Lightsystem_StateIdIdle);
			vDecrement = true;
			vStartCyclicDecrement = false;
			vCountStep = 1;
			vCountIndex = 0;
			vCountdown = LIGHTSYSTEM_STATE_NEXT_MULT;
			vDecrementTime = LIGHTSYSTEM_100MS_TO_TICKS;
		}
    }
    return fsmStatus ;
}

FSM_StatusType Lightsystem_StateActiveOnEntry( FSM_ContextTypePtr context ){
    FSM_StatusType fsmStatus = FSM_ERROR ;
    tTimeKeeper *pLsInstance = (tTimeKeeper*)context;
    
    if( NULL_PTR != pLsInstance){

		pLsInstance->vLastSetTime = pLsInstance->vCurrentTimer;
		eeprom_write_word (&ADDRESS_LAST_TIME[EeprLastSetTime], pLsInstance->vLastSetTime);
		commonIO_clearPin(PIN_B1);
		uart0_puts("StateActive");
		uart0_putLF();
    }
    return fsmStatus ;
}

FSM_StatusType Lightsystem_StateActiveCyclic( FSM_ContextTypePtr context ){
    FSM_StatusType fsmStatus = FSM_ERROR ;
	static uint16_t vCountdown = LIGHTSYSTEM_SEC_TO_TICKS(1U);
	static uint8_t vButtonWasOFF = false;
	static uint8_t vExitState = false;
    tTimeKeeper *pLsInstance = (tTimeKeeper*)context;

    if( NULL_PTR != pLsInstance){

		// if no button is active and a state transition was requested
		if ((BTN_off == pLsInstance->vActiveBtn)&&(vExitState == true))	
		{
			vExitState = false;
			vButtonWasOFF = false;
			uart0_puts("LS_Active_exit");
			uart0_putLF();
			commonIO_setPin(PIN_B1);

			(void) Fsm_InternalTransition(0U,Lightsystem_StateIdIdle);
		}
		else if (BTN_off == pLsInstance->vActiveBtn)
		{
			vButtonWasOFF = true;

			// Countdown for 1 sek
			uint8_t vTimerEnable = false;
			if (vCountdown > 0U)
			{
				vCountdown--;
			}
			else
			{
				// reset counter to 1 sec
				vCountdown = LIGHTSYSTEM_SEC_TO_TICKS(1U);
				vTimerEnable = true;
			}
			
			// if 1 sec is left and the displayed number is bigger than 0, then cound down
			if ((pLsInstance->vCurrentTimer > 0U)&& (vTimerEnable == true))
			{
				pLsInstance->vCurrentTimer--;
				Anzeige_setNum(Lightsystem_secToTimer(pLsInstance->vCurrentTimer));
			}
			// if the displayed number is 0, exit the state
			else if (pLsInstance->vCurrentTimer == 0U)
			{
				vExitState = true;
			}
		}
		// if button was off in this state and is active again, then exit the state
		else if ((BTN_off != pLsInstance->vActiveBtn)&&(vButtonWasOFF == true))	
		{
			vButtonWasOFF = false;
			vExitState = true;
		}
    }
    return fsmStatus ;
}


FSM_StatusType Lightsystem_StateIdSave1Cyclic( FSM_ContextTypePtr context ){
    FSM_StatusType fsmStatus = FSM_ERROR ;
	static uint16_t vCountdown = LIGHTSYSTEM_SEC_TO_TICKS(1U);
	static uint8_t vState = 0U;
	static uint8_t vExitState = false;
    tTimeKeeper *pLsInstance = (tTimeKeeper*)context;

    if( NULL_PTR != pLsInstance){

		if (BTN_save1 == pLsInstance->vActiveBtn)
		{
			switch (vState)
			{
			case 0:
				if (0U<vCountdown)
				{
					vCountdown--;
				}
				else
				{
					vCountdown = LIGHTSYSTEM_SEC_TO_TICKS(1U)/2;
					vState = 1U;
					Anzeige_off();
					eeprom_write_word (&ADDRESS_LAST_TIME[EeprSave1], pLsInstance->vCurrentTimer);
				}
				break;
			case 1:
				if (0<vCountdown)
				{
					vCountdown--;
				}
				else
				{
					Anzeige_setNum(Lightsystem_secToTimer(pLsInstance->vCurrentTimer));
					vExitState = true;
				}
				break;
			
			default:
				break;
			}
		}
		else 
		{
			
			pLsInstance->vLastSetTime = eeprom_read_word (&ADDRESS_LAST_TIME[EeprSave1]);
			pLsInstance->vCurrentTimer = pLsInstance->vLastSetTime;
			Anzeige_setNum(Lightsystem_secToTimer(pLsInstance->vCurrentTimer));
			vExitState = true;
		}
		if (true == vExitState)
		{
			vState = 0;
			vExitState = false;
			vCountdown = LIGHTSYSTEM_SEC_TO_TICKS(1U);
			(void) Fsm_InternalTransition(0U,Lightsystem_StateIdIdle);
		}
    }
    return fsmStatus ;
}

FSM_StatusType Lightsystem_StateIdSave2Cyclic( FSM_ContextTypePtr context ){
    FSM_StatusType fsmStatus = FSM_ERROR ;
	static uint16_t vCountdown = LIGHTSYSTEM_SEC_TO_TICKS(1U);
	static uint8_t vState = 0U;
	static uint8_t vExitState = false;
    tTimeKeeper *pLsInstance = (tTimeKeeper*)context;

    if( NULL_PTR != pLsInstance){

		if (BTN_save2 == pLsInstance->vActiveBtn)
		{
			switch (vState)
			{
			case 0:
				if (0U<vCountdown)
				{
					vCountdown--;
				}
				else
				{
					vCountdown = LIGHTSYSTEM_SEC_TO_TICKS(1U)/2;
					vState = 1U;
					Anzeige_off();
					eeprom_write_word (&ADDRESS_LAST_TIME[EeprSave2], pLsInstance->vCurrentTimer);
				}
				break;
			case 1:
				if (0<vCountdown)
				{
					vCountdown--;
				}
				else
				{
					Anzeige_setNum(Lightsystem_secToTimer(pLsInstance->vCurrentTimer));
					vExitState = true;
				}
				break;
			
			default:
				break;
			}
		}
		else 
		{
			
			pLsInstance->vLastSetTime = eeprom_read_word (&ADDRESS_LAST_TIME[EeprSave2]);
			pLsInstance->vCurrentTimer = pLsInstance->vLastSetTime;
			Anzeige_setNum(Lightsystem_secToTimer(pLsInstance->vCurrentTimer));
			vExitState = true;
		}
		if (true == vExitState)
		{
			vState = 0;
			vExitState = false;
			vCountdown = LIGHTSYSTEM_SEC_TO_TICKS(1U);
			(void) Fsm_InternalTransition(0U,Lightsystem_StateIdIdle);
		}
    }
    return fsmStatus ;
}

FSM_StatusType Lightsystem_StateIdSave3Cyclic( FSM_ContextTypePtr context ){
    FSM_StatusType fsmStatus = FSM_ERROR ;
	static uint16_t vCountdown = LIGHTSYSTEM_SEC_TO_TICKS(1U);
	static uint8_t vState = 0U;
	static uint8_t vExitState = false;
    tTimeKeeper *pLsInstance = (tTimeKeeper*)context;

    if( NULL_PTR != pLsInstance){

		if (BTN_save3 == pLsInstance->vActiveBtn)
		{
			switch (vState)
			{
			case 0:
				if (0U<vCountdown)
				{
					vCountdown--;
				}
				else
				{
					vCountdown = LIGHTSYSTEM_SEC_TO_TICKS(1U)/2;
					vState = 1U;
					Anzeige_off();
					eeprom_write_word (&ADDRESS_LAST_TIME[EeprSave3], pLsInstance->vCurrentTimer);
				}
				break;
			case 1:
				if (0<vCountdown)
				{
					vCountdown--;
				}
				else
				{
					Anzeige_setNum(Lightsystem_secToTimer(pLsInstance->vCurrentTimer));
					vExitState = true;
				}
				break;
			
			default:
				break;
			}
		}
		else 
		{
			
			pLsInstance->vLastSetTime = eeprom_read_word (&ADDRESS_LAST_TIME[EeprSave3]);
			pLsInstance->vCurrentTimer = pLsInstance->vLastSetTime;
			Anzeige_setNum(Lightsystem_secToTimer(pLsInstance->vCurrentTimer));
			vExitState = true;
		}
		if (true == vExitState)
		{
			vState = 0;
			vExitState = false;
			vCountdown = LIGHTSYSTEM_SEC_TO_TICKS(1U);
			(void) Fsm_InternalTransition(0U,Lightsystem_StateIdIdle);
		}
    }
    return fsmStatus ;
}
