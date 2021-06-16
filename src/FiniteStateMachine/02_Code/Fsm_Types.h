#ifndef FSM_TYPES_H_
#define FSM_TYPES_H_

/*******************************************************************************
**                     Include Section                                        **
*******************************************************************************/

/* AUTOSAR standard types */
#include "Std_Types.h"
// #include "BswStd_Types.h"

/*******************************************************************************
**                      Global Symbols                                        **
*******************************************************************************/

#define FSM_ITERATION_TIMER_EXPIRED ( (FSM_StateIterationType) 0 )

#define FSM_UNINIT_STATE_ID ( (FSM_StateIdType) -1 )

/*******************************************************************************
**                   FSM TYPE DEFINITION                                 **
*******************************************************************************/

typedef void* FSM_ContextTypePtr ;

/* Definition of type for Instance ID */
typedef uint8_t FSM_InstanceIdType;

typedef uint8_t FSM_StateIterationType;

/* Definition of status type */
typedef enum ETagFSM_StatusType
{
  FSM_UNINIT = 0,
  FSM_RUN,
  FSM_STOP,
  FSM_DIAGNOSTIG,
  FSM_ERROR
} FSM_StatusType;

typedef struct FSM_HandlerType FSM_HandlerType ;

/* Definition of type for State ID */
typedef uint8_t FSM_StateIdType ;
typedef FSM_StatusType (*FSM_StateFunctionType)( void* context )  ;
typedef struct {
    FSM_StateIdType       id          ;
    FSM_StateFunctionType onEntry     ;
    FSM_StateFunctionType cyclic      ;
    FSM_StateFunctionType onExit      ;
} FSM_StateType ;

/* Definition of type for Event ID */
typedef uint8_t FSM_EventIdType ;

typedef FSM_StatusType (*FSM_EventFunctionType)( void* context )  ;

typedef struct{
    FSM_EventIdType       id       ;
    FSM_EventFunctionType callback ;
} FSM_EventType ;

/* Definition of type for Transition ID */
typedef uint8_t FSM_TransitionIdType ;

typedef FSM_StatusType (*FSM_TransitionFunctionType)( void* context )  ;

typedef struct {
    FSM_TransitionIdType       id                ;
    FSM_StateIdType            activeStateId     ;
    FSM_StateIdType            nextStateId       ;
} FSM_TransitionType ;


typedef struct {
    const FSM_StateType      *states  ;
    const FSM_EventType      *events  ;
    const FSM_TransitionType *transitions  ;
} FSM_ListsConfigType ;

typedef struct {
    FSM_StateIdType      stateId     ;
    FSM_EventIdType      eventId      ;
    FSM_TransitionIdType transitionId ;
} FSM_ListsLimitsConfigType ;

typedef struct {
    FSM_ListsConfigType       lists ;
    FSM_ListsLimitsConfigType limits ;
} FSM_HandlerConfigType ;

typedef struct {
    FSM_StateIdType      last   ;
    FSM_StateIdType      active ;
    FSM_StateIdType      next   ;
    FSM_TransitionIdType transition ;
} FSM_StateHistoryType ;

struct FSM_HandlerType {
    const FSM_HandlerConfigType *config ;
    FSM_ContextTypePtr     context ;
    FSM_StateHistoryType   stateId ;
    FSM_StateIterationType iterationTimer ;
    FSM_StateIterationType timer ;
    FSM_StatusType         status  ;
} ;




#endif /* FSM_TYPES_H_ */

