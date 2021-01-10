/***************************************************************************//**
* \file GLCD_SPIM_PM.c
* \version 4.0
*
* \brief
*  This file provides the source code to the Power Management support for
*  the SCB Component.
*
* Note:
*
********************************************************************************
* \copyright
* Copyright 2013-2017, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "GLCD_SPIM.h"
#include "GLCD_SPIM_PVT.h"

#if(GLCD_SPIM_SCB_MODE_I2C_INC)
    #include "GLCD_SPIM_I2C_PVT.h"
#endif /* (GLCD_SPIM_SCB_MODE_I2C_INC) */

#if(GLCD_SPIM_SCB_MODE_EZI2C_INC)
    #include "GLCD_SPIM_EZI2C_PVT.h"
#endif /* (GLCD_SPIM_SCB_MODE_EZI2C_INC) */

#if(GLCD_SPIM_SCB_MODE_SPI_INC || GLCD_SPIM_SCB_MODE_UART_INC)
    #include "GLCD_SPIM_SPI_UART_PVT.h"
#endif /* (GLCD_SPIM_SCB_MODE_SPI_INC || GLCD_SPIM_SCB_MODE_UART_INC) */


/***************************************
*   Backup Structure declaration
***************************************/

#if(GLCD_SPIM_SCB_MODE_UNCONFIG_CONST_CFG || \
   (GLCD_SPIM_SCB_MODE_I2C_CONST_CFG   && (!GLCD_SPIM_I2C_WAKE_ENABLE_CONST))   || \
   (GLCD_SPIM_SCB_MODE_EZI2C_CONST_CFG && (!GLCD_SPIM_EZI2C_WAKE_ENABLE_CONST)) || \
   (GLCD_SPIM_SCB_MODE_SPI_CONST_CFG   && (!GLCD_SPIM_SPI_WAKE_ENABLE_CONST))   || \
   (GLCD_SPIM_SCB_MODE_UART_CONST_CFG  && (!GLCD_SPIM_UART_WAKE_ENABLE_CONST)))

    GLCD_SPIM_BACKUP_STRUCT GLCD_SPIM_backup =
    {
        0u, /* enableState */
    };
#endif


/*******************************************************************************
* Function Name: GLCD_SPIM_Sleep
****************************************************************************//**
*
*  Prepares the GLCD_SPIM component to enter Deep Sleep.
*  The “Enable wakeup from Deep Sleep Mode” selection has an influence on this 
*  function implementation:
*  - Checked: configures the component to be wakeup source from Deep Sleep.
*  - Unchecked: stores the current component state (enabled or disabled) and 
*    disables the component. See SCB_Stop() function for details about component 
*    disabling.
*
*  Call the GLCD_SPIM_Sleep() function before calling the 
*  CyPmSysDeepSleep() function. 
*  Refer to the PSoC Creator System Reference Guide for more information about 
*  power management functions and Low power section of this document for the 
*  selected mode.
*
*  This function should not be called before entering Sleep.
*
*******************************************************************************/
void GLCD_SPIM_Sleep(void)
{
#if(GLCD_SPIM_SCB_MODE_UNCONFIG_CONST_CFG)

    if(GLCD_SPIM_SCB_WAKE_ENABLE_CHECK)
    {
        if(GLCD_SPIM_SCB_MODE_I2C_RUNTM_CFG)
        {
            GLCD_SPIM_I2CSaveConfig();
        }
        else if(GLCD_SPIM_SCB_MODE_EZI2C_RUNTM_CFG)
        {
            GLCD_SPIM_EzI2CSaveConfig();
        }
    #if(!GLCD_SPIM_CY_SCBIP_V1)
        else if(GLCD_SPIM_SCB_MODE_SPI_RUNTM_CFG)
        {
            GLCD_SPIM_SpiSaveConfig();
        }
        else if(GLCD_SPIM_SCB_MODE_UART_RUNTM_CFG)
        {
            GLCD_SPIM_UartSaveConfig();
        }
    #endif /* (!GLCD_SPIM_CY_SCBIP_V1) */
        else
        {
            /* Unknown mode */
        }
    }
    else
    {
        GLCD_SPIM_backup.enableState = (uint8) GLCD_SPIM_GET_CTRL_ENABLED;

        if(0u != GLCD_SPIM_backup.enableState)
        {
            GLCD_SPIM_Stop();
        }
    }

#else

    #if (GLCD_SPIM_SCB_MODE_I2C_CONST_CFG && GLCD_SPIM_I2C_WAKE_ENABLE_CONST)
        GLCD_SPIM_I2CSaveConfig();

    #elif (GLCD_SPIM_SCB_MODE_EZI2C_CONST_CFG && GLCD_SPIM_EZI2C_WAKE_ENABLE_CONST)
        GLCD_SPIM_EzI2CSaveConfig();

    #elif (GLCD_SPIM_SCB_MODE_SPI_CONST_CFG && GLCD_SPIM_SPI_WAKE_ENABLE_CONST)
        GLCD_SPIM_SpiSaveConfig();

    #elif (GLCD_SPIM_SCB_MODE_UART_CONST_CFG && GLCD_SPIM_UART_WAKE_ENABLE_CONST)
        GLCD_SPIM_UartSaveConfig();

    #else

        GLCD_SPIM_backup.enableState = (uint8) GLCD_SPIM_GET_CTRL_ENABLED;

        if(0u != GLCD_SPIM_backup.enableState)
        {
            GLCD_SPIM_Stop();
        }

    #endif /* defined (GLCD_SPIM_SCB_MODE_I2C_CONST_CFG) && (GLCD_SPIM_I2C_WAKE_ENABLE_CONST) */

#endif /* (GLCD_SPIM_SCB_MODE_UNCONFIG_CONST_CFG) */
}


/*******************************************************************************
* Function Name: GLCD_SPIM_Wakeup
****************************************************************************//**
*
*  Prepares the GLCD_SPIM component for Active mode operation after 
*  Deep Sleep.
*  The “Enable wakeup from Deep Sleep Mode” selection has influence on this 
*  function implementation:
*  - Checked: restores the component Active mode configuration.
*  - Unchecked: enables the component if it was enabled before enter Deep Sleep.
*
*  This function should not be called after exiting Sleep.
*
*  \sideeffect
*   Calling the GLCD_SPIM_Wakeup() function without first calling the 
*   GLCD_SPIM_Sleep() function may produce unexpected behavior.
*
*******************************************************************************/
void GLCD_SPIM_Wakeup(void)
{
#if(GLCD_SPIM_SCB_MODE_UNCONFIG_CONST_CFG)

    if(GLCD_SPIM_SCB_WAKE_ENABLE_CHECK)
    {
        if(GLCD_SPIM_SCB_MODE_I2C_RUNTM_CFG)
        {
            GLCD_SPIM_I2CRestoreConfig();
        }
        else if(GLCD_SPIM_SCB_MODE_EZI2C_RUNTM_CFG)
        {
            GLCD_SPIM_EzI2CRestoreConfig();
        }
    #if(!GLCD_SPIM_CY_SCBIP_V1)
        else if(GLCD_SPIM_SCB_MODE_SPI_RUNTM_CFG)
        {
            GLCD_SPIM_SpiRestoreConfig();
        }
        else if(GLCD_SPIM_SCB_MODE_UART_RUNTM_CFG)
        {
            GLCD_SPIM_UartRestoreConfig();
        }
    #endif /* (!GLCD_SPIM_CY_SCBIP_V1) */
        else
        {
            /* Unknown mode */
        }
    }
    else
    {
        if(0u != GLCD_SPIM_backup.enableState)
        {
            GLCD_SPIM_Enable();
        }
    }

#else

    #if (GLCD_SPIM_SCB_MODE_I2C_CONST_CFG  && GLCD_SPIM_I2C_WAKE_ENABLE_CONST)
        GLCD_SPIM_I2CRestoreConfig();

    #elif (GLCD_SPIM_SCB_MODE_EZI2C_CONST_CFG && GLCD_SPIM_EZI2C_WAKE_ENABLE_CONST)
        GLCD_SPIM_EzI2CRestoreConfig();

    #elif (GLCD_SPIM_SCB_MODE_SPI_CONST_CFG && GLCD_SPIM_SPI_WAKE_ENABLE_CONST)
        GLCD_SPIM_SpiRestoreConfig();

    #elif (GLCD_SPIM_SCB_MODE_UART_CONST_CFG && GLCD_SPIM_UART_WAKE_ENABLE_CONST)
        GLCD_SPIM_UartRestoreConfig();

    #else

        if(0u != GLCD_SPIM_backup.enableState)
        {
            GLCD_SPIM_Enable();
        }

    #endif /* (GLCD_SPIM_I2C_WAKE_ENABLE_CONST) */

#endif /* (GLCD_SPIM_SCB_MODE_UNCONFIG_CONST_CFG) */
}


/* [] END OF FILE */
