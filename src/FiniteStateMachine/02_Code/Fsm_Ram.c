

#include "Fsm.h"
#include "Fsm_Ram.h"


FSM_HandlerType Fsm_HandlerInstances[ FSM_MAX_INSTANCES ] = {
    {     
        .config  = NULL_PTR ,
        .stateId = { 0 ,0 ,0 ,0 }, 
        .status  = FSM_UNINIT 
    }
};


