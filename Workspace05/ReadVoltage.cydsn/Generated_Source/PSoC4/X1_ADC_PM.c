/*******************************************************************************
* File Name: X1_ADC.c  
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
#include "X1_ADC.h"

static X1_ADC_BACKUP_STRUCT  X1_ADC_backup = {0u, 0u, 0u};


/*******************************************************************************
* Function Name: X1_ADC_Sleep
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
*  \snippet X1_ADC_SUT.c usage_X1_ADC_Sleep_Wakeup
*******************************************************************************/
void X1_ADC_Sleep(void)
{
    #if defined(X1_ADC__PC)
        X1_ADC_backup.pcState = X1_ADC_PC;
    #else
        #if (CY_PSOC4_4200L)
            /* Save the regulator state and put the PHY into suspend mode */
            X1_ADC_backup.usbState = X1_ADC_CR1_REG;
            X1_ADC_USB_POWER_REG |= X1_ADC_USBIO_ENTER_SLEEP;
            X1_ADC_CR1_REG &= X1_ADC_USBIO_CR1_OFF;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(X1_ADC__SIO)
        X1_ADC_backup.sioState = X1_ADC_SIO_REG;
        /* SIO requires unregulated output buffer and single ended input buffer */
        X1_ADC_SIO_REG &= (uint32)(~X1_ADC_SIO_LPM_MASK);
    #endif  
}


/*******************************************************************************
* Function Name: X1_ADC_Wakeup
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
*  Refer to X1_ADC_Sleep() for an example usage.
*******************************************************************************/
void X1_ADC_Wakeup(void)
{
    #if defined(X1_ADC__PC)
        X1_ADC_PC = X1_ADC_backup.pcState;
    #else
        #if (CY_PSOC4_4200L)
            /* Restore the regulator state and come out of suspend mode */
            X1_ADC_USB_POWER_REG &= X1_ADC_USBIO_EXIT_SLEEP_PH1;
            X1_ADC_CR1_REG = X1_ADC_backup.usbState;
            X1_ADC_USB_POWER_REG &= X1_ADC_USBIO_EXIT_SLEEP_PH2;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(X1_ADC__SIO)
        X1_ADC_SIO_REG = X1_ADC_backup.sioState;
    #endif
}


/* [] END OF FILE */
