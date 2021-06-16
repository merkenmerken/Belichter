/*============================================================================*/
/* Project      = AUTOSAR STD_SW_COMPONENT_FSM                           */
/* Module       = FSM_Cfg.h                                              */
/*============================================================================*/
/*                                  COPYRIGHT                                 */
/*============================================================================*/
/* Copyright(c) 2012-2016 Lear Corporation Engineering GmbH                   */
/*============================================================================*/
/* Purpose:                                                                   */
/* This file contains the definitions of pre-compile time parameters.         */
/* AUTOMATICALLY GENERATED FILE - DO NOT EDIT                                 */
/*============================================================================*/
/*                                                                            */
/*                                                                            */
/*============================================================================*/
/* Environment:                                                               */
/*              Devices:        X1x                                           */
/*============================================================================*/
#ifndef FSM_CFG_H_
#define FSM_CFG_H_

/*******************************************************************************
**                       Common Published Information                         **
*******************************************************************************/

#define FSM_MODULE_ID_VALUE  22U

/*******************************************************************************
**                      Global Symbols                                        **
*******************************************************************************/

/* Instance ID of the FSM FSMDriver*/
#define FSM_INSTANCE_ID_VALUE                     0U

/* Enables/Disables Development error detection */
#define FSM_DEV_ERROR_DETECT                  STD_ON

/*
 * Enables/Disables the FSM_E_ALREADY_INITIALIZED Det error check 
 * in FSM_Init API
 */
#define FSM_ALREADY_INIT_DET_CHECK            STD_ON


#define FSM_MAX_STATE_ITERATIONS  (FSM_StateIterationType)10

#define FSM_MAX_INSTANCES         (FSM_InstanceIdType)1


/* Handles for configured TPS92520 devices */
#define SM_Lightsystem (FSM_InstanceIdType)0


#endif /* FSM_CFG_H_ */

/*******************************************************************************
**                          End of File                                       **
*******************************************************************************/

