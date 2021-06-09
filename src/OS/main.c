/*
 * BelichterProjekt.c
 *
 * Created: 09.04.2021 13:40:09
 * Author : merke
 */ 

#include <avr/io.h>

/* Scheduler include files. */
#include "FreeRTOS.h"
#include "task.h"

#include "Anzeige.h"
#include "LightSystem.h"

#define mainCHECK_TASK_PRIORITY			( tskIDLE_PRIORITY + 1 )

#define mainCHECK_PERIOD				( ( TickType_t ) 3000 / portTICK_PERIOD_MS  )


int main(void)
{

	//xTaskCreate( vErrorChecks, "Check", configMINIMAL_STACK_SIZE, NULL, mainCHECK_TASK_PRIORITY, NULL );
	
	xTaskCreate( Lightsystem_cyclic, "Anz", configMINIMAL_STACK_SIZE, NULL, mainCHECK_TASK_PRIORITY, NULL);

	// xTaskCreate( TimeKeeper, "Timer", configMINIMAL_STACK_SIZE, NULL, mainCHECK_TASK_PRIORITY, NULL );
	
	
	
	
	
	/* In this port, to use preemptive scheduler define configUSE_PREEMPTION
	as 1 in portmacro.h.  To use the cooperative scheduler define
	configUSE_PREEMPTION as 0. */
	vTaskStartScheduler();
   
}

