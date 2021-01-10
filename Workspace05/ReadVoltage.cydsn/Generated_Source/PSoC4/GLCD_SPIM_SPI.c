/***************************************************************************//**
* \file GLCD_SPIM_SPI.c
* \version 4.0
*
* \brief
*  This file provides the source code to the API for the SCB Component in
*  SPI mode.
*
* Note:
*
*******************************************************************************
* \copyright
* Copyright 2013-2017, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "GLCD_SPIM_PVT.h"
#include "GLCD_SPIM_SPI_UART_PVT.h"

#if(GLCD_SPIM_SCB_MODE_UNCONFIG_CONST_CFG)

    /***************************************
    *  Configuration Structure Initialization
    ***************************************/

    const GLCD_SPIM_SPI_INIT_STRUCT GLCD_SPIM_configSpi =
    {
        GLCD_SPIM_SPI_MODE,
        GLCD_SPIM_SPI_SUB_MODE,
        GLCD_SPIM_SPI_CLOCK_MODE,
        GLCD_SPIM_SPI_OVS_FACTOR,
        GLCD_SPIM_SPI_MEDIAN_FILTER_ENABLE,
        GLCD_SPIM_SPI_LATE_MISO_SAMPLE_ENABLE,
        GLCD_SPIM_SPI_WAKE_ENABLE,
        GLCD_SPIM_SPI_RX_DATA_BITS_NUM,
        GLCD_SPIM_SPI_TX_DATA_BITS_NUM,
        GLCD_SPIM_SPI_BITS_ORDER,
        GLCD_SPIM_SPI_TRANSFER_SEPARATION,
        0u,
        NULL,
        0u,
        NULL,
        (uint32) GLCD_SPIM_SCB_IRQ_INTERNAL,
        GLCD_SPIM_SPI_INTR_RX_MASK,
        GLCD_SPIM_SPI_RX_TRIGGER_LEVEL,
        GLCD_SPIM_SPI_INTR_TX_MASK,
        GLCD_SPIM_SPI_TX_TRIGGER_LEVEL,
        (uint8) GLCD_SPIM_SPI_BYTE_MODE_ENABLE,
        (uint8) GLCD_SPIM_SPI_FREE_RUN_SCLK_ENABLE,
        (uint8) GLCD_SPIM_SPI_SS_POLARITY
    };


    /*******************************************************************************
    * Function Name: GLCD_SPIM_SpiInit
    ****************************************************************************//**
    *
    *  Configures the GLCD_SPIM for SPI operation.
    *
    *  This function is intended specifically to be used when the GLCD_SPIM 
    *  configuration is set to “Unconfigured GLCD_SPIM” in the customizer. 
    *  After initializing the GLCD_SPIM in SPI mode using this function, 
    *  the component can be enabled using the GLCD_SPIM_Start() or 
    * GLCD_SPIM_Enable() function.
    *  This function uses a pointer to a structure that provides the configuration 
    *  settings. This structure contains the same information that would otherwise 
    *  be provided by the customizer settings.
    *
    *  \param config: pointer to a structure that contains the following list of 
    *   fields. These fields match the selections available in the customizer. 
    *   Refer to the customizer for further description of the settings.
    *
    *******************************************************************************/
    void GLCD_SPIM_SpiInit(const GLCD_SPIM_SPI_INIT_STRUCT *config)
    {
        if(NULL == config)
        {
            CYASSERT(0u != 0u); /* Halt execution due to bad function parameter */
        }
        else
        {
            /* Configure pins */
            GLCD_SPIM_SetPins(GLCD_SPIM_SCB_MODE_SPI, config->mode, GLCD_SPIM_DUMMY_PARAM);

            /* Store internal configuration */
            GLCD_SPIM_scbMode       = (uint8) GLCD_SPIM_SCB_MODE_SPI;
            GLCD_SPIM_scbEnableWake = (uint8) config->enableWake;
            GLCD_SPIM_scbEnableIntr = (uint8) config->enableInterrupt;

            /* Set RX direction internal variables */
            GLCD_SPIM_rxBuffer      =         config->rxBuffer;
            GLCD_SPIM_rxDataBits    = (uint8) config->rxDataBits;
            GLCD_SPIM_rxBufferSize  =         config->rxBufferSize;

            /* Set TX direction internal variables */
            GLCD_SPIM_txBuffer      =         config->txBuffer;
            GLCD_SPIM_txDataBits    = (uint8) config->txDataBits;
            GLCD_SPIM_txBufferSize  =         config->txBufferSize;

            /* Configure SPI interface */
            GLCD_SPIM_CTRL_REG     = GLCD_SPIM_GET_CTRL_OVS(config->oversample)           |
                                            GLCD_SPIM_GET_CTRL_BYTE_MODE(config->enableByteMode) |
                                            GLCD_SPIM_GET_CTRL_EC_AM_MODE(config->enableWake)    |
                                            GLCD_SPIM_CTRL_SPI;

            GLCD_SPIM_SPI_CTRL_REG = GLCD_SPIM_GET_SPI_CTRL_CONTINUOUS    (config->transferSeperation)  |
                                            GLCD_SPIM_GET_SPI_CTRL_SELECT_PRECEDE(config->submode &
                                                                          GLCD_SPIM_SPI_MODE_TI_PRECEDES_MASK) |
                                            GLCD_SPIM_GET_SPI_CTRL_SCLK_MODE     (config->sclkMode)            |
                                            GLCD_SPIM_GET_SPI_CTRL_LATE_MISO_SAMPLE(config->enableLateSampling)|
                                            GLCD_SPIM_GET_SPI_CTRL_SCLK_CONTINUOUS(config->enableFreeRunSclk)  |
                                            GLCD_SPIM_GET_SPI_CTRL_SSEL_POLARITY (config->polaritySs)          |
                                            GLCD_SPIM_GET_SPI_CTRL_SUB_MODE      (config->submode)             |
                                            GLCD_SPIM_GET_SPI_CTRL_MASTER_MODE   (config->mode);

            /* Configure RX direction */
            GLCD_SPIM_RX_CTRL_REG     =  GLCD_SPIM_GET_RX_CTRL_DATA_WIDTH(config->rxDataBits)         |
                                                GLCD_SPIM_GET_RX_CTRL_BIT_ORDER (config->bitOrder)           |
                                                GLCD_SPIM_GET_RX_CTRL_MEDIAN    (config->enableMedianFilter) |
                                                GLCD_SPIM_SPI_RX_CTRL;

            GLCD_SPIM_RX_FIFO_CTRL_REG = GLCD_SPIM_GET_RX_FIFO_CTRL_TRIGGER_LEVEL(config->rxTriggerLevel);

            /* Configure TX direction */
            GLCD_SPIM_TX_CTRL_REG      = GLCD_SPIM_GET_TX_CTRL_DATA_WIDTH(config->txDataBits) |
                                                GLCD_SPIM_GET_TX_CTRL_BIT_ORDER (config->bitOrder)   |
                                                GLCD_SPIM_SPI_TX_CTRL;

            GLCD_SPIM_TX_FIFO_CTRL_REG = GLCD_SPIM_GET_TX_FIFO_CTRL_TRIGGER_LEVEL(config->txTriggerLevel);

            /* Configure interrupt with SPI handler but do not enable it */
            CyIntDisable    (GLCD_SPIM_ISR_NUMBER);
            CyIntSetPriority(GLCD_SPIM_ISR_NUMBER, GLCD_SPIM_ISR_PRIORITY);
            (void) CyIntSetVector(GLCD_SPIM_ISR_NUMBER, &GLCD_SPIM_SPI_UART_ISR);

            /* Configure interrupt sources */
            GLCD_SPIM_INTR_I2C_EC_MASK_REG = GLCD_SPIM_NO_INTR_SOURCES;
            GLCD_SPIM_INTR_SPI_EC_MASK_REG = GLCD_SPIM_NO_INTR_SOURCES;
            GLCD_SPIM_INTR_SLAVE_MASK_REG  = GLCD_SPIM_GET_SPI_INTR_SLAVE_MASK(config->rxInterruptMask);
            GLCD_SPIM_INTR_MASTER_MASK_REG = GLCD_SPIM_GET_SPI_INTR_MASTER_MASK(config->txInterruptMask);
            GLCD_SPIM_INTR_RX_MASK_REG     = GLCD_SPIM_GET_SPI_INTR_RX_MASK(config->rxInterruptMask);
            GLCD_SPIM_INTR_TX_MASK_REG     = GLCD_SPIM_GET_SPI_INTR_TX_MASK(config->txInterruptMask);
            
            /* Configure TX interrupt sources to restore. */
            GLCD_SPIM_IntrTxMask = LO16(GLCD_SPIM_INTR_TX_MASK_REG);

            /* Set active SS0 */
            GLCD_SPIM_SpiSetActiveSlaveSelect(GLCD_SPIM_SPI_SLAVE_SELECT0);

            /* Clear RX buffer indexes */
            GLCD_SPIM_rxBufferHead     = 0u;
            GLCD_SPIM_rxBufferTail     = 0u;
            GLCD_SPIM_rxBufferOverflow = 0u;

            /* Clear TX buffer indexes */
            GLCD_SPIM_txBufferHead = 0u;
            GLCD_SPIM_txBufferTail = 0u;
        }
    }

#else

    /*******************************************************************************
    * Function Name: GLCD_SPIM_SpiInit
    ****************************************************************************//**
    *
    *  Configures the SCB for the SPI operation.
    *
    *******************************************************************************/
    void GLCD_SPIM_SpiInit(void)
    {
        /* Configure SPI interface */
        GLCD_SPIM_CTRL_REG     = GLCD_SPIM_SPI_DEFAULT_CTRL;
        GLCD_SPIM_SPI_CTRL_REG = GLCD_SPIM_SPI_DEFAULT_SPI_CTRL;

        /* Configure TX and RX direction */
        GLCD_SPIM_RX_CTRL_REG      = GLCD_SPIM_SPI_DEFAULT_RX_CTRL;
        GLCD_SPIM_RX_FIFO_CTRL_REG = GLCD_SPIM_SPI_DEFAULT_RX_FIFO_CTRL;

        /* Configure TX and RX direction */
        GLCD_SPIM_TX_CTRL_REG      = GLCD_SPIM_SPI_DEFAULT_TX_CTRL;
        GLCD_SPIM_TX_FIFO_CTRL_REG = GLCD_SPIM_SPI_DEFAULT_TX_FIFO_CTRL;

        /* Configure interrupt with SPI handler but do not enable it */
    #if(GLCD_SPIM_SCB_IRQ_INTERNAL)
            CyIntDisable    (GLCD_SPIM_ISR_NUMBER);
            CyIntSetPriority(GLCD_SPIM_ISR_NUMBER, GLCD_SPIM_ISR_PRIORITY);
            (void) CyIntSetVector(GLCD_SPIM_ISR_NUMBER, &GLCD_SPIM_SPI_UART_ISR);
    #endif /* (GLCD_SPIM_SCB_IRQ_INTERNAL) */

        /* Configure interrupt sources */
        GLCD_SPIM_INTR_I2C_EC_MASK_REG = GLCD_SPIM_SPI_DEFAULT_INTR_I2C_EC_MASK;
        GLCD_SPIM_INTR_SPI_EC_MASK_REG = GLCD_SPIM_SPI_DEFAULT_INTR_SPI_EC_MASK;
        GLCD_SPIM_INTR_SLAVE_MASK_REG  = GLCD_SPIM_SPI_DEFAULT_INTR_SLAVE_MASK;
        GLCD_SPIM_INTR_MASTER_MASK_REG = GLCD_SPIM_SPI_DEFAULT_INTR_MASTER_MASK;
        GLCD_SPIM_INTR_RX_MASK_REG     = GLCD_SPIM_SPI_DEFAULT_INTR_RX_MASK;
        GLCD_SPIM_INTR_TX_MASK_REG     = GLCD_SPIM_SPI_DEFAULT_INTR_TX_MASK;

        /* Configure TX interrupt sources to restore. */
        GLCD_SPIM_IntrTxMask = LO16(GLCD_SPIM_INTR_TX_MASK_REG);
            
        /* Set active SS0 for master */
    #if (GLCD_SPIM_SPI_MASTER_CONST)
        GLCD_SPIM_SpiSetActiveSlaveSelect(GLCD_SPIM_SPI_SLAVE_SELECT0);
    #endif /* (GLCD_SPIM_SPI_MASTER_CONST) */

    #if(GLCD_SPIM_INTERNAL_RX_SW_BUFFER_CONST)
        GLCD_SPIM_rxBufferHead     = 0u;
        GLCD_SPIM_rxBufferTail     = 0u;
        GLCD_SPIM_rxBufferOverflow = 0u;
    #endif /* (GLCD_SPIM_INTERNAL_RX_SW_BUFFER_CONST) */

    #if(GLCD_SPIM_INTERNAL_TX_SW_BUFFER_CONST)
        GLCD_SPIM_txBufferHead = 0u;
        GLCD_SPIM_txBufferTail = 0u;
    #endif /* (GLCD_SPIM_INTERNAL_TX_SW_BUFFER_CONST) */
    }
#endif /* (GLCD_SPIM_SCB_MODE_UNCONFIG_CONST_CFG) */


/*******************************************************************************
* Function Name: GLCD_SPIM_SpiPostEnable
****************************************************************************//**
*
*  Restores HSIOM settings for the SPI master output pins (SCLK and/or SS0-SS3) 
*  to be controlled by the SCB SPI.
*
*******************************************************************************/
void GLCD_SPIM_SpiPostEnable(void)
{
#if(GLCD_SPIM_SCB_MODE_UNCONFIG_CONST_CFG)

    if (GLCD_SPIM_CHECK_SPI_MASTER)
    {
    #if (GLCD_SPIM_CTS_SCLK_PIN)
        /* Set SCB SPI to drive output pin */
        GLCD_SPIM_SET_HSIOM_SEL(GLCD_SPIM_CTS_SCLK_HSIOM_REG, GLCD_SPIM_CTS_SCLK_HSIOM_MASK,
                                       GLCD_SPIM_CTS_SCLK_HSIOM_POS, GLCD_SPIM_CTS_SCLK_HSIOM_SEL_SPI);
    #endif /* (GLCD_SPIM_CTS_SCLK_PIN) */

    #if (GLCD_SPIM_RTS_SS0_PIN)
        /* Set SCB SPI to drive output pin */
        GLCD_SPIM_SET_HSIOM_SEL(GLCD_SPIM_RTS_SS0_HSIOM_REG, GLCD_SPIM_RTS_SS0_HSIOM_MASK,
                                       GLCD_SPIM_RTS_SS0_HSIOM_POS, GLCD_SPIM_RTS_SS0_HSIOM_SEL_SPI);
    #endif /* (GLCD_SPIM_RTS_SS0_PIN) */

    #if (GLCD_SPIM_SS1_PIN)
        /* Set SCB SPI to drive output pin */
        GLCD_SPIM_SET_HSIOM_SEL(GLCD_SPIM_SS1_HSIOM_REG, GLCD_SPIM_SS1_HSIOM_MASK,
                                       GLCD_SPIM_SS1_HSIOM_POS, GLCD_SPIM_SS1_HSIOM_SEL_SPI);
    #endif /* (GLCD_SPIM_SS1_PIN) */

    #if (GLCD_SPIM_SS2_PIN)
        /* Set SCB SPI to drive output pin */
        GLCD_SPIM_SET_HSIOM_SEL(GLCD_SPIM_SS2_HSIOM_REG, GLCD_SPIM_SS2_HSIOM_MASK,
                                       GLCD_SPIM_SS2_HSIOM_POS, GLCD_SPIM_SS2_HSIOM_SEL_SPI);
    #endif /* (GLCD_SPIM_SS2_PIN) */

    #if (GLCD_SPIM_SS3_PIN)
        /* Set SCB SPI to drive output pin */
        GLCD_SPIM_SET_HSIOM_SEL(GLCD_SPIM_SS3_HSIOM_REG, GLCD_SPIM_SS3_HSIOM_MASK,
                                       GLCD_SPIM_SS3_HSIOM_POS, GLCD_SPIM_SS3_HSIOM_SEL_SPI);
    #endif /* (GLCD_SPIM_SS3_PIN) */
    }

#else

    #if (GLCD_SPIM_SPI_MASTER_SCLK_PIN)
        /* Set SCB SPI to drive output pin */
        GLCD_SPIM_SET_HSIOM_SEL(GLCD_SPIM_SCLK_M_HSIOM_REG, GLCD_SPIM_SCLK_M_HSIOM_MASK,
                                       GLCD_SPIM_SCLK_M_HSIOM_POS, GLCD_SPIM_SCLK_M_HSIOM_SEL_SPI);
    #endif /* (GLCD_SPIM_MISO_SDA_TX_PIN_PIN) */

    #if (GLCD_SPIM_SPI_MASTER_SS0_PIN)
        /* Set SCB SPI to drive output pin */
        GLCD_SPIM_SET_HSIOM_SEL(GLCD_SPIM_SS0_M_HSIOM_REG, GLCD_SPIM_SS0_M_HSIOM_MASK,
                                       GLCD_SPIM_SS0_M_HSIOM_POS, GLCD_SPIM_SS0_M_HSIOM_SEL_SPI);
    #endif /* (GLCD_SPIM_SPI_MASTER_SS0_PIN) */

    #if (GLCD_SPIM_SPI_MASTER_SS1_PIN)
        /* Set SCB SPI to drive output pin */
        GLCD_SPIM_SET_HSIOM_SEL(GLCD_SPIM_SS1_M_HSIOM_REG, GLCD_SPIM_SS1_M_HSIOM_MASK,
                                       GLCD_SPIM_SS1_M_HSIOM_POS, GLCD_SPIM_SS1_M_HSIOM_SEL_SPI);
    #endif /* (GLCD_SPIM_SPI_MASTER_SS1_PIN) */

    #if (GLCD_SPIM_SPI_MASTER_SS2_PIN)
        /* Set SCB SPI to drive output pin */
        GLCD_SPIM_SET_HSIOM_SEL(GLCD_SPIM_SS2_M_HSIOM_REG, GLCD_SPIM_SS2_M_HSIOM_MASK,
                                       GLCD_SPIM_SS2_M_HSIOM_POS, GLCD_SPIM_SS2_M_HSIOM_SEL_SPI);
    #endif /* (GLCD_SPIM_SPI_MASTER_SS2_PIN) */

    #if (GLCD_SPIM_SPI_MASTER_SS3_PIN)
        /* Set SCB SPI to drive output pin */
        GLCD_SPIM_SET_HSIOM_SEL(GLCD_SPIM_SS3_M_HSIOM_REG, GLCD_SPIM_SS3_M_HSIOM_MASK,
                                       GLCD_SPIM_SS3_M_HSIOM_POS, GLCD_SPIM_SS3_M_HSIOM_SEL_SPI);
    #endif /* (GLCD_SPIM_SPI_MASTER_SS3_PIN) */

#endif /* (GLCD_SPIM_SCB_MODE_UNCONFIG_CONST_CFG) */

    /* Restore TX interrupt sources. */
    GLCD_SPIM_SetTxInterruptMode(GLCD_SPIM_IntrTxMask);
}


/*******************************************************************************
* Function Name: GLCD_SPIM_SpiStop
****************************************************************************//**
*
*  Changes the HSIOM settings for the SPI master output pins 
*  (SCLK and/or SS0-SS3) to keep them inactive after the block is disabled. 
*  The output pins are controlled by the GPIO data register.
*
*******************************************************************************/
void GLCD_SPIM_SpiStop(void)
{
#if(GLCD_SPIM_SCB_MODE_UNCONFIG_CONST_CFG)

    if (GLCD_SPIM_CHECK_SPI_MASTER)
    {
    #if (GLCD_SPIM_CTS_SCLK_PIN)
        /* Set output pin state after block is disabled */
        GLCD_SPIM_uart_cts_spi_sclk_Write(GLCD_SPIM_GET_SPI_SCLK_INACTIVE);

        /* Set GPIO to drive output pin */
        GLCD_SPIM_SET_HSIOM_SEL(GLCD_SPIM_CTS_SCLK_HSIOM_REG, GLCD_SPIM_CTS_SCLK_HSIOM_MASK,
                                       GLCD_SPIM_CTS_SCLK_HSIOM_POS, GLCD_SPIM_CTS_SCLK_HSIOM_SEL_GPIO);
    #endif /* (GLCD_SPIM_uart_cts_spi_sclk_PIN) */

    #if (GLCD_SPIM_RTS_SS0_PIN)
        /* Set output pin state after block is disabled */
        GLCD_SPIM_uart_rts_spi_ss0_Write(GLCD_SPIM_GET_SPI_SS0_INACTIVE);

        /* Set GPIO to drive output pin */
        GLCD_SPIM_SET_HSIOM_SEL(GLCD_SPIM_RTS_SS0_HSIOM_REG, GLCD_SPIM_RTS_SS0_HSIOM_MASK,
                                       GLCD_SPIM_RTS_SS0_HSIOM_POS, GLCD_SPIM_RTS_SS0_HSIOM_SEL_GPIO);
    #endif /* (GLCD_SPIM_uart_rts_spi_ss0_PIN) */

    #if (GLCD_SPIM_SS1_PIN)
        /* Set output pin state after block is disabled */
        GLCD_SPIM_spi_ss1_Write(GLCD_SPIM_GET_SPI_SS1_INACTIVE);

        /* Set GPIO to drive output pin */
        GLCD_SPIM_SET_HSIOM_SEL(GLCD_SPIM_SS1_HSIOM_REG, GLCD_SPIM_SS1_HSIOM_MASK,
                                       GLCD_SPIM_SS1_HSIOM_POS, GLCD_SPIM_SS1_HSIOM_SEL_GPIO);
    #endif /* (GLCD_SPIM_SS1_PIN) */

    #if (GLCD_SPIM_SS2_PIN)
        /* Set output pin state after block is disabled */
        GLCD_SPIM_spi_ss2_Write(GLCD_SPIM_GET_SPI_SS2_INACTIVE);

        /* Set GPIO to drive output pin */
        GLCD_SPIM_SET_HSIOM_SEL(GLCD_SPIM_SS2_HSIOM_REG, GLCD_SPIM_SS2_HSIOM_MASK,
                                       GLCD_SPIM_SS2_HSIOM_POS, GLCD_SPIM_SS2_HSIOM_SEL_GPIO);
    #endif /* (GLCD_SPIM_SS2_PIN) */

    #if (GLCD_SPIM_SS3_PIN)
        /* Set output pin state after block is disabled */
        GLCD_SPIM_spi_ss3_Write(GLCD_SPIM_GET_SPI_SS3_INACTIVE);

        /* Set GPIO to drive output pin */
        GLCD_SPIM_SET_HSIOM_SEL(GLCD_SPIM_SS3_HSIOM_REG, GLCD_SPIM_SS3_HSIOM_MASK,
                                       GLCD_SPIM_SS3_HSIOM_POS, GLCD_SPIM_SS3_HSIOM_SEL_GPIO);
    #endif /* (GLCD_SPIM_SS3_PIN) */
    
        /* Store TX interrupt sources (exclude level triggered) for master. */
        GLCD_SPIM_IntrTxMask = LO16(GLCD_SPIM_GetTxInterruptMode() & GLCD_SPIM_INTR_SPIM_TX_RESTORE);
    }
    else
    {
        /* Store TX interrupt sources (exclude level triggered) for slave. */
        GLCD_SPIM_IntrTxMask = LO16(GLCD_SPIM_GetTxInterruptMode() & GLCD_SPIM_INTR_SPIS_TX_RESTORE);
    }

#else

#if (GLCD_SPIM_SPI_MASTER_SCLK_PIN)
    /* Set output pin state after block is disabled */
    GLCD_SPIM_sclk_m_Write(GLCD_SPIM_GET_SPI_SCLK_INACTIVE);

    /* Set GPIO to drive output pin */
    GLCD_SPIM_SET_HSIOM_SEL(GLCD_SPIM_SCLK_M_HSIOM_REG, GLCD_SPIM_SCLK_M_HSIOM_MASK,
                                   GLCD_SPIM_SCLK_M_HSIOM_POS, GLCD_SPIM_SCLK_M_HSIOM_SEL_GPIO);
#endif /* (GLCD_SPIM_MISO_SDA_TX_PIN_PIN) */

#if (GLCD_SPIM_SPI_MASTER_SS0_PIN)
    /* Set output pin state after block is disabled */
    GLCD_SPIM_ss0_m_Write(GLCD_SPIM_GET_SPI_SS0_INACTIVE);

    /* Set GPIO to drive output pin */
    GLCD_SPIM_SET_HSIOM_SEL(GLCD_SPIM_SS0_M_HSIOM_REG, GLCD_SPIM_SS0_M_HSIOM_MASK,
                                   GLCD_SPIM_SS0_M_HSIOM_POS, GLCD_SPIM_SS0_M_HSIOM_SEL_GPIO);
#endif /* (GLCD_SPIM_SPI_MASTER_SS0_PIN) */

#if (GLCD_SPIM_SPI_MASTER_SS1_PIN)
    /* Set output pin state after block is disabled */
    GLCD_SPIM_ss1_m_Write(GLCD_SPIM_GET_SPI_SS1_INACTIVE);

    /* Set GPIO to drive output pin */
    GLCD_SPIM_SET_HSIOM_SEL(GLCD_SPIM_SS1_M_HSIOM_REG, GLCD_SPIM_SS1_M_HSIOM_MASK,
                                   GLCD_SPIM_SS1_M_HSIOM_POS, GLCD_SPIM_SS1_M_HSIOM_SEL_GPIO);
#endif /* (GLCD_SPIM_SPI_MASTER_SS1_PIN) */

#if (GLCD_SPIM_SPI_MASTER_SS2_PIN)
    /* Set output pin state after block is disabled */
    GLCD_SPIM_ss2_m_Write(GLCD_SPIM_GET_SPI_SS2_INACTIVE);

    /* Set GPIO to drive output pin */
    GLCD_SPIM_SET_HSIOM_SEL(GLCD_SPIM_SS2_M_HSIOM_REG, GLCD_SPIM_SS2_M_HSIOM_MASK,
                                   GLCD_SPIM_SS2_M_HSIOM_POS, GLCD_SPIM_SS2_M_HSIOM_SEL_GPIO);
#endif /* (GLCD_SPIM_SPI_MASTER_SS2_PIN) */

#if (GLCD_SPIM_SPI_MASTER_SS3_PIN)
    /* Set output pin state after block is disabled */
    GLCD_SPIM_ss3_m_Write(GLCD_SPIM_GET_SPI_SS3_INACTIVE);

    /* Set GPIO to drive output pin */
    GLCD_SPIM_SET_HSIOM_SEL(GLCD_SPIM_SS3_M_HSIOM_REG, GLCD_SPIM_SS3_M_HSIOM_MASK,
                                   GLCD_SPIM_SS3_M_HSIOM_POS, GLCD_SPIM_SS3_M_HSIOM_SEL_GPIO);
#endif /* (GLCD_SPIM_SPI_MASTER_SS3_PIN) */

    #if (GLCD_SPIM_SPI_MASTER_CONST)
        /* Store TX interrupt sources (exclude level triggered). */
        GLCD_SPIM_IntrTxMask = LO16(GLCD_SPIM_GetTxInterruptMode() & GLCD_SPIM_INTR_SPIM_TX_RESTORE);
    #else
        /* Store TX interrupt sources (exclude level triggered). */
        GLCD_SPIM_IntrTxMask = LO16(GLCD_SPIM_GetTxInterruptMode() & GLCD_SPIM_INTR_SPIS_TX_RESTORE);
    #endif /* (GLCD_SPIM_SPI_MASTER_CONST) */

#endif /* (GLCD_SPIM_SCB_MODE_UNCONFIG_CONST_CFG) */
}


#if (GLCD_SPIM_SPI_MASTER_CONST)
    /*******************************************************************************
    * Function Name: GLCD_SPIM_SetActiveSlaveSelect
    ****************************************************************************//**
    *
    *  Selects one of the four slave select lines to be active during the transfer.
    *  After initialization the active slave select line is 0.
    *  The component should be in one of the following states to change the active
    *  slave select signal source correctly:
    *   - The component is disabled.
    *   - The component has completed transfer (TX FIFO is empty and the
    *     SCB_INTR_MASTER_SPI_DONE status is set).
    *
    *  This function does not check that these conditions are met.
    *  This function is only applicable to SPI Master mode of operation.
    *
    *  \param slaveSelect: slave select line which will be active while the following
    *   transfer.
    *   - GLCD_SPIM_SPI_SLAVE_SELECT0 - Slave select 0.
    *   - GLCD_SPIM_SPI_SLAVE_SELECT1 - Slave select 1.
    *   - GLCD_SPIM_SPI_SLAVE_SELECT2 - Slave select 2.
    *   - GLCD_SPIM_SPI_SLAVE_SELECT3 - Slave select 3.
    *
    *******************************************************************************/
    void GLCD_SPIM_SpiSetActiveSlaveSelect(uint32 slaveSelect)
    {
        uint32 spiCtrl;

        spiCtrl = GLCD_SPIM_SPI_CTRL_REG;

        spiCtrl &= (uint32) ~GLCD_SPIM_SPI_CTRL_SLAVE_SELECT_MASK;
        spiCtrl |= (uint32)  GLCD_SPIM_GET_SPI_CTRL_SS(slaveSelect);

        GLCD_SPIM_SPI_CTRL_REG = spiCtrl;
    }
#endif /* (GLCD_SPIM_SPI_MASTER_CONST) */


#if !(GLCD_SPIM_CY_SCBIP_V0 || GLCD_SPIM_CY_SCBIP_V1)
    /*******************************************************************************
    * Function Name: GLCD_SPIM_SpiSetSlaveSelectPolarity
    ****************************************************************************//**
    *
    *  Sets active polarity for slave select line.
    *  The component should be in one of the following states to change the active
    *  slave select signal source correctly:
    *   - The component is disabled.
    *   - The component has completed transfer.
    *  
    *  This function does not check that these conditions are met.
    *
    *  \param slaveSelect: slave select line to change active polarity.
    *   - GLCD_SPIM_SPI_SLAVE_SELECT0 - Slave select 0.
    *   - GLCD_SPIM_SPI_SLAVE_SELECT1 - Slave select 1.
    *   - GLCD_SPIM_SPI_SLAVE_SELECT2 - Slave select 2.
    *   - GLCD_SPIM_SPI_SLAVE_SELECT3 - Slave select 3.
    *
    *  \param polarity: active polarity of slave select line.
    *   - GLCD_SPIM_SPI_SS_ACTIVE_LOW  - Slave select is active low.
    *   - GLCD_SPIM_SPI_SS_ACTIVE_HIGH - Slave select is active high.
    *
    *******************************************************************************/
    void GLCD_SPIM_SpiSetSlaveSelectPolarity(uint32 slaveSelect, uint32 polarity)
    {
        uint32 ssPolarity;

        /* Get position of the polarity bit associated with slave select line */
        ssPolarity = GLCD_SPIM_GET_SPI_CTRL_SSEL_POLARITY((uint32) 1u << slaveSelect);

        if (0u != polarity)
        {
            GLCD_SPIM_SPI_CTRL_REG |= (uint32)  ssPolarity;
        }
        else
        {
            GLCD_SPIM_SPI_CTRL_REG &= (uint32) ~ssPolarity;
        }
    }
#endif /* !(GLCD_SPIM_CY_SCBIP_V0 || GLCD_SPIM_CY_SCBIP_V1) */


#if(GLCD_SPIM_SPI_WAKE_ENABLE_CONST)
    /*******************************************************************************
    * Function Name: GLCD_SPIM_SpiSaveConfig
    ****************************************************************************//**
    *
    *  Clears INTR_SPI_EC.WAKE_UP and enables it. This interrupt
    *  source triggers when the master assigns the SS line and wakes up the device.
    *
    *******************************************************************************/
    void GLCD_SPIM_SpiSaveConfig(void)
    {
        /* Clear and enable SPI wakeup interrupt source */
        GLCD_SPIM_ClearSpiExtClkInterruptSource(GLCD_SPIM_INTR_SPI_EC_WAKE_UP);
        GLCD_SPIM_SetSpiExtClkInterruptMode(GLCD_SPIM_INTR_SPI_EC_WAKE_UP);
    }


    /*******************************************************************************
    * Function Name: GLCD_SPIM_SpiRestoreConfig
    ****************************************************************************//**
    *
    *  Disables the INTR_SPI_EC.WAKE_UP interrupt source. After wakeup
    *  slave does not drive the MISO line and the master receives 0xFF.
    *
    *******************************************************************************/
    void GLCD_SPIM_SpiRestoreConfig(void)
    {
        /* Disable SPI wakeup interrupt source */
        GLCD_SPIM_SetSpiExtClkInterruptMode(GLCD_SPIM_NO_INTR_SOURCES);
    }
#endif /* (GLCD_SPIM_SPI_WAKE_ENABLE_CONST) */


/* [] END OF FILE */
