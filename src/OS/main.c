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

static void vErrorChecks( void *pvParameters );

int main(void)
{

	//xTaskCreate( vErrorChecks, "Check", configMINIMAL_STACK_SIZE, NULL, mainCHECK_TASK_PRIORITY, NULL );
	
	xTaskCreate( Anzeige_cyclic, "Anz", configMINIMAL_STACK_SIZE, NULL, mainCHECK_TASK_PRIORITY, NULL);

	// xTaskCreate( TimeKeeper, "Timer", configMINIMAL_STACK_SIZE, NULL, mainCHECK_TASK_PRIORITY, NULL );
	
	
	
	
	
	/* In this port, to use preemptive scheduler define configUSE_PREEMPTION
	as 1 in portmacro.h.  To use the cooperative scheduler define
	configUSE_PREEMPTION as 0. */
	vTaskStartScheduler();
   
}

static void vErrorChecks( void *pvParameters )
{
static volatile unsigned long ulDummyVariable = 3UL;

	/* The parameters are not used. */
	( void ) pvParameters;

	/* Cycle for ever, delaying then checking all the other tasks are still
	operating without error. */
	for( ;; )
	{
		vTaskDelay( mainCHECK_PERIOD );

		/* Perform a bit of 32bit maths to ensure the registers used by the
		integer tasks get some exercise. The result here is not important -
		see the demo application documentation for more info. */
		ulDummyVariable *= 3;
	}
}