/*---------Include---------*/
#include  "CM3DS_dualtimer.h"
#include  "CM3DS_rcc.h"

/**
  *
  * @brief: 将DualTimer配置初始化为默认配置。
  *
  * @param: CM3DS_MPS2_DUALTIMERx,设置为CM3DS_MPS2_DUALTIMER0。
  *
  * @retVal: void
  */
void DTIM_DeInit(CM3DS_MPS2_DUALTIMER_BOTH_TypeDef* CM3DS_MPS2_DUALTIMERx)
{
	assert_param(IS_DUALTIMER_ALL_PERIPH(CM3DS_MPS2_ADCx));

	if (CM3DS_MPS2_DUALTIMERx == CM3DS_MPS2_DUALTIMER0)
	{
		RCC_APB1PeriphResetCmd(RCC_APB1Periph_DTIMER0, ENABLE);
		RCC_APB1PeriphResetCmd(RCC_APB1Periph_DTIMER0, DISABLE);
	}
}

/**
  *
  * @brief: DualTimer初始化设置。
  *
  * @param: CM3DS_MPS2_DUALTIMERx,设置为CM3DS_MPS2_DUALTIMER0。
  * @param: DTIM,双定时器下的哪个定时器,双定时器共有两个定时器可供选择,DTIM_DUALTIMER0_1或DTIM_DUALTIMER0_2。
  * @param: DTIM_SIZE,选择16位或者32位的计数器，取值为DTIM_SIZE_16bit或DTIM_SIZE_32bit。
  * @param: DTIM_TIMERPRE,时钟分频系数,取值为DTIM_TIMERPRE_1或DTIM_TIMERPRE_16或DTIM_TIMERPRE_256。
  * @param: LOAD,定时器初始加载值。
  *
  * @retVal: void
  */
void DTIM_Init(CM3DS_MPS2_DUALTIMER_BOTH_TypeDef* CM3DS_MPS2_DUALTIMERx, uint32_t DTIM, uint32_t DTIM_SIZE, uint32_t DTIM_TIMERPRE, uint32_t LOAD)
{
	uint32_t read0, read1;
	assert_param(IS_DUALTIMER_ALL_PERIPH(CM3DS_MPS2_ADCx));
	assert_param(IS_DTIM_CLOCK_SEQUENCE(DTIM));
	assert_param(IS_DTIM_TIMER_SIZE(SIZE));
	assert_param(IS_DTIM_TIMER_PRE(PRE));

	CM3DS_MPS2_DUALTIMERx->Timer1Control = 0;
	CM3DS_MPS2_DUALTIMERx->Timer2Control = 0;
	if (DTIM == DTIM_DUALTIMER0_1)
	{
		read0 = CM3DS_MPS2_DUALTIMERx->Timer1Control;
		CM3DS_MPS2_DUALTIMERx->Timer1Control = read0 | DTIM_SIZE | DTIM_TIMERPRE;
		CM3DS_MPS2_DUALTIMERx->Timer1Load = LOAD;
		//CM3DS_MPS2_DUALTIMERx->Timer1BGLoad  = BGLOAD;
	}
	else if (DTIM == DTIM_DUALTIMER0_2)
	{
		read1 = CM3DS_MPS2_DUALTIMERx->Timer2Control;
		CM3DS_MPS2_DUALTIMERx->Timer2Control = read1 | DTIM_SIZE | DTIM_TIMERPRE;
		CM3DS_MPS2_DUALTIMERx->Timer2Load = LOAD;
		//CM3DS_MPS2_DUALTIMERx->Timer2BGLoad  = BGLOAD;
	}
}

/**
  *
  * @brief: DualTimer工作模式设置。
  *
  * @param: CM3DS_MPS2_DUALTIMERx,设置为CM3DS_MPS2_DUALTIMER0。
  * @param: DTIM,双定时器下的哪个定时器,双定时器共有两个定时器可供选择,DTIM_DUALTIMER0_1或DTIM_DUALTIMER0_2。
  * @param: DTIM_MODE,工作模式；
  * 					可设置的值包括：
  *							DTIM_MODE_ONE_SHOT_COUNT - 单次计时模式；
  *							DTIM_MODE_FREE_RUNNING - 自由运行模式；
  *							DTIM_MODE_PERIODIC - 周期计时模式。
  *
  * @retVal: void
  */
void DTIM_MODE(CM3DS_MPS2_DUALTIMER_BOTH_TypeDef* CM3DS_MPS2_DUALTIMERx, uint32_t DTIM, uint32_t DTIM_MODE)
{
	uint32_t read2, read3;
	assert_param(IS_DUALTIMER_ALL_PERIPH(CM3DS_MPS2_TIMERx));
	assert_param(IS_DTIM_CLOCK_SEQUENCE(DTIM));
	assert_param(IS_DTIM_WORK_MODE(DTIM_MODE));
	if (DTIM == DTIM_DUALTIMER0_1)
	{
		read2 = CM3DS_MPS2_DUALTIMERx->Timer1Control;
		CM3DS_MPS2_DUALTIMERx->Timer1Control = read2 | DTIM_MODE;
	}
	else if (DTIM == DTIM_DUALTIMER0_2)
	{
		read3 = CM3DS_MPS2_DUALTIMERx->Timer1Control;
		CM3DS_MPS2_DUALTIMERx->Timer2Control = read3 | DTIM_MODE;
	}
}

/**
  *
  * @brief: DualTimer使能设置。
  *
  * @param: CM3DS_MPS2_DUALTIMERx,设置为CM3DS_MPS2_DUALTIMER0。
  * @param: DTIM,双定时器下的哪个定时器,双定时器共有两个定时器可供选择,DTIM_DUALTIMER0_1或DTIM_DUALTIMER0_2。
  * @param: NewState,是否使能DualTimer;ENABLE：使能， DISABLE：不使能。
  *
  * @retVal: void
  */
void DTIM_START(CM3DS_MPS2_DUALTIMER_BOTH_TypeDef* CM3DS_MPS2_DUALTIMERx, uint32_t DTIM, FunctionalState NewState)
{
	uint32_t read4, read5;
	assert_param(IS_DUALTIMER_ALL_PERIPH(CM3DS_MPS2_TIMERx));
	assert_param(IS_DTIM_CLOCK_SEQUENCE(DTIM));
	assert_param(IS_FUNCTIONAL_STATE(NewState));

	if ((DTIM == DTIM_DUALTIMER0_1) && (NewState != DISABLE))
	{
		read4 = CM3DS_MPS2_DUALTIMERx->Timer1Control;
		CM3DS_MPS2_DUALTIMERx->Timer1Control = read4 | (0x1ul << CM3DS_MPS2_DUALTIMER1_CTRL_EN_Pos);
	}
	else if ((DTIM == DTIM_DUALTIMER0_2) && (NewState != DISABLE))
	{
		read5 = CM3DS_MPS2_DUALTIMERx->Timer2Control;
		CM3DS_MPS2_DUALTIMERx->Timer2Control = read5 | (0x1ul << CM3DS_MPS2_DUALTIMER1_CTRL_EN_Pos);
	}
	else
	{
		//read4 = CM3DS_MPS2_DUALTIMERx->Timer1Control;
		//read5 = CM3DS_MPS2_DUALTIMERx->Timer2Control;
		CM3DS_MPS2_DUALTIMERx->Timer1Control &= ~CM3DS_MPS2_DUALTIMER_CTRL_EN_Msk;
		CM3DS_MPS2_DUALTIMERx->Timer2Control &= ~CM3DS_MPS2_DUALTIMER_CTRL_EN_Msk;

	}
}

/**
  *
  * @brief: 设置DualTimer的重新加载值。
  *
  * @param: CM3DS_MPS2_DUALTIMERx,设置为CM3DS_MPS2_DUALTIMER0。
  * @param: DTIM,双定时器下的哪个定时器,双定时器共有两个定时器可供选择,DTIM_DUALTIMER0_1或DTIM_DUALTIMER0_2。
  * @param: BGLOAD,重新加载值。
  *
  * @retVal: void
  */
void DTIM_SetBGLOAD(CM3DS_MPS2_DUALTIMER_BOTH_TypeDef* CM3DS_MPS2_DUALTIMERx, uint32_t DTIM, uint32_t BGLOAD)
{
	assert_param(IS_DUALTIMER_ALL_PERIPH(CM3DS_MPS2_TIMERx));
	assert_param(IS_DTIM_CLOCK_SEQUENCE(DTIM));

	if (DTIM == DTIM_DUALTIMER0_1)
	{
		CM3DS_MPS2_DUALTIMERx->Timer1BGLoad = BGLOAD;
	}
	else if (DTIM == DTIM_DUALTIMER0_2)
	{
		CM3DS_MPS2_DUALTIMERx->Timer2BGLoad = BGLOAD;
	}
}

/**
  *
  * @brief: DualTimer中断设置。
  *
  * @param: CM3DS_MPS2_DUALTIMERx,设置为CM3DS_MPS2_DUALTIMER0。
  * @param: DTIM,双定时器下的哪个定时器,双定时器共有两个定时器可供选择,DTIM_DUALTIMER0_1或DTIM_DUALTIMER0_2。
  * @param: NewState,是否使能DualTimer中断;ENABLE：使能， DISABLE：不使能。
  *
  * @retVal: void
  */
void DTIM_ITConfig(CM3DS_MPS2_DUALTIMER_BOTH_TypeDef* CM3DS_MPS2_DUALTIMERx, uint32_t DTIM, FunctionalState NewState)
{
	/*Check the parameters*/
	uint32_t temp0, temp1;
	assert_param(IS_DUALTIMER_ALL_PERIPH(CM3DS_MPS2_TIMERx));
	assert_param(IS_DTIM_CLOCK_SEQUENCE(DTIM));
	assert_param(IS_FUNCTIONAL_STATE(NewState));

	if ((DTIM == DTIM_DUALTIMER0_1) && (NewState != DISABLE))
	{
		temp0 = CM3DS_MPS2_DUALTIMERx->Timer1Control;
		CM3DS_MPS2_DUALTIMERx->Timer1Control = temp0 | (0x1ul << CM3DS_MPS2_DUALTIMER1_CTRL_INTEN_Pos);
	}
	else if ((DTIM == DTIM_DUALTIMER0_2) && (NewState != DISABLE))
	{
		temp1 = CM3DS_MPS2_DUALTIMERx->Timer2Control;
		CM3DS_MPS2_DUALTIMERx->Timer2Control = temp1 | (0x1ul << CM3DS_MPS2_DUALTIMER2_CTRL_INTEN_Pos);
	}
	else
	{
		temp0 = CM3DS_MPS2_DUALTIMER0->Timer1Control;
		temp1 = CM3DS_MPS2_DUALTIMER0->Timer2Control;
		CM3DS_MPS2_DUALTIMERx->Timer1Control = temp0 | (0x0ul << CM3DS_MPS2_DUALTIMER1_CTRL_INTEN_Pos);
		CM3DS_MPS2_DUALTIMERx->Timer2Control = temp1 | (0x0ul << CM3DS_MPS2_DUALTIMER2_CTRL_INTEN_Pos);
	}
}

/**
  *
  * @brief: 清除DualTimer中断。
  *
  * @param: CM3DS_MPS2_DUALTIMERx,设置为CM3DS_MPS2_DUALTIMER0。
  * @param: DTIM,双定时器下的哪个定时器,双定时器共有两个定时器可供选择,DTIM_DUALTIMER0_1或DTIM_DUALTIMER0_2。
  * @param: NewState,是否清除DualTimer中断;ENABLE：清除， DISABLE：不清除。
  *
  * @retVal: void
  */
void DTIM_ClearIT(CM3DS_MPS2_DUALTIMER_BOTH_TypeDef* CM3DS_MPS2_DUALTIMERx, uint32_t DTIM, FunctionalState NewState)
{
	uint32_t temp2, temp3;
	assert_param(IS_DUALTIMER_ALL_PERIPH(CM3DS_MPS2_TIMERx));
	assert_param(IS_DTIM_CLOCK_SEQUENCE(DTIM));

	temp2 = CM3DS_MPS2_DUALTIMERx->Timer1IntClr;
	temp3 = CM3DS_MPS2_DUALTIMERx->Timer2IntClr;
	if ((DTIM == DTIM_DUALTIMER0_1) && (NewState != DISABLE))
	{
		CM3DS_MPS2_DUALTIMERx->Timer1IntClr = temp2 | (0x1ul << CM3DS_MPS2_DUALTIMER1_INTCLR_Pos);
	}
	else if ((DTIM == DTIM_DUALTIMER0_2) && (NewState != DISABLE))
	{
		CM3DS_MPS2_DUALTIMERx->Timer2IntClr = temp3 | (0x1ul << CM3DS_MPS2_DUALTIMER1_INTCLR_Pos);
	}
	else
	{
		CM3DS_MPS2_DUALTIMERx->Timer1IntClr = temp2;
		CM3DS_MPS2_DUALTIMERx->Timer2IntClr = temp3;
	}
}

/**
  *
  * @brief: 查看DualTimer计数器当前值。
  *
  * @param: CM3DS_MPS2_DUALTIMERx,设置为CM3DS_MPS2_DUALTIMER0。
  * @param: DTIM,双定时器下的哪个定时器,双定时器共有两个定时器可供选择,DTIM_DUALTIMER0_1或DTIM_DUALTIMER0_2。
  *
  * @retVal: value,获取到的计数器当前值。
  */
uint32_t DTIM_Timer0CurrentValue(CM3DS_MPS2_DUALTIMER_BOTH_TypeDef* CM3DS_MPS2_DUALTIMERx, uint32_t DTIM)
{
	uint32_t value = 0;
	assert_param(IS_DUALTIMER_ALL_PERIPH(CM3DS_MPS2_TIMERx));
	assert_param(IS_DTIM_CLOCK_SEQUENCE(DTIM));

	if (DTIM == DTIM_DUALTIMER0_1)
	{
		value = CM3DS_MPS2_DUALTIMERx->Timer1Value;
	}
	else if (DTIM == DTIM_DUALTIMER0_2)
	{
		value = CM3DS_MPS2_DUALTIMERx->Timer2Value;
	}
	return value;
}

/**
  *
  * @brief: 获取DualTimer原始中断状态。
  *
  * @param: CM3DS_MPS2_DUALTIMERx,设置为CM3DS_MPS2_DUALTIMER0。
  * @param: DTIM,双定时器下的哪个定时器,双定时器共有两个定时器可供选择,DTIM_DUALTIMER0_1或DTIM_DUALTIMER0_2。
  *
  * @retVal: RIS,获取到的原始中断状态。
  */
uint32_t DTIM_Timer0RISValue(CM3DS_MPS2_DUALTIMER_BOTH_TypeDef* CM3DS_MPS2_DUALTIMERx, uint32_t DTIM)
{
	uint32_t RIS = 0;
	assert_param(IS_DUALTIMER_ALL_PERIPH(CM3DS_MPS2_TIMERx));
	assert_param(IS_DTIM_CLOCK_SEQUENCE(DTIM));

	if (DTIM == DTIM_DUALTIMER0_1)
	{
		RIS = CM3DS_MPS2_DUALTIMERx->Timer1RIS;
	}
	else if (DTIM == DTIM_DUALTIMER0_2)
	{
		RIS = CM3DS_MPS2_DUALTIMERx->Timer2RIS;
	}
	return RIS;
}

/**
  *
  * @brief: 获取DualTimer中断寄存器状态。
  *
  * @param: CM3DS_MPS2_DUALTIMERx,设置为CM3DS_MPS2_DUALTIMER0。
  * @param: DTIM,双定时器下的哪个定时器,双定时器共有两个定时器可供选择，DTIM_DUALTIMER0_1或DTIM_DUALTIMER0_2。
  *
  * @retVal: MIS,获取到的中断寄存器状态。
  */
uint32_t DTIM_Timer0MISValue(CM3DS_MPS2_DUALTIMER_BOTH_TypeDef* CM3DS_MPS2_DUALTIMERx, uint32_t DTIM)
{
	uint32_t MIS = 0;
	assert_param(IS_DUALTIMER_ALL_PERIPH(CM3DS_MPS2_TIMERx));
	assert_param(IS_DTIM_CLOCK_SEQUENCE(DTIM));

	if (DTIM == DTIM_DUALTIMER0_1)
	{
		MIS = CM3DS_MPS2_DUALTIMERx->Timer1MIS;

	}
	else if (DTIM == DTIM_DUALTIMER0_2)
	{
		MIS = CM3DS_MPS2_DUALTIMERx->Timer2MIS;
	}
	return MIS;
}

