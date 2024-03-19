#include "string.h"

#include "CMSDK_CM0.h"

#include "delay.h"
#include "ahb_uart.h"
#include "ahb_led.h"

#include "scd_inc.h"

void uart_ahb_init()
{
    __ISB();
    __DSB();
    __DMB();
    AHB_UART->cmd.all = 0;
    __ISB();
    __DSB();
    __DMB();
    AHB_UART->buad_div_2 = (SystemCoreClock / (115200ul * 2ul)) - 1;
    // AHB_UART->buad_div_2 = (SystemCoreClock / (460800ul * 2ul)) - 1;
    __ISB();
    __DSB();
    __DMB();
    AHB_UART->cmd.all = 1;
    __ISB();
    __DSB();
    __DMB();
}

volatile uint32_t ms_cnt = 0;

uint16_t test1 = 0;
uint16_t test2 = 0;
uint16_t test3 = 0;
uint16_t test4 = 0;

uint16_t test1r = 0;
uint16_t test2r = 0;
uint16_t test3r = 0;
uint16_t test4r = 0;

uint8_t txdata = 0;
uint8_t rxdata = 0;
uint8_t rxbuff[256] = { 0 };
uint8_t rxbuffptr = 0;

int main(void)
{
    SysTick_Config(SystemCoreClock / 1000ul - 1ul);
    uart_ahb_init();
    test3 = AHB_UART->buad_div_2;

    // 测试delay函数
    // delay_ms(1000);
    // test1 = ms_cnt;
    // DELAY_TICK(1000 * 1000 * 50);
    // test2 = ms_cnt;

    scd_init_1();

    while (1)
    {
        // if (AHB_UART->cmd.bit.TX_FIFO_FULL == 0)
        // {
        //     AHB_UART->data = scd_send1Byte(&scd_1);
        // }

        // if (AHB_UART->cmd.bit.RX_FIFO_EMPTY == 0)
        // {
        //     SCD_Rev1Byte(&scd_1, AHB_UART->data);
        // }

        AHB_LED->seg0 = (ms_cnt >> 0) & 0xful;
        AHB_LED->seg1 = (ms_cnt >> 4) & 0xful;
        AHB_LED->seg2 = (ms_cnt >> 8) & 0xful;
        AHB_LED->seg3 = (ms_cnt >> 12) & 0xful;
        AHB_LED->seg4 = (ms_cnt >> 16) & 0xful;
        AHB_LED->seg5 = (ms_cnt >> 20) & 0xful;
        AHB_LED->seg6 = (ms_cnt >> 24) & 0xful;
        AHB_LED->seg7 = (ms_cnt >> 28) & 0xful;

        test1r = AHB_LED->seg1;
        test1r <<= 8;
        test1r |= AHB_LED->seg0;
        test2r = AHB_LED->seg3;
        test2r <<= 8;
        test2r |= AHB_LED->seg2;
        test3r = AHB_LED->seg5;
        test3r <<= 8;
        test3r |= AHB_LED->seg4;
        test4r = AHB_LED->seg7;
        test4r <<= 8;
        test4r |= AHB_LED->seg6;
    }

}



