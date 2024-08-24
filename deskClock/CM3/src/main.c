#include "string.h"
#include "stdio.h"

#include "CM3DS_gpio.h"
#include "CM3DS_rcc.h"
#include "CM3DS_misc.h"
#include "CM3DS_uart.h"

#include "delay.h"
#include "ahb_ledseg.h"
#include "ahb_uart.h"
#include "ahb_epwm.h"

#include "scd_inc.h"
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"


#include "lcd_9488_drv.h"
#include "touch_GT911_drv.h"
#include "thp_bme280_drv.h"
#include "i2c_gpio2.h"

uint32_t ms_cnt = 0;

uint16_t rwWay = 0;

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

float pwmD = 0.5f;
float temp = 0;
float hum = 0;
float press = 0;

TaskHandle_t TouchRefreshTask;
TaskHandle_t BME280RefreshTask;
TaskHandle_t LedRefreshTask;

SemaphoreHandle_t MuxSemLcd;

void nvicInit(void)
{
    NVIC_SetPriorityGrouping(NVIC_PriorityGroup_2);

    // UART
    NVIC_InitTypeDef InitTypeDef_NVIC;
    InitTypeDef_NVIC.NVIC_IRQChannel = UART0_IRQn;
    InitTypeDef_NVIC.NVIC_IRQChannelPreemptionPriority = 1;
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

void epwm_ahb_init()
{
    AHB_EPWM->mode = 0;
    AHB_EPWM->TBPRD_shadow = (SystemCoreClock / (20000ul * 2ul)) - 1;
    AHB_EPWM->CMPA_shadow = AHB_EPWM->TBPRD_shadow / 2;
    AHB_EPWM->CMPB_shadow = AHB_EPWM->CMPA_shadow;
    AHB_EPWM->CMPC_shadow = AHB_EPWM->CMPB_shadow;
    AHB_EPWM->mode = 1;
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
    swi2c_init2();
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

void touchRefreshTask(void* pvParameters)
{
    while (1)
    {
        if (GT911_Scan(&touchInfo1) == 0)
        {
            if (touchInfo1.nums > 0)
            {
                int x_true = LCD_W - touchInfo1.touchPointInfos[0].y;
                int y_true = touchInfo1.touchPointInfos[1].x;

                pwmD = x_true / ((float)LCD_W);

                if (pwmD > 0.9f)
                {
                    pwmD = 1.0f;
                }
                else if (pwmD < 0.1f)
                {
                    pwmD = 0;
                }
                else
                {
                    pwmD = (pwmD - 0.1f) * 1.25f;
                }

                if (xSemaphoreTake(MuxSemLcd, portMAX_DELAY))
                {
                    LCD_fill(0, 0, x_true, 79, ORANGE);
                    LCD_fill(x_true, 0, LCD_W - 1, 79, DARKORANGE);

                    xSemaphoreGive(MuxSemLcd);
                }
                else
                {
                    printf("MuxSemLcd take err!\r\n");
                }

                AHB_EPWM->CMPA_shadow = AHB_EPWM->TBPRD_shadow * pwmD;
            }
        }

        vTaskDelay(10 / portTICK_PERIOD_MS);
    }
}

void bme280RefreshTask(void* pvParameters)
{
    while (1)
    {
        //读取温度、湿度、压力
        char buff[16];
        if (BME280_Get_ALL(&BME280_1, &temp, &hum, &press))
        {
            printf("bme280 read err!\r\n");
        }
        else if (xSemaphoreTake(MuxSemLcd, portMAX_DELAY))
        {

            POINT_COLOR = RED;
            BACK_COLOR = DARKRED;
            sprintf(buff, "%0.2f", temp);
            LCD_ShowString(32, 16, 48, 16, buff, 0x51);
            printf("Temp=%sC, ", buff);

            POINT_COLOR = GREEN;
            BACK_COLOR = DARKGREEN;
            sprintf(buff, "%6d", (int)(press + 0.5f));
            LCD_ShowString(28, 32, 48, 16, buff, 0x51);
            printf("Press=%sPa, ", buff);

            POINT_COLOR = BLUE;
            BACK_COLOR = DARKBLUE;
            sprintf(buff, "%0.2f", hum);
            LCD_ShowString(32, 48, 48, 16, buff, 0x51);
            printf("Hum=%s%%RH\r\n", buff);

            xSemaphoreGive(MuxSemLcd);
        }
        else
        {
            printf("MuxSemLcd take err!\r\n");
        }

        vTaskDelay(500 / portTICK_PERIOD_MS);
    }
}

void ledRefreshTask(void* pvParameters)
{
    int isRun = 1;
    uint32_t cnt0 = 0;
    uint16_t btnRaw = 0xffffu;
    int btnSta = 1;

    while (1)
    {
        while (AHB_UART->cmd.bit.TX_FIFO_FULL == 0)
        {
            AHB_UART->data = scd_send1Byte(&scd_1);
        }
        while (AHB_UART->cmd.bit.RX_FIFO_EMPTY == 0)
        {
            SCD_Rev1Byte(&scd_1, AHB_UART->data);
        }

        {
            uint32_t cntRaw = xTaskGetTickCount() * portTICK_PERIOD_MS;

            // gpio4 clear
            if (GPIO_ReadInputData(CM3DS_MPS2_GPIO0, GPIO_Pin_4) == 0)
            {
                cnt0 = cntRaw;
            }

            // gpio5 stop
            btnRaw = (btnRaw << 1) | GPIO_ReadInputData(CM3DS_MPS2_GPIO0, GPIO_Pin_5);
            if (btnRaw == 0)
            {
                if (btnSta == 1)
                {
                    isRun = !isRun;
                }

                btnSta = 0;
            }
            else if (btnRaw == 0xffffu)
            {
                btnSta = 1;
            }

            if (isRun)
            {
                ms_cnt = cntRaw - cnt0;
            }

            // 毫秒计时
            // ms
            AHB_LED->seg0 = ms_cnt % 10;
            AHB_LED->seg1 = (ms_cnt / 10) % 10;
            AHB_LED->seg2 = (ms_cnt / 100) % 10;

            // s
            AHB_LED->seg3 = ((ms_cnt / 1000) % 10) | 0x10;
            AHB_LED->seg4 = ((ms_cnt / 10000) % 6);

            // min
            AHB_LED->seg5 = ((ms_cnt / 60000) % 10) | 0x10;
            AHB_LED->seg6 = ((ms_cnt / 600000) % 6);

            // h
            AHB_LED->seg7 = ((ms_cnt / 3600000) % 10) | 0x10;
        }

        {
            // 呼吸灯
            int tbprd = AHB_EPWM->TBPRD_shadow;
            AHB_EPWM->CMPB_shadow = abs((ms_cnt % (2 * tbprd)) - tbprd);
        }

        vTaskDelay(1 / portTICK_PERIOD_MS);
    }
}

void img_init(void)
{
    LCD_fill(0, 0, LCD_W / 2, 79, ORANGE);
    LCD_fill(LCD_W / 2, 0, LCD_W - 1, 79, DARKORANGE);
    POINT_COLOR = WHITE;

    LCD_fill(0, 80, LCD_W - 1, 160 - 1, DARKRED);
    LCD_ShowString(0, 16, 32, 16, "TMP", 0x50);
    LCD_ShowString(80, 16, 32, 16, "C", 0x50);

    LCD_fill(0, 160, LCD_W - 1, 240 - 1, DARKGREEN);
    LCD_ShowString(0, 32, 32, 16, "PRE", 0x50);
    LCD_ShowString(80, 32, 32, 16, "Pa", 0x50);

    LCD_fill(0, 240, LCD_W - 1, LCD_H - 1, DARKBLUE);
    LCD_ShowString(0, 48, 32, 16, "R.H", 0x50);
    LCD_ShowString(80, 48, 32, 16, "%", 0x50);
}

int main(void)
{
    GPIO_DeInit(CM3DS_MPS2_GPIO0);
    nvicInit();

    // 由freertos管理
    // SysTick_Config(SystemCoreClock / 1000ul - 1ul);

    uart0_init();

    printf("SA5Z30 CM3+FPGA TEST\r\n");

    volatile int ret;
    if (ret = mem_addr16b_test())
    {
        while (1);
    }

    uart_ahb_init();
    epwm_ahb_init();
    scd_init_1();

    LCD_Init();
    img_init();
    GT911_init();
    BME280_Init();

    xTaskCreate((TaskFunction_t)touchRefreshTask, /* 任务函数 */
        (const char*)"touchRefresh", /* 任务名称 */
        (uint16_t)128, /* 任务堆栈大小 */
        (void*)NULL, /* 传入给任务函数的参数 */
        (UBaseType_t)2, /* 任务优先级 */
        (TaskHandle_t*)&TouchRefreshTask); /* 任务句柄 */

    xTaskCreate((TaskFunction_t)bme280RefreshTask, /* 任务函数 */
        (const char*)"BME280Refresh", /* 任务名称 */
        (uint16_t)128, /* 任务堆栈大小 */
        (void*)NULL, /* 传入给任务函数的参数 */
        (UBaseType_t)5, /* 任务优先级 */
        (TaskHandle_t*)&BME280RefreshTask); /* 任务句柄 */

    xTaskCreate((TaskFunction_t)ledRefreshTask, /* 任务函数 */
        (const char*)"ledRefreshTask", /* 任务名称 */
        (uint16_t)128, /* 任务堆栈大小 */
        (void*)NULL, /* 传入给任务函数的参数 */
        (UBaseType_t)1, /* 任务优先级 */
        (TaskHandle_t*)&LedRefreshTask); /* 任务句柄 */

    MuxSemLcd = xSemaphoreCreateMutex();

    vTaskStartScheduler();

    while (1)
    {
        // never reach here
        continue;
    }
}

