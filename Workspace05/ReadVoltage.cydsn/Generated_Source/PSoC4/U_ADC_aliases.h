/*******************************************************************************
* File Name: U_ADC.h  
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

#if !defined(CY_PINS_U_ADC_ALIASES_H) /* Pins U_ADC_ALIASES_H */
#define CY_PINS_U_ADC_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define U_ADC_0			(U_ADC__0__PC)
#define U_ADC_0_PS		(U_ADC__0__PS)
#define U_ADC_0_PC		(U_ADC__0__PC)
#define U_ADC_0_DR		(U_ADC__0__DR)
#define U_ADC_0_SHIFT	(U_ADC__0__SHIFT)
#define U_ADC_0_INTR	((uint16)((uint16)0x0003u << (U_ADC__0__SHIFT*2u)))

#define U_ADC_INTR_ALL	 ((uint16)(U_ADC_0_INTR))


#endif /* End Pins U_ADC_ALIASES_H */


/* [] END OF FILE */
