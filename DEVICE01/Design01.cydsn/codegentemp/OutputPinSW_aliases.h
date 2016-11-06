/*******************************************************************************
* File Name: OutputPinSW.h  
* Version 2.20
*
* Description:
*  This file contains the Alias definitions for Per-Pin APIs in cypins.h. 
*  Information on using these APIs can be found in the System Reference Guide.
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_OutputPinSW_ALIASES_H) /* Pins OutputPinSW_ALIASES_H */
#define CY_PINS_OutputPinSW_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define OutputPinSW_0			(OutputPinSW__0__PC)
#define OutputPinSW_0_PS		(OutputPinSW__0__PS)
#define OutputPinSW_0_PC		(OutputPinSW__0__PC)
#define OutputPinSW_0_DR		(OutputPinSW__0__DR)
#define OutputPinSW_0_SHIFT	(OutputPinSW__0__SHIFT)
#define OutputPinSW_0_INTR	((uint16)((uint16)0x0003u << (OutputPinSW__0__SHIFT*2u)))

#define OutputPinSW_INTR_ALL	 ((uint16)(OutputPinSW_0_INTR))


#endif /* End Pins OutputPinSW_ALIASES_H */


/* [] END OF FILE */
