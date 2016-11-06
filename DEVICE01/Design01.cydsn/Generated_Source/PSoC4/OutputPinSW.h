/*******************************************************************************
* File Name: OutputPinSW.h  
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

#if !defined(CY_PINS_OutputPinSW_H) /* Pins OutputPinSW_H */
#define CY_PINS_OutputPinSW_H

#include "cytypes.h"
#include "cyfitter.h"
#include "OutputPinSW_aliases.h"


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
} OutputPinSW_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   OutputPinSW_Read(void);
void    OutputPinSW_Write(uint8 value);
uint8   OutputPinSW_ReadDataReg(void);
#if defined(OutputPinSW__PC) || (CY_PSOC4_4200L) 
    void    OutputPinSW_SetDriveMode(uint8 mode);
#endif
void    OutputPinSW_SetInterruptMode(uint16 position, uint16 mode);
uint8   OutputPinSW_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void OutputPinSW_Sleep(void); 
void OutputPinSW_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(OutputPinSW__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define OutputPinSW_DRIVE_MODE_BITS        (3)
    #define OutputPinSW_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - OutputPinSW_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the OutputPinSW_SetDriveMode() function.
         *  @{
         */
        #define OutputPinSW_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define OutputPinSW_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define OutputPinSW_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define OutputPinSW_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define OutputPinSW_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define OutputPinSW_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define OutputPinSW_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define OutputPinSW_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define OutputPinSW_MASK               OutputPinSW__MASK
#define OutputPinSW_SHIFT              OutputPinSW__SHIFT
#define OutputPinSW_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in OutputPinSW_SetInterruptMode() function.
     *  @{
     */
        #define OutputPinSW_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define OutputPinSW_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define OutputPinSW_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define OutputPinSW_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(OutputPinSW__SIO)
    #define OutputPinSW_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(OutputPinSW__PC) && (CY_PSOC4_4200L)
    #define OutputPinSW_USBIO_ENABLE               ((uint32)0x80000000u)
    #define OutputPinSW_USBIO_DISABLE              ((uint32)(~OutputPinSW_USBIO_ENABLE))
    #define OutputPinSW_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define OutputPinSW_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define OutputPinSW_USBIO_ENTER_SLEEP          ((uint32)((1u << OutputPinSW_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << OutputPinSW_USBIO_SUSPEND_DEL_SHIFT)))
    #define OutputPinSW_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << OutputPinSW_USBIO_SUSPEND_SHIFT)))
    #define OutputPinSW_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << OutputPinSW_USBIO_SUSPEND_DEL_SHIFT)))
    #define OutputPinSW_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(OutputPinSW__PC)
    /* Port Configuration */
    #define OutputPinSW_PC                 (* (reg32 *) OutputPinSW__PC)
#endif
/* Pin State */
#define OutputPinSW_PS                     (* (reg32 *) OutputPinSW__PS)
/* Data Register */
#define OutputPinSW_DR                     (* (reg32 *) OutputPinSW__DR)
/* Input Buffer Disable Override */
#define OutputPinSW_INP_DIS                (* (reg32 *) OutputPinSW__PC2)

/* Interrupt configuration Registers */
#define OutputPinSW_INTCFG                 (* (reg32 *) OutputPinSW__INTCFG)
#define OutputPinSW_INTSTAT                (* (reg32 *) OutputPinSW__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define OutputPinSW_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(OutputPinSW__SIO)
    #define OutputPinSW_SIO_REG            (* (reg32 *) OutputPinSW__SIO)
#endif /* (OutputPinSW__SIO_CFG) */

/* USBIO registers */
#if !defined(OutputPinSW__PC) && (CY_PSOC4_4200L)
    #define OutputPinSW_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define OutputPinSW_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define OutputPinSW_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define OutputPinSW_DRIVE_MODE_SHIFT       (0x00u)
#define OutputPinSW_DRIVE_MODE_MASK        (0x07u << OutputPinSW_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins OutputPinSW_H */


/* [] END OF FILE */
