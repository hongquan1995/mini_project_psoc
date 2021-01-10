/***************************************************************************//**
* \file GLCD_SPIM_BOOT.h
* \version 4.0
*
* \brief
*  This file provides constants and parameter values of the bootloader
*  communication APIs for the SCB Component.
*
* Note:
*
********************************************************************************
* \copyright
* Copyright 2014-2017, Cypress Semiconductor Corporation. All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_SCB_BOOT_GLCD_SPIM_H)
#define CY_SCB_BOOT_GLCD_SPIM_H

#include "GLCD_SPIM_PVT.h"

#if (GLCD_SPIM_SCB_MODE_I2C_INC)
    #include "GLCD_SPIM_I2C.h"
#endif /* (GLCD_SPIM_SCB_MODE_I2C_INC) */

#if (GLCD_SPIM_SCB_MODE_EZI2C_INC)
    #include "GLCD_SPIM_EZI2C.h"
#endif /* (GLCD_SPIM_SCB_MODE_EZI2C_INC) */

#if (GLCD_SPIM_SCB_MODE_SPI_INC || GLCD_SPIM_SCB_MODE_UART_INC)
    #include "GLCD_SPIM_SPI_UART.h"
#endif /* (GLCD_SPIM_SCB_MODE_SPI_INC || GLCD_SPIM_SCB_MODE_UART_INC) */


/***************************************
*  Conditional Compilation Parameters
****************************************/

/* Bootloader communication interface enable */
#define GLCD_SPIM_BTLDR_COMM_ENABLED ((CYDEV_BOOTLOADER_IO_COMP == CyBtldr_GLCD_SPIM) || \
                                             (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_Custom_Interface))

/* Enable I2C bootloader communication */
#if (GLCD_SPIM_SCB_MODE_I2C_INC)
    #define GLCD_SPIM_I2C_BTLDR_COMM_ENABLED     (GLCD_SPIM_BTLDR_COMM_ENABLED && \
                                                            (GLCD_SPIM_SCB_MODE_UNCONFIG_CONST_CFG || \
                                                             GLCD_SPIM_I2C_SLAVE_CONST))
#else
     #define GLCD_SPIM_I2C_BTLDR_COMM_ENABLED    (0u)
#endif /* (GLCD_SPIM_SCB_MODE_I2C_INC) */

/* EZI2C does not support bootloader communication. Provide empty APIs */
#if (GLCD_SPIM_SCB_MODE_EZI2C_INC)
    #define GLCD_SPIM_EZI2C_BTLDR_COMM_ENABLED   (GLCD_SPIM_BTLDR_COMM_ENABLED && \
                                                         GLCD_SPIM_SCB_MODE_UNCONFIG_CONST_CFG)
#else
    #define GLCD_SPIM_EZI2C_BTLDR_COMM_ENABLED   (0u)
#endif /* (GLCD_SPIM_EZI2C_BTLDR_COMM_ENABLED) */

/* Enable SPI bootloader communication */
#if (GLCD_SPIM_SCB_MODE_SPI_INC)
    #define GLCD_SPIM_SPI_BTLDR_COMM_ENABLED     (GLCD_SPIM_BTLDR_COMM_ENABLED && \
                                                            (GLCD_SPIM_SCB_MODE_UNCONFIG_CONST_CFG || \
                                                             GLCD_SPIM_SPI_SLAVE_CONST))
#else
        #define GLCD_SPIM_SPI_BTLDR_COMM_ENABLED (0u)
#endif /* (GLCD_SPIM_SPI_BTLDR_COMM_ENABLED) */

/* Enable UART bootloader communication */
#if (GLCD_SPIM_SCB_MODE_UART_INC)
       #define GLCD_SPIM_UART_BTLDR_COMM_ENABLED    (GLCD_SPIM_BTLDR_COMM_ENABLED && \
                                                            (GLCD_SPIM_SCB_MODE_UNCONFIG_CONST_CFG || \
                                                             (GLCD_SPIM_UART_RX_DIRECTION && \
                                                              GLCD_SPIM_UART_TX_DIRECTION)))
#else
     #define GLCD_SPIM_UART_BTLDR_COMM_ENABLED   (0u)
#endif /* (GLCD_SPIM_UART_BTLDR_COMM_ENABLED) */

/* Enable bootloader communication */
#define GLCD_SPIM_BTLDR_COMM_MODE_ENABLED    (GLCD_SPIM_I2C_BTLDR_COMM_ENABLED   || \
                                                     GLCD_SPIM_SPI_BTLDR_COMM_ENABLED   || \
                                                     GLCD_SPIM_EZI2C_BTLDR_COMM_ENABLED || \
                                                     GLCD_SPIM_UART_BTLDR_COMM_ENABLED)


/***************************************
*        Function Prototypes
***************************************/

#if defined(CYDEV_BOOTLOADER_IO_COMP) && (GLCD_SPIM_I2C_BTLDR_COMM_ENABLED)
    /* I2C Bootloader physical layer functions */
    void GLCD_SPIM_I2CCyBtldrCommStart(void);
    void GLCD_SPIM_I2CCyBtldrCommStop (void);
    void GLCD_SPIM_I2CCyBtldrCommReset(void);
    cystatus GLCD_SPIM_I2CCyBtldrCommRead       (uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
    cystatus GLCD_SPIM_I2CCyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);

    /* Map I2C specific bootloader communication APIs to SCB specific APIs */
    #if (GLCD_SPIM_SCB_MODE_I2C_CONST_CFG)
        #define GLCD_SPIM_CyBtldrCommStart   GLCD_SPIM_I2CCyBtldrCommStart
        #define GLCD_SPIM_CyBtldrCommStop    GLCD_SPIM_I2CCyBtldrCommStop
        #define GLCD_SPIM_CyBtldrCommReset   GLCD_SPIM_I2CCyBtldrCommReset
        #define GLCD_SPIM_CyBtldrCommRead    GLCD_SPIM_I2CCyBtldrCommRead
        #define GLCD_SPIM_CyBtldrCommWrite   GLCD_SPIM_I2CCyBtldrCommWrite
    #endif /* (GLCD_SPIM_SCB_MODE_I2C_CONST_CFG) */

#endif /* defined(CYDEV_BOOTLOADER_IO_COMP) && (GLCD_SPIM_I2C_BTLDR_COMM_ENABLED) */


#if defined(CYDEV_BOOTLOADER_IO_COMP) && (GLCD_SPIM_EZI2C_BTLDR_COMM_ENABLED)
    /* Bootloader physical layer functions */
    void GLCD_SPIM_EzI2CCyBtldrCommStart(void);
    void GLCD_SPIM_EzI2CCyBtldrCommStop (void);
    void GLCD_SPIM_EzI2CCyBtldrCommReset(void);
    cystatus GLCD_SPIM_EzI2CCyBtldrCommRead       (uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
    cystatus GLCD_SPIM_EzI2CCyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);

    /* Map EZI2C specific bootloader communication APIs to SCB specific APIs */
    #if (GLCD_SPIM_SCB_MODE_EZI2C_CONST_CFG)
        #define GLCD_SPIM_CyBtldrCommStart   GLCD_SPIM_EzI2CCyBtldrCommStart
        #define GLCD_SPIM_CyBtldrCommStop    GLCD_SPIM_EzI2CCyBtldrCommStop
        #define GLCD_SPIM_CyBtldrCommReset   GLCD_SPIM_EzI2CCyBtldrCommReset
        #define GLCD_SPIM_CyBtldrCommRead    GLCD_SPIM_EzI2CCyBtldrCommRead
        #define GLCD_SPIM_CyBtldrCommWrite   GLCD_SPIM_EzI2CCyBtldrCommWrite
    #endif /* (GLCD_SPIM_SCB_MODE_EZI2C_CONST_CFG) */

#endif /* defined(CYDEV_BOOTLOADER_IO_COMP) && (GLCD_SPIM_EZI2C_BTLDR_COMM_ENABLED) */

#if defined(CYDEV_BOOTLOADER_IO_COMP) && (GLCD_SPIM_SPI_BTLDR_COMM_ENABLED)
    /* SPI Bootloader physical layer functions */
    void GLCD_SPIM_SpiCyBtldrCommStart(void);
    void GLCD_SPIM_SpiCyBtldrCommStop (void);
    void GLCD_SPIM_SpiCyBtldrCommReset(void);
    cystatus GLCD_SPIM_SpiCyBtldrCommRead       (uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
    cystatus GLCD_SPIM_SpiCyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);

    /* Map SPI specific bootloader communication APIs to SCB specific APIs */
    #if (GLCD_SPIM_SCB_MODE_SPI_CONST_CFG)
        #define GLCD_SPIM_CyBtldrCommStart   GLCD_SPIM_SpiCyBtldrCommStart
        #define GLCD_SPIM_CyBtldrCommStop    GLCD_SPIM_SpiCyBtldrCommStop
        #define GLCD_SPIM_CyBtldrCommReset   GLCD_SPIM_SpiCyBtldrCommReset
        #define GLCD_SPIM_CyBtldrCommRead    GLCD_SPIM_SpiCyBtldrCommRead
        #define GLCD_SPIM_CyBtldrCommWrite   GLCD_SPIM_SpiCyBtldrCommWrite
    #endif /* (GLCD_SPIM_SCB_MODE_SPI_CONST_CFG) */

#endif /* defined(CYDEV_BOOTLOADER_IO_COMP) && (GLCD_SPIM_SPI_BTLDR_COMM_ENABLED) */

#if defined(CYDEV_BOOTLOADER_IO_COMP) && (GLCD_SPIM_UART_BTLDR_COMM_ENABLED)
    /* UART Bootloader physical layer functions */
    void GLCD_SPIM_UartCyBtldrCommStart(void);
    void GLCD_SPIM_UartCyBtldrCommStop (void);
    void GLCD_SPIM_UartCyBtldrCommReset(void);
    cystatus GLCD_SPIM_UartCyBtldrCommRead       (uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
    cystatus GLCD_SPIM_UartCyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);

    /* Map UART specific bootloader communication APIs to SCB specific APIs */
    #if (GLCD_SPIM_SCB_MODE_UART_CONST_CFG)
        #define GLCD_SPIM_CyBtldrCommStart   GLCD_SPIM_UartCyBtldrCommStart
        #define GLCD_SPIM_CyBtldrCommStop    GLCD_SPIM_UartCyBtldrCommStop
        #define GLCD_SPIM_CyBtldrCommReset   GLCD_SPIM_UartCyBtldrCommReset
        #define GLCD_SPIM_CyBtldrCommRead    GLCD_SPIM_UartCyBtldrCommRead
        #define GLCD_SPIM_CyBtldrCommWrite   GLCD_SPIM_UartCyBtldrCommWrite
    #endif /* (GLCD_SPIM_SCB_MODE_UART_CONST_CFG) */

#endif /* defined(CYDEV_BOOTLOADER_IO_COMP) && (GLCD_SPIM_UART_BTLDR_COMM_ENABLED) */

/**
* \addtogroup group_bootloader
* @{
*/

#if defined(CYDEV_BOOTLOADER_IO_COMP) && (GLCD_SPIM_BTLDR_COMM_ENABLED)
    #if (GLCD_SPIM_SCB_MODE_UNCONFIG_CONST_CFG)
        /* Bootloader physical layer functions */
        void GLCD_SPIM_CyBtldrCommStart(void);
        void GLCD_SPIM_CyBtldrCommStop (void);
        void GLCD_SPIM_CyBtldrCommReset(void);
        cystatus GLCD_SPIM_CyBtldrCommRead       (uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
        cystatus GLCD_SPIM_CyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
    #endif /* (GLCD_SPIM_SCB_MODE_UNCONFIG_CONST_CFG) */

    /* Map SCB specific bootloader communication APIs to common APIs */
    #if (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_GLCD_SPIM)
        #define CyBtldrCommStart    GLCD_SPIM_CyBtldrCommStart
        #define CyBtldrCommStop     GLCD_SPIM_CyBtldrCommStop
        #define CyBtldrCommReset    GLCD_SPIM_CyBtldrCommReset
        #define CyBtldrCommWrite    GLCD_SPIM_CyBtldrCommWrite
        #define CyBtldrCommRead     GLCD_SPIM_CyBtldrCommRead
    #endif /* (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_GLCD_SPIM) */

#endif /* defined(CYDEV_BOOTLOADER_IO_COMP) && (GLCD_SPIM_BTLDR_COMM_ENABLED) */

/** @} group_bootloader */

/***************************************
*           API Constants
***************************************/

/* Timeout unit in milliseconds */
#define GLCD_SPIM_WAIT_1_MS  (1u)

/* Return number of bytes to copy into bootloader buffer */
#define GLCD_SPIM_BYTES_TO_COPY(actBufSize, bufSize) \
                            ( ((uint32)(actBufSize) < (uint32)(bufSize)) ? \
                                ((uint32) (actBufSize)) : ((uint32) (bufSize)) )

/* Size of Read/Write buffers for I2C bootloader  */
#define GLCD_SPIM_I2C_BTLDR_SIZEOF_READ_BUFFER   (64u)
#define GLCD_SPIM_I2C_BTLDR_SIZEOF_WRITE_BUFFER  (64u)

/* Byte to byte time interval: calculated basing on current component
* data rate configuration, can be defined in project if required.
*/
#ifndef GLCD_SPIM_SPI_BYTE_TO_BYTE
    #define GLCD_SPIM_SPI_BYTE_TO_BYTE   (18u)
#endif

/* Byte to byte time interval: calculated basing on current component
* baud rate configuration, can be defined in the project if required.
*/
#ifndef GLCD_SPIM_UART_BYTE_TO_BYTE
    #define GLCD_SPIM_UART_BYTE_TO_BYTE  (2500u)
#endif /* GLCD_SPIM_UART_BYTE_TO_BYTE */

#endif /* (CY_SCB_BOOT_GLCD_SPIM_H) */


/* [] END OF FILE */
