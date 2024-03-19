#include "delay.h"
#include "stdint.h"

#include "CMSDK_CM0.h"

__asm void
SysCtlDelay(uint32_t ui32Count)
{
    subs    r0, #1;
    bne     SysCtlDelay;
    bx      lr;
}

void DELAY_TICK(uint32_t ticks)
{
    const uint32_t diff = 8;

    ticks /= 3;
    if (ticks > diff)
    {
        ticks -= diff;
    }
    else
    {
        return;
    }

    SysCtlDelay(ticks);
    return;
}

void delay_ms(uint32_t delay_ms)
{
    for (uint32_t i = 0;i < delay_ms;i++)
    {
        while ((SysTick->CTRL & SysTick_CTRL_COUNTFLAG_Msk) == 0)
        {
            // wait
        }
    }
}
