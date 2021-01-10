/*******************************************************************************
* File Name: GLCD_SS.c  
* Version 2.20
*
* Description:
*  This file contains APIs to set up the Pins component for low power modes.
*
* Note:
*
********************************************************************************
* Copyright 2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "cytypes.h"
#include "GLCD_SS.h"

static GLCD_SS_BACKUP_STRUCT  GLCD_SS_backup = {0u, 0u, 0u};


/*******************************************************************************
* Function Name: GLCD_SS_Sleep
****************************************************************************//**
*
* \brief Stores the pin configuration and prepares the pin for entering chip 
*  deep-sleep/hibernate modes. This function applies only to SIO and USBIO pins.
*  It should not be called for GPIO or GPIO_OVT pins.
*
* <b>Note</b> This function is available in PSoC 4 only.
*
* \return 
*  None 
*  
* \sideeffect
*  For SIO pins, this function configures the pin input threshold to CMOS and
*  drive level to Vddio. This is needed for SIO pins when in device 
*  deep-sleep/hibernate modes.
*
* \funcusage
*  \snippet GLCD_SS_SUT.c usage_GLCD_SS_Sleep_Wakeup
*******************************************************************************/
void GLCD_SS_Sleep(void)
{
    #if defined(GLCD_SS__PC)
        GLCD_SS_backup.pcState = GLCD_SS_PC;
    #else
        #if (CY_PSOC4_4200L)
            /* Save the regulator state and put the PHY into suspend mode */
            GLCD_SS_backup.usbState = GLCD_SS_CR1_REG;
            GLCD_SS_USB_POWER_REG |= GLCD_SS_USBIO_ENTER_SLEEP;
            GLCD_SS_CR1_REG &= GLCD_SS_USBIO_CR1_OFF;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(GLCD_SS__SIO)
        GLCD_SS_backup.sioState = GLCD_SS_SIO_REG;
        /* SIO requires unregulated output buffer and single ended input buffer */
        GLCD_SS_SIO_REG &= (uint32)(~GLCD_SS_SIO_LPM_MASK);
    #endif  
}


/*******************************************************************************
* Function Name: GLCD_SS_Wakeup
****************************************************************************//**
*
* \brief Restores the pin configuration that was saved during Pin_Sleep(). This 
* function applies only to SIO and USBIO pins. It should not be called for
* GPIO or GPIO_OVT pins.
*
* For USBIO pins, the wakeup is only triggered for falling edge interrupts.
*
* <b>Note</b> This function is available in PSoC 4 only.
*
* \return 
*  None
*  
* \funcusage
*  Refer to GLCD_SS_Sleep() for an example usage.
*******************************************************************************/
void GLCD_SS_Wakeup(void)
{
    #if defined(GLCD_SS__PC)
        GLCD_SS_PC = GLCD_SS_backup.pcState;
    #else
        #if (CY_PSOC4_4200L)
            /* Restore the regulator state and come out of suspend mode */
            GLCD_SS_USB_POWER_REG &= GLCD_SS_USBIO_EXIT_SLEEP_PH1;
            GLCD_SS_CR1_REG = GLCD_SS_backup.usbState;
            GLCD_SS_USB_POWER_REG &= GLCD_SS_USBIO_EXIT_SLEEP_PH2;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(GLCD_SS__SIO)
        GLCD_SS_SIO_REG = GLCD_SS_backup.sioState;
    #endif
}


/* [] END OF FILE */
