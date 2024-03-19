
/*---------Include---------*/
#include "CM3DS_adc.h"
#include "CM3DS_rcc.h"


//volatile uint16_t ADC_Value;

/** @defgroup ADC_Private_Defines
  * @{
  */

  /* CR1 register Mask */
#define CR1_CLEAR_Mask              ((uint32_t)0xFFFFFFFD)

/*CR2 register Mask*/
#define CR2_CLEAR_Mask	            ((uint32_t)0xFFFFFFC5)

/*CSR1 register Mask*/
#define CSR1_CLEAR_Mask            ((uint8_t)0x00)\

/* ADC Software start mask */
#define CR1_EXTTRIG_ADON_Set     ((uint32_t)0x00000001)
#define CR1_EXTTRIG_ADON_Reset   ((uint32_t)0xFFFFFFFE)

/* ADC SWSTART mask */
#define CR1_ADON_Set             ((uint32_t)0x00400000)


/**
  *
  * @brief: 将ADC初始化为默认配置。
  *
  * @param: CM3DS_MPS2_ADCx,使用哪组ADC,CM3只有一组ADC,该参数只能设置为 CM3DS_MPS2_ADC。
  *
  * @retVal: void
  */
void ADC_DeInit(CM3DS_MPS2_ADC_TypeDef* CM3DS_MPS2_ADCx)
{
	/*Check the parameters*/
	assert_param(IS_ADC_ALL_PERIPH(CM3DS_MPS2_ADCx));

	if (CM3DS_MPS2_ADCx == CM3DS_MPS2_ADC)
	{
		RCC_APB1PeriphResetCmd(RCC_APB1Periph_ADC, ENABLE);
		RCC_APB1PeriphResetCmd(RCC_APB1Periph_ADC, DISABLE);
	}
}


/**
  *
  * @brief: ADC转换通道选择。
  *
  * @param: CM3DS_MPS2_ADCx,使用哪组ADC,CM3只有一组ADC,该参数只能设置为CM3DS_MPS2_ADC。
  * @param: Channel,选择的转换通道；可设置的值包括Channel_0(0x0)和Channel_1(0x01);
  *					CM3的ADC转换通道软件上可以选8个通道，即Channel_0~Channel_7;但是硬件上只向外连接了两个通道，
  *					且连接到了固定的IO口(R1和P2)，无需再手动绑定；因此通道只能设置为Channel_0(0x0)或Channel_1(0x01)。
  *
  * @retVal: void
  */
void ADC_Channel_Select(CM3DS_MPS2_ADC_TypeDef* CM3DS_MPS2_ADCx, uint8_t Channel)
{
	uint8_t temp;
	assert_param(IS_ADC_ALL_PERIPH(CM3DS_MPS2_ADCx));
	assert_param(IS_ADC_CHANNEL(Channel));

	temp = Channel & 0x01;
	if (temp != 0x1)
	{
		CM3DS_MPS2_ADCx->ADC_CSR_1 = 0x0;
	}
	else
	{
		CM3DS_MPS2_ADCx->ADC_CSR_1 = 0x1;
	}
}

/**
  *
  * @brief: ADC初始化设置。
  *
  * @param: CM3DS_MPS2_ADCx,使用哪组ADC,CM3只有一组ADC,该参数只能设置为CM3DS_MPS2_ADC。
  * @param: ADC_InitStruct,ADC设置参数结构体变量，该结构体变量包括时钟分频系数、转换模式（连续或单次）、
  *							上电、数据缓冲、溢出标志、外部触发、触发类型、数据对齐方式、扫描模式。
  *
  * @retVal: void
  */
void ADC_Init(CM3DS_MPS2_ADC_TypeDef* CM3DS_MPS2_ADCx, ADC_InitTypeDef* ADC_InitStruct)
{
	/*Check the parameters*/
	assert_param(IS_ADC_ALL_PERIPH(CM3DS_MPS2_ADCx));
	assert_param(IS_ADC_Freq_Clk(SPSEL));
	assert_param(IS_ADC_TRANSFOR_MODE(CONT));
	assert_param(IS_ADC_Converter_ADON(ADON));
	assert_param(IS_ADC_External_TrigConv(EXTTRIG));
	assert_param(IS_ADC_DATA_ALIGN(DataAlign));
	assert_param(IS_ADC_EXT_INJEC_TRIG(EXTSEL));
	assert_param(IS_ADC_ScanConv_Mode(ScanMode));
	assert_param(IS_ADC_Data_buffer(DBUF));
	assert_param(IS_ADC_Overrun_flag(OVR));

	/*-------------------------------ADC_CR_1-----------------------------*/
	CM3DS_MPS2_ADCx->ADC_CR_1 = ((ADC_InitStruct->Clock) << 4)
		| ((ADC_InitStruct->Transfor_mode) << 1)
		| ((ADC_InitStruct->Converter_adon) << 0);
	/*------------------------------ADC_CR_2_3----------------------------*/
	CM3DS_MPS2_ADCx->ADC_CR_2_3 = (((ADC_InitStruct->Data_buffer) << 17)
		| ((ADC_InitStruct->Overrun_flag) << 16)
		| ((ADC_InitStruct->Ext_trig) << 6)
		| ((ADC_InitStruct->Ext_sel) << 4)
		| ((ADC_InitStruct->Data_align) << 3)
		| ((ADC_InitStruct->ScanConvMode) << 1));
}


/**
  *
  * @brief: 启动ADC转换。
  *
  * @param: void
  *
  * @retVal: void
  */
void ADC_StartConversion(void)
{
	CM3DS_MPS2_ADC->ADC_CR_1 |= (1 << 0);//ADON Write 1
}


/**
  *
  * @brief: 停止ADC转换。
  *
  * @param: void
  *
  * @retVal: void
  */
void ADC_StopConversion(void)
{
	CM3DS_MPS2_ADC->ADC_CR_1 &= ~(1 << 0);//ADON Write 0

}

/**
  *
  * @brief: ADC中断配置，在ADC转换结束时是否产生中断。
  *
  * @param: CM3DS_MPS2_ADCx,使用哪组ADC,CM3只有一组ADC,该参数只能设置为CM3DS_MPS2_ADC。
  * @param: NewState,是否使能中断，ENABLE - 使能中断；DISABLE - 不使能中断。
  *
  * @retVal: void
  */
void ADC_ITConfig(CM3DS_MPS2_ADC_TypeDef* CM3DS_MPS2_ADCx, FunctionalState NewState)
{
	/*Check the parameters*/
	assert_param(IS_ADC_ALL_PERIPH(CM3DS_MPS2_ADCx));
	assert_param(IS_FUNCTIONAL_STATE(NewState));

	if (NewState != DISABLE)
	{
		CM3DS_MPS2_ADCx->ADC_CSR_0 = (0x1 << 1);
	}
	else
	{
		CM3DS_MPS2_ADCx->ADC_CSR_0 = (0x0 << 1);
	}
}


/**
  *
  * @brief: 读取ADC采样数据(单次或非缓冲连续模式时),单次或非缓冲连续模式下，ADC转换的值存储在ADC_DR寄存器中。
  *
  * @param: CM3DS_MPS2_ADCx,使用哪组ADC,CM3只有一组ADC,该参数只能设置为CM3DS_MPS2_ADC。
  *
  * @retVal: Value3,读取到的ADC采样数据。
  */
uint16_t ADC_GetValueFromDR(CM3DS_MPS2_ADC_TypeDef* CM3DS_MPS2_ADCx)
{
	volatile uint32_t temp3;
	uint32_t temp4 = 0x0000FFFF;
	uint16_t Value3 = 0x0000;
	/*Check the parameters*/
	assert_param(IS_ADC_ALL_PERIPH(CM3DS_MPS2_ADCx));

	temp3 = CM3DS_MPS2_ADCx->ADC_DR;
	Value3 = temp4 & temp3;
	return Value3;
}

/**
  *
  * @brief: 读取ADC采样数据(数据缓冲模式时),在开启数据缓冲模式下，ADC 转换的值存储在ADC_DBR_x 寄存器中。
  *
  * @param: CM3DS_MPS2_ADCx,使用哪组ADC,CM3只有一组ADC,该参数只能设置为CM3DS_MPS2_ADC。
  * @param: ADC_buf,存储ADC采样数据的缓存。
  *
  * @retVal: void
  */
void ADC_GetValueFromDBR(CM3DS_MPS2_ADC_TypeDef* CM3DS_MPS2_ADCx, uint32_t* ADC_buf)
{
	int num = 0;

	ADC_buf[num * 4 + 0] = CM3DS_MPS2_ADCx->ADC_DBR_1_0;
	ADC_buf[num * 4 + 1] = CM3DS_MPS2_ADCx->ADC_DBR_3_2;
	ADC_buf[num * 4 + 2] = CM3DS_MPS2_ADCx->ADC_DBR_5_4;
	ADC_buf[num * 4 + 3] = CM3DS_MPS2_ADCx->ADC_DBR_7_6;
	num++;
	while (num == 7);
}

/**
  *
  * @brief: 外部触发ADC启动设置。
  *
  * @param: CM3DS_MPS2_ADCx,使用哪组ADC,CM3只有一组ADC,该参数只能设置为CM3DS_MPS2_ADC。
  * @param: ADC_ExternalTrigInjecConv,设置的外部触发事件；
  * 							可设置的值包括：EXTSEL_Timer0(0x0) - 内部TRGO事件，连接到定时器0中断；
  *												EXTSEL_Pin (0x01) - ADC_ETR管脚上的中断。
  *
  * @retVal: void
  */
void ADC_ExternalTrigInjectedConvConfig(CM3DS_MPS2_ADC_TypeDef* CM3DS_MPS2_ADCx, uint32_t ADC_ExternalTrigInjecConv)
{
	uint32_t temp4;
	assert_param(IS_ADC_ALL_PERIPH(CM3DS_MPS2_ADCx));
	assert_param(IS_ADC_EXT_INJEC_TRIG(ADC_ExternalTrigInjecConv));

	temp4 = CM3DS_MPS2_ADCx->ADC_CR_2_3;

	CM3DS_MPS2_ADCx->ADC_CR_2_3 = temp4 | (ADC_ExternalTrigInjecConv << 4);
}

/**
  *
  * @brief: 清除ADC中断。
  *
  * @param: CM3DS_MPS2_ADCx,使用哪组ADC,CM3只有一组ADC,该参数只能设置为CM3DS_MPS2_ADC。
  *
  * @retVal: void
  */
void ADC_EXTI_ClearFlag(CM3DS_MPS2_ADC_TypeDef* CM3DS_MPS2_ADCx)
{
	assert_param(IS_ADC_ALL_PERIPH(CM3DS_MPS2_ADCx));
	CM3DS_MPS2_ADCx->ADC_CSR_0 = ~(1 << 0);
}


FlagStatus ADC_GetSoftwareStartConvStatus(CM3DS_MPS2_ADC_TypeDef* CM3DS_MPS2_ADCx)
{
	FlagStatus bitStatus = RESET;

	/*Check the parameters*/
	assert_param(IS_ADC_ALL_PERIPH(CM3DS_MPS2_ADCx));

	/* Check the status of ADON bit */
	if ((CM3DS_MPS2_ADCx->ADC_CR_1 & CR1_ADON_Set) != (uint32_t)RESET)
	{
		/* ADON bit is set */
		bitStatus = SET;
	}
	else
	{
		/* ADON bit is reset */
		bitStatus = RESET;
	}

	/* Return the ADON bit status */
	return bitStatus;

}




