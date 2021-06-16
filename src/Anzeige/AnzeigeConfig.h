/*
 * IncFile1.h
 *
 * Created: 16.05.2021 11:17:00
 *  Author: merke
 */ 



#ifndef ANZEIGECONFIG_H_
#define ANZEIGECONFIG_H_

#include "Std_Types.h"
#include "commonIO.h"

#define MAX_SEG_NUMBERS 17U
#define MAX_DISPLAY 4U
#define NUM_SEGMENTS 7U
#define MAX_DISPLAYED_NUMBER 9999U

typedef uint8_t SegmentInhalt;

typedef struct {
	const SegmentInhalt *vSegMask;				// points to the bitmask of the shown number
	uint8_t vSegNumber;							//dargestellte Zahl der Segmentanzeige
}t_Segment;

typedef struct {
	uint8_t vSwitchPos; 						// Position of active display
	const COMMONIO_PIN* xDispPin; 				// Pointer to defaultconfig of display pin config
	const COMMONIO_PIN* xSegPin; 				// Pointer to defaultconfig of segments pin config
}t_Multiplex;


typedef struct {
	t_Segment xSegmentAnzeige[MAX_DISPLAY];		//einzelne Segmentanzeigen
	t_Multiplex xMultiPlexIO;					//Anzeige aktiv (f�r Multiplexer)
}t_Anzeige;

extern const SegmentInhalt segDecode[];
extern const COMMONIO_PIN PinConfigMult[];
extern const COMMONIO_PIN PinConfigSeg[];


#endif /* ANZEIGECONFIG_H_ */
