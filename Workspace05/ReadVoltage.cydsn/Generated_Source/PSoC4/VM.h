/*******************************************************************************
* File Name: VM.h  
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

#if !defined(CY_PINS_VM_H) /* Pins VM_H */
#define CY_PINS_VM_H

#include "cytypes.h"
#include "cyfitter.h"
#include "VM_aliases.h"


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
} VM_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   VM_Read(void);
void    VM_Write(uint8 value);
uint8   VM_ReadDataReg(void);
#if defined(VM__PC) || (CY_PSOC4_4200L) 
    void    VM_SetDriveMode(uint8 mode);
#endif
void    VM_SetInterruptMode(uint16 position, uint16 mode);
uint8   VM_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void VM_Sleep(void); 
void VM_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(VM__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define VM_DRIVE_MODE_BITS        (3)
    #define VM_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - VM_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the VM_SetDriveMode() function.
         *  @{
         */
        #define VM_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define VM_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define VM_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define VM_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define VM_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define VM_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define VM_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define VM_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define VM_MASK               VM__MASK
#define VM_SHIFT              VM__SHIFT
#define VM_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in VM_SetInterruptMode() function.
     *  @{
     */
        #define VM_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define VM_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define VM_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define VM_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(VM__SIO)
    #define VM_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(VM__PC) && (CY_PSOC4_4200L)
    #define VM_USBIO_ENABLE               ((uint32)0x80000000u)
    #define VM_USBIO_DISABLE              ((uint32)(~VM_USBIO_ENABLE))
    #define VM_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define VM_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define VM_USBIO_ENTER_SLEEP          ((uint32)((1u << VM_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << VM_USBIO_SUSPEND_DEL_SHIFT)))
    #define VM_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << VM_USBIO_SUSPEND_SHIFT)))
    #define VM_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << VM_USBIO_SUSPEND_DEL_SHIFT)))
    #define VM_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(VM__PC)
    /* Port Configuration */
    #define VM_PC                 (* (reg32 *) VM__PC)
#endif
/* Pin State */
#define VM_PS                     (* (reg32 *) VM__PS)
/* Data Register */
#define VM_DR                     (* (reg32 *) VM__DR)
/* Input Buffer Disable Override */
#define VM_INP_DIS                (* (reg32 *) VM__PC2)

/* Interrupt configuration Registers */
#define VM_INTCFG                 (* (reg32 *) VM__INTCFG)
#define VM_INTSTAT                (* (reg32 *) VM__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define VM_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(VM__SIO)
    #define VM_SIO_REG            (* (reg32 *) VM__SIO)
#endif /* (VM__SIO_CFG) */

/* USBIO registers */
#if !defined(VM__PC) && (CY_PSOC4_4200L)
    #define VM_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define VM_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define VM_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define VM_DRIVE_MODE_SHIFT       (0x00u)
#define VM_DRIVE_MODE_MASK        (0x07u << VM_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins VM_H */


/* [] END OF FILE */
