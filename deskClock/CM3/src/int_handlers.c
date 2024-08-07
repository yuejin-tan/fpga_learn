#include "main.h"
#include "scd_inc.h"
#include "delay.h"
#include "CM3DS_uart.h"

// 由freertos管理
// void SysTick_Handler(void)
// {
//     ms_cnt++;
// }

//uart0 中断处理函数
void UART0_Handler(void)
{
    SCD_Rev1Byte(&scd_1, UART_ReceiveData(CM3DS_MPS2_UART0));

    //清除中断
    UART_ITCLEAR(CM3DS_MPS2_UART0, UART_INTCLEAR_RxInterrupt);
}
