/**
 * @file Anzeige.c
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2021-06-03
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "Anzeige.h"	
#include "uart_custom.h"	
#include "commonIO.h"	

/**
 * @brief Struktur in der alle relevanten Daten für die Anzeige benötigt werden
 * 
 */
t_Anzeige Anzeige;

/**
 * @brief Umrechnung der angeforderten Zahl auf eine die gewünschte Basis
 * 
 * @param Basis Gewünschte Basis
 * @param Potenz Stelle der Basis
 * @return uint16_t 
 */
static uint16_t Anzeige_pow_private(uint16_t Basis, uint16_t Potenz) {

	uint16_t vTempResult = Basis;

	if (Potenz != 0)
	{
		for (uint16_t i = 0; i < (Potenz - 1); i++)
		{
			vTempResult *= Basis;
		}
	}
	else vTempResult = 1;

	return vTempResult;
}



/**
 * @brief Sets pins for the actual set number on display position vPos
 * 
 * @param vPos Seg display number
 */
static void Anzeige_switchNumPrivate(uint8_t vPos){

	if (MAX_DISPLAY > vPos)
	{
		uint8_t vSegStatus = 0U;
		const uint8_t vSegMask = *(Anzeige.xSegmentAnzeige[vPos].vSegMask);
		const uint8_t* vSegPin;

		for (uint8_t vSegNum = 0U; vSegNum < NUM_SEGMENTS; vSegNum++)		// cycle trough the bitmask and set the pin if the segment is actve
		{
			vSegPin = &(Anzeige.xMultiPlexIO.xSegPin[vSegNum]);
			vSegStatus = vSegMask & (1U<<vSegNum);
			if (0U != vSegStatus)
			{
				vSegStatus = 1U;
			}
			commonIO_setPinLevel(*vSegPin, vSegStatus);
		}	
	}
	else
	{
		uart0_putLF();
		uart0_putErrorMsg();
	}
}



/**
 * @brief Cycles to the next disp position of the segment displays. 
 * Function has to be called in a cyclic function with the desired frequency. 
 * Frequency has to be MAX_DISPLAY times higher than the desired Frequency.
 * 
 */
void Anzeige_switchPos(void){
		uint8_t vCurPos = Anzeige.xMultiPlexIO.vSwitchPos;
		uint8_t vNextPos = vCurPos + 1;

		if (vNextPos >= MAX_DISPLAY){
			vNextPos = 0;
		}	
		Anzeige.xMultiPlexIO.vSwitchPos = vNextPos;
		
		//Clear old switching pos bit
		commonIO_clearPin(Anzeige.xMultiPlexIO.xDispPin[vCurPos]);	
		
		//Set new Value
		Anzeige_switchNumPrivate(vNextPos);
		
		//Set new switching pos bit
		commonIO_setPin(Anzeige.xMultiPlexIO.xDispPin[vNextPos]);

	}



void Anzeige_init(){
	uint8_t* vSegNumber;
	for(uint8_t vDisplay = 0; vDisplay < MAX_DISPLAY; vDisplay++){

		vSegNumber = &(Anzeige.xSegmentAnzeige[vDisplay].vSegNumber);
		*vSegNumber = 16U;		// Start with an empty display after reset
		
		Anzeige.xSegmentAnzeige[vDisplay].vSegMask = &segDecode[*vSegNumber];
	}
	Anzeige.xMultiPlexIO.vSwitchPos = 0u;

	Anzeige.xMultiPlexIO.xDispPin = PinConfigMult;
	Anzeige.xMultiPlexIO.xSegPin = PinConfigSeg;
	
}



void Anzeige_setNumDisplay(uint8_t Display, uint8_t Num) {

	if ((MAX_DISPLAY > Display)&&(MAX_SEG_NUMBERS > Num))
	{
		uint8_t* vSegNumber = &(Anzeige.xSegmentAnzeige[Display].vSegNumber);

		if (MAX_SEG_NUMBERS > Num)
		{
			if (*vSegNumber != Num) {		// if new seg number is not equal to the current number, then make an update
				*vSegNumber = Num;
				Anzeige.xSegmentAnzeige[Display].vSegMask = &segDecode[*vSegNumber];
			}
		}
	}
	else
	{
		uart0_putErrorMsg();
	}
}



void Anzeige_setNum(uint16_t Num) {

	if (MAX_DISPLAYED_NUMBER > Num)
	{
		uint8_t Result;
		uint16_t Value = Num;
		for (uint16_t i = MAX_DISPLAY; i > 0; i--)
		{
			uint16_t divider = Anzeige_pow_private(10,(i-1));
			Result = (Value / divider);
			Anzeige_setNumDisplay((i-1), Result);
			Value = Value % divider;
		}
	}
	else
	{
		uart0_putErrorMsg();
	}
}



void Anzeige_off(void) {

	for (uint8_t vDisp = 0u; vDisp < MAX_DISPLAY; vDisp++)
	{
		Anzeige_setNumDisplay(vDisp, 16u);
	}
}


















// void Anzeige_cyclic(void *pvParameters){
// 	(void) pvParameters;
	
// 	Anzeige_init();

// 	TickType_t xLastExecutionTime;
// 	xLastExecutionTime = xTaskGetTickCount();
	
// 	xTaskCreate( Anzeige_mult, "Multi", configMINIMAL_STACK_SIZE, NULL, 2, NULL );
// 	// QueueHandle_t TimerQueueHandle;
// 	// TimeKeeperGetQueueHandle(&TimerQueueHandle);
	
// 	// TimeKeeperMessage tempMessage;

// 	// tempMessage.vNumberShown = 55U;
// 	// tempMessage.vSchaltZustand = AnzeigeON;

// 	uart0_init(UART_BAUD_SELECT(56000UL,F_CPU));

// 	// const char testtext[] = "testtext,hallo Welt1testtext,hallo ";

// 	// const char RAMdata[]         = "UART_send()\n";

// 	commonIO_init();

// 	uart0_puts("test\n");

// 	uint8_t num = 250U;

// 	uint8_t testpin = 0U;
	
// 	for( ;; )
// 	{

// 		vTaskDelayUntil( &xLastExecutionTime, pdMS_TO_TICKS(100UL) );

// 		commonIO_readPin(PIN_C5, &testpin);
// 		uart0_putc(testpin);
//     	uart0_putLF();

// 		if (0U == num)
// 		{
// 			Anzeige_off();
// 		}
// 		else
// 		{
// 			Anzeige_setNum(num);
// 		}
		
// 		num++;


		
// 		// xQueueReceive( TimerQueueHandle, &tempMessage, pdMS_TO_TICKS(1100) );
		
// 		// if (tempMessage.vSchaltZustand == AnzeigeON)
// 		// {
				
// 		// }
// 		// else 
// 		// {
// 		// 	Anzeige_off();
// 		// }	
// 	}	
// }


// void Anzeige_mult(void *pvParameters){

// 	static TickType_t xLastExecutionTime;
// 	xLastExecutionTime = xTaskGetTickCount();
// 	(void) pvParameters;
	
// 	for( ;; )
// 	{
// 		vTaskDelayUntil( &xLastExecutionTime, pdMS_TO_TICKS( 5 ) );	
// 		Anzeige_switchPosPrivate();	

// 		// uart0_putNum(Anzeige.xMultiPlexIO.vSwitchPos);
// 	}
// }