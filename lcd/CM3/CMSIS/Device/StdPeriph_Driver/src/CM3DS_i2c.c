#include "CM3DS_i2c.h"
#include "CM3DS_rcc.h"
#include "CM3DS_gpio.h"
#include "CM3DS_MPS2.h"

/**
  *
  * @brief: 将I2C初始化为默认配置。
  *
  * @param: CM3DS_MPS2_I2Cx,设置为CM3DS_MPS2_I2C。
  *
  * @retVal: void
  */
void I2C_DeInit(CM3DS_MPS2_I2C_TypeDef* CM3DS_MPS2_I2Cx)
{
  /*Check the parameters*/
  assert_param(IS_I2C_ALL_PERIPH(CM3DS_MPS2_I2Cx));

  if (CM3DS_MPS2_I2Cx == CM3DS_MPS2_I2C)
  {
    /* reset I2C1 reset state */
    RCC_APB1PeriphResetCmd(RCC_APB1Periph_I2C, ENABLE);

    /* Release I2C1 from reset state */
    RCC_APB1PeriphResetCmd(RCC_APB1Periph_I2C, DISABLE);
  }
}

/**
  *
  * @brief: I2C初始化配置。
  *
  * @param: CM3DS_MPS2_I2Cx,设置为CM3DS_MPS2_I2C。
  * @param: Mode,I2C模式；I2C_Mode_Master - I2C主模式; I2C_Mode_Slave - I2C从模式;
  * @param: Speed,I2C工作时钟速率模式；
  *					可设置的值:
  *						I2C_Speed_Standard - 标准速率模式；
  *						I2C_Speed_Fast - 快速速率模式；
  *						I2C_Speed_High - 高速速率模式。
  *	@param: OwnAddress,主机地址。
  *
  * @retVal: void
  */
void I2C_Init(CM3DS_MPS2_I2C_TypeDef* CM3DS_MPS2_I2Cx, uint16_t Mode, uint32_t Speed, uint32_t OwnAddress)
{
  /* Check the parameters */
  assert_param(IS_I2C_ALL_PERIPH(CM3DS_MPS2_I2Cx));
  assert_param(IS_I2C_ClockSpeed_STATE(Speed));
  CM3DS_MPS2_I2Cx->CONTROL = 0x80000000;
  CM3DS_MPS2_I2Cx->CONTROL = 0x00000000;
  /*---------------------------- I2Cx  Configuration ------------------------*/
  CM3DS_MPS2_I2Cx->CONTROL |= Mode | (0UL << CM3DS_MPS2_I2C_SWRST_Pos);

  CM3DS_MPS2_I2Cx->FREQDIV |= Speed;
  //|0x000000|(00UL << I2C_Speed_Mode_Pos)
  //|(0x39 << I2C_clock_divide_factor_Pos) 
  //|(11UL << I2C_SDA_Delay_count_selection_pos)
  //|(0x0  << I2C_SDA_delay_count_Pos); 
  CM3DS_MPS2_I2Cx->OWNADDR |= OwnAddress;
}

/**
  *
  * @brief: I2C从机地址设置。
  *
  * @param: CM3DS_MPS2_I2Cx,设置为CM3DS_MPS2_I2C。
  * @param: SlvAddress,要设置的从机地址。读操作或写操作由SlvAddress[15]位确定，该位为0表示写，为1表示读。
  *
  * @retVal: void
  */
void I2C_SlvaddrConfig(CM3DS_MPS2_I2C_TypeDef* CM3DS_MPS2_I2Cx, uint32_t SlvAddress)
{
  /*Check the parameters*/
  assert_param(IS_I2C_ALL_PERIPH(CM3DS_MPS2_I2Cx));

  CM3DS_MPS2_I2Cx->SLVADDR = SlvAddress;
}

/**
  *
  * @brief: 生成I2C起始信号。
  *
  * @param: CM3DS_MPS2_I2Cx,设置为CM3DS_MPS2_I2C。
  * @param: NewState,是否使能生成I2C起始信号；ENABLE - 使能；DISABLE - 不使能。
  *
  * @retVal: void
  */
void I2C_GenerateSTART(CM3DS_MPS2_I2C_TypeDef* CM3DS_MPS2_I2Cx, FunctionalState NewState)
{
  //uint32_t Ctrl_Read;
  /*Check the parameters*/
  assert_param(IS_I2C_ALL_PERIPH(CM3DS_MPS2_I2Cx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    /*Generate a START condition	*/

    CM3DS_MPS2_I2Cx->CONTROL |= (1UL << CM3DS_MPS2_I2C_START_SET_Pos);

    while ((CM3DS_MPS2_I2Cx->STATUS1 & 1) != 1)
    {
      CM3DS_MPS2_I2Cx->CONTROL = (CM3DS_MPS2_I2Cx->CONTROL) & (~CM3DS_MPS2_I2C_SWRST_Msk);
    }
  }
  else
  {
    /*	DISABLE the START condition generation	*/
    CM3DS_MPS2_I2Cx->CONTROL &= (~CM3DS_MPS2_I2C_START_SET_Msk);
  }
}

/**
  *
  * @brief: 使能I2C发送。
  *
  * @param: CM3DS_MPS2_I2Cx,设置为CM3DS_MPS2_I2C。
  * @param: NewState,是否使能I2C发送；ENABLE - 使能；DISABLE - 不使能。
  *
  * @retVal: void
  */
void I2C_TxEnable(CM3DS_MPS2_I2C_TypeDef* CM3DS_MPS2_I2Cx, FunctionalState NewState)
{
  uint32_t Ctrl_Read;
  assert_param(IS_I2C_ALL_PERIPH(CM3DS_MPS2_I2Cx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    /*	Generate a STOP condition	*/
    Ctrl_Read = CM3DS_MPS2_I2Cx->CONTROL;
    CM3DS_MPS2_I2Cx->CONTROL = Ctrl_Read | CM3DS_MPS2_I2C_TX_ENA_Msk;
  }
  else
  {
    /*	DISKABLE the STOP condition generation	*/
    CM3DS_MPS2_I2Cx->CONTROL &= (0UL << CM3DS_MPS2_I2C_TX_ENA_Pos);
  }
}

/**
  *
  * @brief: 使能I2C接收。
  *
  * @param: CM3DS_MPS2_I2Cx,设置为CM3DS_MPS2_I2C。
  * @param: NewState,是否使能I2C接收；ENABLE - 使能；DISABLE - 不使能。
  *
  * @retVal: void
  */
void I2C_RxEnable(CM3DS_MPS2_I2C_TypeDef* CM3DS_MPS2_I2Cx, FunctionalState NewState)
{
  //uint32_t Ctrl_Read;
  assert_param(IS_I2C_ALL_PERIPH(CM3DS_MPS2_I2Cx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    /*	Generate a STOP condition	*/
    CM3DS_MPS2_I2Cx->CONTROL |= (0UL << CM3DS_MPS2_I2C_TX_ENA_Pos) | (1UL << CM3DS_MPS2_I2C_RX_ENA_Pos);
  }
  else
  {
    /*	DISKABLE the STOP condition generation	*/
    CM3DS_MPS2_I2Cx->CONTROL &= (~CM3DS_MPS2_I2C_RX_ENA_Msk);
  }
}

/**
  *
  * @brief: 生成I2C停止信号。
  *
  * @param: CM3DS_MPS2_I2Cx,设置为CM3DS_MPS2_I2C。
  * @param: NewState,是否生成I2C停止信号；ENABLE - 使能；DISABLE - 不使能。
  *
  * @retVal: void
  */
void I2C_GenerateSTOP(CM3DS_MPS2_I2C_TypeDef* CM3DS_MPS2_I2Cx, FunctionalState NewState)
{
  //uint32_t Ctrl_Read;
    /* Check the parameters */
  assert_param(IS_I2C_ALL_PERIPH(CM3DS_MPS2_I2Cx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    /*	Generate a STOP condition	*/
    CM3DS_MPS2_I2Cx->CONTROL |= (1UL << CM3DS_MPS2_I2C_STOP_SET_Pos);
    while ((CM3DS_MPS2_I2Cx->STATUS1 & (1UL << 15)) == 0);  //stop bit detect
  }
  else
  {
    /*	DISKABLE the STOP condition generation	*/
    CM3DS_MPS2_I2Cx->CONTROL &= (~CM3DS_MPS2_I2C_STOP_SET_Msk);
  }
}

/**
  *
  * @brief: I2C中断配置。
  *
  * @param: CM3DS_MPS2_I2Cx,设置为CM3DS_MPS2_I2C。
  * @param: I2C_IT,I2C中断触发类型；
  *					可设置的值包括：
  *						I2C_IT_ERR(0x80) - I2C总线错误中断；
  *						I2C_IT_TC(0x2000) - I2C发送完成中断；
  *						I2C_IT_STOP(0x4000) - I2C停止中断；
  *						I2C_IT_TX(0x02)中断不能使用该函数进行设置，需要使用I2C_IT_TxbufferConfig 设置；
  *						I2C_IT_RX(0x0200)中断不能使用该函数进行设置，需要使用I2C_IT_RxbufferConfig 设置。
  * @param: NewState,是否使能中断；ENABLE - 使能；DISABLE - 不使能。
  *
  * @retVal: void
  */
void I2C_ITConfig(CM3DS_MPS2_I2C_TypeDef* CM3DS_MPS2_I2Cx, uint16_t I2C_IT, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_I2C_ALL_PERIPH(CM3DS_MPS2_I2Cx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  assert_param(IS_I2C_CONFIG_IT(I2C_IT));

  if (NewState != DISABLE)
  {
    /* Enable the selected I2C interrupts */
    CM3DS_MPS2_I2Cx->CONTROL |= I2C_IT;
  }
  else
  {
    /* Disable the selected I2C interrupts */
    CM3DS_MPS2_I2Cx->CONTROL &= ~I2C_IT;
  }
}

/**
  *
  * @brief: I2C发送中断配置。
  *
  * @param: CM3DS_MPS2_I2Cx,设置为CM3DS_MPS2_I2C。
  * @param: I2C_IT,I2C中断触发类型,只能设置为I2C_IT_TX(0x02)。
  * @param: NewState,是否使能中断；ENABLE - 使能；DISABLE - 不使能。
  * @param: Txbuffer, 发送buffer中断触发门限ctrl_tx_buff_wlevel；当TX FIFO占用的空间大于该值时将触发I2C发送中断；
  *						可设置的值为0/1/2/3。
  *
  * @retVal: void
  */
void I2C_IT_TxbufferConfig(CM3DS_MPS2_I2C_TypeDef* CM3DS_MPS2_I2Cx, uint16_t I2C_IT, FunctionalState NewState, uint16_t Txbuffer)
{
  /* Check the parameters */
  uint32_t Ctrl_Read;
  assert_param(IS_I2C_ALL_PERIPH(CM3DS_MPS2_I2Cx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  assert_param(IS_I2C_CONFIG_IT(I2C_IT));

  if (NewState != DISABLE)
  {
    Ctrl_Read = CM3DS_MPS2_I2Cx->CONTROL;
    CM3DS_MPS2_I2Cx->CONTROL = Ctrl_Read | CM3DS_MPS2_I2C_TX_IRQ_ENA_Msk
      | (Txbuffer << CM3DS_MPS2_I2C_TX_BUFFER_LEVEL_Pos);
  }
  else
  {
    CM3DS_MPS2_I2Cx->CONTROL &= ~I2C_IT;
  }
}

/**
  *
  * @brief: I2C接收中断配置。
  *
  * @param: CM3DS_MPS2_I2Cx,设置为CM3DS_MPS2_I2C。
  * @param: I2C_IT,I2C中断触发类型,只能设置为I2C_IT_RX(0x0200)。
  * @param: NewState,是否使能中断；ENABLE - 使能；DISABLE - 不使能。
  * @param: Rxbuffer, 接收buffer中断触发门限ctrl_rx_buff_wlevel；当RX FIFO占用的空间大于该值时将触发I2C接收中断；
  *						可设置的值为0/1/2/3。
  *
  * @retVal: void
  */
void I2C_IT_RxbufferConfig(CM3DS_MPS2_I2C_TypeDef* CM3DS_MPS2_I2Cx, uint16_t I2C_IT, FunctionalState NewState, uint16_t Rxbuffer)
{
  /* Check the parameters */
  assert_param(IS_I2C_ALL_PERIPH(CM3DS_MPS2_I2Cx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  assert_param(IS_I2C_CONFIG_IT(I2C_IT));
  if (NewState != DISABLE)
  {
    CM3DS_MPS2_I2Cx->CONTROL |= (CM3DS_MPS2_I2C_RX_IRQ_ENA_Msk)
      | (Rxbuffer << CM3DS_MPS2_I2C_RX_BUFFER_LEVEL_Pos)
      | (0UL << CM3DS_MPS2_I2C_SWRST_Pos);
  }
  else
  {
    CM3DS_MPS2_I2Cx->CONTROL &= ~I2C_IT;
  }
}

/**
  *
  * @brief: 设置I2C发送数据的个数。
  *
  * @param: CM3DS_MPS2_I2Cx,设置为CM3DS_MPS2_I2C。
  * @param: Num,需要发送数据的个数。
  *
  * @retVal: void
  */
void I2C_WriteByteNum(CM3DS_MPS2_I2C_TypeDef* CM3DS_MPS2_I2Cx, uint16_t Num)
{
  //uint32_t Ctrl_Read;
  /*Check the parameters*/
  assert_param(IS_I2C_ALL_PERIPH(CM3DS_MPS2_I2Cx));

  CM3DS_MPS2_I2Cx->CONTROL |= (Num << CM3DS_MPS2_I2C_TX_NUM_Pos)
    | (0UL << CM3DS_MPS2_I2C_SWRST_Pos);
}

/**
  *
  * @brief: 使用I2C发送数据。
  *
  * @param: CM3DS_MPS2_I2Cx,设置为CM3DS_MPS2_I2C。
  * @param: Byte,需要发送的数据。
  *
  * @retVal: void
  */
void I2C_WriteByte(CM3DS_MPS2_I2C_TypeDef* CM3DS_MPS2_I2Cx, uint8_t Byte)
{
  /*Check the parameters*/
  assert_param(IS_I2C_ALL_PERIPH(CM3DS_MPS2_I2Cx));

  CM3DS_MPS2_I2Cx->TXDATA = Byte;
}

/**
  *
  * @brief: 等待I2C发送完成。
  *
  * @param: CM3DS_MPS2_I2Cx,设置为CM3DS_MPS2_I2C。
  *
  * @retVal: void
  */
void I2C_WriteFinish(CM3DS_MPS2_I2C_TypeDef* CM3DS_MPS2_I2Cx)
{
  /*Check the parameters*/
  assert_param(IS_I2C_ALL_PERIPH(CM3DS_MPS2_I2Cx));

  while ((CM3DS_MPS2_I2Cx->STATUS1 & (1UL << 16)) == 0);		   //transmit complete flag
}

/**
  *
  * @brief: I2C等待接收数据，直到RX FIFO非空。
  *
  * @param: CM3DS_MPS2_I2Cx,设置为CM3DS_MPS2_I2C。
  *
  * @retVal: void
  */
void I2C_ReceiveReady(CM3DS_MPS2_I2C_TypeDef* CM3DS_MPS2_I2Cx)
{
  /*Check the parameters*/
  assert_param(IS_I2C_ALL_PERIPH(CM3DS_MPS2_I2Cx));

  while ((CM3DS_MPS2_I2Cx->STATUS1 & 0x00000400));
}

/**
  *
  * @brief: I2C接收数据。
  *
  * @param: CM3DS_MPS2_I2Cx,设置为CM3DS_MPS2_I2C。
  *
  * @retVal: Rx_Byte,I2C接收到的数据。
  */
uint8_t I2C_ReceiveByte(CM3DS_MPS2_I2C_TypeDef* CM3DS_MPS2_I2Cx)
{
  /*Check the parameters*/
  uint8_t Rx_Byte = 0x00;
  assert_param(IS_I2C_ALL_PERIPH(CM3DS_MPS2_I2Cx));

  Rx_Byte = (CM3DS_MPS2_I2Cx->RXDATA);
  return Rx_Byte;
}

/**
  *
  * @brief: 获取I2C状态寄存器1的值。
  *
  * @param: CM3DS_MPS2_I2Cx,设置为CM3DS_MPS2_I2C。
  *
  * @retVal: Values,获取到的状态寄存器值。
  */
uint32_t I2C_GetStatus1Values(CM3DS_MPS2_I2C_TypeDef* CM3DS_MPS2_I2Cx)
{
  /*Check the parameters*/
  uint32_t Values;
  assert_param(IS_I2C_ALL_PERIPH(CM3DS_MPS2_I2Cx));

  Values = (CM3DS_MPS2_I2Cx->STATUS1);
  /* Return the selected I2C status1 value */
  return Values;
}

/**
  *
  * @brief: 获取I2C状态寄存器2的值。
  *
  * @param: CM3DS_MPS2_I2Cx,设置为CM3DS_MPS2_I2C。
  *
  * @retVal: values,获取到的状态寄存器值。
  */
uint16_t I2C_GetStatus2Values(CM3DS_MPS2_I2C_TypeDef* CM3DS_MPS2_I2Cx)
{
  /*Check the parameters*/
  uint16_t values;
  assert_param(IS_I2C_ALL_PERIPH(CM3DS_MPS2_I2Cx));

  values = (CM3DS_MPS2_I2Cx->STATUS2);
  /* Return the selected I2C status1 value */
  return values;
}

/**
  *
  * @brief: 获取I2C指定状态是否发生。
  *
  * @param: CM3DS_MPS2_I2Cx,设置为CM3DS_MPS2_I2C。
  * @param: I2C_IT,要获取的状态类型；
  *					可设置的值包括:
  *						start_bit_det - 起始位信号被检测;
  *						addr_7bit_match - 地址7位发送/接收匹配;	addr_10bit_math - 地址10位发送/接收匹配；
  *						tx_fifo_full - 发送FIFO已满;	tx_fifo_empty - 发送FIFO已空；
  *						rx_fifo_full - 接收FIFO已满;	rx_fifo_empty - 接收FIFO已空；
  *						stop_bit_det - 停止位信号被检测; tc_flag - 发送完成；
  *						data_received - 数据到达。
  *
  *
  * @retVal: bitStatus,获取到的状态，SET - 指定状态已发生；RESET - 指定状态未发生。
  */
ITStatus I2C_GetITStatus(CM3DS_MPS2_I2C_TypeDef* CM3DS_MPS2_I2Cx, uint32_t I2C_IT)
{
  ITStatus bitStatus = RESET;
  uint32_t enablestatus = 0;
  /*Check the parameters*/
  assert_param(IS_I2C_ALL_PERIPH(CM3DS_MPS2_I2Cx));
  assert_param(IS_I2C_STATUS1(I2C_IT));

  enablestatus = CM3DS_MPS2_I2Cx->STATUS1;
  if ((enablestatus & I2C_IT) != RESET)
  {
    bitStatus = SET;
  }
  else
  {
    bitStatus = RESET;
  }
  return bitStatus;
}

/**
  *
  * @brief: 等待I2C总线为IDLE状态。
  *
  * @param: CM3DS_MPS2_I2Cx,设置为CM3DS_MPS2_I2C。
  *
  * @retVal: void
  */
void I2C_BUS_IDLE(CM3DS_MPS2_I2C_TypeDef* CM3DS_MPS2_I2Cx)
{
  assert_param(IS_I2C_ALL_PERIPH(CM3DS_MPS2_I2Cx));

  while ((CM3DS_MPS2_I2Cx->STATUS2 & (1UL << 4)));
}

