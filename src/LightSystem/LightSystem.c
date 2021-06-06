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



void Anzeige_cyclic(void *pvParameters){
	(void) pvParameters;
	
	Anzeige_init();

	TickType_t xLastExecutionTime;
	xLastExecutionTime = xTaskGetTickCount();
	
	xTaskCreate( Anzeige_mult, "Multi", configMINIMAL_STACK_SIZE, NULL, 2, NULL );
	// QueueHandle_t TimerQueueHandle;
	// TimeKeeperGetQueueHandle(&TimerQueueHandle);
	
	// TimeKeeperMessage tempMessage;

	// tempMessage.vNumberShown = 55U;
	// tempMessage.vSchaltZustand = AnzeigeON;

	uart0_init(UART_BAUD_SELECT(56000UL,F_CPU));

	// const char testtext[] = "testtext,hallo Welt1testtext,hallo ";

	// const char RAMdata[]         = "UART_send()\n";

	commonIO_init();

	uart0_puts("test\n");

	uint8_t num = 250U;

	uint8_t testpin = 0U;
	
	for( ;; )
	{

		vTaskDelayUntil( &xLastExecutionTime, pdMS_TO_TICKS(50UL) );

		// commonIO_readPin(PIN_C5, &testpin);
		// uart0_putc(testpin);
		// uart0_putc(ADCH);
		// uart0_putc(ADCL);
		
		// ADCSRA |= (1<<ADIF);
		uint8_t vtemp = ADCSRA & (1<<ADIF);
		if(0!= vtemp){
			uart0_putc(ADCH);
			// uart0_putNum(ADCL);
			Anzeige_setNum(ADCL);	
			ADCSRA |= (1<<ADIF);
		}
		

    	uart0_putLF();

		// if (0U == num)
		// {
		// 	Anzeige_off();
		// }
		// else
		// {
		// 	Anzeige_setNum(num);
		// }
		
		// num++;


		
		// xQueueReceive( TimerQueueHandle, &tempMessage, pdMS_TO_TICKS(1100) );
		
		// if (tempMessage.vSchaltZustand == AnzeigeON)
		// {
				
		// }
		// else 
		// {
		// 	Anzeige_off();
		// }	
	}	
}


void Anzeige_mult(void *pvParameters){

	static TickType_t xLastExecutionTime;
	xLastExecutionTime = xTaskGetTickCount();
	(void) pvParameters;
	
	for( ;; )
	{
		vTaskDelayUntil( &xLastExecutionTime, pdMS_TO_TICKS( 5 ) );	
		Anzeige_switchPos();	

		// uart0_putNum(Anzeige.xMultiPlexIO.vSwitchPos);
	}
}