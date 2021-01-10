/*******************************************************************************
* File Name: V.h  
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

#if !defined(CY_PINS_V_H) /* Pins V_H */
#define CY_PINS_V_H

#include "cytypes.h"
#include "cyfitter.h"
#include "V_aliases.h"


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
} V_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   V_Read(void);
void    V_Write(uint8 value);
uint8   V_ReadDataReg(void);
#if defined(V__PC) || (CY_PSOC4_4200L) 
    void    V_SetDriveMode(uint8 mode);
#endif
void    V_SetInterruptMode(uint16 position, uint16 mode);
uint8   V_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void V_Sleep(void); 
void V_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(V__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define V_DRIVE_MODE_BITS        (3)
    #define V_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - V_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the V_SetDriveMode() function.
         *  @{
         */
        #define V_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define V_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define V_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define V_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define V_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define V_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define V_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define V_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define V_MASK               V__MASK
#define V_SHIFT              V__SHIFT
#define V_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in V_SetInterruptMode() function.
     *  @{
     */
        #define V_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define V_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define V_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define V_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(V__SIO)
    #define V_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(V__PC) && (CY_PSOC4_4200L)
    #define V_USBIO_ENABLE               ((uint32)0x80000000u)
    #define V_USBIO_DISABLE              ((uint32)(~V_USBIO_ENABLE))
    #define V_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define V_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define V_USBIO_ENTER_SLEEP          ((uint32)((1u << V_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << V_USBIO_SUSPEND_DEL_SHIFT)))
    #define V_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << V_USBIO_SUSPEND_SHIFT)))
    #define V_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << V_USBIO_SUSPEND_DEL_SHIFT)))
    #define V_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(V__PC)
    /* Port Configuration */
    #define V_PC                 (* (reg32 *) V__PC)
#endif
/* Pin State */
#define V_PS                     (* (reg32 *) V__PS)
/* Data Register */
#define V_DR                     (* (reg32 *) V__DR)
/* Input Buffer Disable Override */
#define V_INP_DIS                (* (reg32 *) V__PC2)

/* Interrupt configuration Registers */
#define V_INTCFG                 (* (reg32 *) V__INTCFG)
#define V_INTSTAT                (* (reg32 *) V__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define V_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(V__SIO)
    #define V_SIO_REG            (* (reg32 *) V__SIO)
#endif /* (V__SIO_CFG) */

/* USBIO registers */
#if !defined(V__PC) && (CY_PSOC4_4200L)
    #define V_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define V_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define V_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define V_DRIVE_MODE_SHIFT       (0x00u)
#define V_DRIVE_MODE_MASK        (0x07u << V_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins V_H */


/* [] END OF FILE */
