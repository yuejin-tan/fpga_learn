#include "main.h"
#include "scd_inc.h"
#include "delay.h"

void SysTick_Handler(void)
{
    ms_cnt++;
}
