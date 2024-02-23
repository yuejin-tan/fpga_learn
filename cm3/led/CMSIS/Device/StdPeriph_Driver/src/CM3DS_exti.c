#include "CM3DS_exti.h"
#include "CM3DS_MPS2.h"
#include "CM3DS_gpio.h"
#include "CM3DS_rcc.h"

/**
  *
  * @brief: 将EXTI相关寄存器初始化为默认值。
  *
  * @param: CM3DS_MPS2_GPIOx，使用哪组GPIO;由于CM3只提供1组GPIO，因此该参数只能设为CM3DS_MPS2_GPIO0。
  *
  * @retVal: void
  */
void EXTI_DeInit(CM3DS_MPS2_GPIO_TypeDef* CM3DS_MPS2_GPIOx)
{
  CM3DS_MPS2_GPIOx->INTENSET = 0x00000000;	//interrupt set
  CM3DS_MPS2_GPIOx->INTENCLR = 0x00000000;	//set clear
  CM3DS_MPS2_GPIOx->INTTYPESET = 0x00000000;	//interrupt type set
  CM3DS_MPS2_GPIOx->INTTYPECLR = 0x00000000;	//type set
  CM3DS_MPS2_GPIOx->INTPOLSET = 0x00000000;	//interrupt POL set(IRQ)
  CM3DS_MPS2_GPIOx->INTPOLCLR = 0x00000000;	//POL clear
  //CM3DS_MPS2_GPIOx->INTSTATUS = 0x00000000;	//only read (IRQ)
  CM3DS_MPS2_GPIOx->INTCLEAR = 0x00000000;	//only write ,clear interrupt request
}

/**
  *
  * @brief: 将对应的GPIO管脚的EXTI中断使能。
  *
  * @param: CM3DS_MPS2_GPIOx，使用哪组GPIO;由于CM3只提供1组GPIO，因此该参数只能设为CM3DS_MPS2_GPIO0。
  * @param: GPIO_Pin_x，使用哪个GPIO;取值范围：GPIO_Pin_0~GPIO_Pin_31。
  *
  * @retVal: void
  */
void EXTI_GenerateInterrupt(CM3DS_MPS2_GPIO_TypeDef* CM3DS_MPS2_GPIOx, uint16_t GPIO_Pin_x)
{
  /* Check the parameters*/
  assert_param(IS_GET_GPIO_PIN(GPIO_Pin_x));
  /*configure the pin function*/
  CM3DS_MPS2_GPIOx->INTENSET |= (1 << GPIO_Pin_x);

}

/**
  *
  * @brief: 清除对应的GPIO管脚的EXTI中断。
  *
  * @param: CM3DS_MPS2_GPIOx，使用哪组GPIO;由于CM3只提供1组GPIO，因此该参数只能设为CM3DS_MPS2_GPIO0。
  * @param: GPIO_Pin_x，使用哪个GPIO;取值范围：GPIO_Pin_0~GPIO_Pin_31。
  *
  * @retVal: void
  */
void EXTI_ClearFlag(CM3DS_MPS2_GPIO_TypeDef* CM3DS_MPS2_GPIOx, uint16_t GPIO_Pin_x)
{
  /* Check the parameters*/
  assert_param(IS_GET_GPIO_PIN(GPIO_Pin_x));
  /*configure the pin function*/
  CM3DS_MPS2_GPIOx->INTCLEAR |= (1 << GPIO_Pin_x);
}

/**
  *
  * @brief: 清除对应的GPIO管脚的EXTI中断。
  *
  * @param: CM3DS_MPS2_GPIOx，使用哪组GPIO;由于CM3只提供1组GPIO，因此该参数只能设为CM3DS_MPS2_GPIO0。
  * @param: GPIO_Pin_x，使用哪个GPIO;取值范围：GPIO_Pin_0~GPIO_Pin_31。
  *
  * @retVal: void
  */
void EXTI_ClearITPendingBit(CM3DS_MPS2_GPIO_TypeDef* CM3DS_MPS2_GPIOx, uint16_t GPIO_Pin_x)
{
  /* Check the parameters*/
  assert_param(IS_GET_GPIO_PIN(GPIO_Pin_x));
  /*configure the pin function*/
  CM3DS_MPS2_GPIOx->INTCLEAR |= (1 << GPIO_Pin_x);
}

/**
  *
  * @brief: 清除对应的GPIO管脚的EXTI中断，并返回中断状态。
  *
  * @param: CM3DS_MPS2_GPIOx，使用哪组GPIO;由于CM3只提供1组GPIO，因此该参数只能设为CM3DS_MPS2_GPIO0。
  * @param: Num, 使用哪个GPIO;取值范围：GPIO_Pin_0~GPIO_Pin_31。
  *
  * @retVal: 返回中断状态寄存器值。
  */
uint32_t CM3DS_MPS2_gpio_IntClear(CM3DS_MPS2_GPIO_TypeDef* CM3DS_MPS2_GPIO, uint32_t Num)
{
  CM3DS_MPS2_GPIO->INTCLEAR = (1 << Num);
  return CM3DS_MPS2_GPIO->INTSTATUS;
}

