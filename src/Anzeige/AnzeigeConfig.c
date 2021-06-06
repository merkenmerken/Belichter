/*
 * CFile1.c
 *
 * Created: 16.05.2021 11:16:35
 *  Author: merke
 */ 

#include "AnzeigeConfig.h"
#include "commonIO.h"



const SegmentInhalt segDecode[MAX_SEG_NUMBERS] = {
		0x3F,		//0
		0x6,		//1
		0x5B,		//2
		0x4F,		//3
		0x66,		//4
		0x6D,		//5
		0x7D,		//6
		0x7,		//7
		0x7F,		//8
		0x6F,		//9
		0x77,		//A
		0x7c,		//B
		0x39,		//C
		0x5E,		//D
		0x79,		//E
		0x71,		//F
		0x00		//OFF
};


const COMMONIO_PIN PinConfigMult[MAX_DISPLAY]={
		PIN_C0	,	//Anzeige 0
		PIN_C1	,	//Anzeige 1
		PIN_C2	,	//Anzeige 2
		PIN_C3		//Anzeige 3
};


const COMMONIO_PIN PinConfigSeg[NUM_SEGMENTS]={
		PIN_B6	,	//Seg a
		PIN_B7	,	//Seg b
		PIN_D2	,	//Seg c
		PIN_D3	,	//Seg d
		PIN_D4	,	//Seg e
		PIN_D5	,	//Seg f
		PIN_D6		//Seg g
};