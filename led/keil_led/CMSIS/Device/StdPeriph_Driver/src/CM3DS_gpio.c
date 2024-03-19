
/*---------Include---------*/
#include "CM3DS_gpio.h"
#include "CM3DS_MPS2.h"

/**
  *
  * @brief: 将GPIO外设寄存器初始化为默认值。
  *
  * @param: CM3DS_MPS2_GPIOx，使用哪组GPIO;由于CM3只提供1组GPIO，因此该参数只能设为CM3DS_MPS2_GPIO0。
  *
  * @retVal: void
  */
void GPIO_DeInit(CM3DS_MPS2_GPIO_TypeDef* CM3DS_MPS2_GPIOx)
{
    /* Check the parameters */
    assert_param(IS_GPIO_ALL_PERIPH(CM3DS_MPS2_GPIOx));
    assert_param(IS_GET_GPIO_PIN(GPIO_Pin_x));

    if (CM3DS_MPS2_GPIOx == CM3DS_MPS2_GPIO0)
    {
        CM3DS_MPS2_GPIOx->ALTFUNCCLR = 0xffffffff;
    }
}

/**
  *
  * @brief: 将指定GPIO口设置为输入模式且读取输入电平。
  *
  * @param: CM3DS_MPS2_GPIOx，使用哪组GPIO;由于CM3只提供1组GPIO，因此该参数只能设为CM3DS_MPS2_GPIO0。
  * @param: GPIO_Pin_x，使用哪个GPIO;取值范围：GPIO_Pin_0~GPIO_Pin_31。
  *
  * @retVal: bitStatus，读取到的GPIO电平值;取值范围: 低电平-Bit_RESET(0)或高电平-Bit_SET(1)。
  */
uint8_t GPIO_ReadInputData(CM3DS_MPS2_GPIO_TypeDef* CM3DS_MPS2_GPIOx, uint16_t GPIO_Pin_x)
{
    uint8_t bitStatus = 0x00;
    uint32_t readValue = 0x00000000;

    /*Check the parameters*/
    assert_param(IS_GPIO_ALL_PERIPH(CM3DS_MPS2_GPIOx));
    assert_param(IS_GET_GPIO_PIN(GPIO_Pin_x));

    CM3DS_MPS2_GPIOx->OUTENABLECLR = (1 << GPIO_Pin_x);
    readValue = CM3DS_MPS2_GPIOx->DATA;

    if ((readValue & (Bit_SET << GPIO_Pin_x)) == 0)
    {
        bitStatus = (uint8_t)Bit_RESET;
    }
    else
    {
        bitStatus = (uint8_t)Bit_SET;
    }

    return bitStatus;
}

/**
  *
  * @brief: 设置指定GPIO口高电平输出。
  *
  * @param: CM3DS_MPS2_GPIOx，使用哪组GPIO;由于CM3只提供1组GPIO，因此该参数只能设为CM3DS_MPS2_GPIO0。
  * @param: GPIO_Pin_x，使用哪个GPIO;取值范围：GPIO_Pin_0~GPIO_Pin_31。
  *
  * @retVal: void
  */
void GPIO_SetBit(CM3DS_MPS2_GPIO_TypeDef* CM3DS_MPS2_GPIOx, uint16_t GPIO_Pin_x)
{
    uint32_t gpioDatamask = 0x00;

    /* Check the parameters */
    assert_param(IS_GPIO_ALL_PERIPH(CM3DS_MPS2_GPIOx));
    assert_param(IS_GET_GPIO_PIN(GPIO_Pin_x));

    /*set the output enable bit*/
    CM3DS_MPS2_GPIOx->OUTENABLESET = (1 << GPIO_Pin_x);
    CM3DS_MPS2_GPIOx->ALTFUNCCLR = (1 << GPIO_Pin_x);
    CM3DS_MPS2_GPIOx->INTENCLR = (1 << GPIO_Pin_x);

    if (CM3DS_MPS2_GPIOx == CM3DS_MPS2_GPIO0)
    {
        gpioDatamask = (1 << GPIO_Pin_x % 8);

        if (GPIO_Pin_x <= 7) {
            CM3DS_MPS2_GPIOx->BYTE0_MASKED[gpioDatamask] |= (1 << GPIO_Pin_x);
        }
        else if ((8 <= GPIO_Pin_x) && (GPIO_Pin_x <= 15)) {
            CM3DS_MPS2_GPIOx->BYTE1_MASKED[gpioDatamask] |= (1 << GPIO_Pin_x);
        }
        else if ((16 <= GPIO_Pin_x) && (GPIO_Pin_x <= 23)) {
            CM3DS_MPS2_GPIOx->BYTE2_MASKED[gpioDatamask] |= (1 << GPIO_Pin_x);
        }
        else if ((24 <= GPIO_Pin_x) && (GPIO_Pin_x <= 31)) {
            CM3DS_MPS2_GPIOx->BYTE3_MASKED[gpioDatamask] |= (1 << GPIO_Pin_x);
        }
    }
}

/**
  *
  * @brief: 设置指定GPIO口低电平输出。
  *
  * @param: CM3DS_MPS2_GPIOx，使用哪组GPIO;由于CM3只提供1组GPIO，因此该参数只能设为CM3DS_MPS2_GPIO0。
  * @param: GPIO_Pin_x，使用哪个GPIO;取值范围：GPIO_Pin_0~GPIO_Pin_31。
  *
  * @retVal: void
  */
void GPIO_ResetBit(CM3DS_MPS2_GPIO_TypeDef* CM3DS_MPS2_GPIOx, uint16_t GPIO_Pin_x)
{
    uint32_t gpioDatamask = 0x00;

    /* Check the parameters*/
    assert_param(IS_GPIO_ALL_PERIPH(CM3DS_MPS2_GPIOx));
    assert_param(IS_GET_GPIO_PIN(GPIO_Pin_x));

    /*set the output enable bit*/
    CM3DS_MPS2_GPIOx->OUTENABLESET = (1 << GPIO_Pin_x);
    CM3DS_MPS2_GPIOx->ALTFUNCCLR = (1 << GPIO_Pin_x);
    CM3DS_MPS2_GPIOx->INTENCLR = (1 << GPIO_Pin_x);

    if (CM3DS_MPS2_GPIOx == CM3DS_MPS2_GPIO0)
    {
        gpioDatamask = (1 << GPIO_Pin_x % 8);

        if (GPIO_Pin_x <= 7) {
            CM3DS_MPS2_GPIOx->BYTE0_MASKED[gpioDatamask] &= (~(1 << GPIO_Pin_x));
        }
        else if ((8 <= GPIO_Pin_x) && (GPIO_Pin_x <= 15)) {
            CM3DS_MPS2_GPIOx->BYTE1_MASKED[gpioDatamask] &= (~(1 << GPIO_Pin_x));
        }
        else if ((16 <= GPIO_Pin_x) && (GPIO_Pin_x <= 23)) {
            CM3DS_MPS2_GPIOx->BYTE2_MASKED[gpioDatamask] &= (~(1 << GPIO_Pin_x));
        }
        else if ((24 <= GPIO_Pin_x) && (GPIO_Pin_x <= 31)) {
            CM3DS_MPS2_GPIOx->BYTE3_MASKED[gpioDatamask] &= (~(1 << GPIO_Pin_x));
        }
    }
}

/**
  *
  * @brief: 设置指定GPIO口输出电平取反。
  *
  * @param: CM3DS_MPS2_GPIOx，使用哪组GPIO;由于CM3只提供1组GPIO，因此该参数只能设为CM3DS_MPS2_GPIO0。
  * @param: GPIO_Pin_x，使用哪个GPIO;取值范围：GPIO_Pin_0~GPIO_Pin_31。
  *
  * @retVal: void
  */
void GPIO_BitNotSet(CM3DS_MPS2_GPIO_TypeDef* CM3DS_MPS2_GPIOx, uint16_t GPIO_Pin_x)
{
    uint32_t gpioDatamask = 0x00;

    /* Check the parameters*/
    assert_param(IS_GPIO_ALL_PERIPH(CM3DS_MPS2_GPIOx));
    assert_param(IS_GET_GPIO_PIN(GPIO_Pin_x));

    /*set the output enable bit*/
    CM3DS_MPS2_GPIOx->OUTENABLESET = (1 << GPIO_Pin_x);
    CM3DS_MPS2_GPIOx->ALTFUNCCLR = (1 << GPIO_Pin_x);
    CM3DS_MPS2_GPIOx->INTENCLR = (1 << GPIO_Pin_x);

    if (CM3DS_MPS2_GPIOx == CM3DS_MPS2_GPIO0)
    {
        gpioDatamask = (1 << GPIO_Pin_x % 8);

        if (GPIO_Pin_x <= 7) {
            CM3DS_MPS2_GPIOx->BYTE0_MASKED[gpioDatamask] ^= (1 << GPIO_Pin_x);
        }
        else if ((8 <= GPIO_Pin_x) && (GPIO_Pin_x <= 15)) {
            CM3DS_MPS2_GPIOx->BYTE1_MASKED[gpioDatamask] ^= (1 << GPIO_Pin_x);
        }
        else if ((16 <= GPIO_Pin_x) && (GPIO_Pin_x <= 23)) {
            CM3DS_MPS2_GPIOx->BYTE2_MASKED[gpioDatamask] ^= (1 << GPIO_Pin_x);
        }
        else if ((24 <= GPIO_Pin_x) && (GPIO_Pin_x <= 31)) {
            CM3DS_MPS2_GPIOx->BYTE3_MASKED[gpioDatamask] ^= (1 << GPIO_Pin_x);
        }
    }
}

/**
  *
  * @brief: 设置指定GPIO口输出高电平或低电平。
  *
  * @param: CM3DS_MPS2_GPIOx，使用哪组GPIO;由于CM3只提供1组GPIO，因此该参数只能设为CM3DS_MPS2_GPIO0。
  * @param: GPIO_Pin_x，使用哪个GPIO;取值范围：GPIO_Pin_0~GPIO_Pin_31。
  * @param: BitVal，高电平(Bit_SET)或低电平(Bit_RESET);取值范围：Bit_SET(1)或Bit_RESET(0)。
  *
  * @retVal: void
  */
void GPIO_WriteBit(CM3DS_MPS2_GPIO_TypeDef* CM3DS_MPS2_GPIOx, uint16_t GPIO_Pin_x, BitAction BitVal)
{
    /*Check the parameters*/
    assert_param(IS_GPIO_ALL_PERIPH(CM3DS_MPS2_GPIOx));
    assert_param(IS_GET_GPIO_PIN(GPIO_Pin_x));
    assert_param(IS_GPIO_BIT_ACTION(BitVal));

    /*set the output enable bit*/
    CM3DS_MPS2_GPIOx->OUTENABLESET = (1 << GPIO_Pin_x);
    CM3DS_MPS2_GPIOx->ALTFUNCCLR = (1 << GPIO_Pin_x);
    CM3DS_MPS2_GPIOx->INTENCLR = (1 << GPIO_Pin_x);

    if (BitVal != Bit_RESET)
    {
        CM3DS_MPS2_GPIOx->DATA |= (Bit_SET << GPIO_Pin_x);
    }
    else
    {
        CM3DS_MPS2_GPIOx->DATA &= (~(Bit_SET << GPIO_Pin_x));
    }
}

/**
  *
  * @brief: 设置GPIO的复用功能，如UART、ADC、Timer、I2C、SPI等。
  *
  * @param: CM3DS_MPS2_GPIOx，使用哪组GPIO;由于CM3只提供1组GPIO，因此该参数只能设为CM3DS_MPS2_GPIO0。
  * @param: GPIO_Remap，选择对哪个GPIO口进行复用，取值参考GPIO_Remap_define。
  * @param: NewState，是否使能复用，ENABLE：使能复用，DISABLE:不使能复用；取值范围：ENABLE或DISABLE。
  *
  * @retVal: void
  */
void GPIO_PinRemapConfig(CM3DS_MPS2_GPIO_TypeDef* CM3DS_MPS2_GPIOx, uint32_t  GPIO_Remap, FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_GPIO_ALL_PERIPH(CM3DS_MPS2_GPIOx));
    assert_param(IS_GPIO_REMAP(GPIO_Remap));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    /*configure the pin function*/
    if (NewState != DISABLE)
    {
        CM3DS_MPS2_GPIOx->ALTFUNCSET = GPIO_Remap;
    }
    else
    {
        CM3DS_MPS2_GPIOx->ALTFUNCCLR = GPIO_Remap;
    }
}

/**
  *
  * @brief: 设置指定GPIO的中断触发方式。
  *
  * @param: CM3DS_MPS2_GPIOx，使用哪组GPIO;由于CM3只提供1组GPIO，因此该参数只能设为CM3DS_MPS2_GPIO0。
  * @param: GPIO_Pin_x，使用哪个GPIO;取值范围：GPIO_Pin_0~GPIO_Pin_31。
  * @param: INTTYPE，中断触发方式;
  *					取值范围：Bit_LOWLEVEL - 低电平触发；Bit_HIGHLEVEL - 高电平触发；
  *							  Bit_FALLINGEDGE - 下降沿触发；Bit_RISINGEDGE - 上升沿触发。
  * @param: NewState，是否使能中断，Interrupt_ENABLE：使能，Interrupt_DISABLE:不使能；
  *						取值范围：Interrupt_ENABLE或Interrupt_DISABLE。
  *
  * @retVal: void
  */
void GPIO_PinInterruptTypeConfig(CM3DS_MPS2_GPIO_TypeDef* CM3DS_MPS2_GPIOx, uint16_t GPIO_Pin_x,
    BitInterruptType INTTYPE, InterruptState NewState)
{
    /*Check the parameters*/
    assert_param(IS_GPIO_ALL_PERIPH(CM3DS_MPS2_GPIOx));
    assert_param(IS_GET_GPIO_PIN(GPIO_Pin_x));
    assert_param(IS_GPIO_BIT_INTTYPE(INTTYPE));
    assert_param(IS_INTERRUPT_STATE(NewState));

    /*configure the pin interrupt Type*/
    if (NewState != Interrupt_DISABLE)
    {
        CM3DS_MPS2_GPIOx->INTENSET = (Interrupt_ENABLE << GPIO_Pin_x);
        switch (INTTYPE)
        {
        case  Bit_LOWLEVEL:
            CM3DS_MPS2_GPIOx->INTTYPECLR = (Interrupt_ENABLE << GPIO_Pin_x);
            CM3DS_MPS2_GPIOx->INTPOLCLR = (Interrupt_ENABLE << GPIO_Pin_x);
            break;
        case  Bit_HIGHLEVEL:
            CM3DS_MPS2_GPIOx->INTTYPECLR = (Interrupt_ENABLE << GPIO_Pin_x);
            CM3DS_MPS2_GPIOx->INTPOLSET = (Interrupt_ENABLE << GPIO_Pin_x);
            break;
        case  Bit_FALLINGEDGE:
            CM3DS_MPS2_GPIOx->INTTYPESET = (Interrupt_ENABLE << GPIO_Pin_x);
            CM3DS_MPS2_GPIOx->INTPOLCLR = (Interrupt_ENABLE << GPIO_Pin_x);
            break;
        case  Bit_RISINGEDGE:
            CM3DS_MPS2_GPIOx->INTTYPESET = (Interrupt_ENABLE << GPIO_Pin_x);
            CM3DS_MPS2_GPIOx->INTPOLSET = (Interrupt_ENABLE << GPIO_Pin_x);
            break;
        }
    }
    else
    {
        CM3DS_MPS2_GPIOx->INTENCLR = (Interrupt_ENABLE << GPIO_Pin_x);
    }
}

