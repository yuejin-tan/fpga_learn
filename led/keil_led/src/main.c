#include "string.h"

#include "CM3DS_gpio.h"
#include "CM3DS_rcc.h"
#include "CM3DS_misc.h"
#include "CM3DS_uart.h"

#include "delay.h"
#include "ahb_led.h"
#include "ahb_uart.h"

#include "scd_inc.h"

void nvicInit(void)
{
    NVIC_SetPriorityGrouping(NVIC_PriorityGroup_2);

    // UART
    NVIC_InitTypeDef InitTypeDef_NVIC;
    InitTypeDef_NVIC.NVIC_IRQChannel = UART0_IRQn;
    InitTypeDef_NVIC.NVIC_IRQChannelPreemptionPriority = 2;
    InitTypeDef_NVIC.NVIC_IRQChannelSubPriority = 0;
    InitTypeDef_NVIC.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&InitTypeDef_NVIC);
    NVIC_ClearPendingIRQ(UART0_IRQn);
}

void uart0_init()
{
    UART_InitTypeDef  UART_InitStructure;
    RCC_APB1PeriphResetCmd(RCC_APB1Periph_UART0, DISABLE);//clock enable
    //将对应的GPIO管脚复用为UART0的收发管脚
    GPIO_PinRemapConfig(CM3DS_MPS2_GPIO0, GPIO_Remap_USART0_RXD, ENABLE);
    GPIO_PinRemapConfig(CM3DS_MPS2_GPIO0, GPIO_Remap_USART0_TXD, ENABLE);
    //波特率
    UART_InitStructure.UART_BundRate = 115200;
    //收发使能
    UART_InitStructure.UART_CTRL = UART_CTRL_TxEnable | UART_CTRL_RxEnable;
    UART_Init(CM3DS_MPS2_UART0, &UART_InitStructure);
    //接收中断配置
    UART_ITConfig(CM3DS_MPS2_UART0, UART_RxInterrupt, ENABLE);
    NVIC_EnableIRQ(UART0_IRQn);
}

void uart_ahb_init()
{
    AHB_UART->cmd.all = 0;
    AHB_UART->buad_div_2 = (100ul * 1000ul * 1000ul / (115200ul * 2ul)) - 1;
    // AHB_UART->buad_div_2 = (100ul * 1000ul * 1000ul / (460800ul * 2ul)) - 1;
    AHB_UART->cmd.all = 1;
}

uint32_t mem_addr16b_test()
{
    uint32_t start_addr = CM3DS_MPS2_TARGEXP0_BASE;
    uint32_t addr_size = 19;
    uint32_t k;
    uint32_t xshift;
    uint32_t retval = 0;

    uint8_t sram_rd8;
    uint8_t sram_wd8;
    volatile uint8_t* XMEM_p8;

    uint16_t sram_rd16;
    uint16_t sram_wd16;
    volatile uint16_t* XMEM_p16;

    uint32_t sram_rd32;
    uint32_t sram_wd32;
    volatile uint32_t* XMEM_p32;

    memset((void*)CM3DS_MPS2_TARGEXP0_BASE, 0, 1000ul * 1000ul);

    //Write loop 8
    xshift = 0x00000001ul << addr_size;
    sram_wd8 = 0xAAul;
    for (k = 0; k < addr_size + 2; k++)
    {
        XMEM_p8 = (uint8_t*)(start_addr + xshift);
        *XMEM_p8 = sram_wd8;

        xshift = xshift >> 1;
        if (sram_wd8 & 0x80ul)
            sram_wd8 = (sram_wd8 << 1) + 1;
        else
            sram_wd8 = sram_wd8 << 1;
    }

    //Read loop 8
    xshift = 0x00000001ul << addr_size;
    sram_wd8 = 0xAAul;
    for (k = 0; k < addr_size + 2; k++)
    {
        XMEM_p8 = (uint8_t*)(start_addr + xshift);
        sram_rd8 = *XMEM_p8;
        if (sram_rd8 != sram_wd8)
        {
            retval++;
        }

        xshift = xshift >> 1;
        if (sram_wd8 & 0x80ul)
            sram_wd8 = (sram_wd8 << 1) + 1;
        else
            sram_wd8 = sram_wd8 << 1;
    }

    //Write loop 16
    xshift = 0x00000001ul << addr_size;
    sram_wd16 = 0xAAAAul;
    for (k = 0; k < addr_size; k++)
    {
        XMEM_p16 = (uint16_t*)(start_addr + xshift);
        *XMEM_p16 = sram_wd16;

        xshift = xshift >> 1;
        if (sram_wd16 & 0x8000ul)
            sram_wd16 = (sram_wd16 << 1) + 1;
        else
            sram_wd16 = sram_wd16 << 1;
    }

    //Read loop 16
    xshift = 0x00000001ul << addr_size;
    sram_wd16 = 0xAAAAul;
    for (k = 0; k < addr_size; k++)
    {
        XMEM_p16 = (uint16_t*)(start_addr + xshift);
        sram_rd16 = *XMEM_p16;
        if (sram_rd16 != sram_wd16)
        {
            retval++;
        }

        xshift = xshift >> 1;
        if (sram_wd16 & 0x8000ul)
            sram_wd16 = (sram_wd16 << 1) + 1;
        else
            sram_wd16 = sram_wd16 << 1;
    }

    //Write loop 32
    xshift = 0x00000001ul << addr_size;
    sram_wd32 = 0xAAAAAAAAul;
    for (k = 0; k < addr_size - 1; k++)
    {
        XMEM_p32 = (uint32_t*)(start_addr + xshift);
        *XMEM_p32 = sram_wd32;

        xshift = xshift >> 1;
        if (sram_wd32 & 0x80000000ul)
            sram_wd32 = (sram_wd32 << 1) + 1;
        else
            sram_wd32 = sram_wd32 << 1;
    }

    //Read loop 32
    xshift = 0x00000001ul << addr_size;
    sram_wd32 = 0xAAAAAAAAul;
    for (k = 0; k < addr_size - 1; k++)
    {
        XMEM_p32 = (uint32_t*)(start_addr + xshift);
        sram_rd32 = *XMEM_p32;
        if (sram_rd32 != sram_wd32)
        {
            retval++;
        }

        xshift = xshift >> 1;
        if (sram_wd32 & 0x80000000ul)
            sram_wd32 = (sram_wd32 << 1) + 1;
        else
            sram_wd32 = sram_wd32 << 1;
    }

    return retval;
}

#define LED1_ON GPIO_ResetBit( CM3DS_MPS2_GPIO0, GPIO_Pin_0)
#define LED2_ON GPIO_ResetBit( CM3DS_MPS2_GPIO0, GPIO_Pin_1)

#define LED1_OFF GPIO_SetBit( CM3DS_MPS2_GPIO0, GPIO_Pin_0)
#define LED2_OFF GPIO_SetBit( CM3DS_MPS2_GPIO0, GPIO_Pin_1)

enum rwWay {
    rw_8bit = 0,
    rw_16bit,
    rw_32bit,
    uart_test,
    uart_test2,
    rw_clock,
};

uint32_t ms_cnt = 0;

uint16_t rwWay = uart_test2;

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

SCD_REG_DECLEAR(_2);

int main(void)
{
    nvicInit();
    SysTick_Config(SystemCoreClock / 1000ul - 1ul);

    uart0_init();

    scd_init_1();
    scd_init_2();

    // if (mem_addr16b_test())
    // {
    //     while (1);
    // }

    uart_ahb_init();

    while (1)
    {
        if ((UART_GetFlagStatus(CM3DS_MPS2_UART0, 0x01)) == RESET)
        {
            UART_SendData(CM3DS_MPS2_UART0, scd_send1Byte(&scd_1));
        }

        // uart test
        switch (rwWay)
        {
        case uart_test2:
            while (AHB_UART->cmd.bit.TX_FIFO_FULL == 0)
            {
                AHB_UART->data = scd_send1Byte(&scd_2);
            }
            // DELAY_TICK(100 * 1000 * 100);

            while (AHB_UART->cmd.bit.RX_FIFO_EMPTY == 0)
            {
                SCD_Rev1Byte(&scd_2, AHB_UART->data);
            }
            break;

        case uart_test:
            if ((CM3DS_MPS2_GPIO0->DATA & 0x2) == 0)
            {
                while (AHB_UART->cmd.bit.TX_FIFO_FULL == 0)
                {
                    txdata++;
                    AHB_UART->data = txdata;
                }
                // DELAY_TICK(100 * 1000 * 100);

                while (AHB_UART->cmd.bit.RX_FIFO_EMPTY == 0)
                {
                    rxbuff[rxbuffptr++] = AHB_UART->data;
                }
            }
            break;

        default:
            // if ((CM3DS_MPS2_GPIO0->DATA & 0x2) == 0)
            {
                if (AHB_UART->cmd.bit.TX_FIFO_FULL == 0)
                {
                    AHB_UART->data = test1;
                }
                if (AHB_UART->cmd.bit.RX_FIFO_EMPTY == 0)
                {
                    rxdata = AHB_UART->data;
                }
                break;
            }
        }


        // uint8_t recvData = AHB_UART->data;
        // AHB_LED->seg6 = recvData & 0xfu;
        // AHB_LED->seg7 = recvData >> 4;
        // if (AHB_UART->cmd.bit.TX_FIFO_FULL)
        // {
        //     AHB_LED->seg6 |= 0x10u;
        // }
        // if (AHB_UART->cmd.bit.TX_FIFO_EMPTY)
        // {
        //     AHB_LED->seg7 |= 0x10u;
        // }

        // led seg test
        switch (rwWay)
        {
        case rw_8bit:
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

            AHB_LED->seg0 = test1;
            AHB_LED->seg1 = test1 >> 8;
            AHB_LED->seg2 = test2;
            AHB_LED->seg3 = test2 >> 8;
            AHB_LED->seg4 = test3;
            AHB_LED->seg5 = test3 >> 8;
            AHB_LED->seg6 = test4;
            AHB_LED->seg7 = test4 >> 8;
            break;

        case rw_16bit:
            test1r = *(volatile uint16_t*)(CM3DS_MPS2_TARGEXP1_BASE + 0);
            test2r = *(volatile uint16_t*)(CM3DS_MPS2_TARGEXP1_BASE + 2);
            test3r = *(volatile uint16_t*)(CM3DS_MPS2_TARGEXP1_BASE + 4);
            test4r = *(volatile uint16_t*)(CM3DS_MPS2_TARGEXP1_BASE + 6);

            *(volatile uint16_t*)(CM3DS_MPS2_TARGEXP1_BASE + 0) = test1;
            *(volatile uint16_t*)(CM3DS_MPS2_TARGEXP1_BASE + 2) = test2;
            *(volatile uint16_t*)(CM3DS_MPS2_TARGEXP1_BASE + 4) = test3;
            *(volatile uint16_t*)(CM3DS_MPS2_TARGEXP1_BASE + 6) = test4;
            break;

        case rw_32bit:
            test1r = *(volatile uint32_t*)(CM3DS_MPS2_TARGEXP1_BASE + 0);
            test2r = *(volatile uint32_t*)(CM3DS_MPS2_TARGEXP1_BASE + 0) >> 16;
            test3r = *(volatile uint32_t*)(CM3DS_MPS2_TARGEXP1_BASE + 4);
            test4r = *(volatile uint32_t*)(CM3DS_MPS2_TARGEXP1_BASE + 4) >> 16;

            *(volatile uint32_t*)(CM3DS_MPS2_TARGEXP1_BASE + 0) = (((uint32_t)test2) << 16) | test1;
            *(volatile uint32_t*)(CM3DS_MPS2_TARGEXP1_BASE + 4) = (((uint32_t)test4) << 16) | test3;
            break;

        case uart_test:
            AHB_LED->seg0 = (ms_cnt >> 0) & 0xful;
            AHB_LED->seg1 = (ms_cnt >> 4) & 0xful;
            AHB_LED->seg2 = (ms_cnt >> 8) & 0xful;
            AHB_LED->seg3 = (ms_cnt >> 12) & 0xful;
            AHB_LED->seg4 = (ms_cnt >> 16) & 0xful;
            AHB_LED->seg5 = (ms_cnt >> 20) & 0xful;
            break;

        default:
            AHB_LED->seg0 = (ms_cnt >> 0) & 0xful;
            AHB_LED->seg1 = (ms_cnt >> 4) & 0xful;
            AHB_LED->seg2 = (ms_cnt >> 8) & 0xful;
            AHB_LED->seg3 = (ms_cnt >> 12) & 0xful;
            AHB_LED->seg4 = (ms_cnt >> 16) & 0xful;
            AHB_LED->seg5 = (ms_cnt >> 20) & 0xful;
            AHB_LED->seg6 = (ms_cnt >> 24) & 0xful;
            AHB_LED->seg7 = (ms_cnt >> 28) & 0xful;
            break;
        }


        // LED1_ON;
        // delay_ms(50);
        // LED1_OFF;
        // DELAY_TICK(200 * 1000 * 50);
    }
}


