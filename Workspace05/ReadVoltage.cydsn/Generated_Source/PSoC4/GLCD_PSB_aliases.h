/*******************************************************************************
* File Name: GLCD_PSB.h  
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

#if !defined(CY_PINS_GLCD_PSB_ALIASES_H) /* Pins GLCD_PSB_ALIASES_H */
#define CY_PINS_GLCD_PSB_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define GLCD_PSB_0			(GLCD_PSB__0__PC)
#define GLCD_PSB_0_PS		(GLCD_PSB__0__PS)
#define GLCD_PSB_0_PC		(GLCD_PSB__0__PC)
#define GLCD_PSB_0_DR		(GLCD_PSB__0__DR)
#define GLCD_PSB_0_SHIFT	(GLCD_PSB__0__SHIFT)
#define GLCD_PSB_0_INTR	((uint16)((uint16)0x0003u << (GLCD_PSB__0__SHIFT*2u)))

#define GLCD_PSB_INTR_ALL	 ((uint16)(GLCD_PSB_0_INTR))


#endif /* End Pins GLCD_PSB_ALIASES_H */


/* [] END OF FILE */
