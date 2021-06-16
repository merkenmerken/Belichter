
#include "Fsm.h"
#include "Fsm_Ram.h"


// #define CALL_STATE_FUNCTION_ON_EXIT(  dfsm, dcontex   ) dfsm->config->lists.states[ dfsm->stateId.active ].onExit( dfsm, dcontex  )


FSM_StatusType Fsm_TaskStates( FSM_HandlerType *fsm );

FSM_StatusType Fsm_Init( FSM_InstanceIdType fsmId, const FSM_HandlerConfigType *config, FSM_StateIdType entryPoint,FSM_ContextTypePtr *context  ){
    FSM_StatusType fsmStatus = FSM_ERROR ;
    if( FSM_MAX_INSTANCES > fsmId){
        fsmStatus = FSM_RUN ;
        Fsm_HandlerInstances[ fsmId ].status  = fsmStatus ;
        Fsm_HandlerInstances[ fsmId ].config  = config  ;
        Fsm_HandlerInstances[ fsmId ].context = context ; 
        Fsm_HandlerInstances[ fsmId ].stateId.last       = FSM_UNINIT_STATE_ID ;
        Fsm_HandlerInstances[ fsmId ].stateId.active     = FSM_UNINIT_STATE_ID ;
        Fsm_HandlerInstances[ fsmId ].stateId.next       = entryPoint          ;
        Fsm_HandlerInstances[ fsmId ].stateId.transition = FSM_UNINIT_STATE_ID ;
    }
    return fsmStatus ;
}

FSM_StatusType Fsm_TaskRun( FSM_InstanceIdType fsmId ){
    
    FSM_StatusType fsmStatus = FSM_ERROR ;
 
    if(    ( FSM_MAX_INSTANCES  > fsmId )
        && ( NULL_PTR          != Fsm_HandlerInstances[ fsmId ].config ) ) {
        fsmStatus = Fsm_HandlerInstances[ fsmId ].status ;
        
        Fsm_HandlerInstances[ fsmId ].iterationTimer = FSM_MAX_STATE_ITERATIONS ;
        while( ( FSM_RUN == fsmStatus ) && ( FSM_ITERATION_TIMER_EXPIRED < Fsm_HandlerInstances[ fsmId ].iterationTimer   )  ){
            
            fsmStatus = Fsm_TaskStates( &(Fsm_HandlerInstances[ fsmId ]) );
            
            if( FSM_ITERATION_TIMER_EXPIRED < Fsm_HandlerInstances[ fsmId ].iterationTimer ){
                Fsm_HandlerInstances[ fsmId ].iterationTimer--;
            }

        }
        if( FSM_ITERATION_TIMER_EXPIRED < Fsm_HandlerInstances[ fsmId ].timer  ){
            Fsm_HandlerInstances[ fsmId ].timer-- ;
        }
        fsmStatus = Fsm_HandlerInstances[ fsmId ].status ;

    }

    return fsmStatus ;

}


Std_ReturnType Fsm_ValidateState( FSM_InstanceIdType fsmId , FSM_StateIdType expectedState ){
    Std_ReturnType vReturnStatus = STD_NOT_OK ;
    if( ( FSM_MAX_INSTANCES  > fsmId ) ) 
    {
        if( Fsm_HandlerInstances[fsmId].stateId.active == expectedState )
        {
            vReturnStatus = STD_OK ;
        }
        else if( Fsm_HandlerInstances[fsmId].stateId.next == expectedState  )
        {
            vReturnStatus = STD_PENDING ;
        }
        else
        {
            vReturnStatus = STD_NOT_OK ;
        }
    }
    
    return vReturnStatus ;
}

FSM_StatusType Fsm_TaskStates( FSM_HandlerType *fsm  ){

    FSM_StatusType fsmStatus = FSM_ERROR ;

    if ( fsm->stateId.next != fsm->stateId.active ){
        fsm->stateId.active = fsm->stateId.next ;
        if( fsm->config->limits.stateId > fsm->stateId.active ){
            if( NULL_PTR != fsm->config->lists.states[ fsm->stateId.active ].onEntry){
                fsmStatus = fsm->config->lists.states[ fsm->stateId.active ].onEntry( fsm->context  );
            }
        }
    }

    if( fsm->config->limits.stateId  > fsm->stateId.transition ){
        fsm->stateId.next       = fsm->stateId.transition      ;
        fsm->stateId.transition = fsm->config->limits.stateId  ;
        fsmStatus               = FSM_RUN                      ;
    }
    else if( fsm->config->limits.stateId > fsm->stateId.active )
    {
        if( NULL_PTR != fsm->config->lists.states[ fsm->stateId.active ].cyclic){
            fsmStatus = fsm->config->lists.states[ fsm->stateId.active ].cyclic(  fsm->context  );
        }
    }
    else
    {
        /* nothing to do but fatal error happens*/
    }
    

    if ( fsm->stateId.active != fsm->stateId.next ){
        fsm->stateId.last = fsm->stateId.active ;
        if( fsm->config->limits.stateId > fsm->stateId.active ){
            if( NULL_PTR != fsm->config->lists.states[ fsm->stateId.active ].onExit ){
                fsmStatus = fsm->config->lists.states[ fsm->stateId.active ].onExit(  fsm->context  );
            }
            //CALL_STATE_FUNCTION_ON_EXIT( fsm, context  );
        }
    }

    return fsmStatus ;
}

FSM_StatusType Fsm_ExternalTransition( FSM_InstanceIdType fsmId , FSM_TransitionIdType transitionId ){
    FSM_StatusType fsmStatus = FSM_ERROR ;
    if( FSM_MAX_INSTANCES > fsmId){
        fsmStatus = FSM_RUN ;
        if( Fsm_HandlerInstances[ fsmId ].config->limits.transitionId > transitionId ){
            if(     ( Fsm_HandlerInstances[ fsmId ].config->lists.transitions[ transitionId ].activeStateId == Fsm_HandlerInstances[ fsmId ].stateId.active )
                ||  ( Fsm_HandlerInstances[ fsmId ].config->lists.transitions[ transitionId ].activeStateId == Fsm_HandlerInstances[ fsmId ].config->limits.stateId ) ){
                Fsm_HandlerInstances[ fsmId ].stateId.transition = Fsm_HandlerInstances[ fsmId ].config->lists.transitions[ transitionId ].nextStateId ;
            }
            
        }
    }
    return fsmStatus ; 
}

// FSM_StatusType Fsm_InternalTransition( FSM_InstanceIdType fsmId , FSM_TransitionIdType transitionId ){
FSM_StatusType Fsm_InternalTransition( FSM_InstanceIdType fsmId , FSM_StateIdType nextStateId ){
    FSM_StatusType fsmStatus = FSM_ERROR ;
    if( FSM_MAX_INSTANCES > fsmId){
        fsmStatus = FSM_RUN ;
        // if( Fsm_HandlerInstances[ fsmId ].config->limits.transitionId > transitionId ){
            // if(     ( Fsm_HandlerInstances[ fsmId ].config->lists.transitions[ transitionId ].activeStateId == Fsm_HandlerInstances[ fsmId ].stateId.active )
            //     ||  ( Fsm_HandlerInstances[ fsmId ].config->lists.transitions[ transitionId ].activeStateId == Fsm_HandlerInstances[ fsmId ].config->limits.stateId ) ){
            //     Fsm_HandlerInstances[ fsmId ].stateId.next = Fsm_HandlerInstances[ fsmId ].config->lists.transitions[ transitionId ].nextStateId ;
            // }
            // else
            // {
            //     ;//Lint
            // }
        // }
        Fsm_HandlerInstances[ fsmId ].stateId.next = nextStateId ;
    }
    return fsmStatus ; 
}

FSM_StatusType Fsm_SetIterationTimerLimit( FSM_InstanceIdType fsmId , FSM_StateIterationType iterationTime ){
    FSM_StatusType fsmStatus = FSM_ERROR ;
    if( FSM_MAX_INSTANCES > fsmId){
        fsmStatus = FSM_RUN ;
        if(    ( FSM_MAX_STATE_ITERATIONS == Fsm_HandlerInstances[ fsmId ].iterationTimer )
            && ( FSM_MAX_STATE_ITERATIONS > iterationTime) ){
            Fsm_HandlerInstances[ fsmId ].iterationTimer = iterationTime ;
        }
    }
    return fsmStatus ; 
}


FSM_StatusType Fsm_StartTimer( FSM_InstanceIdType fsmId , FSM_StateIterationType iterationTime ){
    FSM_StatusType fsmStatus = FSM_ERROR ;
    if( FSM_MAX_INSTANCES > fsmId){
        fsmStatus = FSM_RUN ;
        if( FSM_ITERATION_TIMER_EXPIRED == Fsm_HandlerInstances[ fsmId ].timer  ){
            if( FSM_ITERATION_TIMER_EXPIRED < iterationTime){
                Fsm_HandlerInstances[ fsmId ].timer = iterationTime ;
            }
        }
    }
    return fsmStatus ; 
}


FSM_StatusType Fsm_GetTimerStatus( FSM_InstanceIdType fsmId  ){
    FSM_StatusType fsmStatus = FSM_ERROR ;
    if( FSM_MAX_INSTANCES > fsmId){
        
        if( FSM_ITERATION_TIMER_EXPIRED == Fsm_HandlerInstances[ fsmId ].timer  ){
            fsmStatus = FSM_STOP ;
        }
        else
        {
            fsmStatus = FSM_RUN ;
        }
    }
    return fsmStatus ; 
}

FSM_StatusType Fsm_GetCurrentState( FSM_InstanceIdType vFsmId , FSM_StateIdType *pFsmState ){
    FSM_StatusType fsmStatus = FSM_ERROR ;
    if( FSM_MAX_INSTANCES > vFsmId){
        
        if( NULL_PTR != pFsmState ){
            *pFsmState = Fsm_HandlerInstances[vFsmId].stateId.active ;
            fsmStatus = FSM_UNINIT ;
        }
    }
    return fsmStatus ; 
}

