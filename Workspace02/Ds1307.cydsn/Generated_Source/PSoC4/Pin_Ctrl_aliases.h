/*******************************************************************************
* File Name: Pin_Ctrl.h  
* Version 2.20
*
* Description:
*  This file contains the Alias definitions for Per-Pin APIs in cypins.h. 
*  Information on using these APIs can be found in the System Reference Guide.
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_Pin_Ctrl_ALIASES_H) /* Pins Pin_Ctrl_ALIASES_H */
#define CY_PINS_Pin_Ctrl_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define Pin_Ctrl_0			(Pin_Ctrl__0__PC)
#define Pin_Ctrl_0_PS		(Pin_Ctrl__0__PS)
#define Pin_Ctrl_0_PC		(Pin_Ctrl__0__PC)
#define Pin_Ctrl_0_DR		(Pin_Ctrl__0__DR)
#define Pin_Ctrl_0_SHIFT	(Pin_Ctrl__0__SHIFT)
#define Pin_Ctrl_0_INTR	((uint16)((uint16)0x0003u << (Pin_Ctrl__0__SHIFT*2u)))

#define Pin_Ctrl_1			(Pin_Ctrl__1__PC)
#define Pin_Ctrl_1_PS		(Pin_Ctrl__1__PS)
#define Pin_Ctrl_1_PC		(Pin_Ctrl__1__PC)
#define Pin_Ctrl_1_DR		(Pin_Ctrl__1__DR)
#define Pin_Ctrl_1_SHIFT	(Pin_Ctrl__1__SHIFT)
#define Pin_Ctrl_1_INTR	((uint16)((uint16)0x0003u << (Pin_Ctrl__1__SHIFT*2u)))

#define Pin_Ctrl_2			(Pin_Ctrl__2__PC)
#define Pin_Ctrl_2_PS		(Pin_Ctrl__2__PS)
#define Pin_Ctrl_2_PC		(Pin_Ctrl__2__PC)
#define Pin_Ctrl_2_DR		(Pin_Ctrl__2__DR)
#define Pin_Ctrl_2_SHIFT	(Pin_Ctrl__2__SHIFT)
#define Pin_Ctrl_2_INTR	((uint16)((uint16)0x0003u << (Pin_Ctrl__2__SHIFT*2u)))

#define Pin_Ctrl_3			(Pin_Ctrl__3__PC)
#define Pin_Ctrl_3_PS		(Pin_Ctrl__3__PS)
#define Pin_Ctrl_3_PC		(Pin_Ctrl__3__PC)
#define Pin_Ctrl_3_DR		(Pin_Ctrl__3__DR)
#define Pin_Ctrl_3_SHIFT	(Pin_Ctrl__3__SHIFT)
#define Pin_Ctrl_3_INTR	((uint16)((uint16)0x0003u << (Pin_Ctrl__3__SHIFT*2u)))

#define Pin_Ctrl_INTR_ALL	 ((uint16)(Pin_Ctrl_0_INTR| Pin_Ctrl_1_INTR| Pin_Ctrl_2_INTR| Pin_Ctrl_3_INTR))


#endif /* End Pins Pin_Ctrl_ALIASES_H */


/* [] END OF FILE */
