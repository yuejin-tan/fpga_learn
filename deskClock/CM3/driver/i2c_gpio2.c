#include "i2c_gpio2.h"

#include "CM3DS_MPS2.h"
#include "CM3DS_gpio.h"
#include "CM3DS_timer.h"

static inline void tyj_i2c_sda_1()
{
    CM3DS_MPS2_GPIO0->OUTENABLECLR = (1ul << GPIO_Pin_21);
}

static inline void tyj_i2c_sda_0()
{
    CM3DS_MPS2_GPIO0->OUTENABLESET = (1ul << GPIO_Pin_21);
}

static inline void tyj_i2c_scl_1()
{
    CM3DS_MPS2_GPIO0->OUTENABLECLR = (1ul << GPIO_Pin_20);
}

static inline void tyj_i2c_scl_0()
{
    CM3DS_MPS2_GPIO0->OUTENABLESET = (1ul << GPIO_Pin_20);
}

static inline uint16_t tyj_i2c_scl_read()
{
    if (CM3DS_MPS2_GPIO0->DATA & (1ul << GPIO_Pin_20))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

static inline uint16_t tyj_i2c_sda_read()
{
    if (CM3DS_MPS2_GPIO0->DATA & (1ul << GPIO_Pin_21))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

static void hfUnitDelay2()
{
    CM3DS_MPS2_TIMER1->CTRL = 0;
    CM3DS_MPS2_TIMER1->VALUE = CM3DS_MPS2_TIMER1->RELOAD;
    CM3DS_MPS2_TIMER1->INTCLEAR = 1;
    CM3DS_MPS2_TIMER1->CTRL = 9;
    while (CM3DS_MPS2_TIMER1->INTSTATUS == 0)
    {
        continue;
    }
    CM3DS_MPS2_TIMER1->CTRL = 0;
    CM3DS_MPS2_TIMER1->INTCLEAR = 1;
}

void swi2c_init2()
{
    CM3DS_MPS2_GPIO0->OUTENABLECLR = (1ul << GPIO_Pin_20);
    CM3DS_MPS2_GPIO0->OUTENABLECLR = (1ul << GPIO_Pin_21);

    CM3DS_MPS2_GPIO0->DATAOUT &= ~(1ul << GPIO_Pin_20);
    CM3DS_MPS2_GPIO0->DATAOUT &= ~(1ul << GPIO_Pin_21);

    // 不可以共用定时器
    CM3DS_MPS2_TIMER1->CTRL = 0;
    CM3DS_MPS2_TIMER1->RELOAD = SystemCoreClock / 100000 / 2;
    CM3DS_MPS2_TIMER1->VALUE = CM3DS_MPS2_TIMER1->RELOAD;
    CM3DS_MPS2_TIMER1->INTCLEAR = 1;
}

int16_t start_i2c2()
{
    tyj_i2c_scl_0();
    hfUnitDelay2();
    tyj_i2c_sda_1();
    hfUnitDelay2();
    tyj_i2c_scl_1();
    hfUnitDelay2();
    if (tyj_i2c_scl_read() == 0)
    {
        return -__LINE__;
    }
    if (tyj_i2c_sda_read() == 0)
    {
        return -__LINE__;
    }
    tyj_i2c_sda_0();
    hfUnitDelay2();
    tyj_i2c_scl_0();
    hfUnitDelay2();
    return 0;
}

int16_t write_i2c2(uint16_t data)
{
    for (int ii = 7; ii >= 0; ii--)
    {
        int bitTmp = (data & (1ul << ii)) ? 1 : 0;
        if (bitTmp)
        {
            tyj_i2c_sda_1();
        }
        else
        {
            tyj_i2c_sda_0();
        }
        hfUnitDelay2();
        tyj_i2c_scl_1();
        hfUnitDelay2();
        if (tyj_i2c_scl_read() == 0)
        {
            return -__LINE__;
        }
        int bitCheckRead = tyj_i2c_sda_read();
        if (bitTmp != bitCheckRead)
        {
            return -__LINE__;
        }
        tyj_i2c_scl_0();
        hfUnitDelay2();
    }
    tyj_i2c_sda_1();
    hfUnitDelay2();
    tyj_i2c_scl_1();
    hfUnitDelay2();
    uint16_t ret = tyj_i2c_sda_read();
    tyj_i2c_scl_0();
    hfUnitDelay2();
    return (int16_t)ret;
}

int16_t read_i2c2(uint16_t ack)
{
    uint16_t ret = 0;
    tyj_i2c_sda_1();
    for (int ii = 7; ii >= 0; ii--)
    {
        hfUnitDelay2();
        tyj_i2c_scl_1();
        hfUnitDelay2();
        if (tyj_i2c_scl_read() == 0)
        {
            return -__LINE__;
        }
        ret = (uint16_t)(ret << 1) | tyj_i2c_sda_read();
        tyj_i2c_scl_0();
        hfUnitDelay2();
    }
    if (ack)
    {
        tyj_i2c_sda_1();
    }
    else
    {
        tyj_i2c_sda_0();
    }
    hfUnitDelay2();
    tyj_i2c_scl_1();
    hfUnitDelay2();
    if (tyj_i2c_sda_read() != ack)
    {
        return -__LINE__;
    }
    tyj_i2c_scl_0();
    hfUnitDelay2();
    return (int16_t)ret;
}

int16_t stop_i2c2()
{
    tyj_i2c_sda_0();
    hfUnitDelay2();
    tyj_i2c_scl_1();
    hfUnitDelay2();
    tyj_i2c_sda_1();
    hfUnitDelay2();
    if (tyj_i2c_scl_read() == 0)
    {
        return -__LINE__;
    }
    if (tyj_i2c_sda_read() == 0)
    {
        return -__LINE__;
    }
    return 0;
}
