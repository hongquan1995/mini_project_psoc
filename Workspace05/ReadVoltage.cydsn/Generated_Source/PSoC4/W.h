/*******************************************************************************
* File Name: W.h  
* Version 2.20
*
* Description:
*  This file contains Pin function prototypes and register defines
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_W_H) /* Pins W_H */
#define CY_PINS_W_H

#include "cytypes.h"
#include "cyfitter.h"
#include "W_aliases.h"


/***************************************
*     Data Struct Definitions
***************************************/

/**
* \addtogroup group_structures
* @{
*/
    
/* Structure for sleep mode support */
typedef struct
{
    uint32 pcState; /**< State of the port control register */
    uint32 sioState; /**< State of the SIO configuration */
    uint32 usbState; /**< State of the USBIO regulator */
} W_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   W_Read(void);
void    W_Write(uint8 value);
uint8   W_ReadDataReg(void);
#if defined(W__PC) || (CY_PSOC4_4200L) 
    void    W_SetDriveMode(uint8 mode);
#endif
void    W_SetInterruptMode(uint16 position, uint16 mode);
uint8   W_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void W_Sleep(void); 
void W_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(W__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define W_DRIVE_MODE_BITS        (3)
    #define W_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - W_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the W_SetDriveMode() function.
         *  @{
         */
        #define W_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define W_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define W_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define W_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define W_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define W_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define W_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define W_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define W_MASK               W__MASK
#define W_SHIFT              W__SHIFT
#define W_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in W_SetInterruptMode() function.
     *  @{
     */
        #define W_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define W_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define W_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define W_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(W__SIO)
    #define W_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(W__PC) && (CY_PSOC4_4200L)
    #define W_USBIO_ENABLE               ((uint32)0x80000000u)
    #define W_USBIO_DISABLE              ((uint32)(~W_USBIO_ENABLE))
    #define W_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define W_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define W_USBIO_ENTER_SLEEP          ((uint32)((1u << W_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << W_USBIO_SUSPEND_DEL_SHIFT)))
    #define W_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << W_USBIO_SUSPEND_SHIFT)))
    #define W_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << W_USBIO_SUSPEND_DEL_SHIFT)))
    #define W_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(W__PC)
    /* Port Configuration */
    #define W_PC                 (* (reg32 *) W__PC)
#endif
/* Pin State */
#define W_PS                     (* (reg32 *) W__PS)
/* Data Register */
#define W_DR                     (* (reg32 *) W__DR)
/* Input Buffer Disable Override */
#define W_INP_DIS                (* (reg32 *) W__PC2)

/* Interrupt configuration Registers */
#define W_INTCFG                 (* (reg32 *) W__INTCFG)
#define W_INTSTAT                (* (reg32 *) W__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define W_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(W__SIO)
    #define W_SIO_REG            (* (reg32 *) W__SIO)
#endif /* (W__SIO_CFG) */

/* USBIO registers */
#if !defined(W__PC) && (CY_PSOC4_4200L)
    #define W_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define W_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define W_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define W_DRIVE_MODE_SHIFT       (0x00u)
#define W_DRIVE_MODE_MASK        (0x07u << W_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins W_H */


/* [] END OF FILE */
