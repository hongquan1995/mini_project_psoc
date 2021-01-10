/*******************************************************************************
* File Name: MUX_C.c  
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
#include "MUX_C.h"

static MUX_C_BACKUP_STRUCT  MUX_C_backup = {0u, 0u, 0u};


/*******************************************************************************
* Function Name: MUX_C_Sleep
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
*  \snippet MUX_C_SUT.c usage_MUX_C_Sleep_Wakeup
*******************************************************************************/
void MUX_C_Sleep(void)
{
    #if defined(MUX_C__PC)
        MUX_C_backup.pcState = MUX_C_PC;
    #else
        #if (CY_PSOC4_4200L)
            /* Save the regulator state and put the PHY into suspend mode */
            MUX_C_backup.usbState = MUX_C_CR1_REG;
            MUX_C_USB_POWER_REG |= MUX_C_USBIO_ENTER_SLEEP;
            MUX_C_CR1_REG &= MUX_C_USBIO_CR1_OFF;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(MUX_C__SIO)
        MUX_C_backup.sioState = MUX_C_SIO_REG;
        /* SIO requires unregulated output buffer and single ended input buffer */
        MUX_C_SIO_REG &= (uint32)(~MUX_C_SIO_LPM_MASK);
    #endif  
}


/*******************************************************************************
* Function Name: MUX_C_Wakeup
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
*  Refer to MUX_C_Sleep() for an example usage.
*******************************************************************************/
void MUX_C_Wakeup(void)
{
    #if defined(MUX_C__PC)
        MUX_C_PC = MUX_C_backup.pcState;
    #else
        #if (CY_PSOC4_4200L)
            /* Restore the regulator state and come out of suspend mode */
            MUX_C_USB_POWER_REG &= MUX_C_USBIO_EXIT_SLEEP_PH1;
            MUX_C_CR1_REG = MUX_C_backup.usbState;
            MUX_C_USB_POWER_REG &= MUX_C_USBIO_EXIT_SLEEP_PH2;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(MUX_C__SIO)
        MUX_C_SIO_REG = MUX_C_backup.sioState;
    #endif
}


/* [] END OF FILE */
