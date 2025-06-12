/**
 * CAN1 Generated Driver Header File
 *
 * @file can1.h
 *
 * @defgroup can_driver CAN FD DRIVER
 *
 * @brief This file contains API prototypes and other data types for the CAN1 driver.
 *
 * @version CAN Driver Version 1.0.0
*/

/*
? [2025] Microchip Technology Inc. and its subsidiaries.

    Subject to your compliance with these terms, you may use Microchip 
    software and any derivatives exclusively with Microchip products. 
    You are responsible for complying with 3rd party license terms  
    applicable to your use of 3rd party software (including open source  
    software) that may accompany Microchip software. SOFTWARE IS ?AS IS.? 
    NO WARRANTIES, WHETHER EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS 
    SOFTWARE, INCLUDING ANY IMPLIED WARRANTIES OF NON-INFRINGEMENT,  
    MERCHANTABILITY, OR FITNESS FOR A PARTICULAR PURPOSE. IN NO EVENT 
    WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY 
    KIND WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF 
    MICROCHIP HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE 
    FORESEEABLE. TO THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP?S 
    TOTAL LIABILITY ON ALL CLAIMS RELATED TO THE SOFTWARE WILL NOT 
    EXCEED AMOUNT OF FEES, IF ANY, YOU PAID DIRECTLY TO MICROCHIP FOR 
    THIS SOFTWARE.
*/

#ifndef CAN1_H
#define CAN1_H

#include <xc.h>
#include <stdbool.h>
#include <stdint.h>
#include "can_types.h"
#include "can_interface.h"

/**
 @ingroup  can_driver
 @brief    Structure object of type CAN_INTERFACE with the custom name given by
           the user. 
*/
extern const struct CAN_INTERFACE CAN_FD1;

/**
 * @ingroup  can_driver
 * @brief    Defines the Custom Name for CAN1_Initialize() API.
 */
#define CAN_FD1_Initialize CAN1_Initialize
/**
 * @ingroup  can_driver
 * @brief    Defines the Custom Name for CAN1_Deinitialize() API.
 */
#define CAN_FD1_Deinitialize CAN1_Deinitialize
/**
 * @ingroup  can_driver
 * @brief    Defines the Custom Name for CAN1_OperationModeSet() API.
 */
#define CAN_FD1_OperationModeSet CAN1_OperationModeSet
/**
 * @ingroup  can_driver
 * @brief    Defines the Custom Name for CAN1_OperationModeGet() API.
 */
#define CAN_FD1_OperationModeGet CAN1_OperationModeGet
/**
 * @ingroup  can_driver
 * @brief    Defines the Custom Name for CAN1_IsBusOff() API.
 */
#define CAN_FD1_IsBusOff CAN1_IsBusOff
/**
 * @ingroup  can_driver
 * @brief    Defines the Custom Name for CAN1_Sleep() API.
 */
#define CAN_FD1_Sleep CAN1_Sleep
/**
 * @ingroup  can_driver
 * @brief    Defines the Custom Name for CAN1_InvalidMessageCallbackRegister() API.
 */
#define CAN_FD1_InvalidMessageCallbackRegister CAN1_InvalidMessageCallbackRegister
/**
 * @ingroup  can_driver
 * @brief    Defines the Custom Name for CAN1_BusWakeUpActivityCallbackRegister() API.
 */
#define CAN_FD1_BusWakeUpActivityCallbackRegister CAN1_BusWakeUpActivityCallbackRegister
/**
 * @ingroup  can_driver
 * @brief    Defines the Custom Name for CAN1_BusErrorCallbackRegister() API.
 */
#define CAN_FD1_BusErrorCallbackRegister CAN1_BusErrorCallbackRegister
/**
 * @ingroup  can_driver
 * @brief    Defines the Custom Name for CAN1_ModeChangeCallbackRegister() API.
 */
#define CAN_FD1_ModeChangeCallbackRegister CAN1_ModeChangeCallbackRegister
/**
 * @ingroup  can_driver
 * @brief    Defines the Custom Name for CAN1_SystemErrorCallbackRegister() API.
 */
#define CAN_FD1_SystemErrorCallbackRegister CAN1_SystemErrorCallbackRegister
/**
 * @ingroup  can_driver
 * @brief    Defines the Custom Name for CAN1_Tasks() API.
 */
#define CAN_FD1_Tasks CAN1_Tasks

/**
 * @ingroup can_driver
 * @brief Initializes the CAN1 module.
 * @param None.
 * @return None.
 */
void CAN1_Initialize(void);

/**
 * @ingroup can_driver
 * @brief Resets the CAN1 registers and settings to their POR values.
 * @param None.
 * @return None.
 */
void CAN1_Deinitialize(void);

/**
 * @ingroup can_driver
 * @brief Sets the CAN1 Operation mode.
 * @pre CAN1_Initialize() function is already called.
 * @param [in] requestMode - CAN1 Operation mode as described in CAN_OP_MODES.
 * @return Status of request to set the CAN1 Operation mode as described in CAN_OP_MODE_STATUS.
 */
enum CAN_OP_MODE_STATUS CAN1_OperationModeSet(const enum CAN_OP_MODES requestMode);

/**
 * @ingroup can_driver
 * @brief Gets the CAN1 Operation mode.
 * @pre CAN1_Initialize() function is already called.
 * @param None.
 * @return The present CAN1 Operation mode as described in CAN_OP_MODES.
 */
enum CAN_OP_MODES CAN1_OperationModeGet(void);

/**
 * @ingroup can_driver
 * @brief Returns the Bus Off status.
 * @pre CAN1_Initialize() function is already called.
 * @param None.
 * @retval True - CAN1 node is in Bus Off state.
 * @retval False - CAN1 node is not in Bus Off state.
 */
bool CAN1_IsBusOff(void);

/**
 * @ingroup can_driver
 * @brief Puts the CAN1 node into Sleep mode.
 * @pre CAN1_Initialize() function is already called.
 * @param None.
 * @return None.
 */
void CAN1_Sleep(void);

/**
 * @ingroup can_driver
 * @brief Setter function for the CAN1_InvalidMessage callback.
 * @param [in] handler - Pointer to the callback routine.
 * @return None.
 */
void CAN1_InvalidMessageCallbackRegister(void (*handler)(void));

/**
 * @ingroup can_driver
 * @brief Setter function for the CAN1_BusWakeUpActivity callback.
 * @param [in] handler - Pointer to the callback routine.
 * @return None.
 */
void CAN1_BusWakeUpActivityCallbackRegister(void (*handler)(void));

/**
 * @ingroup can_driver
 * @brief Setter function for the CAN1_BusError callback.
 * @param [in] handler - Pointer to the callback routine.
 * @return None.
 */
void CAN1_BusErrorCallbackRegister(void (*handler)(void));

/**
 * @ingroup can_driver
 * @brief Setter function for the CAN1_ModeChange callback.
 * @param [in] handler - Pointer to the callback routine.
 * @return None.
 */
void CAN1_ModeChangeCallbackRegister(void (*handler)(void));

/**
 * @ingroup can_driver
 * @brief Setter function for the CAN1_SystemError callback.
 * @param [in] handler - Pointer to the callback routine.
 * @return None.
 */
void CAN1_SystemErrorCallbackRegister(void (*handler)(void));



/**
 * @ingroup can_driver
 * @brief Used to implement the tasks for polled implementations.
 * @pre CAN1_Initialize() function is already called.
 * @param None.
 * @return None.
 */
void CAN1_Tasks(void);

/**
 * @ingroup can_driver
 * @brief CAN1 Information Interrupt Service Routine (ISR) function.
 * @param None.
 * @return None.
 */
void CAN1_InformationISR(void);

#endif  //CAN1_H
