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

/***********************************************************************************************
**                              Include Section                                               **
***********************************************************************************************/

#include "CDD_Lightsystem_Fsm.h"



/***********************************************************************************************
**                              MISRA C Rule Violations                                       **
***********************************************************************************************/

    /**************************************************************************************/
    /* 1. MISRA C RULE VIOLATION:                                                         */
    /* Message       : Duplicate initialization of object element                         */
    /* Lint Id       : Warnung 485                                                        */
    /* Rule          : MISRA 2012 Rule 9.4, required                                      */
    /* Justification :                                                                    */
    /* Verification  :                                                                    */
    /* Reference     : LINT[485:1]                                                        */
    /**************************************************************************************/



/***********************************************************************************************
**                                 Global Data                                                **
***********************************************************************************************/

/*******************************************************************************
**                      State configuration Section                           **
*******************************************************************************/
/*lint -e485 LINT[485:1] */
const FSM_StateType  LIGHTSYSTEM_FSM_STATES[ Lightsystem_StateIdMax ]={
    {
        .id          = (FSM_StateIdType) Lightsystem_StateIdInit        ,
        .onEntry     = Lightsystem_StateInitOnEntry ,
        .cyclic      = Lightsystem_StateInitCyclic ,
        .onExit      = NULL_PTR 
    },
    {
        .id          = (FSM_StateIdType) Lightsystem_StateIdIdle        ,
        .onEntry     = Lightsystem_StateIdleOnEntry ,
        .cyclic      = Lightsystem_StateIdleCyclic ,
        .onExit      = NULL_PTR 
    },
    {
        .id          = (FSM_StateIdType) Lightsystem_StateIdUp       ,
        .onEntry     = NULL_PTR ,
        .cyclic      = Lightsystem_StateUpCyclic ,
        .onExit      = NULL_PTR 
    },
    {
        .id          = (FSM_StateIdType) Lightsystem_StateIdDown        ,
        .onEntry     = NULL_PTR ,
        .cyclic      = Lightsystem_StateDownCyclic ,
        .onExit      = NULL_PTR 
    },
    {
        .id          = (FSM_StateIdType) Lightsystem_StateIdActive        ,
        .onEntry     = Lightsystem_StateActiveOnEntry ,
        .cyclic      = Lightsystem_StateActiveCyclic ,
        .onExit      = NULL_PTR 
    },

    {
        .id          = (FSM_StateIdType) Lightsystem_StateIdSave1        ,
        .onEntry     = NULL_PTR ,
        .cyclic      = Lightsystem_StateIdSave1Cyclic ,
        .onExit      = NULL_PTR 
    },

    {
        .id          = (FSM_StateIdType) Lightsystem_StateIdSave2        ,
        .onEntry     = NULL_PTR ,
        .cyclic      = Lightsystem_StateIdSave2Cyclic ,
        .onExit      = NULL_PTR 
    },

    {
        .id          = (FSM_StateIdType) Lightsystem_StateIdSave3        ,
        .onEntry     = NULL_PTR ,
        .cyclic      = Lightsystem_StateIdSave3Cyclic ,
        .onExit      = NULL_PTR 
    },


    // {
    //     .id          = (FSM_StateIdType) Lightsystem_StateIdOff        ,
    //     .onEntry     = NULL_PTR ,
    //     .cyclic      = Lightsystem_StateOffCyclic ,
    //     .onExit      = NULL_PTR 
    // },
    // {
    //     .id          = (FSM_StateIdType) Lightsystem_StateIdOn        ,
    //     .onEntry     = NULL_PTR ,
    //     .cyclic      = Lightsystem_StateOnCyclic ,
    //     .onExit      = NULL_PTR 
    // }
    // ,
    // {
    //     .id          = (FSM_StateIdType) Lightsystem_StateIdOnUnderVoltage ,
    //     .onEntry     = Lightsystem_StateOnUnderVoltageOnEntry ,
    //     .cyclic      = Lightsystem_StateOnUnderVoltageCyclic ,
    //     .onExit      = Lightsystem_StateOnUnderVoltageOnExit 
    // }
};
/*lint +e485 LINT[485:1] */
/*******************************************************************************
**                      Event configuration Section                           **
*******************************************************************************/

// FSM_EventType TPS92520_FSM_EVENTS[ 1 ]={

// };

/*******************************************************************************
**                      Transition configuration Section                      **
*******************************************************************************/
/*lint -e485 LINT[485:1] */
const FSM_TransitionType LIGHTSYSTEM_FSM_TRANSITIONS[ Lightsystem_TransitionIdMax ]={
    /*  Transition from init state to off states */
    {
        .id             = (FSM_StateIdType) Lightsystem_TransitionIdInitToOn ,
        .activeStateId  = (FSM_StateIdType) Lightsystem_StateIdInit ,
        .nextStateId    = (FSM_StateIdType) Lightsystem_StateIdIdle  
    }
    // ,
    // /*  Transition from off state to init state */
    // {
    //     .id             = (FSM_StateIdType) Lightsystem_TransitionIdOffToInit ,
    //     .activeStateId  = (FSM_StateIdType) Lightsystem_StateIdOff   ,
    //     .nextStateId    = (FSM_StateIdType) Lightsystem_StateIdInit
    // },
    // /*  Transition from off state to on state */
    // {
    //     .id             = (FSM_StateIdType) Lightsystem_TransitionIdOffToOn ,
    //     .activeStateId  = (FSM_StateIdType) Lightsystem_StateIdOff   ,
    //     .nextStateId    = (FSM_StateIdType) Lightsystem_StateIdOn
    // },
    // /*  Transition from on state to off state */
    // {
    //     .id             = (FSM_StateIdType) Lightsystem_TransitionIdOnToOff ,
    //     .activeStateId  = (FSM_StateIdType) Lightsystem_StateIdOn   ,
    //     .nextStateId    = (FSM_StateIdType) Lightsystem_StateIdOff
    // },
    // /*  Transition from on state to on undervoltage state */
    // {
    //     .id             = (FSM_StateIdType) Lightsystem_TransitionIdOnToOnUnderVoltage ,
    //     .activeStateId  = (FSM_StateIdType) Lightsystem_StateIdOn ,
    //     .nextStateId    = (FSM_StateIdType) Lightsystem_StateIdOnUnderVoltage
    // },
    // /*  Transition from on state to on undervoltage state */
    // {
    //     .id             = (FSM_StateIdType) Lightsystem_TransitionIdOnUnderVoltageToOn ,
    //     .activeStateId  = (FSM_StateIdType) Lightsystem_StateIdOnUnderVoltage,
    //     .nextStateId    = (FSM_StateIdType) Lightsystem_StateIdOn
    // },
    // /*  Transition from on state to on undervoltage state */
    // {
    //     .id             = (FSM_StateIdType) Lightsystem_TransitionIdAllToInit ,
    //     .activeStateId  = (FSM_StateIdType) Lightsystem_StateIdMax,
    //     .nextStateId    = (FSM_StateIdType) Lightsystem_StateIdInit
    // }
};
/*lint +e485 LINT[485:1] */
/*******************************************************************************
**                      FSM configuration Section                             **
*******************************************************************************/

const FSM_HandlerConfigType LIGHTSYSTEM_FSM_CONFIGURATION = {
    .lists = {
        .states      = LIGHTSYSTEM_FSM_STATES      ,
        .events      = NULL_PTR                 ,
        .transitions = LIGHTSYSTEM_FSM_TRANSITIONS ,
    },
    .limits = {
        .stateId      = (FSM_StateIdType) Lightsystem_StateIdMax,
        .eventId      = (FSM_EventIdType) 0,
        .transitionId = (FSM_StateIdType) Lightsystem_TransitionIdMax
    }
};




/***********************************************************************************************
**                              Function Definitions                                          **
***********************************************************************************************/


