/***************************************************************************//**
* \file .h
* \version 4.0
*
* \brief
*  This private file provides constants and parameter values for the
*  SCB Component.
*  Please do not use this file or its content in your project.
*
* Note:
*
********************************************************************************
* \copyright
* Copyright 2013-2017, Cypress Semiconductor Corporation. All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_SCB_PVT_GLCD_SPIM_H)
#define CY_SCB_PVT_GLCD_SPIM_H

#include "GLCD_SPIM.h"


/***************************************
*     Private Function Prototypes
***************************************/

/* APIs to service INTR_I2C_EC register */
#define GLCD_SPIM_SetI2CExtClkInterruptMode(interruptMask) GLCD_SPIM_WRITE_INTR_I2C_EC_MASK(interruptMask)
#define GLCD_SPIM_ClearI2CExtClkInterruptSource(interruptMask) GLCD_SPIM_CLEAR_INTR_I2C_EC(interruptMask)
#define GLCD_SPIM_GetI2CExtClkInterruptSource()                (GLCD_SPIM_INTR_I2C_EC_REG)
#define GLCD_SPIM_GetI2CExtClkInterruptMode()                  (GLCD_SPIM_INTR_I2C_EC_MASK_REG)
#define GLCD_SPIM_GetI2CExtClkInterruptSourceMasked()          (GLCD_SPIM_INTR_I2C_EC_MASKED_REG)

#if (!GLCD_SPIM_CY_SCBIP_V1)
    /* APIs to service INTR_SPI_EC register */
    #define GLCD_SPIM_SetSpiExtClkInterruptMode(interruptMask) \
                                                                GLCD_SPIM_WRITE_INTR_SPI_EC_MASK(interruptMask)
    #define GLCD_SPIM_ClearSpiExtClkInterruptSource(interruptMask) \
                                                                GLCD_SPIM_CLEAR_INTR_SPI_EC(interruptMask)
    #define GLCD_SPIM_GetExtSpiClkInterruptSource()                 (GLCD_SPIM_INTR_SPI_EC_REG)
    #define GLCD_SPIM_GetExtSpiClkInterruptMode()                   (GLCD_SPIM_INTR_SPI_EC_MASK_REG)
    #define GLCD_SPIM_GetExtSpiClkInterruptSourceMasked()           (GLCD_SPIM_INTR_SPI_EC_MASKED_REG)
#endif /* (!GLCD_SPIM_CY_SCBIP_V1) */

#if(GLCD_SPIM_SCB_MODE_UNCONFIG_CONST_CFG)
    extern void GLCD_SPIM_SetPins(uint32 mode, uint32 subMode, uint32 uartEnableMask);
#endif /* (GLCD_SPIM_SCB_MODE_UNCONFIG_CONST_CFG) */


/***************************************
*     Vars with External Linkage
***************************************/

#if (GLCD_SPIM_SCB_IRQ_INTERNAL)
#if !defined (CY_REMOVE_GLCD_SPIM_CUSTOM_INTR_HANDLER)
    extern cyisraddress GLCD_SPIM_customIntrHandler;
#endif /* !defined (CY_REMOVE_GLCD_SPIM_CUSTOM_INTR_HANDLER) */
#endif /* (GLCD_SPIM_SCB_IRQ_INTERNAL) */

extern GLCD_SPIM_BACKUP_STRUCT GLCD_SPIM_backup;

#if(GLCD_SPIM_SCB_MODE_UNCONFIG_CONST_CFG)
    /* Common configuration variables */
    extern uint8 GLCD_SPIM_scbMode;
    extern uint8 GLCD_SPIM_scbEnableWake;
    extern uint8 GLCD_SPIM_scbEnableIntr;

    /* I2C configuration variables */
    extern uint8 GLCD_SPIM_mode;
    extern uint8 GLCD_SPIM_acceptAddr;

    /* SPI/UART configuration variables */
    extern volatile uint8 * GLCD_SPIM_rxBuffer;
    extern uint8   GLCD_SPIM_rxDataBits;
    extern uint32  GLCD_SPIM_rxBufferSize;

    extern volatile uint8 * GLCD_SPIM_txBuffer;
    extern uint8   GLCD_SPIM_txDataBits;
    extern uint32  GLCD_SPIM_txBufferSize;

    /* EZI2C configuration variables */
    extern uint8 GLCD_SPIM_numberOfAddr;
    extern uint8 GLCD_SPIM_subAddrSize;
#endif /* (GLCD_SPIM_SCB_MODE_UNCONFIG_CONST_CFG) */

#if (! (GLCD_SPIM_SCB_MODE_I2C_CONST_CFG || \
        GLCD_SPIM_SCB_MODE_EZI2C_CONST_CFG))
    extern uint16 GLCD_SPIM_IntrTxMask;
#endif /* (! (GLCD_SPIM_SCB_MODE_I2C_CONST_CFG || \
              GLCD_SPIM_SCB_MODE_EZI2C_CONST_CFG)) */


/***************************************
*        Conditional Macro
****************************************/

#if(GLCD_SPIM_SCB_MODE_UNCONFIG_CONST_CFG)
    /* Defines run time operation mode */
    #define GLCD_SPIM_SCB_MODE_I2C_RUNTM_CFG     (GLCD_SPIM_SCB_MODE_I2C      == GLCD_SPIM_scbMode)
    #define GLCD_SPIM_SCB_MODE_SPI_RUNTM_CFG     (GLCD_SPIM_SCB_MODE_SPI      == GLCD_SPIM_scbMode)
    #define GLCD_SPIM_SCB_MODE_UART_RUNTM_CFG    (GLCD_SPIM_SCB_MODE_UART     == GLCD_SPIM_scbMode)
    #define GLCD_SPIM_SCB_MODE_EZI2C_RUNTM_CFG   (GLCD_SPIM_SCB_MODE_EZI2C    == GLCD_SPIM_scbMode)
    #define GLCD_SPIM_SCB_MODE_UNCONFIG_RUNTM_CFG \
                                                        (GLCD_SPIM_SCB_MODE_UNCONFIG == GLCD_SPIM_scbMode)

    /* Defines wakeup enable */
    #define GLCD_SPIM_SCB_WAKE_ENABLE_CHECK       (0u != GLCD_SPIM_scbEnableWake)
#endif /* (GLCD_SPIM_SCB_MODE_UNCONFIG_CONST_CFG) */

/* Defines maximum number of SCB pins */
#if (!GLCD_SPIM_CY_SCBIP_V1)
    #define GLCD_SPIM_SCB_PINS_NUMBER    (7u)
#else
    #define GLCD_SPIM_SCB_PINS_NUMBER    (2u)
#endif /* (!GLCD_SPIM_CY_SCBIP_V1) */

#endif /* (CY_SCB_PVT_GLCD_SPIM_H) */


/* [] END OF FILE */
