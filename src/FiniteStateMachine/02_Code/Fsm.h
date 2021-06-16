#ifndef FSM_H_
#define FSM_H_

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/

#include "fsm_Cfg.h"
#include "fsm_Types.h"      /* Included for FSM Type declaration */

/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/

#define FSM_INSTANCE_ID            FSM_INSTANCE_ID_VALUE
/* Version identification */
#define FSM_MODULE_ID              FSM_MODULE_ID_VALUE

/*******************************************************************************
**                     Service IDs                                            **
*******************************************************************************/
/* Service ID for FSM_Init() */
#define FSM_INIT_SID                  (uint8)0x00
/* Service ID for FSM_DeInit() */
#define FSM_DEINIT_SID                (uint8)0x01



/*******************************************************************************
**                      DET Error Codes                                       **
*******************************************************************************/
/* API services invoked with invalid driver ID */
#define FSM_E_PARAM_DRIVER            (uint8)0x0A


#define FSM_E_ALREADY_INITIALIZED     (uint8)0x4A

/*******************************************************************************
**                      Function Prototypes                                   **
*******************************************************************************/
FSM_StatusType Fsm_Init( FSM_InstanceIdType fsmId, const FSM_HandlerConfigType *config, FSM_StateIdType entryPoint, FSM_ContextTypePtr *context  );
FSM_StatusType Fsm_TaskRun( FSM_InstanceIdType fsmId  );

Std_ReturnType Fsm_ValidateState( FSM_InstanceIdType fsmId , FSM_StateIdType expectedState );

FSM_StatusType Fsm_ExternalTransition( FSM_InstanceIdType fsmId , FSM_TransitionIdType transitionId );
FSM_StatusType Fsm_InternalTransition( FSM_InstanceIdType fsmId , FSM_TransitionIdType transitionId );

FSM_StatusType Fsm_SetIterationTimerLimit( FSM_InstanceIdType fsmId , FSM_StateIterationType iterationTime );

FSM_StatusType Fsm_StartTimer( FSM_InstanceIdType fsmId , FSM_StateIterationType iterationTime );
FSM_StatusType Fsm_GetTimerStatus( FSM_InstanceIdType fsmId  );
FSM_StatusType Fsm_GetCurrentState( FSM_InstanceIdType vFsmId , FSM_StateIdType *pFsmState );

#endif /* FSM_H_ */

