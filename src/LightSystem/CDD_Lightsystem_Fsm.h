#ifndef LIGHTSYSTEM_FSM_H_
#define LIGHTSYSTEM_FSM_H_

/**
* @ingroup CDD_Lightsystem
* @file
* @defgroup CDD_Lightsystem CDD_Lightsystem: CDD_Lightsystem
* @brief THIS SHALL EDITED UPON COMPONENT CREATION
* @par
*        CDD_Lightsystem
*
*        What is doing this component
*        How is used this component
* @code
*        Usage example:
* @endcode
*
*        Design documentation references
*        ASIL Classification (QM/A/B/C/D)
*
* @author dschubert
* @copyright (c) Copyright 2021, Lear Corporation
* @{
*/

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/

#include "Fsm.h"

/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/


/*******************************************************************************
**                      State Types                                           **
*******************************************************************************/
typedef enum ETagLightsystem_StateIdType{
    Lightsystem_StateIdInit,
    Lightsystem_StateIdIdle,
    Lightsystem_StateIdUp,
    Lightsystem_StateIdDown,
    Lightsystem_StateIdActive,
    Lightsystem_StateIdSave1,
    Lightsystem_StateIdSave2,
    Lightsystem_StateIdSave3,
    Lightsystem_StateIdMax
} Lightsystem_StateIdType;

typedef enum ETagLightsystem_TransitionIdType{
    Lightsystem_TransitionIdInitToOn,
    Lightsystem_TransitionIdMax
} Lightsystem_TransitionIdType;

/*******************************************************************************
**                      DET Error Codes                                       **
*******************************************************************************/

/*******************************************************************************
**                      Function Prototypes                                   **
*******************************************************************************/

FSM_StatusType Lightsystem_StateInitOnEntry( FSM_ContextTypePtr context );
FSM_StatusType Lightsystem_StateInitCyclic( FSM_ContextTypePtr context );
// FSM_StatusType Lightsystem_StateInitOnExit( FSM_ContextTypePtr context );
FSM_StatusType Lightsystem_StateIdleOnEntry( FSM_ContextTypePtr context );
FSM_StatusType Lightsystem_StateIdleCyclic( FSM_ContextTypePtr context );
// FSM_StatusType Lightsystem_StateIdleOnExit( FSM_ContextTypePtr context );
// FSM_StatusType Lightsystem_StateUpOnEntry( FSM_ContextTypePtr context );
FSM_StatusType Lightsystem_StateUpCyclic( FSM_ContextTypePtr context );
// FSM_StatusType Lightsystem_StateIdleOnExit( FSM_ContextTypePtr context );
// FSM_StatusType Lightsystem_StateDownOnEntry( FSM_ContextTypePtr context );
FSM_StatusType Lightsystem_StateDownCyclic( FSM_ContextTypePtr context );
// FSM_StatusType Lightsystem_StateIdleOnExit( FSM_ContextTypePtr context );
FSM_StatusType Lightsystem_StateActiveOnEntry( FSM_ContextTypePtr context );
FSM_StatusType Lightsystem_StateActiveCyclic( FSM_ContextTypePtr context );
// FSM_StatusType Lightsystem_StateIdleOnExit( FSM_ContextTypePtr context );


FSM_StatusType Lightsystem_StateIdSave1Cyclic( FSM_ContextTypePtr context );
FSM_StatusType Lightsystem_StateIdSave2Cyclic( FSM_ContextTypePtr context );
FSM_StatusType Lightsystem_StateIdSave3Cyclic( FSM_ContextTypePtr context );



// FSM_StatusType Lightsystem_StateOffCyclic( FSM_ContextTypePtr context );

// FSM_StatusType Lightsystem_StateOnOnEntry( FSM_ContextTypePtr context );
FSM_StatusType Lightsystem_StateOnCyclic( FSM_ContextTypePtr context );
// FSM_StatusType Lightsystem_StateOnOnExit( FSM_ContextTypePtr context );

// FSM_StatusType Lightsystem_StateOnUnderVoltageOnEntry( FSM_ContextTypePtr context );
// FSM_StatusType Lightsystem_StateOnUnderVoltageCyclic( FSM_ContextTypePtr context );
// FSM_StatusType Lightsystem_StateOnUnderVoltageOnExit( FSM_ContextTypePtr context );

/*----------------------------------------------------------------------------
** Required Functions declaration
*/

extern const FSM_HandlerConfigType LIGHTSYSTEM_FSM_CONFIGURATION ;

#endif /* LIGHTSYSTEM_FSM_H_ */
