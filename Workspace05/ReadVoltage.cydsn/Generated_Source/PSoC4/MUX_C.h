/*******************************************************************************
* File Name: MUX_C.h  
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

#if !defined(CY_PINS_MUX_C_H) /* Pins MUX_C_H */
#define CY_PINS_MUX_C_H

#include "cytypes.h"
#include "cyfitter.h"
#include "MUX_C_aliases.h"


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
} MUX_C_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   MUX_C_Read(void);
void    MUX_C_Write(uint8 value);
uint8   MUX_C_ReadDataReg(void);
#if defined(MUX_C__PC) || (CY_PSOC4_4200L) 
    void    MUX_C_SetDriveMode(uint8 mode);
#endif
void    MUX_C_SetInterruptMode(uint16 position, uint16 mode);
uint8   MUX_C_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void MUX_C_Sleep(void); 
void MUX_C_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(MUX_C__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define MUX_C_DRIVE_MODE_BITS        (3)
    #define MUX_C_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - MUX_C_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the MUX_C_SetDriveMode() function.
         *  @{
         */
        #define MUX_C_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define MUX_C_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define MUX_C_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define MUX_C_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define MUX_C_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define MUX_C_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define MUX_C_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define MUX_C_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define MUX_C_MASK               MUX_C__MASK
#define MUX_C_SHIFT              MUX_C__SHIFT
#define MUX_C_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in MUX_C_SetInterruptMode() function.
     *  @{
     */
        #define MUX_C_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define MUX_C_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define MUX_C_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define MUX_C_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(MUX_C__SIO)
    #define MUX_C_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(MUX_C__PC) && (CY_PSOC4_4200L)
    #define MUX_C_USBIO_ENABLE               ((uint32)0x80000000u)
    #define MUX_C_USBIO_DISABLE              ((uint32)(~MUX_C_USBIO_ENABLE))
    #define MUX_C_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define MUX_C_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define MUX_C_USBIO_ENTER_SLEEP          ((uint32)((1u << MUX_C_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << MUX_C_USBIO_SUSPEND_DEL_SHIFT)))
    #define MUX_C_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << MUX_C_USBIO_SUSPEND_SHIFT)))
    #define MUX_C_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << MUX_C_USBIO_SUSPEND_DEL_SHIFT)))
    #define MUX_C_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(MUX_C__PC)
    /* Port Configuration */
    #define MUX_C_PC                 (* (reg32 *) MUX_C__PC)
#endif
/* Pin State */
#define MUX_C_PS                     (* (reg32 *) MUX_C__PS)
/* Data Register */
#define MUX_C_DR                     (* (reg32 *) MUX_C__DR)
/* Input Buffer Disable Override */
#define MUX_C_INP_DIS                (* (reg32 *) MUX_C__PC2)

/* Interrupt configuration Registers */
#define MUX_C_INTCFG                 (* (reg32 *) MUX_C__INTCFG)
#define MUX_C_INTSTAT                (* (reg32 *) MUX_C__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define MUX_C_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(MUX_C__SIO)
    #define MUX_C_SIO_REG            (* (reg32 *) MUX_C__SIO)
#endif /* (MUX_C__SIO_CFG) */

/* USBIO registers */
#if !defined(MUX_C__PC) && (CY_PSOC4_4200L)
    #define MUX_C_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define MUX_C_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define MUX_C_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define MUX_C_DRIVE_MODE_SHIFT       (0x00u)
#define MUX_C_DRIVE_MODE_MASK        (0x07u << MUX_C_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins MUX_C_H */


/* [] END OF FILE */
