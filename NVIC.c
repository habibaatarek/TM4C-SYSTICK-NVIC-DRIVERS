#include "NVIC.h"

/*********************************************************************
 * Service Name: NVIC_EnableIRQ
 * Sync/Async: Synchronous
 * Reentrancy: Reentrant
 * Parameters (in): IRQ_Num - Number of the IRQ from the target vector table
 * Parameters (inout): None
 * Parameters (out): None
 * Return value: None
 * Description: Function to enable Interrupt request for specific IRQ
**********************************************************************/
void NVIC_EnableIRQ(NVIC_IRQType IRQ_Num){
    if(IRQ_Num <= 31){
        NVIC_EN0_REG |= (1<<IRQ_Num);
    }
    else if(IRQ_Num <= 63){
        NVIC_EN1_REG |= (1<<(IRQ_Num - 32));
    }
    else if(IRQ_Num <= 95){
        NVIC_EN2_REG |= (1<<(IRQ_Num - 64));
    }
    else if(IRQ_Num <= 127){
        NVIC_EN3_REG |= (1<<(IRQ_Num - 95));
    }
    else if(IRQ_Num <= 138){
        NVIC_EN4_REG |= (1<<(IRQ_Num - 128));
    }
}


/*********************************************************************
 * Service Name: NVIC_DisableIRQ
 * Sync/Async: Synchronous
 * Reentrancy: Reentrant
 * Parameters (in): IRQ_Num - Number of the IRQ from the target vector table
 * Parameters (inout): None
 * Parameters (out): None
 * Return value: None
 * Description: Function to disable Interrupt request for specific IRQ
**********************************************************************/
void NVIC_DisableIRQ(NVIC_IRQType IRQ_Num){
    if(IRQ_Num <= 31){
        NVIC_DIS0_REG |= (1<<IRQ_Num);
    }
    else if(IRQ_Num <= 63){
        NVIC_DIS1_REG |= (1<<(IRQ_Num - 32));
    }
    else if(IRQ_Num <= 95){
        NVIC_DIS2_REG |= (1<<(IRQ_Num - 64));
    }
    else if(IRQ_Num <= 127){
        NVIC_DIS3_REG |= (1<<(IRQ_Num - 95));
    }
    else if(IRQ_Num <= 138){
        NVIC_DIS4_REG |= (1<<(IRQ_Num - 127));
    }
}


/*********************************************************************
 * Service Name: NVIC_SetPriorityIRQ
 * Sync/Async: Synchronous
 * Reentrancy: Reentrant
 * Parameters (in): IRQ_Num - Number of the IRQ from the target vector table
 *                  IRQ_Priority - Priority value to be set for the specific IRQ
 * Parameters (inout): None
 * Parameters (out): None
 * Return value: None
 * Description: Function to set the priority value for specific IRQ.
**********************************************************************/
void NVIC_SetPriorityIRQ(NVIC_IRQType IRQ_Num, NVIC_IRQPriorityType IRQ_Priority){
    uint32 priorityMask = 0;
    uint8  priorityBitsPosition = 0;
    uint32 priorityAddressOffset = 0;
    volatile uint32 *priorityRegAddress;

    if((IRQ_Num % 4)==0){
        priorityBitsPosition = 5;
    }
    else if((IRQ_Num % 4)==1){
        priorityBitsPosition = 13;
    }
    else if((IRQ_Num % 4)==2){
        priorityBitsPosition = 21;
    }
    else if((IRQ_Num % 4)==3){
        priorityBitsPosition = 29;
    }

    priorityMask = ~(0x7<<priorityBitsPosition);

    priorityAddressOffset = IRQ_Num / 4;

    priorityRegAddress = (volatile uint32 *)(0xE000E400 + (priorityAddressOffset * sizeof(uint32)));

    *priorityRegAddress = (*priorityRegAddress & priorityMask) | (IRQ_Priority << priorityBitsPosition);

}


/**********************************************************************
 * Service Name: NVIC_EnableException
 * Sync/Async: Synchronous
 * Reentrancy: Reentrant
 * Parameters (in): Exception_Num - Number of the exception
 * Parameters (inout): None
 * Parameters (out): None
 * Return value: None
 * Description: Function to enable a specific ARM system or fault exception.
 **********************************************************************/
void NVIC_EnableException(NVIC_ExceptionType Exception_Num){

    if(Exception_Num == EXCEPTION_MEM_FAULT_TYPE)
    {
        /* Enable the Memory Fault Exception */
        NVIC_SYSTEM_SYSHNDCTRL |= MEM_FAULT_ENABLE_MASK;
    }
    else if(Exception_Num == EXCEPTION_BUS_FAULT_TYPE)
    {
        /* Enable the Bus Fault Exception */
        NVIC_SYSTEM_SYSHNDCTRL |= BUS_FAULT_ENABLE_MASK;
    }
    else if(Exception_Num == EXCEPTION_USAGE_FAULT_TYPE)
    {
        /* Enable the Usage Fault Exception */
        NVIC_SYSTEM_SYSHNDCTRL |= USAGE_FAULT_ENABLE_MASK;
    }
}


/**********************************************************************
 * Service Name: NVIC_DisableException
 * Sync/Async: Synchronous
 * Reentrancy: Reentrant
 * Parameters (in): Exception_Num - Number of the exception
 * Parameters (inout): None
 * Parameters (out): None
 * Return value: None
 * Description: Function to disable a specific ARM system or fault exception.
 **********************************************************************/
void NVIC_DisableException(NVIC_ExceptionType Exception_Num){

    if(Exception_Num == EXCEPTION_MEM_FAULT_TYPE)
    {
        /* Disable the Memory Fault Exception */
        NVIC_SYSTEM_SYSHNDCTRL &= ~MEM_FAULT_ENABLE_MASK;
    }
    else if(Exception_Num == EXCEPTION_BUS_FAULT_TYPE)
    {
        /* Disable the Bus Fault Exception */
        NVIC_SYSTEM_SYSHNDCTRL &= ~BUS_FAULT_ENABLE_MASK;
    }
    else if(Exception_Num == EXCEPTION_USAGE_FAULT_TYPE)
    {
        /* Disable the Usage Fault Exception */
        NVIC_SYSTEM_SYSHNDCTRL &= ~USAGE_FAULT_ENABLE_MASK;
    }
}


/**********************************************************************
 * Service Name: NVIC_SetPriorityException
 * Sync/Async: Synchronous
 * Reentrancy: Reentrant
 * Parameters (in): Exception_Num - Number of the exception
 *                  Exception_Priority - Exception priority value
 * Parameters (inout): None
 * Parameters (out): None
 * Return value: None
 * Description: Function to set the priority of a specific ARM system or fault exception.
 **********************************************************************/
void NVIC_SetPriorityException(NVIC_ExceptionType Exception_Num, NVIC_ExceptionPriorityType Exception_Priority){

    if(Exception_Num == EXCEPTION_MEM_FAULT_TYPE)
    {
        NVIC_SYSTEM_PRI1_REG = (NVIC_SYSTEM_PRI1_REG & ~MEM_FAULT_PRIORITY_MASK) | (Exception_Priority << MEM_FAULT_PRIORITY_BITS_POS);
    }
    else if(Exception_Num == EXCEPTION_BUS_FAULT_TYPE)
    {
        NVIC_SYSTEM_PRI1_REG = (NVIC_SYSTEM_PRI1_REG & ~BUS_FAULT_PRIORITY_MASK) | (Exception_Priority << BUS_FAULT_PRIORITY_BITS_POS);
    }
    else if(Exception_Num == EXCEPTION_USAGE_FAULT_TYPE)
    {
        NVIC_SYSTEM_PRI1_REG = (NVIC_SYSTEM_PRI1_REG & ~USAGE_FAULT_PRIORITY_MASK) | (Exception_Priority << USAGE_FAULT_PRIORITY_BITS_POS);
    }
    else if(Exception_Num == EXCEPTION_SVC_TYPE)
    {
        NVIC_SYSTEM_PRI2_REG = (NVIC_SYSTEM_PRI2_REG & ~SVC_PRIORITY_MASK) | (Exception_Priority << SVC_PRIORITY_BITS_POS);
    }
    else if(Exception_Num == EXCEPTION_DEBUG_MONITOR_TYPE)
    {
        NVIC_SYSTEM_PRI3_REG = (NVIC_SYSTEM_PRI3_REG & ~DEBUG_MONITOR_PRIORITY_MASK) | (Exception_Priority << DEBUG_MONITOR_PRIORITY_BITS_POS);
    }
    else if(Exception_Num == EXCEPTION_PEND_SV_TYPE)
    {
        NVIC_SYSTEM_PRI3_REG = (NVIC_SYSTEM_PRI3_REG & ~PENDSV_PRIORITY_MASK) | (Exception_Priority << PENDSV_PRIORITY_BITS_POS);
    }
    else if(Exception_Num == EXCEPTION_SYSTICK_TYPE)
    {
        NVIC_SYSTEM_PRI3_REG =  (NVIC_SYSTEM_PRI3_REG & ~SYSTICK_PRIORITY_MASK) | (Exception_Priority << SYSTICK_PRIORITY_BITS_POS);
    }

}




