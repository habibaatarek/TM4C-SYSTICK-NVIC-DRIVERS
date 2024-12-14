
#ifndef SYSTICK_H_
#define SYSTICK_H_

#include "tm4c123gh6pm_registers.h"
#include "std_types.h"

#define MCU_Freq_Hz  16000000

/*********************************************************************
 * Service Name: SysTick_Init
 * Sync/Async: Synchronous
 * Reentrancy:
 * Parameters (in): a_TimeInMilliSeconds - specified time in milliseconds
 * Parameters (inout): None
 * Parameters (out): None
 * Return value: None
 * Description: Initialize the SysTick timer with the specified time in milliseconds using interrupts.
**********************************************************************/
void SysTick_Init(uint16 a_TimeInMilliSeconds);


/*********************************************************************
 * Service Name: SysTick_StartBusyWait
 * Sync/Async: Synchronous
 * Reentrancy:
 * Parameters (in): a_TimeInMilliSeconds - specified time in milliseconds
 * Parameters (inout): None
 * Parameters (out): None
 * Return value: None
 * Description: Initialize the SysTick timer with the specified time in milliseconds using polling or busy-wait technique.
**********************************************************************/
void SysTick_StartBusyWait(uint16 a_TimeInMilliSeconds);


/*********************************************************************
 * Service Name: SysTick_Handler
 * Sync/Async: Asynchronous
 * Reentrancy:
 * Parameters (in): None
 * Parameters (inout): None
 * Parameters (out): None
 * Return value: None
 * Description: Handler for SysTick interrupt use to call the call-back function.
**********************************************************************/
void SysTick_Handler(void);


/*********************************************************************
 * Service Name: SysTick_SetCallBack
 * Sync/Async: Synchronous
 * Reentrancy:
 * Parameters (in): (*Ptr2Func) - Pointer to function
 * Parameters (inout): None
 * Parameters (out): None
 * Return value: None
 * Description: Function to setup the SysTick Timer call back to be executed in SysTick Handler.
**********************************************************************/
void SysTick_SetCallBack(volatile void (*Ptr2Func) (void));


/*********************************************************************
 * Service Name: SysTick_Stop
 * Sync/Async: Synchronous
 * Reentrancy:
 * Parameters (in): None
 * Parameters (inout): None
 * Parameters (out): None
 * Return value: None
 * Description: Function to stop the SysTick Timer
**********************************************************************/
void SysTick_Stop(void);


/*********************************************************************
 * Service Name: SysTick_Start
 * Sync/Async: Synchronous
 * Reentrancy:
 * Parameters (in): None
 * Parameters (inout): None
 * Parameters (out): None
 * Return value: None
 * Description: Function to start the SysTick Timer
**********************************************************************/
void SysTick_Start(void);


/*********************************************************************
 * Service Name: SysTick_DeInit
 * Sync/Async: Synchronous
 * Reentrancy:
 * Parameters (in): None
 * Parameters (inout): None
 * Parameters (out): None
 * Return value: None
 * Description: Function to De-initialize the SysTick Timer
**********************************************************************/
void SysTick_DeInit(void);

#endif /* SYSTICK_H_ */
