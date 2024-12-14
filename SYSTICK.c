#include "SYSTICK.h"

/* Global variable to hold the address of the call back function */
static volatile void (*g_SysTickcallBackPtr)(void) = NULL_PTR;


/*********************************************************************
 * Service Name: SysTick_Init
 * Sync/Async: Synchronous
 * Reentrancy: Reentrant
 * Parameters (in): a_TimeInMilliSeconds - specified time in milliseconds
 * Parameters (inout): None
 * Parameters (out): None
 * Return value: None
 * Description: Initialize the SysTick timer with the specified time in milliseconds using interrupts.
**********************************************************************/
void SysTick_Init(uint16 a_TimeInMilliSeconds){
    SYSTICK_CTRL_REG    = 0;                                               /* Disable the SysTick Timer by Clear the ENABLE Bit */
    uint32 reloadValue  = ((MCU_Freq_Hz/1000)*a_TimeInMilliSeconds) - 1;
    SYSTICK_RELOAD_REG  = reloadValue;                                     /* Set the Reload value with time needed */
    SYSTICK_CURRENT_REG = 0;                                               /* Clear the Current Register value */

    /* Configure the SysTick Control Register
     * Enable the SysTick Timer (ENABLE = 1)
     * Disable SysTick Interrupt (INTEN = 1)
     * Choose the clock source to be System Clock (CLK_SRC = 1)
     */
    SYSTICK_CTRL_REG   |= 0x07;
}


/*********************************************************************
 * Service Name: SysTick_StartBusyWait
 * Sync/Async: Synchronous
 * Reentrancy: Reentrant
 * Parameters (in): a_TimeInMilliSeconds - specified time in milliseconds
 * Parameters (inout): None
 * Parameters (out): None
 * Return value: None
 * Description: Initialize the SysTick timer with the specified time in milliseconds using polling or busy-wait technique.
**********************************************************************/
void SysTick_StartBusyWait(uint16 a_TimeInMilliSeconds){
    SYSTICK_CTRL_REG    = 0;                                               /* Disable the SysTick Timer by Clear the ENABLE Bit */
    uint32 reloadValue  = ((MCU_Freq_Hz/1000)*a_TimeInMilliSeconds) - 1;
    SYSTICK_RELOAD_REG  = reloadValue;                                     /* Set the Reload value with time needed */
    SYSTICK_CURRENT_REG = 0;                                               /* Clear the Current Register value */

    /* Configure the SysTick Control Register
     * Enable the SysTick Timer (ENABLE = 1)
     * Disable SysTick Interrupt (INTEN = 0)
     * Choose the clock source to be System Clock (CLK_SRC = 1)
     */
    SYSTICK_CTRL_REG   |= 0x05;

    while(!(SYSTICK_CTRL_REG & (1<<16))); /* wait until the COUNT flag = 1 which mean SysTick Timer reaches ZERO value ... COUNT flag is cleared after read the CTRL register value */
    SYSTICK_CTRL_REG    = 0;                                               /* Disable the SysTick Timer by Clear the ENABLE Bit */
}


/*********************************************************************
 * Service Name: SysTick_Handler
 * Sync/Async: Asynchronous
 * Reentrancy: Reentrant
 * Parameters (in): None
 * Parameters (inout): None
 * Parameters (out): None
 * Return value: None
 * Description: Handler for SysTick interrupt used to call the call-back function.
**********************************************************************/
void SysTick_Handler(void){
    if(g_SysTickcallBackPtr != NULL_PTR){
        (*g_SysTickcallBackPtr)();
    }
}


/*********************************************************************
 * Service Name: SysTick_SetCallBack
 * Sync/Async: Synchronous
 * Reentrancy: Reentrant
 * Parameters (in): (*Ptr2Func) - Pointer to function
 * Parameters (inout): None
 * Parameters (out): None
 * Return value: None
 * Description: Function to setup the SysTick Timer call back to be executed in SysTick Handler.
**********************************************************************/
void SysTick_SetCallBack(volatile void (*Ptr2Func) (void)){
    g_SysTickcallBackPtr = Ptr2Func;
}


/*********************************************************************
 * Service Name: SysTick_Stop
 * Sync/Async: Synchronous
 * Reentrancy: Reentrant
 * Parameters (in): None
 * Parameters (inout): None
 * Parameters (out): None
 * Return value: None
 * Description: Function to stop the SysTick Timer
**********************************************************************/
void SysTick_Stop(void){
    SYSTICK_CTRL_REG  &= ~(1<<0);    /* Stop the SysTick Timer by Clear the ENABLE Bit */
}


/*********************************************************************
 * Service Name: SysTick_Start
 * Sync/Async: Synchronous
 * Reentrancy: Reentrant
 * Parameters (in): None
 * Parameters (inout): None
 * Parameters (out): None
 * Return value: None
 * Description: Function to start the SysTick Timer
**********************************************************************/
void SysTick_Start(void){
    SYSTICK_CTRL_REG  |= (1<<0);    /* Resume the SysTick Timer by setting the ENABLE Bit */
}


/*********************************************************************
 * Service Name: SysTick_DeInit
 * Sync/Async: Synchronous
 * Reentrancy: Reentrant
 * Parameters (in): None
 * Parameters (inout): None
 * Parameters (out): None
 * Return value: None
 * Description: Function to De-initialize the SysTick Timer
**********************************************************************/
void SysTick_DeInit(void){
    SYSTICK_CTRL_REG    = 0;             /* Disable the SysTick Timer by Clear the ENABLE Bit */
    SYSTICK_RELOAD_REG  = 0;             /* Clear Reload Register value */
    SYSTICK_CURRENT_REG = 0;             /* Clear the Current Register value */
}
