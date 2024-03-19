#ifndef __CM3DS_WATCHDOG_H
#define __CM3DS_WATCHDOG_H

#ifdef __cplusplus
extern "C" {
#endif 

#include "CM3DS_MPS2.h"


#define IS_WatchDog_ALL_PERIPH(PERIPH)  ((PERIPH) == CM3DS_MPS2_WATCHDOG))


#define RESEN_Enable                			 1
#define RESEN_Disable               			 0
#define IS_RESEN(RESEN) 					(((RESEN) == RESEN_Enable ) || \
															     ((RESEN) == RESEN_Disable ))

#define INTEN_Enable            					 1
#define INTEN_Disable           					 0
#define IS_INTEN(INTEN) 				 (((INTEN) ==  RESEN_Enable ) || \
															    ((INTEN) ==  RESEN_Disable ))


	void WatchDog_LOAD(CM3DS_MPS2_WATCHDOG_TypeDef* CM3DS_MPS2_WATCHDOGx, uint32_t wdogload);
	uint32_t WatchDog_VALUE(CM3DS_MPS2_WATCHDOG_TypeDef* CM3DS_MPS2_WATCHDOGx);
	void WatchDog_CTRL(CM3DS_MPS2_WATCHDOG_TypeDef* CM3DS_MPS2_WATCHDOGx, int resen, int wdgen_inten);
	void WatchDog_INTCLR(CM3DS_MPS2_WATCHDOG_TypeDef* CM3DS_MPS2_WATCHDOGx);
	void WatchDog_UNLOCK(CM3DS_MPS2_WATCHDOG_TypeDef* CM3DS_MPS2_WATCHDOGx);
	void WatchDog_LOCK(CM3DS_MPS2_WATCHDOG_TypeDef* CM3DS_MPS2_WATCHDOGx);

	uint32_t WatchDog_RAWINTSTAT(CM3DS_MPS2_WATCHDOG_TypeDef* CM3DS_MPS2_WATCHDOGx);
	uint32_t WatchDog_MASKINTSTAT(CM3DS_MPS2_WATCHDOG_TypeDef* CM3DS_MPS2_WATCHDOGx);
	void WatchDog_Test_Control(CM3DS_MPS2_WATCHDOG_TypeDef* CM3DS_MPS2_WATCHDOGx, FunctionalState NewState);
	void WatchDog_ITOP(CM3DS_MPS2_WATCHDOG_TypeDef* CM3DS_MPS2_WATCHDOGx, int value1, int value0);


#ifdef __cplusplus
}
#endif

#endif

