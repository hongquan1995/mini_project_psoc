/*******************************************************************************
* File Name: GLCD_CS.h  
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

#if !defined(CY_PINS_GLCD_CS_ALIASES_H) /* Pins GLCD_CS_ALIASES_H */
#define CY_PINS_GLCD_CS_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define GLCD_CS_0			(GLCD_CS__0__PC)
#define GLCD_CS_0_PS		(GLCD_CS__0__PS)
#define GLCD_CS_0_PC		(GLCD_CS__0__PC)
#define GLCD_CS_0_DR		(GLCD_CS__0__DR)
#define GLCD_CS_0_SHIFT	(GLCD_CS__0__SHIFT)
#define GLCD_CS_0_INTR	((uint16)((uint16)0x0003u << (GLCD_CS__0__SHIFT*2u)))

#define GLCD_CS_INTR_ALL	 ((uint16)(GLCD_CS_0_INTR))


#endif /* End Pins GLCD_CS_ALIASES_H */


/* [] END OF FILE */
