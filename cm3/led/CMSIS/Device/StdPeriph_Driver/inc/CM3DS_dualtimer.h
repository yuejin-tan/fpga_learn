#ifndef __CM3DS_DUALTIMER_H
#define __CM3DS_DUALTIMER_H

#ifdef __cplusplus
extern "C" {
#endif

    /* Includes ------------------------------------------------------------------*/
#include "CM3DS_MPS2.h"

    typedef struct
    {
        uint32_t  DTIM_Ctrl;
        uint32_t  DTIM_Load;
        uint32_t  DTIM_BGLoad;

    } DTIM_TimeBaseInitTypeDef;



#define IS_DUALTIMER_ALL_PERIPH(PERIPH) (((PERIPH) == CM3DS_MPS2_DUALTIMER0));	


#define DTIM_SIZE_32bit                     (0x1ul << CM3DS_MPS2_DUALTIMER1_CTRL_SIZE_Pos) 
#define DTIM_SIZE_16bit                     (0x0ul << CM3DS_MPS2_DUALTIMER1_CTRL_SIZE_Pos)
#define IS_DTIM_TIMER_SIZE(SIZE) 	 (((SIZE) == DTIM_SIZE_32bit) || \
                                   (( SIZE) == DTIM_SIZE_16bit))	


#define DTIM_TIMERPRE_1                 	  (0x00ul << CM3DS_MPS2_DUALTIMER1_CTRL_PRESCALE_Pos) 
#define DTIM_TIMERPRE_16                  	(0x01ul << CM3DS_MPS2_DUALTIMER1_CTRL_PRESCALE_Pos)
#define DTIM_TIMERPRE_256                   (0x10ul << CM3DS_MPS2_DUALTIMER1_CTRL_PRESCALE_Pos)
#define IS_DTIM_TIMER_PRE(PRE) 	   (((PRE) == DTIM_TIMERPRE_1) || \
																		(((PRE) == DTIM_TIMERPRE_16) || \
                                   (( PRE) == DTIM_TIMERPRE_256))	



#define DTIM_DUALTIMER0_1                   ((uint32_t)0x0000FFFF)
#define DTIM_DUALTIMER0_2                  	((uint32_t)0xFFFFFFFF)
#define IS_DTIM_CLOCK_SEQUENCE(SEQUENCE) (((SEQUENCE) == DTIM_DUALTIMER0_1) || \
																				 (( SEQUENCE) == DTIM_DUALTIMER0_2))	 


#define DTIM_MODE_ONE_SHOT_COUNT						(0x1ul << CM3DS_MPS2_DUALTIMER1_CTRL_ONESHOOT_Pos)
#define DTIM_MODE_FREE_RUNNING							(0x0ul << CM3DS_MPS2_DUALTIMER1_CTRL_MODE_Pos)
#define DTIM_MODE_PERIODIC									(0x1ul << CM3DS_MPS2_DUALTIMER1_CTRL_MODE_Pos)
#define IS_DTIM_WORK_MODE(MODE) 	(((MODE) == DTIM_MODE_ONE_SHOT_COUNT) || \
																   ((MODE) == DTIM_MODE_FREE_RUNNING) || \
																	(( MODE) == DTIM_MODE_PERIODIC))	  



    void DTIM_Init(CM3DS_MPS2_DUALTIMER_BOTH_TypeDef* CM3DS_MPS2_DUALTIMERx, uint32_t DTIM, uint32_t DTIM_SIZE, uint32_t DTIM_TIMERPRE, uint32_t LOAD);
    void DTIM_DeInit(CM3DS_MPS2_DUALTIMER_BOTH_TypeDef* CM3DS_MPS2_DUALTIMERx);
    void DTIM_ITConfig(CM3DS_MPS2_DUALTIMER_BOTH_TypeDef* CM3DS_MPS2_DUALTIMERx, uint32_t DTIM, FunctionalState NewState);
    void DTIM_ClearIT(CM3DS_MPS2_DUALTIMER_BOTH_TypeDef* CM3DS_MPS2_DUALTIMERx, uint32_t DTIM, FunctionalState NewState);
    void DTIM_MODE(CM3DS_MPS2_DUALTIMER_BOTH_TypeDef* CM3DS_MPS2_DUALTIMERx, uint32_t DTIM, uint32_t DTIM_MODE);

    uint32_t DTIM_Timer0CurrentValue(CM3DS_MPS2_DUALTIMER_BOTH_TypeDef* CM3DS_MPS2_DUALTIMERx, uint32_t DTIM);
    uint32_t DTIM_Timer0RISValue(CM3DS_MPS2_DUALTIMER_BOTH_TypeDef* CM3DS_MPS2_DUALTIMERx, uint32_t DTIM);
    uint32_t DTIM_Timer0MISValue(CM3DS_MPS2_DUALTIMER_BOTH_TypeDef* CM3DS_MPS2_DUALTIMERx, uint32_t DTIM);
    void DTIM_SetBGLOAD(CM3DS_MPS2_DUALTIMER_BOTH_TypeDef* CM3DS_MPS2_DUALTIMERx, uint32_t DTIM, uint32_t BGLOAD);
    void DTIM_START(CM3DS_MPS2_DUALTIMER_BOTH_TypeDef* CM3DS_MPS2_DUALTIMERx, uint32_t DTIM, FunctionalState NewState);

#ifdef __cplusplus
}
#endif

#endif /* __CM3DS_DUALTIMER_H */

