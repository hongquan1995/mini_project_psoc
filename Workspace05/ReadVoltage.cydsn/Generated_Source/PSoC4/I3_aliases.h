/*******************************************************************************
* File Name: I3.h  
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

#if !defined(CY_PINS_I3_ALIASES_H) /* Pins I3_ALIASES_H */
#define CY_PINS_I3_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define I3_0			(I3__0__PC)
#define I3_0_PS		(I3__0__PS)
#define I3_0_PC		(I3__0__PC)
#define I3_0_DR		(I3__0__DR)
#define I3_0_SHIFT	(I3__0__SHIFT)
#define I3_0_INTR	((uint16)((uint16)0x0003u << (I3__0__SHIFT*2u)))

#define I3_INTR_ALL	 ((uint16)(I3_0_INTR))


#endif /* End Pins I3_ALIASES_H */


/* [] END OF FILE */
