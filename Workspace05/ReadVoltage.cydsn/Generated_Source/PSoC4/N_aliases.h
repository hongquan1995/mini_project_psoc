/*******************************************************************************
* File Name: N.h  
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

#if !defined(CY_PINS_N_ALIASES_H) /* Pins N_ALIASES_H */
#define CY_PINS_N_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define N_0			(N__0__PC)
#define N_0_PS		(N__0__PS)
#define N_0_PC		(N__0__PC)
#define N_0_DR		(N__0__DR)
#define N_0_SHIFT	(N__0__SHIFT)
#define N_0_INTR	((uint16)((uint16)0x0003u << (N__0__SHIFT*2u)))

#define N_INTR_ALL	 ((uint16)(N_0_INTR))


#endif /* End Pins N_ALIASES_H */


/* [] END OF FILE */
