/*******************************************************************************
* File Name: U.h  
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

#if !defined(CY_PINS_U_H) /* Pins U_H */
#define CY_PINS_U_H

#include "cytypes.h"
#include "cyfitter.h"
#include "U_aliases.h"


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
} U_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   U_Read(void);
void    U_Write(uint8 value);
uint8   U_ReadDataReg(void);
#if defined(U__PC) || (CY_PSOC4_4200L) 
    void    U_SetDriveMode(uint8 mode);
#endif
void    U_SetInterruptMode(uint16 position, uint16 mode);
uint8   U_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void U_Sleep(void); 
void U_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(U__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define U_DRIVE_MODE_BITS        (3)
    #define U_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - U_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the U_SetDriveMode() function.
         *  @{
         */
        #define U_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define U_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define U_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define U_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define U_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define U_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define U_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define U_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define U_MASK               U__MASK
#define U_SHIFT              U__SHIFT
#define U_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in U_SetInterruptMode() function.
     *  @{
     */
        #define U_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define U_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define U_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define U_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(U__SIO)
    #define U_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(U__PC) && (CY_PSOC4_4200L)
    #define U_USBIO_ENABLE               ((uint32)0x80000000u)
    #define U_USBIO_DISABLE              ((uint32)(~U_USBIO_ENABLE))
    #define U_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define U_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define U_USBIO_ENTER_SLEEP          ((uint32)((1u << U_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << U_USBIO_SUSPEND_DEL_SHIFT)))
    #define U_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << U_USBIO_SUSPEND_SHIFT)))
    #define U_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << U_USBIO_SUSPEND_DEL_SHIFT)))
    #define U_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(U__PC)
    /* Port Configuration */
    #define U_PC                 (* (reg32 *) U__PC)
#endif
/* Pin State */
#define U_PS                     (* (reg32 *) U__PS)
/* Data Register */
#define U_DR                     (* (reg32 *) U__DR)
/* Input Buffer Disable Override */
#define U_INP_DIS                (* (reg32 *) U__PC2)

/* Interrupt configuration Registers */
#define U_INTCFG                 (* (reg32 *) U__INTCFG)
#define U_INTSTAT                (* (reg32 *) U__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define U_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(U__SIO)
    #define U_SIO_REG            (* (reg32 *) U__SIO)
#endif /* (U__SIO_CFG) */

/* USBIO registers */
#if !defined(U__PC) && (CY_PSOC4_4200L)
    #define U_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define U_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define U_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define U_DRIVE_MODE_SHIFT       (0x00u)
#define U_DRIVE_MODE_MASK        (0x07u << U_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins U_H */


/* [] END OF FILE */
