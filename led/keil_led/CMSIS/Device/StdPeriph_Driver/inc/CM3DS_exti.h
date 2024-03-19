/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __CM3DS_EXTI_H
#define __CM3DS_EXTI_H

#ifdef __cplusplus
extern "C" {
#endif

  /* Includes ------------------------------------------------------------------*/
  /* Includes ------------------------------------------------------------------*/
#include "CM3DS_MPS2.h"


//#define GPIO_Pin_0                  (0)  /*!< Pin 0 selected */
//#define GPIO_Pin_1                  (1)  /*!< Pin 1 selected */
//#define GPIO_Pin_2                  (2)  /*!< Pin 2 selected */
//#define GPIO_Pin_3                  (3)  /*!< Pin 3 selected */
//#define GPIO_Pin_4                  (4)  /*!< Pin 4 selected */
//#define GPIO_Pin_5                  (5)  /*!< Pin 5 selected */
//#define GPIO_Pin_6                  (6)  /*!< Pin 6 selected */
//#define GPIO_Pin_7                  (7)  /*!< Pin 7 selected */
//#define GPIO_Pin_8                  (8)  /*!< Pin 8 selected */
//#define GPIO_Pin_9                  (9)  /*!< Pin 9 selected */
//#define GPIO_Pin_10                (10)  /*!< Pin 10 selected */
//#define GPIO_Pin_11                (11)  /*!< Pin 11 selected */
//#define GPIO_Pin_12                (12)  /*!< Pin 12 selected */
//#define GPIO_Pin_13                (13)  /*!< Pin 13 selected */
//#define GPIO_Pin_14                (14)  /*!< Pin 14 selected */
//#define GPIO_Pin_15                (15)  /*!< Pin 15 selected */

//#define GPIO_Pin_16                (16)  /*!< Pin 16 selected */
//#define GPIO_Pin_17                (17)  /*!< Pin 17 selected */
//#define GPIO_Pin_18                (18)  /*!< Pin 18 selected */
//#define GPIO_Pin_19                (19)  /*!< Pin 19 selected */
//#define GPIO_Pin_20                (20)  /*!< Pin 20 selected */
//#define GPIO_Pin_21                (21)  /*!< Pin 21 selected */
//#define GPIO_Pin_22                (22)  /*!< Pin 22 selected */
//#define GPIO_Pin_23                (23)  /*!< Pin 23 selected */
//#define GPIO_Pin_24                (24)  /*!< Pin 24 selected */
//#define GPIO_Pin_25                (25)  /*!< Pin 25 selected */
//#define GPIO_Pin_26                (26)  /*!< Pin 26 selected */
//#define GPIO_Pin_27                (27)  /*!< Pin 27 selected */
//#define GPIO_Pin_28                (28)  /*!< Pin 28 selected */
//#define GPIO_Pin_29                (29)  /*!< Pin 29 selected */
//#define GPIO_Pin_30                (30)  /*!< Pin 30 selected */
//#define GPIO_Pin_31                (31)  /*!< Pin 31 selected */
//#define GPIO_Pin_All                ((uint32_t)0xFFFFFFFF)  /*!< All pins selected */


//#define IS_GPIO_PIN(PIN) ((((PIN) & (uint16_t)0x00) == 0x00) && ((PIN) != (uint16_t)0x00))

//#define IS_GET_GPIO_PIN(PIN) (((PIN) == GPIO_Pin_0) || \
//                              ((PIN) == GPIO_Pin_1) || ((PIN) == GPIO_Pin_2) || ((PIN) == GPIO_Pin_3) || \
//                              ((PIN) == GPIO_Pin_4) || ((PIN) == GPIO_Pin_6) || ((PIN) == GPIO_Pin_7) || \
//                              ((PIN) == GPIO_Pin_8) || ((PIN) == GPIO_Pin_9) || ((PIN) == GPIO_Pin_10) || \
//                              ((PIN) == GPIO_Pin_11) ||((PIN) == GPIO_Pin_12) ||((PIN) == GPIO_Pin_13) || \
//                              ((PIN) == GPIO_Pin_14) || ((PIN) == GPIO_Pin_15)||((PIN) == GPIO_Pin_16) || \
//                              ((PIN) == GPIO_Pin_17) || ((PIN) == GPIO_Pin_18)||((PIN) == GPIO_Pin_19) || \
//                              ((PIN) == GPIO_Pin_20) || ((PIN) == GPIO_Pin_21)||((PIN) == GPIO_Pin_22) || \
//                              ((PIN) == GPIO_Pin_23) || ((PIN) == GPIO_Pin_24)||((PIN) == GPIO_Pin_25) || \
//                              ((PIN) == GPIO_Pin_26) || ((PIN) == GPIO_Pin_27)||((PIN) == GPIO_Pin_28) || \
//                              ((PIN) == GPIO_Pin_29) || ((PIN) == GPIO_Pin_30)||((PIN) == GPIO_Pin_31))
/**
  * @}
  */





  /** @defgroup EXTI_Exported_Functions
  * @{
  */

  void EXTI_DeInit(CM3DS_MPS2_GPIO_TypeDef* CM3DS_MPS2_GPIOx);
  void EXTI_GenerateInterrupt(CM3DS_MPS2_GPIO_TypeDef* CM3DS_MPS2_GPIOx, uint16_t GPIO_Pin_x);
  void EXTI_ClearFlag(CM3DS_MPS2_GPIO_TypeDef* CM3DS_MPS2_GPIOx, uint16_t GPIO_Pin_x);
  void EXTI_ClearITPendingBit(CM3DS_MPS2_GPIO_TypeDef* CM3DS_MPS2_GPIOx, uint16_t GPIO_Pin_x);
  uint32_t CM3DS_MPS2_gpio_IntClear(CM3DS_MPS2_GPIO_TypeDef* CM3DS_MPS2_GPIO, uint32_t Num);

#ifdef __cplusplus
}
#endif

#endif
