/*---------Include---------*/
#include "CM3DS_uart.h"
#include "CM3DS_rcc.h"


/**
  *
  * @brief: 将UART初始化为默认配置。
  *
  * @param: CM3DS_MPS2_UARTx,使用哪组UART;CM3有2组UART:CM3DS_MPS2_UART0和CM3DS_MPS2_UART1。
  *
  * @retVal: void
  */
void UART_DeInit(CM3DS_MPS2_UART_TypeDef* CM3DS_MPS2_UARTx)
{
  /* Check the parameters */
  assert_param(IS_UART_ALL_PERIPH(CM3DS_MPS2_UARTx));

  if (CM3DS_MPS2_UARTx == CM3DS_MPS2_UART0)
  {
    //APB_PERI_RSTCTL->RESETPERI &= (~PERI_RSTCTL_UART0_Msk);
    RCC_APB1PeriphResetCmd(RCC_APB1Periph_UART0, ENABLE);
    RCC_APB1PeriphResetCmd(RCC_APB1Periph_UART0, DISABLE);
  }
  else if (CM3DS_MPS2_UARTx == CM3DS_MPS2_UART1)
  {
    //APB_PERI_RSTCTL->RESETPERI &= (~PERI_RSTCTL_UART1_Msk);
    RCC_APB1PeriphResetCmd(RCC_APB1Periph_UART1, ENABLE);
    RCC_APB1PeriphResetCmd(RCC_APB1Periph_UART1, DISABLE);
  }
}

/**
  *
  * @brief: UART初始化设置。
  *
  * @param: CM3DS_MPS2_UARTx,使用哪组UART;CM3有2组UART:CM3DS_MPS2_UART0和CM3DS_MPS2_UART1。
  * @param: UART_InitStruct,UART设置参数结构体变量，该结构体的成员变量包括串口波特率、串口工作方式。
  *
  * @retVal: void
  */
void UART_Init(CM3DS_MPS2_UART_TypeDef* CM3DS_MPS2_UARTx, UART_InitTypeDef* UART_InitStruct)
{
  /*Check the parameters*/
  assert_param(IS_UART_ALL_PERIPH(CM3DS_MPS2_UARTx));
  assert_param(IS_USART_CTRL(UART_InitStruct->UART_CTRL));

  /*--------UART Configuration---------*/
  CM3DS_MPS2_UARTx->BAUDDIV = SystemCoreClock / UART_InitStruct->UART_BundRate;
  CM3DS_MPS2_UARTx->CTRL = UART_InitStruct->UART_CTRL;
}

/**
  *
  * @brief: UART中断设置。
  *
  * @param: CM3DS_MPS2_UARTx,使用哪组UART;CM3有2组UART:CM3DS_MPS2_UART0和CM3DS_MPS2_UART1。
  * @param: UART_IT,UART中断类型；可设置的值包括:
  *							UART_TxInterrupt(0x04) - UART发送中断；
  *							UART_RxInterrupt(0x08) - UART接收中断；
  *							UART_TxInterruptOverrun(0x10) - UART发送buffer溢出中断；
  *							UART_RxInterruptOverrun(0x20) - UART接收buffer溢出中断。
  * @param: NewState,是否使能UART中断: ENABLE - 使能中断；DISABLE - 不使能中断。
  * @retVal: void
  */
void UART_ITConfig(CM3DS_MPS2_UART_TypeDef* CM3DS_MPS2_UARTx, uint16_t UART_IT, FunctionalState NewState)
{
  /*Check the parameters*/
  assert_param(IS_UART_ALL_PERIPH(CM3DS_MPS2_UARTx));
  assert_param(IS_UART_CONFIG_IT(UART_IT));
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    CM3DS_MPS2_UARTx->CTRL |= UART_IT;
  }
  else
  {
    CM3DS_MPS2_UARTx->CTRL &= ~UART_IT;
  }
}

/**
  *
  * @brief: 清除UART中断。
  *
  * @param: CM3DS_MPS2_UARTx,使用哪组UART;CM3有2组UART:CM3DS_MPS2_UART0和CM3DS_MPS2_UART1。
  * @param: USART_INTCLEAR,要清除的串口中断类型；可设置的值包括:
  *							UART_INTCLEAR_TxInterrupt(0x01) - UART发送中断清除；
  *							UART_INTCLEAR_RxInterrupt(0x02) - UART接收中断清除；
  *							UART_INTCLEAR_TxInterruptOverrun(0x04) - UART发送buffer溢出中断清除；
  *							UART_INTCLEAR_RxInterruptOverrun(0x08) - UART接收buffer溢出中断清除。
  *
  * @retVal: void
  */
void UART_ITCLEAR(CM3DS_MPS2_UART_TypeDef* CM3DS_MPS2_UARTx, uint16_t USART_INTCLEAR)
{
  /*Checking the parameters*/
  assert_param(IS_UART_ALL_PERIPH(CM3DS_MPS2_UARTx));
  assert_param(IS_USART_INTCLEAR(INTCLEAR));
  CM3DS_MPS2_UARTx->INTCLEAR |= USART_INTCLEAR;
}

/**
  *
  * @brief: 获取UART中断状态。
  *
  * @param: CM3DS_MPS2_UARTx,使用哪组UART;CM3有2组UART:CM3DS_MPS2_UART0和CM3DS_MPS2_UART1。
  * @param: UART_IT,要获取中断状态的中断类型；可设置的值包括:
  *							UART_TxInterrupt(0x04) - UART发送中断；
  *							UART_RxInterrupt(0x08) - UART接收中断；
  *							UART_TxInterruptOverrun(0x10) - UART发送buffer溢出中断；
  *							UART_RxInterruptOverrun(0x20) - UART接收buffer溢出中断。
  *
  * @retVal: bitstatus,获取到的中断状态；
  *						SET - 产生了UART_IT指定中断类型的中断；RESET - 未产生UART_IT指定中断类型的中断。
  */
FlagStatus UART_GetITStatus(CM3DS_MPS2_UART_TypeDef* CM3DS_MPS2_UARTx, uint16_t UART_IT)
{
  FlagStatus bitstatus = RESET;
  /*Checking the parameters*/
  assert_param(IS_UART_ALL_PERIPH(CM3DS_MPS2_UARTx));
  assert_param(IS_UART_GET_IT(UART_IT));

  if ((CM3DS_MPS2_UARTx->INTSTATUS & (UART_IT >> 2)) != RESET)
  {
    bitstatus = SET;
  }
  else
  {
    bitstatus = RESET;
  }
  return bitstatus;
}

/**
  *
  * @brief: 获取UART接收buffer和发送buffer状态。
  *
  * @param: CM3DS_MPS2_UARTx,使用哪组UART;CM3有2组UART:CM3DS_MPS2_UART0和CM3DS_MPS2_UART1。
  * @param: UART_FLAG,要获取buffer的状态类型；可设置的值包括:
  *							UART_TxBufferFull_FLAG(0x01) - UART发送buffer已满状态；
  *							UART_RxBufferFull_FLAG(0x02) - UART接收buffer已满状态；
  *							UART_TxBufferOverrun_FLAG(0x04) - UART发送buffer溢出状态；
  *							UART_RxBufferOverrun_FLAG(0x08) - UART接收buffer溢出状态。
  *
  * @retVal: bitstatus,获取到的buffer状态是否是查询的状态；如UART_FLAG为UART_TxBufferFull_FLAG；返回值为SET，
  *						则表明UART发送buffer已满；如果返回值为RESET，则表明UART发送buffer未满。
  */
FlagStatus UART_GetFlagStatus(CM3DS_MPS2_UART_TypeDef* CM3DS_MPS2_UARTx, uint16_t UART_FLAG)
{
  FlagStatus bitstatus = RESET;
  /*Checking the parameters*/
  assert_param(IS_UART_ALL_PERIPH(CM3DS_MPS2_UARTx));
  assert_param(IS_UART_FLAG(UART_FLAG));

  if ((CM3DS_MPS2_UARTx->STATE & UART_FLAG) != RESET)
  {
    bitstatus = SET;
  }
  else
  {
    bitstatus = RESET;
  }
  return bitstatus;
}


/**
  *
  * @brief: UART发送数据。
  *
  * @param: CM3DS_MPS2_UARTx,使用哪组UART;CM3有2组UART:CM3DS_MPS2_UART0和CM3DS_MPS2_UART1。
  * @param: Data,需要发送的数据。
  *
  * @retVal: void
  */
void UART_SendData(CM3DS_MPS2_UART_TypeDef* CM3DS_MPS2_UARTx, uint8_t Data)
{
  /*Check the parameters*/
  assert_param(IS_UART_ALL_PERIPH(CM3DS_MPS2_UARTx));

  /*Transmit data*/
  // Wait if Transmit Holding register is full
  while ((CM3DS_MPS2_UARTx->STATE & CM3DS_MPS2_UART_STATE_TXBF_Msk));
  CM3DS_MPS2_UARTx->DATA = (Data & (uint8_t)0xff);
}

/**
  *
  * @brief: UART接收数据。
  *
  * @param: CM3DS_MPS2_UARTx,使用哪组UART;CM3有2组UART:CM3DS_MPS2_UART0和CM3DS_MPS2_UART1。
  *
  * @retVal: read_value,UART接收到的数据。
  */
uint8_t  UART_ReceiveData(CM3DS_MPS2_UART_TypeDef* CM3DS_MPS2_UARTx)
{
  uint8_t read_value = 0x00;

  /*Check the parameters*/
  assert_param(IS_UART_ALL_PERIPH(CM3DS_MPS2_UARTx));

  /* Receive Data */
  while ((CM3DS_MPS2_UARTx->STATE & CM3DS_MPS2_UART_STATE_RXBF_Msk) == 0);
  read_value = (uint8_t)(CM3DS_MPS2_UARTx->DATA & (uint8_t)0xff);

  return  read_value;
}


