/*******************************************************************************
* File Name: W_ADC.h  
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

#if !defined(CY_PINS_W_ADC_ALIASES_H) /* Pins W_ADC_ALIASES_H */
#define CY_PINS_W_ADC_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define W_ADC_0			(W_ADC__0__PC)
#define W_ADC_0_PS		(W_ADC__0__PS)
#define W_ADC_0_PC		(W_ADC__0__PC)
#define W_ADC_0_DR		(W_ADC__0__DR)
#define W_ADC_0_SHIFT	(W_ADC__0__SHIFT)
#define W_ADC_0_INTR	((uint16)((uint16)0x0003u << (W_ADC__0__SHIFT*2u)))

#define W_ADC_INTR_ALL	 ((uint16)(W_ADC_0_INTR))


#endif /* End Pins W_ADC_ALIASES_H */


/* [] END OF FILE */
