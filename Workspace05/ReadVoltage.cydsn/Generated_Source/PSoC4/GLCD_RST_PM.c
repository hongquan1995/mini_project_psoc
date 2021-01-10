/*******************************************************************************
* File Name: GLCD_RST.c  
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
#include "GLCD_RST.h"

static GLCD_RST_BACKUP_STRUCT  GLCD_RST_backup = {0u, 0u, 0u};


/*******************************************************************************
* Function Name: GLCD_RST_Sleep
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
*  \snippet GLCD_RST_SUT.c usage_GLCD_RST_Sleep_Wakeup
*******************************************************************************/
void GLCD_RST_Sleep(void)
{
    #if defined(GLCD_RST__PC)
        GLCD_RST_backup.pcState = GLCD_RST_PC;
    #else
        #if (CY_PSOC4_4200L)
            /* Save the regulator state and put the PHY into suspend mode */
            GLCD_RST_backup.usbState = GLCD_RST_CR1_REG;
            GLCD_RST_USB_POWER_REG |= GLCD_RST_USBIO_ENTER_SLEEP;
            GLCD_RST_CR1_REG &= GLCD_RST_USBIO_CR1_OFF;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(GLCD_RST__SIO)
        GLCD_RST_backup.sioState = GLCD_RST_SIO_REG;
        /* SIO requires unregulated output buffer and single ended input buffer */
        GLCD_RST_SIO_REG &= (uint32)(~GLCD_RST_SIO_LPM_MASK);
    #endif  
}


/*******************************************************************************
* Function Name: GLCD_RST_Wakeup
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
*  Refer to GLCD_RST_Sleep() for an example usage.
*******************************************************************************/
void GLCD_RST_Wakeup(void)
{
    #if defined(GLCD_RST__PC)
        GLCD_RST_PC = GLCD_RST_backup.pcState;
    #else
        #if (CY_PSOC4_4200L)
            /* Restore the regulator state and come out of suspend mode */
            GLCD_RST_USB_POWER_REG &= GLCD_RST_USBIO_EXIT_SLEEP_PH1;
            GLCD_RST_CR1_REG = GLCD_RST_backup.usbState;
            GLCD_RST_USB_POWER_REG &= GLCD_RST_USBIO_EXIT_SLEEP_PH2;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(GLCD_RST__SIO)
        GLCD_RST_SIO_REG = GLCD_RST_backup.sioState;
    #endif
}


/* [] END OF FILE */
