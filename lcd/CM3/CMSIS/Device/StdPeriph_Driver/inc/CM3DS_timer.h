#ifndef __CM3DS_TIMER_H
#define __CM3DS_TIMER_H

#ifdef __cplusplus
extern "C" {
#endif

  /* Includes ------------------------------------------------------------------*/
#include "CM3DS_MPS2.h"


/**
  * @brief  TIM Time Base Init structure definition
  * @note   This structure is used with all TIMx except for TIM6 and TIM7.
  */

  typedef struct
  {
    uint32_t TIM_Value;
    uint32_t TIM_Reload;
    uint8_t  TIM_Ctrl;

  } TIM_TimeBaseInitTypeDef;

#define TIM_ENABLE                       					 (0x1)
#define TIM_EXTERNAL_INPUT_AS_ENABLE               (0x2)
#define TIM_EXTERNAL_INPUT_AS_CLOCK                (0x4)
#define TIM_INTERRUPT_ENABLE                			 (0x8)
#define IS_TIME_CTRL_SET(SET) 		(	((SET) == TIM_ENABLE) || \
																		((SET) == TIM_EXTERNAL_INPUT_AS_ENABLE) || \
																		((SET) == TIM_EXTERNAL_INPUT_AS_CLOCK) || \
																		((SET) == TIM_INTERRUPT_ENABLE))

  /** @defgroup TIM_Exported_constants
    * @{
    */

#define IS_TIM_ALL_PERIPH(PERIPH)  (((PERIPH) == CM3DS_MPS2_TIMER0 ) ||((PERIPH) == CM3DS_MPS2_TIMER0))

    /** @defgroup TIM_Exported_Functions
      * @{
      */
  void TIM_DeInit(CM3DS_MPS2_TIMER_TypeDef* CM3DS_MPS2_TIMERx);
  void TIM_TimeBaseStructInit(TIM_TimeBaseInitTypeDef* TIM_TimeBaseInitStruct);
  void TIM_TimeBaseInit(CM3DS_MPS2_TIMER_TypeDef* CM3DS_MPS2_TIMERx, TIM_TimeBaseInitTypeDef* TIM_TimeBaseInitStruct);

  void TIM_CtrlCmd(CM3DS_MPS2_TIMER_TypeDef* CM3DS_MPS2_TIMERx, uint8_t mode, FunctionalState NewState);

  ITStatus TIM_GetITStatus(CM3DS_MPS2_TIMER_TypeDef* CM3DS_MPS2_TIMERx);
  void TIM_ClearIT(CM3DS_MPS2_TIMER_TypeDef* CM3DS_MPS2_TIMERx);

  /**
    * @}
    */

#ifdef __cplusplus
}
#endif

#endif /* __CM3DS_TIMER_H */

