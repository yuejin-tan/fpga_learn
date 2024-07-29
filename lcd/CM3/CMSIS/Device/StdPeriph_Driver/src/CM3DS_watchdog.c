#include "CM3DS_gpio.h"
#include "CM3DS_MPS2.h"
#include "CM3DS_watchdog.h"


/**
  *
  * @brief: 配置WatchDog的加载值。
  *
  * @param: CM3DS_MPS2_WATCHDOGx,CM3只有1个看门狗,只能设置为CM3DS_MPS2_WATCHDOG。
  * @param: wdogload,要设置的加载值。
  *
  * @retVal: void
  */
void WatchDog_LOAD(CM3DS_MPS2_WATCHDOG_TypeDef* CM3DS_MPS2_WATCHDOGx, uint32_t wdogload)
{
  /*Check the parameters*/
  assert_param(IS_WatchDog_ALL_PERIPH(CM3DS_MPS2_WATCHDOGx));

  CM3DS_MPS2_WATCHDOGx->LOAD = wdogload;
}

/**
  *
  * @brief: 锁定WatchDog，禁止对WatchDog寄存器的写访问。
  *
  * @param: CM3DS_MPS2_WATCHDOGx,CM3只有1个看门狗,只能设置为CM3DS_MPS2_WATCHDOG。
  *
  * @retVal: void
  */
void WatchDog_LOCK(CM3DS_MPS2_WATCHDOG_TypeDef* CM3DS_MPS2_WATCHDOGx)
{
  /*Check the parameters*/
  assert_param(IS_WatchDog_ALL_PERIPH(CM3DS_MPS2_WATCHDOGx));

  CM3DS_MPS2_WATCHDOGx->LOCK = 0;
}

/**
  *
  * @brief: 解锁WatchDog，允许对WatchDog寄存器的写访问。
  *
  * @param: CM3DS_MPS2_WATCHDOGx,CM3只有1个看门狗,只能设置为CM3DS_MPS2_WATCHDOG。
  *
  * @retVal: void
  */
void WatchDog_UNLOCK(CM3DS_MPS2_WATCHDOG_TypeDef* CM3DS_MPS2_WATCHDOGx)
{
  /*Check the parameters*/
  assert_param(IS_WatchDog_ALL_PERIPH(CM3DS_MPS2_WATCHDOGx));

  CM3DS_MPS2_WATCHDOGx->LOCK = 0x1ACCE551;
}

/**
  *
  * @brief: WatchDog控制寄存器设置。
  *
  * @param: CM3DS_MPS2_WATCHDOGx,CM3只有1个看门狗,只能设置为CM3DS_MPS2_WATCHDOG。
  * @param: resen,是否使能WatchDog复位输出WDOGRES；使能时，不喂狗就会进行系统复位；
  *					可设置的值包括：RESEN_Disable(0x0) - 不使能；RESEN_Enable(0x01) - 使能。
  * @param: wdgen_inten, 是否使能WatchDog计数器和中断WDOGINT；需使能WatchDog计数器WatchDog才会工作；
  *					可设置的值包括：INTEN_Disable(0x0) -不使能；INTEN_Enable(0x01) -使能。
  *
  * @retVal: void
  */
void WatchDog_CTRL(CM3DS_MPS2_WATCHDOG_TypeDef* CM3DS_MPS2_WATCHDOGx, int resen, int wdgen_inten)
{
  /*Check the parameters*/
  assert_param(IS_WatchDog_ALL_PERIPH(CM3DS_MPS2_WATCHDOGx));
  assert_param(IS_RESEN(resen));
  assert_param(IS_INTEN(wdgen_inten));

  CM3DS_MPS2_WATCHDOGx->CTRL = (resen << 1) | (wdgen_inten << 0);
}

/**
  *
  * @brief: 清除WatchDog中断。
  *
  * @param: CM3DS_MPS2_WATCHDOGx,CM3只有1个看门狗,只能设置为CM3DS_MPS2_WATCHDOG。
  *
  * @retVal: void
  */
void WatchDog_INTCLR(CM3DS_MPS2_WATCHDOG_TypeDef* CM3DS_MPS2_WATCHDOGx)
{
  /*Check the parameters*/
  assert_param(IS_WatchDog_ALL_PERIPH(CM3DS_MPS2_WATCHDOGx));

  WatchDog_UNLOCK(CM3DS_MPS2_WATCHDOGx);
  CM3DS_MPS2_WATCHDOGx->INTCLR = CM3DS_MPS2_Watchdog_INTCLR_Msk;
  WatchDog_LOCK(CM3DS_MPS2_WATCHDOGx);
}

/**
  *
  * @brief: 读取WatchDog计数器当前值。
  *
  * @param: CM3DS_MPS2_WATCHDOGx,CM3只有1个看门狗,只能设置为CM3DS_MPS2_WATCHDOG。
  *
  * @retVal: wdogvalue,读取到的WatchDog计数器当前值。
  */
uint32_t WatchDog_VALUE(CM3DS_MPS2_WATCHDOG_TypeDef* CM3DS_MPS2_WATCHDOGx)
{
  /*Check the parameters*/
  uint32_t wdogvalue;
  assert_param(IS_WatchDog_ALL_PERIPH(CM3DS_MPS2_WATCHDOGx));

  wdogvalue = CM3DS_MPS2_WATCHDOGx->VALUE;
  return wdogvalue;
}

/**
  *
  * @brief: 读取WatchDog原始中断状态寄存器。
  *
  * @param: CM3DS_MPS2_WATCHDOGx,CM3只有1个看门狗,只能设置为CM3DS_MPS2_WATCHDOG。
  *
  * @retVal: temp,读取到的寄存器值。
  */
uint32_t WatchDog_RAWINTSTAT(CM3DS_MPS2_WATCHDOG_TypeDef* CM3DS_MPS2_WATCHDOGx)
{
  /*Check the parameters*/
  uint32_t temp;
  assert_param(IS_WatchDog_ALL_PERIPH(CM3DS_MPS2_WATCHDOGx));

  temp = CM3DS_MPS2_WATCHDOGx->INTCLR;
  return temp;
}

/**
  *
  * @brief: 读取WatchDog中断状态寄存器。
  *
  * @param: CM3DS_MPS2_WATCHDOGx,CM3只有1个看门狗,只能设置为CM3DS_MPS2_WATCHDOG。
  *
  * @retVal: temp, 读取到的寄存器值。
  */
uint32_t WatchDog_MASKINTSTAT(CM3DS_MPS2_WATCHDOG_TypeDef* CM3DS_MPS2_WATCHDOGx)
{
  /*Check the parameters*/
  uint32_t temp;
  assert_param(IS_WatchDog_ALL_PERIPH(CM3DS_MPS2_WATCHDOGx));

  temp = CM3DS_MPS2_WATCHDOGx->MASKINTSTAT;
  return temp;
}

/**
  *
  * @brief: 看门狗集成测试模式控制寄存器设置。
  *
  * @param: CM3DS_MPS2_WATCHDOGx,CM3只有1个看门狗,只能设置为CM3DS_MPS2_WATCHDOG。
  * @param: NewState,是否使能WatchDog集成测试模式；0x0- 不使能；0x01 - 使能。
  *
  * @retVal: void
  */
void WatchDog_Test_Control(CM3DS_MPS2_WATCHDOG_TypeDef* CM3DS_MPS2_WATCHDOGx, FunctionalState NewState)
{
  /*Check the parameters*/
  assert_param(IS_WatchDog_ALL_PERIPH(CM3DS_MPS2_WATCHDOGx));

  if (NewState != DISABLE)
  {
    CM3DS_MPS2_WATCHDOGx->ITCR = (1 << 0);
  }
  else
  {
    CM3DS_MPS2_WATCHDOGx->ITCR = (0 << 0);
  }
}

/**
  *
  * @brief: 看门狗集成测试模式输出寄存器设置。
  *
  * @param: CM3DS_MPS2_WATCHDOGx,CM3只有1个看门狗,只能设置为CM3DS_MPS2_WATCHDOG。
  * @param: value1, 在集成测试模式下，在WDOGINT上输出值。
  * @param: value0, 在集成测试模式下，在WDOGRES上输出值。
  *
  * @retVal: void
  */
void WatchDog_ITOP(CM3DS_MPS2_WATCHDOG_TypeDef* CM3DS_MPS2_WATCHDOGx, int value1, int value0)
{
  /*Check the parameters*/
  assert_param(IS_WatchDog_ALL_PERIPH(CM3DS_MPS2_WATCHDOGx));

  CM3DS_MPS2_WATCHDOGx->ITOP = (value1 << 1) | (value0 << 0);
}

