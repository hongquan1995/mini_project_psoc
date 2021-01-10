/*******************************************************************************
* File Name: VM.h  
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

#if !defined(CY_PINS_VM_ALIASES_H) /* Pins VM_ALIASES_H */
#define CY_PINS_VM_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define VM_0			(VM__0__PC)
#define VM_0_PS		(VM__0__PS)
#define VM_0_PC		(VM__0__PC)
#define VM_0_DR		(VM__0__DR)
#define VM_0_SHIFT	(VM__0__SHIFT)
#define VM_0_INTR	((uint16)((uint16)0x0003u << (VM__0__SHIFT*2u)))

#define VM_INTR_ALL	 ((uint16)(VM_0_INTR))


#endif /* End Pins VM_ALIASES_H */


/* [] END OF FILE */
