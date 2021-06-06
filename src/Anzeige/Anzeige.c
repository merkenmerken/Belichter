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
