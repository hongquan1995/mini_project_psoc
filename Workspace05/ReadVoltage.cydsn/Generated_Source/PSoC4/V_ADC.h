/*******************************************************************************
* File Name: V_ADC.h  
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

#if !defined(CY_PINS_V_ADC_H) /* Pins V_ADC_H */
#define CY_PINS_V_ADC_H

#include "cytypes.h"
#include "cyfitter.h"
#include "V_ADC_aliases.h"


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
} V_ADC_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   V_ADC_Read(void);
void    V_ADC_Write(uint8 value);
uint8   V_ADC_ReadDataReg(void);
#if defined(V_ADC__PC) || (CY_PSOC4_4200L) 
    void    V_ADC_SetDriveMode(uint8 mode);
#endif
void    V_ADC_SetInterruptMode(uint16 position, uint16 mode);
uint8   V_ADC_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void V_ADC_Sleep(void); 
void V_ADC_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(V_ADC__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define V_ADC_DRIVE_MODE_BITS        (3)
    #define V_ADC_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - V_ADC_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the V_ADC_SetDriveMode() function.
         *  @{
         */
        #define V_ADC_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define V_ADC_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define V_ADC_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define V_ADC_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define V_ADC_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define V_ADC_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define V_ADC_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define V_ADC_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define V_ADC_MASK               V_ADC__MASK
#define V_ADC_SHIFT              V_ADC__SHIFT
#define V_ADC_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in V_ADC_SetInterruptMode() function.
     *  @{
     */
        #define V_ADC_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define V_ADC_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define V_ADC_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define V_ADC_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(V_ADC__SIO)
    #define V_ADC_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(V_ADC__PC) && (CY_PSOC4_4200L)
    #define V_ADC_USBIO_ENABLE               ((uint32)0x80000000u)
    #define V_ADC_USBIO_DISABLE              ((uint32)(~V_ADC_USBIO_ENABLE))
    #define V_ADC_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define V_ADC_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define V_ADC_USBIO_ENTER_SLEEP          ((uint32)((1u << V_ADC_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << V_ADC_USBIO_SUSPEND_DEL_SHIFT)))
    #define V_ADC_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << V_ADC_USBIO_SUSPEND_SHIFT)))
    #define V_ADC_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << V_ADC_USBIO_SUSPEND_DEL_SHIFT)))
    #define V_ADC_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(V_ADC__PC)
    /* Port Configuration */
    #define V_ADC_PC                 (* (reg32 *) V_ADC__PC)
#endif
/* Pin State */
#define V_ADC_PS                     (* (reg32 *) V_ADC__PS)
/* Data Register */
#define V_ADC_DR                     (* (reg32 *) V_ADC__DR)
/* Input Buffer Disable Override */
#define V_ADC_INP_DIS                (* (reg32 *) V_ADC__PC2)

/* Interrupt configuration Registers */
#define V_ADC_INTCFG                 (* (reg32 *) V_ADC__INTCFG)
#define V_ADC_INTSTAT                (* (reg32 *) V_ADC__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define V_ADC_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(V_ADC__SIO)
    #define V_ADC_SIO_REG            (* (reg32 *) V_ADC__SIO)
#endif /* (V_ADC__SIO_CFG) */

/* USBIO registers */
#if !defined(V_ADC__PC) && (CY_PSOC4_4200L)
    #define V_ADC_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define V_ADC_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define V_ADC_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define V_ADC_DRIVE_MODE_SHIFT       (0x00u)
#define V_ADC_DRIVE_MODE_MASK        (0x07u << V_ADC_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins V_ADC_H */


/* [] END OF FILE */
