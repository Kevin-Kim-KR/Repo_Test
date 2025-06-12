/**
 * CAN1 Generated Driver Source File
 * 
 * @file can1.c
 *            
 * @ingroup can_driver
 *            
 * @brief Contains the implementation file for the CAN1 driver.
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

#include <string.h>
#include "../can1.h"

/**  
 * @name CAN1 Message object arbitration and control field information
 * Macros for the CAN1 Message object arbitration and control field.
 */
///@{
#define CAN_MSG_OBJ_SID_LOW_WIDTH          (0x8U) 
#define CAN_MSG_OBJ_SID_LOW_MASK           (0xFFU) 
#define CAN_MSG_OBJ_SID_HIGH_WIDTH         (0x3U) 
#define CAN_MSG_OBJ_SID_HIGH_MASK          (0x7U)  
#define CAN_MSG_OBJ_EID_LOW_WIDTH          (0x5U) 
#define CAN_MSG_OBJ_EID_LOW_MASK           (0xF8U)  
#define CAN_MSG_OBJ_EID_LOW_POSN           (0x3U)
#define CAN_MSG_OBJ_EID_MID_WIDTH          (0x8U) 
#define CAN_MSG_OBJ_EID_MID_MASK           (0xFFU)  
#define CAN_MSG_OBJ_EID_HIGH_WIDTH         (0x5U) 
#define CAN_MSG_OBJ_EID_HIGH_MASK          (0x1FU) 
#define CAN_MSG_OBJ_IDE_POSN               (0x4U)   
#define CAN_MSG_OBJ_RTR_POSN               (0x5U)     
#define CAN_MSG_OBJ_BRS_POSN               (0x6U) 
#define CAN_MSG_OBJ_FDF_POSN               (0x7U)  
#define CAN_MSG_OBJ_DLC_FIELD_MASK         (0xFU)  
#define CAN_MSG_OBJ_ID_TYPE_FIELD_MASK     (0x10U)
#define CAN_MSG_OBJ_FRAME_TYPE_FIELD_MASK  (0x20U)
#define CAN_MSG_OBJ_BRS_FIELD_MASK         (0x40U)
#define CAN_MSG_OBJ_FDF_FIELD_MASK         (0x80U)
#define CAN_STD_MSG_ID_SIZE                (CAN_MSG_OBJ_SID_LOW_WIDTH + CAN_MSG_OBJ_SID_HIGH_WIDTH)
///@}

/**
 @ingroup  can_driver
 @struct   CAN1_FIFOREG
 @brief    Defines a structure to access CAN1 FIFO Registers.
*/
struct CAN1_FIFOREG
{
    uint8_t CONL;
    uint8_t CONH;
    uint8_t CONU;
    uint8_t CONT;
    uint8_t STAL;
    uint8_t STAH;
    uint8_t STAU;
    uint8_t STAT;
    uint32_t UA;
};

// CAN1 Driver Interface 
const struct CAN_INTERFACE CAN_FD1 = {
    .Initialize = CAN1_Initialize,
    .Deinitialize = CAN1_Deinitialize,
    .OperationModeSet = CAN1_OperationModeSet,
    .OperationModeGet = CAN1_OperationModeGet,
    .Transmit = NULL,
    .TransmitFIFOStatusGet = NULL,
    .IsTxErrorPassive = NULL,
    .IsTxErrorWarning = NULL,
    .IsTxErrorActive = NULL,	
    .Receive = NULL,
    .ReceiveMessageGet = NULL,
    .ReceivedMessageCountGet = NULL,
    .ReceiveFIFOStatusGet = NULL,
    .IsRxErrorPassive = NULL,
    .IsRxErrorWarning = NULL,
    .IsRxErrorActive = NULL,
    .IsBusOff = CAN1_IsBusOff,
    .SleepMode = CAN1_Sleep,
    .InvalidMessageCallbackRegister = CAN1_InvalidMessageCallbackRegister,
    .BusWakeUpActivityCallbackRegister = CAN1_BusWakeUpActivityCallbackRegister,
    .BusErrorCallbackRegister = CAN1_BusErrorCallbackRegister,
    .ModeChangeCallbackRegister = CAN1_ModeChangeCallbackRegister,
    .SystemErrorCallbackRegister = CAN1_SystemErrorCallbackRegister,
    .TxAttemptCallbackRegister = NULL,
    .RxBufferOverFlowCallbackRegister = NULL,
    .Tasks = CAN1_Tasks
};

// CAN1 Default Callback Handler
static void (*CAN1_InvalidMessageHandler)(void) = NULL;
static void (*CAN1_BusWakeUpActivityHandler)(void) = NULL;
static void (*CAN1_BusErrorHandler)(void) = NULL;
static void (*CAN1_ModeChangeHandler)(void) = NULL;
static void (*CAN1_SystemErrorHandler)(void) = NULL;

// Defining a structure to access FIFO registers.
static volatile struct CAN1_FIFOREG * const FIFO = (struct CAN1_FIFOREG *)&C1TXQCONL;

/**
 * @ingroup can_driver
 * @brief Configures the CAN1 Bit rate settings.
 * @param None.
 * @return None.
*/
static void CAN1_BitRateConfiguration(void)
{
    // SJW 127; 
    C1NBTCFGL = 0x7F;
    // TSEG2 127; 
    C1NBTCFGH = 0x7F;
    // TSEG1 126; 
    C1NBTCFGU = 0x7E;
    // BRP 1; 
    C1NBTCFGT = 0x1;
    // SJW 0; 
    C1DBTCFGL = 0x0;
    // TSEG2 0; 
    C1DBTCFGH = 0x0;
    // TSEG1 0; 
    C1DBTCFGU = 0x0;
    // BRP 0; 
    C1DBTCFGT = 0x0;
    // TDCV 0x0; 
    C1TDCL = 0x0;
    // TDCO 0; 
    C1TDCH = 0x0;
    // TDCMOD Disable; 
    C1TDCU = 0x0;
    // SID11EN disabled; EDGFLTEN disabled; 
    C1TDCT = 0x0;
}


void CAN1_Initialize(void)
{
    /* Enable the CAN1 module */
    C1CONHbits.ON = 1;
	
    // ABAT disabled; TXBWS No delay; 
    C1CONT = 0x4;  
	
    // RTXAT disabled; ESIGM disabled; SERR2LOM disabled; STEF disabled; TXQEN disabled; 
    C1CONU = 0x80;  
    
    // Place CAN1 module in configuration mode
    if (CAN_OP_MODE_REQUEST_SUCCESS == CAN1_OperationModeSet(CAN_CONFIGURATION_MODE))
    {
        // WAKFIL enabled; WFT T11 Filter; SIDL disabled; FRZ disabled; ON enabled; BRSDIS enabled; 
        C1CONH = 0x97;  
	
        // DNCNT 0x0; CLKSEL0 disabled; ISOCRCEN enabled; PXEDIS enabled; 
        C1CONL = 0x60;  

        // Disabled CAN1 Store in Transmit Event FIFO bit
        C1CONUbits.STEF = 0;
        // Disabled CAN1 Transmit Queue bit
        C1CONUbits.TXQEN = 0;
        
        /* Configure CAN1 Bit rate settings */
        CAN1_BitRateConfiguration();        
        
        /* Place CAN1 module in Normal Operation mode */
        (void)CAN1_OperationModeSet(CAN_NORMAL_FD_MODE);    
    }
}

void CAN1_Deinitialize(void)
{
    /* Place CAN1 module in configuration mode */
    if(CAN_OP_MODE_REQUEST_SUCCESS == CAN1_OperationModeSet(CAN_CONFIGURATION_MODE))
    {        
        C1CONL = 0x60;  
        C1CONH = 0x7;  
        C1CONU = 0x98;  
        C1CONT = 0x4;  
           
        /* Reset bit rate settings to POR*/
        C1NBTCFGL = 0xF;
        C1NBTCFGH = 0xF;
        C1NBTCFGU = 0x3E;
        C1NBTCFGT = 0x0;
        C1DBTCFGL = 0x3;
        C1DBTCFGH = 0x3;
        C1DBTCFGU = 0xE;
        C1DBTCFGT = 0x0;
        C1TDCL = 0x0;
        C1TDCH = 0x10;
        C1TDCU = 0x2;
        C1TDCT = 0x0;

    }
    
    /* Disable the CAN1 module */
    C1CONHbits.ON = 0;
}

enum CAN_OP_MODE_STATUS CAN1_OperationModeSet(const enum CAN_OP_MODES requestMode)
{
    enum CAN_OP_MODE_STATUS status = CAN_OP_MODE_REQUEST_SUCCESS;

    if ((CAN1_OperationModeGet() == CAN_CONFIGURATION_MODE)
        || (requestMode == CAN_DISABLE_MODE)
        || (requestMode == CAN_CONFIGURATION_MODE))
    {
        C1CONTbits.REQOP = requestMode;
        
        while (C1CONUbits.OPMOD != requestMode)
        {
            //This condition is avoiding the system error case endless loop
            if (C1INTHbits.SERRIF == 1)
            {
                status = CAN_OP_MODE_SYS_ERROR_OCCURED;
                break;
            }
        }
    }
    else
    {
        status = CAN_OP_MODE_REQUEST_FAIL;
    }

    return status;
}

enum CAN_OP_MODES CAN1_OperationModeGet(void)
{
    return C1CONUbits.OPMOD;
}

bool CAN1_IsBusOff(void)
{
    return C1TRECUbits.TXBO;
}

void CAN1_Sleep(void)
{
    C1INTHbits.WAKIF = 0;
    C1INTTbits.WAKIE = 1;
	
    // CAN Information Interrupt Enable bit
    PIE0bits.CANIE = 1;  
    
    // put the module in disable mode
    (void)CAN1_OperationModeSet(CAN_DISABLE_MODE);
}

void CAN1_InvalidMessageCallbackRegister(void (*handler)(void))
{
    if(handler != NULL)
    {
        CAN1_InvalidMessageHandler = handler;
    }
}

void CAN1_BusWakeUpActivityCallbackRegister(void (*handler)(void))
{
    if(handler != NULL)
    {
        CAN1_BusWakeUpActivityHandler = handler;
    }
}

void CAN1_BusErrorCallbackRegister(void (*handler)(void))
{
    if(handler != NULL)
    {
        CAN1_BusErrorHandler = handler;
    }
}

void CAN1_ModeChangeCallbackRegister(void (*handler)(void))
{
    if(handler != NULL)
    {
        CAN1_ModeChangeHandler = handler;
    }
}

void CAN1_SystemErrorCallbackRegister(void (*handler)(void))
{
    if(handler != NULL)
    {
        CAN1_SystemErrorHandler = handler;
    }
}



void CAN1_InformationISR(void)
{
    // Bus Wake-up Activity Interrupt 
    if(1 == C1INTHbits.WAKIF)
    {
        if(CAN1_BusWakeUpActivityHandler != NULL)
        {
            CAN1_BusWakeUpActivityHandler();
        } 
		
        C1INTHbits.WAKIF = 0;
    }
    
    PIR0bits.CANIF = 0;
}

void CAN1_Tasks(void)
{
	
    if(1 == C1INTHbits.IVMIF)
    {
        if(CAN1_InvalidMessageHandler != NULL)
        {
            CAN1_InvalidMessageHandler();
        } 
		
        C1INTHbits.IVMIF = 0;
    }  
	
    if(1 == C1INTHbits.CERRIF)
    {
        if(CAN1_BusErrorHandler != NULL)
        {
            CAN1_BusErrorHandler();
        } 
		
        C1INTHbits.CERRIF = 0;
    }  
	
    if(1 == C1INTLbits.MODIF)
    {
        if(CAN1_ModeChangeHandler != NULL)
        {
            CAN1_ModeChangeHandler();
        } 
		
        C1INTLbits.MODIF = 0;
    }  
	
    if(1 == C1INTHbits.SERRIF)
    {
        if(CAN1_SystemErrorHandler != NULL)
        {
            CAN1_SystemErrorHandler();
        } 
		
        C1INTHbits.SERRIF = 0;
    }  
}


