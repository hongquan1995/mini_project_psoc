/***************************************************************************//**
* \file GLCD_SPIM_SPI_UART_PVT.h
* \version 4.0
*
* \brief
*  This private file provides constants and parameter values for the
*  SCB Component in SPI and UART modes.
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

#if !defined(CY_SCB_SPI_UART_PVT_GLCD_SPIM_H)
#define CY_SCB_SPI_UART_PVT_GLCD_SPIM_H

#include "GLCD_SPIM_SPI_UART.h"


/***************************************
*     Internal Global Vars
***************************************/

#if (GLCD_SPIM_INTERNAL_RX_SW_BUFFER_CONST)
    extern volatile uint32  GLCD_SPIM_rxBufferHead;
    extern volatile uint32  GLCD_SPIM_rxBufferTail;
    
    /**
    * \addtogroup group_globals
    * @{
    */
    
    /** Sets when internal software receive buffer overflow
     *  was occurred.
    */  
    extern volatile uint8   GLCD_SPIM_rxBufferOverflow;
    /** @} globals */
#endif /* (GLCD_SPIM_INTERNAL_RX_SW_BUFFER_CONST) */

#if (GLCD_SPIM_INTERNAL_TX_SW_BUFFER_CONST)
    extern volatile uint32  GLCD_SPIM_txBufferHead;
    extern volatile uint32  GLCD_SPIM_txBufferTail;
#endif /* (GLCD_SPIM_INTERNAL_TX_SW_BUFFER_CONST) */

#if (GLCD_SPIM_INTERNAL_RX_SW_BUFFER)
    extern volatile uint8 GLCD_SPIM_rxBufferInternal[GLCD_SPIM_INTERNAL_RX_BUFFER_SIZE];
#endif /* (GLCD_SPIM_INTERNAL_RX_SW_BUFFER) */

#if (GLCD_SPIM_INTERNAL_TX_SW_BUFFER)
    extern volatile uint8 GLCD_SPIM_txBufferInternal[GLCD_SPIM_TX_BUFFER_SIZE];
#endif /* (GLCD_SPIM_INTERNAL_TX_SW_BUFFER) */


/***************************************
*     Private Function Prototypes
***************************************/

void GLCD_SPIM_SpiPostEnable(void);
void GLCD_SPIM_SpiStop(void);

#if (GLCD_SPIM_SCB_MODE_SPI_CONST_CFG)
    void GLCD_SPIM_SpiInit(void);
#endif /* (GLCD_SPIM_SCB_MODE_SPI_CONST_CFG) */

#if (GLCD_SPIM_SPI_WAKE_ENABLE_CONST)
    void GLCD_SPIM_SpiSaveConfig(void);
    void GLCD_SPIM_SpiRestoreConfig(void);
#endif /* (GLCD_SPIM_SPI_WAKE_ENABLE_CONST) */

void GLCD_SPIM_UartPostEnable(void);
void GLCD_SPIM_UartStop(void);

#if (GLCD_SPIM_SCB_MODE_UART_CONST_CFG)
    void GLCD_SPIM_UartInit(void);
#endif /* (GLCD_SPIM_SCB_MODE_UART_CONST_CFG) */

#if (GLCD_SPIM_UART_WAKE_ENABLE_CONST)
    void GLCD_SPIM_UartSaveConfig(void);
    void GLCD_SPIM_UartRestoreConfig(void);
#endif /* (GLCD_SPIM_UART_WAKE_ENABLE_CONST) */


/***************************************
*         UART API Constants
***************************************/

/* UART RX and TX position to be used in GLCD_SPIM_SetPins() */
#define GLCD_SPIM_UART_RX_PIN_ENABLE    (GLCD_SPIM_UART_RX)
#define GLCD_SPIM_UART_TX_PIN_ENABLE    (GLCD_SPIM_UART_TX)

/* UART RTS and CTS position to be used in  GLCD_SPIM_SetPins() */
#define GLCD_SPIM_UART_RTS_PIN_ENABLE    (0x10u)
#define GLCD_SPIM_UART_CTS_PIN_ENABLE    (0x20u)


/***************************************
* The following code is DEPRECATED and
* must not be used.
***************************************/

/* Interrupt processing */
#define GLCD_SPIM_SpiUartEnableIntRx(intSourceMask)  GLCD_SPIM_SetRxInterruptMode(intSourceMask)
#define GLCD_SPIM_SpiUartEnableIntTx(intSourceMask)  GLCD_SPIM_SetTxInterruptMode(intSourceMask)
uint32  GLCD_SPIM_SpiUartDisableIntRx(void);
uint32  GLCD_SPIM_SpiUartDisableIntTx(void);


#endif /* (CY_SCB_SPI_UART_PVT_GLCD_SPIM_H) */


/* [] END OF FILE */
