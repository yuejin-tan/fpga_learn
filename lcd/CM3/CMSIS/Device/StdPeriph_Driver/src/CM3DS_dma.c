#include "CM3DS_rcc.h"
#include "CM3DS_gpio.h"
#include "CM3DS_uart.h"	
#include "CM3DS_MPS2.h"	
#include "CM3DS_dma.h"	


/**
  *
  * @brief: 读取DMA中断状态寄存器。
  *
  * @param: CM3DS_MPS2_DMAx,CM3只有1组DMA,只能设置为CM3DS_MPS2_DMA。
  *
  * @retVal: IntStatus,读取到的中断状态寄存器值。
  */
uint32_t DMA_Interrupt_Status(CM3DS_MPS2_DMA_TypeDef* CM3DS_MPS2_DMAx)
{
  uint32_t IntStatus;
  assert_param(IS_DMA_ALL_PERIPH(CM3DS_MPS2_DMAx));
  IntStatus = CM3DS_MPS2_DMAx->DMACIntStatus;

  return IntStatus;
}

/**
  *
  * @brief: 读取DMA终端计数中断状态寄存器。
  *
  * @param: CM3DS_MPS2_DMAx,CM3只有1组DMA,只能设置为CM3DS_MPS2_DMA。
  *
  * @retVal: IntTCStatus,读取到的终端计数中断状态寄存器值。
  */
uint32_t DMA_Terminal_Count_status(CM3DS_MPS2_DMA_TypeDef* CM3DS_MPS2_DMAx)
{
  uint32_t IntTCStatus;
  assert_param(IS_DMA_ALL_PERIPH(CM3DS_MPS2_DMAx));
  IntTCStatus = CM3DS_MPS2_DMAx->DMACIntTCStatus;

  return IntTCStatus;
}

/**
  *
  * @brief: 清除DMA终端计数中断。
  *
  * @param: CM3DS_MPS2_DMAx,CM3只有1组DMA,只能设置为CM3DS_MPS2_DMA。
  * @param: Channel,使用哪个通道；可设置的值包括：Channel_0(0x00) - 通道0；Channel_1 (0x01) - 通道1。
  * @param: NewState,是否清除中断；ENABLE -清除；DISABLE -不清除。
  *
  * @retVal: void
  */
void DMA_Interrupt_Terminal_Count_Clear(CM3DS_MPS2_DMA_TypeDef* CM3DS_MPS2_DMAx, uint8_t Channel, FunctionalState NewState)
{
  assert_param(IS_DMA_ALL_PERIPH(CM3DS_MPS2_DMAx));
  assert_param(IS_DMA_Channel(Channel));

  if (NewState != DISABLE)
  {
    CM3DS_MPS2_DMAx->DMACIntTCClear = 1 << Channel;
  }
  else
  {
    CM3DS_MPS2_DMAx->DMACIntTCClear = 0 << Channel;
  }
}

/**
  *
  * @brief: 读取DMA错误中断状态寄存器。
  *
  * @param: CM3DS_MPS2_DMAx,CM3只有1组DMA,只能设置为CM3DS_MPS2_DMA。
  *
  * @retVal: IntErrorStatus,读取到的错误中断状态寄存器值。
  */
uint32_t DMA_Interrupt_Error_Status(CM3DS_MPS2_DMA_TypeDef* CM3DS_MPS2_DMAx)
{
  uint32_t IntErrorStatus;
  assert_param(IS_DMA_ALL_PERIPH(CM3DS_MPS2_DMAx));

  IntErrorStatus = CM3DS_MPS2_DMAx->DMACIntErrorStatus;
  return IntErrorStatus;
}

/**
 *
 * @brief: 清除DMA错误中断请求。
 *
 * @param: CM3DS_MPS2_DMAx,CM3只有1组DMA,只能设置为CM3DS_MPS2_DMA。
 * @param: Channel,使用哪个通道；可设置的值包括：Channel_0(0x00) - 通道0；Channel_1 (0x01) - 通道1。
 * @param: NewState,是否清除；ENABLE -清除；DISABLE -不清除。
 *
 * @retVal: void
 */
void DMA_Interrupt_Error_Clear(CM3DS_MPS2_DMA_TypeDef* CM3DS_MPS2_DMAx, uint8_t Channel, FunctionalState NewState)
{
  assert_param(IS_DMA_ALL_PERIPH(CM3DS_MPS2_DMAx));
  assert_param(IS_DMA_Channel(Channel));
  if (NewState != DISABLE)
  {
    CM3DS_MPS2_DMAx->DMACIntErrClr = 1 << Channel;
  }
  else
  {
    CM3DS_MPS2_DMAx->DMACIntErrClr = 0 << Channel;
  }
}

/**
  *
  * @brief: 读取DMA终端计数屏蔽之前的中断状态。
  *
  * @param: CM3DS_MPS2_DMAx,CM3只有1组DMA,只能设置为CM3DS_MPS2_DMA。
  *
  * @retVal: RawIntTCStatus,读取到中断状态。
  */
uint32_t DMA_Raw_Interrupt_Terminal_Count_Status(CM3DS_MPS2_DMA_TypeDef* CM3DS_MPS2_DMAx)
{
  uint32_t RawIntTCStatus;
  assert_param(IS_DMA_ALL_PERIPH(CM3DS_MPS2_DMAx));

  RawIntTCStatus = CM3DS_MPS2_DMAx->DMACRawIntTCStatus;
  return RawIntTCStatus;
}

/**
  *
  * @brief: 读取DMA屏蔽之前的错误中断状态。
  *
  * @param: CM3DS_MPS2_DMAx,CM3只有1组DMA,只能设置为CM3DS_MPS2_DMA。
  *
  * @retVal: RawIntErrorStatus,读取到中断状态。
  */
uint32_t DMA_Raw_Error_Interrupt_Status(CM3DS_MPS2_DMA_TypeDef* CM3DS_MPS2_DMAx)
{
  uint32_t RawIntErrorStatus;
  assert_param(IS_DMA_ALL_PERIPH(CM3DS_MPS2_DMAx));

  RawIntErrorStatus = CM3DS_MPS2_DMAx->DMACRawIntTCStatus;
  return RawIntErrorStatus;
}

/**
  *
  * @brief: 读取DMA通道使能状态。
  *
  * @param: CM3DS_MPS2_DMAx,CM3只有1组DMA,只能设置为CM3DS_MPS2_DMA。
  *
  * @retVal: EnabledChannel,读取到的通道使能状态；bit0 -通道0通道使能状态；bit1 - 通道1通道使能状态。
  */
uint32_t DMA_Enable_Channel(CM3DS_MPS2_DMA_TypeDef* CM3DS_MPS2_DMAx)
{
  uint32_t EnabledChannel;
  assert_param(IS_DMA_ALL_PERIPH(CM3DS_MPS2_DMAx));

  EnabledChannel = CM3DS_MPS2_DMAx->DMACEnbldChns;
  return EnabledChannel;
}

/**
  *
  * @brief: DMA配置。
  *
  * @param: CM3DS_MPS2_DMAx,CM3只有1组DMA,只能设置为CM3DS_MPS2_DMA。
  * @param: M,AHB主端大小端格式；0- 小端格式；1- 大端格式；默认为0。
  * @param: E,DMA控制器使能；0 -不使能；1 -使能。
  *
  * @retVal: void
  */
void DMA_Configuration(CM3DS_MPS2_DMA_TypeDef* CM3DS_MPS2_DMAx, int M, int E)
{
  assert_param(IS_DMA_ALL_PERIPH(CM3DS_MPS2_DMAx));
  CM3DS_MPS2_DMAx->DMACConfiguration = 0x00000000;

  CM3DS_MPS2_DMAx->DMACConfiguration |= (M << 1) | (E << 0);
}

/**
  *
  * @brief: 设置DMA源地址。
  *
  * @param: CM3DS_MPS2_DMAx,CM3只有1组DMA,只能设置为CM3DS_MPS2_DMA。
  * @param: Channel,使用哪个通道；可设置的值包括：Channel_0(0x00) - 通道0；Channel_1 (0x01) - 通道1。
  * @param: addr,设置的源地址。
  *
  * @retVal: void
  */
void DMA_Source_Address(CM3DS_MPS2_DMA_TypeDef* CM3DS_MPS2_DMAx, uint8_t Channel, uint32_t addr)
{
  assert_param(IS_DMA_ALL_PERIPH(CM3DS_MPS2_DMAx));
  assert_param(IS_DMA_Channel(Channel));
  CM3DS_MPS2_DMAx->DMACC1SrcAddr = 0x00000000;
  CM3DS_MPS2_DMAx->DMACC0SrcAddr = 0x00000000;
  if (Channel != 0x0)
  {
    CM3DS_MPS2_DMAx->DMACC1SrcAddr = addr;
  }
  else
  {
    CM3DS_MPS2_DMAx->DMACC0SrcAddr = addr;
  }
}

/**
  *
  * @brief: 设置DMA目的地址。
  *
  * @param: CM3DS_MPS2_DMAx,CM3只有1组DMA,只能设置为CM3DS_MPS2_DMA。
  * @param: Channel,使用哪个通道；可设置的值包括：Channel_0(0x00) - 通道0；Channel_1 (0x01) - 通道1。
  * @param: addr,设置的目的地址。
  *
  * @retVal: void
  */
void DMA_Destination_Address(CM3DS_MPS2_DMA_TypeDef* CM3DS_MPS2_DMAx, uint8_t Channel, uint32_t addr)
{
  assert_param(IS_DMA_ALL_PERIPH(CM3DS_MPS2_DMAx));
  assert_param(IS_DMA_Channel(Channel));
  CM3DS_MPS2_DMAx->DMACC1DestAddr = 0x00000000;
  CM3DS_MPS2_DMAx->DMACC0DestAddr = 0x00000000;
  if (Channel != 0x0)
  {
    CM3DS_MPS2_DMAx->DMACC1DestAddr = addr;
  }
  else
  {
    CM3DS_MPS2_DMAx->DMACC0DestAddr = addr;
  }
}

/**
  *
  * @brief: 设置DMA的链式传输。
  *
  * @param: CM3DS_MPS2_DMAx,CM3只有1组DMA,只能设置为CM3DS_MPS2_DMA。
  * @param: Channel,使用哪个通道；可设置的值包括：Channel_0(0x00) - 通道0；Channel_1 (0x01) - 通道1。
  * @param: data,链表项，下一个链表项。
  *
  * @retVal: void
  */
void DMA_LLI(CM3DS_MPS2_DMA_TypeDef* CM3DS_MPS2_DMAx, uint8_t Channel, uint32_t data)
{
  assert_param(IS_DMA_ALL_PERIPH(CM3DS_MPS2_DMAx));
  assert_param(IS_DMA_Channel(Channel));
  CM3DS_MPS2_DMAx->DMACC1LLI = 0x00000000;
  CM3DS_MPS2_DMAx->DMACC0LLI = 0x00000000;
  if (Channel != 0x0)
  {
    CM3DS_MPS2_DMAx->DMACC1LLI = data;
  }
  else
  {
    CM3DS_MPS2_DMAx->DMACC0LLI = data;
  }
}

/**
  *
  * @brief: 配置DMA计数中断(发送完成中断)是否使能及源地址和目标地址在每次传输后是否递增。
  *
  * @param: CM3DS_MPS2_DMAx,CM3只有1组DMA,只能设置为CM3DS_MPS2_DMA。
  * @param: Channel,使用哪个通道；可设置的值包括：Channel_0(0x00) - 通道0；Channel_1 (0x01) - 通道1。
  * @param: I,终端计数中断(发送完成中断)使能；可设置的值包括：I_IT_Dis(0x0) - 不使能中断，I_IT_En (0x01) - 使能中断；默认不使能中断。
  * @param: DI,目的地址是否递增；可设置的值包括：DI_En(0x1) -递增；DI_Dis(0x0) - 不递增。
  * @param: SI,源地址是否递增；可设置的值包括：SI_En(0x1) -递增； SI_Dis (0x0) -不递增。
  *
  * @retVal: void
  */
void DMA_Control_Increment(CM3DS_MPS2_DMA_TypeDef* CM3DS_MPS2_DMAx, uint8_t Channel, int I, int DI, int SI)
{
  assert_param(IS_DMA_ALL_PERIPH(CM3DS_MPS2_DMAx));
  assert_param(IS_DMA_Channel(Channel));

  if (Channel != 0x0)//channel_1
  {
    CM3DS_MPS2_DMAx->DMACC1Control |= (I << 31) | (DI << 27) | (SI << 26);
  }
  else//channel_0
  {
    CM3DS_MPS2_DMAx->DMACC0Control |= (I << 31) | (DI << 27) | (SI << 26);
  }
}

/**
  *
  * @brief: 设置DMA传输数据的数据宽度。
  *
  * @param: CM3DS_MPS2_DMAx,CM3只有1组DMA,只能设置为CM3DS_MPS2_DMA。
  * @param: Channel,使用哪个通道；可设置的值包括：Channel_0(0x00) - 通道0；Channel_1 (0x01) - 通道1。
  * @param: DW,目标地址接收数据的宽度；可设置的值包括：
  *					SWorDWidth_8bit_Byte -8bit; SWorDWidth_16bit_Halfword - 16bit; SWorDWidth_32bit_Word - 32bit。
  * @param: SW,源地址接收数据的宽度；可设置的值包括：
  *					SWorDWidth_8bit_Byte -8bit; SWorDWidth_16bit_Halfword - 16bit; SWorDWidth_32bit_Word - 32bit。
  *
  * @retVal: void
  */
void DMA_Control_DataWidth(CM3DS_MPS2_DMA_TypeDef* CM3DS_MPS2_DMAx, uint8_t Channel, int DW, int SW)
{
  assert_param(IS_DMA_ALL_PERIPH(CM3DS_MPS2_DMAx));
  assert_param(IS_DMA_Channel(Channel));

  if (Channel != 0x0)//channel_1
  {
    CM3DS_MPS2_DMAx->DMACC1Control |= (DW << 21) | (SW << 18);
  }
  else//channel_0
  {
    CM3DS_MPS2_DMAx->DMACC0Control |= (DW << 21) | (SW << 18);
  }
}

/**
  *
  * @brief: 设置DMA传输数据的个数。
  *
  * @param: CM3DS_MPS2_DMAx,CM3只有1组DMA,只能设置为CM3DS_MPS2_DMA。
  * @param: Channel,使用哪个通道；可设置的值包括：Channel_0(0x00) - 通道0；Channel_1 (0x01) - 通道1。
  * @param: DB,目标地址突发传输的数据个数；可设置的值包括：
  *					DB_BurstSize_1 - 1个；DB_BurstSize_4 - 4个；DB_BurstSize_8 -8个；DB_BurstSize_16 - 16个；
  *					DB_BurstSize_32 - 32个； DB_BurstSize_64 - 64个； DB_BurstSize_128 -128个；DB_BurstSize_256 -256个。
  * @param: SB,源地址突发传输的数据个数；可设置的值包括：
  *					SB_BurstSize_1 -1个；SB_BurstSize_4 - 4个；SB_BurstSize_8 -8个；SB_BurstSize_16 - 16个；
  *					SB_BurstSize_32 - 1个；SB_BurstSize_64 -64个；SB_BurstSize_128 -128个；SB_BurstSize_256 -256个。
  * @param: Tx_Size,正常传输下数据的个数。
  *
  * @retVal: void
  */
void DMA_Control_TransferSize(CM3DS_MPS2_DMA_TypeDef* CM3DS_MPS2_DMAx, uint8_t Channel, int DB, int SB, int Tx_Size)
{
  assert_param(IS_DMA_ALL_PERIPH(CM3DS_MPS2_DMAx));
  assert_param(IS_DMA_Channel(Channel));

  if (Channel != 0x0)//channel_1
  {
    CM3DS_MPS2_DMAx->DMACC1Control |= (DB << 15) | (SB << 12) | (Tx_Size << 0);
  }
  else//channel_0
  {
    CM3DS_MPS2_DMAx->DMACC0Control |= (DB << 15) | (SB << 12) | (Tx_Size << 0);
  }
}

/**
  *
  * @brief: DMA通道配置。
  *
  * @param: CM3DS_MPS2_DMAx,CM3只有1组DMA,只能设置为CM3DS_MPS2_DMA。
  * @param: Channel,使用哪个通道；可设置的值包括：Channel_0(0x00) - 通道0；Channel_1 (0x01) - 通道1。
  * @param: Halt,是否忽略后续的源DMA请求；可设置的值包括：Halt_Dis(0x0) - 不忽略；Halt_En(0x01) - 忽略。
  * @param: Lock,是否锁定传输；可设置的值包括： Lock_Dis(0x0) - 不锁定；Lock_En(0x01) - 锁定。
  * @param: ITC,终端计数中断掩码；可设置的值包括：ITC_Mask(0x0) -屏蔽相关通道的终端计数中断;
  * 												ITC_NotMask(0x01) - 不屏蔽相关通道的终端计数中断。
  * @param: IE,错误中断掩码；可设置的值包括：IE_Mask(0x0) - 屏蔽相关通道的错误中断；
  *												IE_NotMask(0x01) - 不屏蔽相关通道的错误中断。
  *
  * @retVal: void
  */
void DMA_ChannelConfig(CM3DS_MPS2_DMA_TypeDef* CM3DS_MPS2_DMAx, uint8_t Channel, int Halt, int Lock, int ITC, int IE)
{
  assert_param(IS_DMA_ALL_PERIPH(CM3DS_MPS2_DMAx));
  assert_param(IS_DMA_Channel(Channel));
  CM3DS_MPS2_DMAx->DMACC1Configuration = 0x00000000;
  CM3DS_MPS2_DMAx->DMACC0Configuration = 0x00000000;

  if (Channel != 0x0)//channel_1
  {
    CM3DS_MPS2_DMAx->DMACC1Configuration |= (Halt << 18) | (Lock << 16) | (ITC << 15) | (IE << 14);
  }
  else//channel_0
  {
    CM3DS_MPS2_DMAx->DMACC0Configuration |= (Halt << 18) | (Lock << 16) | (ITC << 15) | (IE << 14);
  }
}

/**
  *
  * @brief: DMA控制传输类型设置。
  *
  * @param: CM3DS_MPS2_DMAx,CM3只有1组DMA,只能设置为CM3DS_MPS2_DMA。
  * @param: Channel,使用哪个通道；可设置的值包括：Channel_0(0x00) - 通道0；Channel_1 (0x01) - 通道1。
  * @param: Flow_Control,控制传输类型，可设置的值包括：
  *						MtoM_DMA(0x0) - Memory-to-memory(Controller:DMA); MtoP_DMA(0x01) - Memory-to-peripheral(Controller:DMA);
  *						PtoM_DMA(0x02) - Peripheral-to-memory(Controller:DMA); SPtoDP_DMA(0x03) - Source peripheral-to-destination peripheral(Controller:DMA);
  *						SPtoDP_DP(0x04) - Source peripheral-to-destination peripheral(Controller:Destination peripheral);
  *						MtoP_P(0x05) - Memory-to-peripheral(Controller:Peripheral); PtoM_P(0x06) - Peripheral-to-memory(Controller:Peripheral);
  *						SPtoDP_SP(0x07) - Source peripheral-to-destination peripheral(Controller:Source peripheral)。
  *
  * @retVal: void
  */
void DMA_ChannelConfig_Flow(CM3DS_MPS2_DMA_TypeDef* CM3DS_MPS2_DMAx, uint8_t Channel, int Flow_Control)
{
  assert_param(IS_DMA_ALL_PERIPH(CM3DS_MPS2_DMAx));
  assert_param(IS_DMA_Channel(Channel));

  if (Channel != 0x0)//channel_1
  {
    CM3DS_MPS2_DMAx->DMACC1Configuration |= (Flow_Control << 11);
  }
  else//channel_0
  {
    CM3DS_MPS2_DMAx->DMACC0Configuration |= (Flow_Control << 11);
  }
}

/**
  *
  * @brief: 设置DMA目的地址外设和源地址外设并使能DMA通道。
  *
  * @param: CM3DS_MPS2_DMAx,CM3只有1组DMA,只能设置为CM3DS_MPS2_DMA。
  * @param: Channel,使用哪个通道；可设置的值包括：Channel_0(0x00) - 通道0；Channel_1 (0x01) - 通道1。
  * @param: DestPeri,目的地址外设；可设置的值包括：0x4-SPI0-TX; 0x5 -SPI0-RX; 0x6 -SPI1-TX; 0x7 -SPI1-RX。
  * @param: SrcPeri,源地址外设；可设置的值包括：0x4-SPI0-TX; 0x5 -SPI0-RX; 0x6 -SPI1-TX; 0x7 -SPI1-RX。
  * @param: EN,是否使能DMA通道；可设置的值包括：DMA_Dis(0x0) - 不使能；DMA_En(0x01) - 使能。
  *
  * @retVal: void
  */
void DMA_ChannelConfig_Peri(CM3DS_MPS2_DMA_TypeDef* CM3DS_MPS2_DMAx, uint8_t Channel, int DestPeri, int SrcPeri, int EN)
{
  assert_param(IS_DMA_ALL_PERIPH(CM3DS_MPS2_DMAx));
  assert_param(IS_DMA_Channel(Channel));
  if (Channel != 0x0)//channel_1
  {
    CM3DS_MPS2_DMAx->DMACC1Configuration |= (DestPeri << 6) | (SrcPeri << 1) | (EN << 0);
  }
  else//channel_0
  {
    CM3DS_MPS2_DMAx->DMACC0Configuration |= (DestPeri << 6) | (SrcPeri << 1) | (EN << 0);
  }
}

/**
  *
  * @brief: 等待DMA的传输通道空闲。
  *
  * @param: chnl,通道号,可设置的值包括：Channel_0(0x00) - 通道0；Channel_1 (0x01) - 通道1。
  *
  * @retVal: void
  */
void Wait_Channel_Free(int chnl)
{
  int busy = 1 << chnl;
  int read_data = 0;
  while (busy)
  {
    read_data = CM3DS_MPS2_DMA->DMACEnbldChns;
    busy = read_data & (1 << chnl);
  }
}

/**
  *
  * @brief: 设置外设SPI的DMA请求。
  *
  * @param: CM3DS_MPS2_SSPx,使用哪组SPI;CM3有2组SPI:CM3DS_MPS2_SSP0和CM3DS_MPS2_SSP1。
  * @param: TX_EN,SPI发送DMA使能；可设置的值包括：1- 使能；0- 不使能。
  * @param: RX_EN,SPI接收DMA使能；可设置的值包括：1- 使能；0- 不使能。
  *
  * @retVal: void
  */
void SSP_DMA_Request(CM3DS_MPS2_SSP_TypeDef* CM3DS_MPS2_SSPx, int TX_EN, int RX_EN)
{
  CM3DS_MPS2_SSPx->DMACR = 0x00000000;
  assert_param(IS_SSP_ALL_PERIPH(CM3DS_MPS2_SSPx));

  CM3DS_MPS2_SSPx->DMACR |= (TX_EN << 1) | (RX_EN << 0);
}

/**
  *
  * @brief: 设置链表传输的地址。
  *
  * @param: CM3DS_MPS2_DMAx,CM3只有1组DMA,只能设置为CM3DS_MPS2_DMA。
  * @param: DMACCxLLI,使用哪个链表；也就是使用哪个通道的链表；
  *						可设置的值包括：Channel_0(0x00) - 通道0；Channel_1 (0x01) - 通道1。
  * @param: LLL_Address,链表地址。
  *
  * @retVal: void
  */
void DMA_LLI_List_Item(CM3DS_MPS2_DMA_TypeDef* CM3DS_MPS2_DMAx, uint8_t DMACCxLLI, uint32_t LLL_Address)
{
  assert_param(IS_DMA_ALL_PERIPH(CM3DS_MPS2_DMAx));
  if (DMACCxLLI != 0x0)	//DMACC1LLI  0x128
  {
    CM3DS_MPS2_DMAx->DMACC1LLI |= LLL_Address;
  }
  else//DMACC0LLI  0x108
  {
    CM3DS_MPS2_DMAx->DMACC0LLI |= LLL_Address;
  }
}

/**
  *
  * @brief: DMA软件突发请求。
  *
  * @param: CM3DS_MPS2_DMAx,CM3只有1组DMA,只能设置为CM3DS_MPS2_DMA。
  * @param: Breq,突发源。
  *
  * @retVal: void
  */
void DMA_SoftwareBurstRequest(CM3DS_MPS2_DMA_TypeDef* CM3DS_MPS2_DMAx, uint16_t Breq)
{
  assert_param(IS_DMA_ALL_PERIPH(CM3DS_MPS2_DMAx));
  CM3DS_MPS2_DMAx->DMACSoftBReq = Breq;
}

/**
  *
  * @brief: DMA软件单次请求。
  *
  * @param: CM3DS_MPS2_DMAx,CM3只有1组DMA,只能设置为CM3DS_MPS2_DMA。
  * @param: Sreq,软件单次请求源。
  *
  * @retVal: void
  */
void DMA_SoftwareSingleRequest(CM3DS_MPS2_DMA_TypeDef* CM3DS_MPS2_DMAx, uint16_t Sreq)
{
  assert_param(IS_DMA_ALL_PERIPH(CM3DS_MPS2_DMAx));
  CM3DS_MPS2_DMAx->DMACSoftSReq = Sreq;
}

/**
  *
  * @brief: DMA软件最后一次突发请求。
  *
  * @param: CM3DS_MPS2_DMAx,CM3只有1组DMA,只能设置为CM3DS_MPS2_DMA。
  * @param: LBreq,突发源。
  *
  * @retVal: void
  */
void DMA_SoftwareLastBurstRequest(CM3DS_MPS2_DMA_TypeDef* CM3DS_MPS2_DMAx, uint16_t LBreq)
{
  assert_param(IS_DMA_ALL_PERIPH(CM3DS_MPS2_DMAx));
  CM3DS_MPS2_DMAx->DMACSoftLBReq = LBreq;
}

/**
  *
  * @brief: DMA软件最后一次单次请求。
  *
  * @param: CM3DS_MPS2_DMAx,CM3只有1组DMA,只能设置为CM3DS_MPS2_DMA。
  * @param: LSreq,软件单次请求源。
  *
  * @retVal: void
  */
void DMA_SoftwareLastSingleRequest(CM3DS_MPS2_DMA_TypeDef* CM3DS_MPS2_DMAx, uint16_t LSreq)
{
  assert_param(IS_DMA_ALL_PERIPH(CM3DS_MPS2_DMAx));
  CM3DS_MPS2_DMAx->DMACSoftLSReq = LSreq;
}
