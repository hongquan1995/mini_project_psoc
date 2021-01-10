/*******************************************************************************
* File Name: MUX_C.h  
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

#if !defined(CY_PINS_MUX_C_ALIASES_H) /* Pins MUX_C_ALIASES_H */
#define CY_PINS_MUX_C_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define MUX_C_0			(MUX_C__0__PC)
#define MUX_C_0_PS		(MUX_C__0__PS)
#define MUX_C_0_PC		(MUX_C__0__PC)
#define MUX_C_0_DR		(MUX_C__0__DR)
#define MUX_C_0_SHIFT	(MUX_C__0__SHIFT)
#define MUX_C_0_INTR	((uint16)((uint16)0x0003u << (MUX_C__0__SHIFT*2u)))

#define MUX_C_INTR_ALL	 ((uint16)(MUX_C_0_INTR))


#endif /* End Pins MUX_C_ALIASES_H */


/* [] END OF FILE */
