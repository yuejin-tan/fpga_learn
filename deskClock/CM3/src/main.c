#include "string.h"
#include "stdio.h"

#include "CM3DS_gpio.h"
#include "CM3DS_rcc.h"
#include "CM3DS_misc.h"
#include "CM3DS_uart.h"

#include "delay.h"
#include "ahb_ledseg.h"
#include "ahb_uart.h"

#include "scd_inc.h"

#include "lcd_9488_drv.h"
#include "touch_GT911_drv.h"
#include "thp_bme280_drv.h"

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
    // UART_ITConfig(CM3DS_MPS2_UART0, UART_RxInterrupt, ENABLE);
    // NVIC_EnableIRQ(UART0_IRQn);
}

void uart_ahb_init()
{
    AHB_UART->cmd.all = 0;
    AHB_UART->buad_div_2 = (SystemCoreClock / (460800ul * 2ul)) - 1;
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

    memset((void*)CM3DS_MPS2_TARGEXP0_BASE, 0, 1024ul * 1024ul);

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

static GT911info_struct touchInfo1;

Sensor_BME280 BME280_1;

void BME280_Init(void)
{
    /****结构体初始化****/
    //设备参数
    BME280_1.IIC_ADDR = 0xEC;
    BME280_1.BME280_Mode = BME280_Mode_Normal;
    BME280_1.BME280_Tstandby = BME280_Tstandby_0_5;
    BME280_1.BME280_IIR_Time = BME280_Filter_OFF;
    //温度参数
    BME280_1.TEMP_overSamp = BME280_Over_16;
    //湿度参数
    BME280_1.HUM_overSamp = BME280_Over_16;
    //压力参数
    BME280_1.PRESS_overSamp = BME280_Over_16;

    /****初始化程序****/
    //复位设备
    if (BME280_Reset(&BME280_1) != BME280_OK)
    {
        printf("init err@l%d\r\n", __LINE__);
        return;
    }

    //读取ID
    uint8_t ID = { 0 };
    if (BME280_ID(&BME280_1, &ID))
    {
        printf("init err@l%d\r\n", __LINE__);
        return;
    }
    printf("BME280 ID:%x\r\n", ID);

    //读取补偿值
    if (BME280_Get_DIG(&BME280_1))
    {
        printf("init err@l%d\r\n", __LINE__);
        return;
    }

    //上传配置
    if (BME280_Configuration(&BME280_1))
    {
        printf("init err@l%d\r\n", __LINE__);
        return;
    }
    delay_ms(10);

    return;
}

int main(void)
{
    GPIO_DeInit(CM3DS_MPS2_GPIO0);
    nvicInit();
    SysTick_Config(SystemCoreClock / 1000ul - 1ul);

    uart0_init();

    printf("SA5Z30 CM3+FPGA TEST\r\n");

    uart_ahb_init();
    scd_init_1();

    LCD_Init();
    GT911_init();

    LCD_Draw_Circle(100, 100, 20);
    LCD_Draw_Circle(200, 100, 20);
    LCD_Draw_Circle(100, 200, 20);

    volatile int ret;
    if (ret = mem_addr16b_test())
    {
        while (1);
    }

    BME280_Init();

    CM3DS_MPS2_TIMER1->CTRL = 0;
    CM3DS_MPS2_TIMER1->VALUE = 0;
    CM3DS_MPS2_TIMER1->RELOAD = SystemCoreClock / 10;
    CM3DS_MPS2_TIMER1->INTCLEAR = 1;
    CM3DS_MPS2_TIMER1->CTRL = 9;

    while (1)
    {
        while (CM3DS_MPS2_TIMER1->INTSTATUS == 0)
        {
            while (AHB_UART->cmd.bit.TX_FIFO_FULL == 0)
            {
                AHB_UART->data = scd_send1Byte(&scd_1);
            }
            while (AHB_UART->cmd.bit.RX_FIFO_EMPTY == 0)
            {
                SCD_Rev1Byte(&scd_1, AHB_UART->data);
            }

            AHB_LED->seg0 = (ms_cnt >> 0) & 0xful;
            AHB_LED->seg1 = (ms_cnt >> 4) & 0xful;
            AHB_LED->seg2 = (ms_cnt >> 8) & 0xful;
            AHB_LED->seg3 = (ms_cnt >> 12) & 0xful;
            AHB_LED->seg4 = (ms_cnt >> 16) & 0xful;
            AHB_LED->seg5 = (ms_cnt >> 20) & 0xful;
            AHB_LED->seg6 = (ms_cnt >> 24) & 0xful;
            AHB_LED->seg7 = (ms_cnt >> 28) & 0xful;
        }

        CM3DS_MPS2_TIMER1->INTCLEAR = 1;
        // 100ms tick area
        if (GT911_Scan(&touchInfo1) == 0)
        {
            if (touchInfo1.nums == 2)
            {
                LCD_DrawLine(touchInfo1.touchPointInfos[0].x, touchInfo1.touchPointInfos[0].y,
                    touchInfo1.touchPointInfos[1].x, touchInfo1.touchPointInfos[1].y);
            }
            else
            {
                LCD_DrawPoint_color(touchInfo1.touchPointInfos[0].x, touchInfo1.touchPointInfos[0].y, RED);
            }
        }

        //读取温度、湿度、压力
        float DATA1[3] = { 0 };
        if (BME280_Get_ALL(&BME280_1, &DATA1[0], &DATA1[1], &DATA1[2]))
        {
            printf("bme280 read err!\r\n");
        }
        else
        {
            printf("Temp=");
            printf("%0.2fC, ", DATA1[0]);
            printf("Hum=");
            printf("%0.2f%%RH, ", DATA1[1]);
            printf("Press=");
            printf("%dPa\r\n", (int)(DATA1[2]));
        }
    }
}


