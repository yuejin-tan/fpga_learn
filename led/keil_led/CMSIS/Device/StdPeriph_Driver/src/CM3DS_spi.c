#include  "CM3DS_rcc.h"
#include "CM3DS_spi.h"
#include "CM3DS_MPS2.h"
#include "CM3DS_gpio.h"



/**
  *
  * @brief: 将SPI初始化为默认配置。
  *
  * @param: CM3DS_MPS2_SSPx,使用哪组SPI；CM3有2组SPI:CM3DS_MPS2_SSP0和CM3DS_MPS2_SSP1。
  *
  * @retVal: void
  */
void SSP_DeInit(CM3DS_MPS2_SSP_TypeDef* CM3DS_MPS2_SSPx)
{
  assert_param(IS_SSP_ALL_PERIPH(CM3DS_MPS2_SSPx));
  if (CM3DS_MPS2_SSPx == CM3DS_MPS2_SSP0)
  {
    RCC_APB1PeriphResetCmd(RCC_APB1Periph_SPI0, ENABLE);
    RCC_APB1PeriphResetCmd(RCC_APB1Periph_SPI0, DISABLE);
  }
  else if (CM3DS_MPS2_SSPx == CM3DS_MPS2_SSP1)
  {
    RCC_APB1PeriphResetCmd(RCC_APB1Periph_SPI1, ENABLE);
    RCC_APB1PeriphResetCmd(RCC_APB1Periph_SPI1, DISABLE);
  }
}

/**
  *
  * @brief: SPI初始化配置。
  *
  * @param: CM3DS_MPS2_SSPx,使用哪组SPI；CM3有2组SPI:CM3DS_MPS2_SSP0和CM3DS_MPS2_SSP1。
  * @param: SSP_InitStruct,SPI设置参数结构体变量，该结构体的成员变量包括传输数据的大小、SPI 工作模式、
  *								时钟分频系数、传输方式（分时或同时）、数据宽度、为回环模式或正常传输。
  *
  * @retVal: void
  */
void SSP_Init(CM3DS_MPS2_SSP_TypeDef* CM3DS_MPS2_SSPx, SSP_InitTypeDef* SSP_InitStruct)
{
  assert_param(IS_SSP_ALL_PERIPH(CM3DS_MPS2_SSPx));
  assert_param(IS_SSP_Data_Size(Data_Size));
  assert_param(IS_SSP_SPHSPO(Mode));
  assert_param(IS_SSP_SCR_divisor(SCR));
  assert_param(IS_SSP_Prescale_divisor(CLK));
  assert_param(IS_SSP_TXRXSIMULT_Format(Format));
  assert_param(IS_SSP_LBM_Work(Work));
  assert_param(IS_SSP_Data_Width(Width));

  CM3DS_MPS2_SSPx->CR0 = (0x000F & (SSP_InitStruct->Data_Size)) | (SSP_InitStruct->Mode) | (SSP_InitStruct->SCR);
  CM3DS_MPS2_SSPx->CPSR = (SSP_InitStruct->CLK);
  CM3DS_MPS2_SSPx->CR1 = (0x0000) | (SSP_InitStruct->TXRXSIMULT) | (SSP_InitStruct->LBM) | (SSP_InitStruct->Width);
}

/**
  *
  * @brief: 启用SPI，让SPI开始工作。
  *
  * @param: CM3DS_MPS2_SSPx,使用哪组SPI；CM3有2组SPI:CM3DS_MPS2_SSP0和CM3DS_MPS2_SSP1。
  * @param: NewState,是否启用SPI，ENABLE - 启用； DISABLE - 不启用。
  *
  * @retVal: void
  */
void SSP_Cmd(CM3DS_MPS2_SSP_TypeDef* CM3DS_MPS2_SSPx, FunctionalState NewState)
{
  assert_param(IS_SSP_ALL_PERIPH(CM3DS_MPS2_SSPx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    CM3DS_MPS2_SSPx->CR1 |= (0x1UL << 1);
  }
  else
  {
    CM3DS_MPS2_SSPx->CR1 &= (0x0UL << 1);
  }
}

/**
  *
  * @brief: SPI接收数据个数设置。
  *
  * @param: CM3DS_MPS2_SSPx,使用哪组SPI；CM3有2组SPI:CM3DS_MPS2_SSP0和CM3DS_MPS2_SSP1。
  * @param: RxNum,需要接收数据的个数。
  *
  * @retVal: void
  */
void SSP_ReceiveDataNum(CM3DS_MPS2_SSP_TypeDef* CM3DS_MPS2_SSPx, uint32_t RxNum)
{
  assert_param(IS_SSP_ALL_PERIPH(CM3DS_MPS2_SSPx));

  CM3DS_MPS2_SSPx->rx_cnt_lsb = RxNum;
  CM3DS_MPS2_SSPx->rx_cnt_msb = (RxNum >> 16);
}

/**
  *
  * @brief: SPI中断设置。
  *
  * @param: CM3DS_MPS2_SSPx,使用哪组SPI；CM3有2组SPI:CM3DS_MPS2_SSP0和CM3DS_MPS2_SSP1。
  * @param: SSP_IT,SPI中断类型，可设置的值包括：
  *					SSP_IT_RORIM - 接收溢出中断； SSP_IT_RTIM - 接收超时中断；
  *					SSP_IT_RXIM - 接收FIFO中断(接收FIFO半满或更少条件中断)；	SSP_IT_TXIM - 发送FIFO中断(发送FIFO半空或更少条件中断)；
  *					SSP_IT_RXFIM - 接收FIFO几乎满条件中断。
  * @param: NewState,是否使能中断；ENABLE - 使能中断；DISABLE - 不使能中断。
  *
  * @retVal: void
  */
void SSP_ITConfig(CM3DS_MPS2_SSP_TypeDef* CM3DS_MPS2_SSPx, uint16_t SSP_IT, FunctionalState NewState)
{
  assert_param(IS_SSP_ALL_PERIPH(CM3DS_MPS2_SSPx));
  assert_param(IS_SSP_CONFIG_IT(SSP_IT));
  if (NewState != DISABLE)
  {
    /* Enable the selected SSP interrupts */
    CM3DS_MPS2_SSPx->IMSC |= SSP_IT;
  }
  else
  {
    /* Disable the selected SSP interrupts */
    CM3DS_MPS2_SSPx->IMSC &= ~SSP_IT;
  }
}

/**
  *
  * @brief: 使用SPI发送数据。
  *
  * @param: CM3DS_MPS2_SSPx,使用哪组SPI；CM3有2组SPI:CM3DS_MPS2_SSP0和CM3DS_MPS2_SSP1。
  * @param: Data,需要发送的数据。
  *
  * @retVal: void
  */
void SSP_SendData(CM3DS_MPS2_SSP_TypeDef* CM3DS_MPS2_SSPx, uint16_t Data)
{
  assert_param(IS_SSP_ALL_PERIPH(CM3DS_MPS2_SSPx));

  CM3DS_MPS2_SSPx->DR = Data;
}

/**
  *
  * @brief: 等待SPI数据发送完成。
  *
  * @param: CM3DS_MPS2_SSPx,使用哪组SPI；CM3有2组SPI:CM3DS_MPS2_SSP0和CM3DS_MPS2_SSP1。
  *
  * @retVal: void
  */
void SSP_SendFinish(CM3DS_MPS2_SSP_TypeDef* CM3DS_MPS2_SSPx)
{
  assert_param(IS_SSP_ALL_PERIPH(CM3DS_MPS2_SSPx));
  while (CM3DS_MPS2_SSPx->SR & (SSP_SR_BSY_TX_Msk));//Wait to send FIFO idle; 
}

/**
  *
  * @brief: 等待SPI接收数据，直到接收FIFO非空。
  *
  * @param: CM3DS_MPS2_SSPx,使用哪组SPI；CM3有2组SPI:CM3DS_MPS2_SSP0和CM3DS_MPS2_SSP1。
  *
  * @retVal: void
  */
void SSP_ReceiveReady(CM3DS_MPS2_SSP_TypeDef* CM3DS_MPS2_SSPx)
{
  assert_param(IS_SSP_ALL_PERIPH(CM3DS_MPS2_SSPx));
  while (!(CM3DS_MPS2_SSPx->SR & SSP_SR_RNE_Msk));
}

/**
  *
  * @brief: SPI接收数据。
  *
  * @param: CM3DS_MPS2_SSPx,使用哪组SPI；CM3有2组SPI:CM3DS_MPS2_SSP0和CM3DS_MPS2_SSP1。
  *
  * @retVal: rx,接收到的数据。
  */
uint16_t SSP_ReceiveData(CM3DS_MPS2_SSP_TypeDef* CM3DS_MPS2_SSPx)
{
  uint16_t rx = 0x0000;
  assert_param(IS_SSP_ALL_PERIPH(CM3DS_MPS2_SSPx));

  rx = CM3DS_MPS2_SSPx->DR;
  return rx;
}

/**
  *
  * @brief: 读取SPI状态寄存器SR当前值。
  *
  * @param: CM3DS_MPS2_SSPx,使用哪组SPI；CM3有2组SPI:CM3DS_MPS2_SSP0和CM3DS_MPS2_SSP1。
  *
  * @retVal: SRValue,读取到的状态寄存器值。
  */
uint16_t SSP_SRValue(CM3DS_MPS2_SSP_TypeDef* CM3DS_MPS2_SSPx)
{
  uint16_t SRValue;
  assert_param(IS_SSP_ALL_PERIPH(CM3DS_MPS2_SSPx));
  SRValue = CM3DS_MPS2_SSPx->SR;
  return SRValue;
}

/**
  *
  * @brief: 读取SPI RIS寄存器当前值。
  *
  * @param: CM3DS_MPS2_SSPx,使用哪组SPI；CM3有2组SPI:CM3DS_MPS2_SSP0和CM3DS_MPS2_SSP1。
  *
  * @retVal: RISValue,读取到的状态寄存器值。
  */
uint16_t SSP_RISValue(CM3DS_MPS2_SSP_TypeDef* CM3DS_MPS2_SSPx)
{
  uint16_t RISValue;
  assert_param(IS_SSP_ALL_PERIPH(CM3DS_MPS2_SSPx));
  RISValue = CM3DS_MPS2_SSPx->RIS;
  return RISValue;
}

/**
  *
  * @brief: 读取SPI MIS寄存器当前值。
  *
  * @param: CM3DS_MPS2_SSPx,使用哪组SPI；CM3有2组SPI:CM3DS_MPS2_SSP0和CM3DS_MPS2_SSP1。
  *
  * @retVal: MISValue,读取到的状态寄存器值。
  */
uint16_t SSP_MISValue(CM3DS_MPS2_SSP_TypeDef* CM3DS_MPS2_SSPx)
{
  uint16_t MISValue;
  assert_param(IS_SSP_ALL_PERIPH(CM3DS_MPS2_SSPx));
  MISValue = CM3DS_MPS2_SSPx->MIS;
  return MISValue;
}

/**
  *
  * @brief: 清除SPI中断。
  *
  * @param: CM3DS_MPS2_SSPx,使用哪组SPI；CM3有2组SPI:CM3DS_MPS2_SSP0和CM3DS_MPS2_SSP1。
  * @param: IT,中断类型，可设置的值包括：
  *						SSP_IT_RORIC - 清除SSPRORINTR(SPI接收溢出)中断；SSP_IT_RTIC - 清除SSPRTINTR(SPI接收超时)中断。
  *
  * @retVal: void
  */
void SSP_ClearIT(CM3DS_MPS2_SSP_TypeDef* CM3DS_MPS2_SSPx, uint16_t IT)
{
  assert_param(IS_SSP_ALL_PERIPH(CM3DS_MPS2_SSPx));
  assert_param(IS_SSP_Clear_IT(IT));
  if (IT == SSP_IT_RORIC)
  {
    CM3DS_MPS2_SSPx->ICR = 0x0000 | SSP_IT_RORIC;
  }
  else if (IT == SSP_IT_RTIC)
  {
    CM3DS_MPS2_SSPx->ICR = 0x0000 | SSP_IT_RTIC;
  }
  else
  {
    CM3DS_MPS2_SSPx->ICR = 0x0000;
  }
}

/**
  *
  * @brief: 等待直到SPI发送FIFO为空。
  *
  * @param: CM3DS_MPS2_SSPx,使用哪组SPI；CM3有2组SPI:CM3DS_MPS2_SSP0和CM3DS_MPS2_SSP1。
  *
  * @retVal: void
  */
void SSP_Wait_TxfifoNonEmpty(CM3DS_MPS2_SSP_TypeDef* CM3DS_MPS2_SSPx)
{
  assert_param(IS_SSP_ALL_PERIPH(CM3DS_MPS2_SSPx));
  while (!(CM3DS_MPS2_SSPx->SR & SSP_SR_TFE_Msk));
}

/**
  *
  * @brief: 等待直到SPI接收FIFO为空。
  *
  * @param: CM3DS_MPS2_SSPx,使用哪组SPI；CM3有2组SPI:CM3DS_MPS2_SSP0和CM3DS_MPS2_SSP1。
  *
  * @retVal: void
  */
void SSP_Wait_RxfifoNonEmpty(CM3DS_MPS2_SSP_TypeDef* CM3DS_MPS2_SSPx)
{
  assert_param(IS_SSP_ALL_PERIPH(CM3DS_MPS2_SSPx));
  while ((CM3DS_MPS2_SSPx->SR & SSP_SR_RNE_Msk));
}

/**
  *
  * @brief: 等待直到SPI为空闲状态。
  *
  * @param: CM3DS_MPS2_SSPx,使用哪组SPI；CM3有2组SPI:CM3DS_MPS2_SSP0和CM3DS_MPS2_SSP1。
  *
  * @retVal: void
  */
void SSP_Wait_PrimeCellBusy(CM3DS_MPS2_SSP_TypeDef* CM3DS_MPS2_SSPx)
{
  assert_param(IS_SSP_ALL_PERIPH(CM3DS_MPS2_SSPx));
  while (CM3DS_MPS2_SSPx->SR & SSP_SR_BSY_Msk);
}

/**
  *
  * @brief: 等待直到SPI发送为空闲状态，以保证发送完成。
  *
  * @param: CM3DS_MPS2_SSPx,使用哪组SPI；CM3有2组SPI:CM3DS_MPS2_SSP0和CM3DS_MPS2_SSP1。
  *
  * @retVal: void
  */
void SSP_Wait_TxBusy(CM3DS_MPS2_SSP_TypeDef* CM3DS_MPS2_SSPx)
{
  assert_param(IS_SSP_ALL_PERIPH(CM3DS_MPS2_SSPx));
  while (CM3DS_MPS2_SSPx->SR & SSP_SR_BSY_TX_Msk);
}


