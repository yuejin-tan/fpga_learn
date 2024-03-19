#ifndef __CM3DS_ADC_H
#define __CM3DS_ADC_H


#ifdef __cplusplus
extern "C" {
#endif

  /* Includes ------------------------------------------------------------------*/
#include "CM3DS_MPS2.h"


/**
  * @brief  ADC Init structure definition
  */

  typedef struct
  {
    uint8_t Clock;

    uint8_t Transfor_mode;

    uint8_t Converter_adon;

    uint8_t Data_buffer;

    uint8_t Overrun_flag;

    uint8_t Ext_trig;

    uint8_t Ext_sel;

    uint8_t Data_align;

    FunctionalState ScanConvMode;

  }ADC_InitTypeDef;

  /**
    * @}
    */

#define Single_Conversion                       (0x0)
#define Continuous_Conversion                  	(0x1)
#define IS_ADC_TRANSFOR_MODE(MODE) (((MODE) == Single_Conversion) || \
                                   (( MODE) == Continuous_Conversion))

#define Power_down                       				(0x0)
#define Power_on                  							(0x1)
#define IS_ADC_Converter_ADON(ADON) (((ADON) == Power_down) || \
                                    (( ADON) == Power_on))



    /** @defgroup ADC_Exported_Constants
      * @{
      */

#define IS_ADC_ALL_PERIPH(PERIPH) (((PERIPH) == CM3DS_MPS2_ADC))

      /** @defgroup ADC_frequency
        * @{
        */
#define Freq_Clk2																 (0x0)	
#define Freq_Clk4																 (0x1)		
#define Freq_Clk6																 (0x2)		
#define Freq_Clk8																 (0x3)		
#define Freq_Clk10															 (0x4)		
#define Freq_Clk12															 (0x5)		
#define Freq_Clk24															 (0x6)		
#define Freq_Clk48															 (0x7)		

#define IS_ADC_Freq_Clk(Clk)    (((Clk) == Freq_Clk2)  || ((Clk) == Freq_Clk4) || \
                                 ((Clk) == Freq_Clk6)  || ((Clk) == Freq_Clk8) || \
                                 ((Clk) == Freq_Clk10) || ((Clk) == Freq_Clk12)|| \
                                 ((Clk) == Freq_Clk24) || ((Clk) == Freq_Clk48))


        /**
          * @}
          */


#define DBUF_Enable                    				   (0x1)
#define DBUF_Disable                  				   (0x0)	
#define IS_ADC_Data_buffer(buffer) (((buffer) == DBUF_Enable) || \
																	  ((buffer) == DBUF_Disable))

#define OVR_Enable                    				   (0x1)
#define OVR_Disable                  				     (0x0)	
#define IS_ADC_Overrun_flag(flag) (((flag) == OVR_Enable) || \
																	 ((flag) == OVR_Disable))
          /** @defgroup ADC_data_align
            * @{
            */

#define DataAlign_Right                          (0x0)
#define DataAlign_Left                           (0x1)
#define IS_ADC_DATA_ALIGN(ALIGN) (((ALIGN) == DataAlign_Right) || \
                                  ((ALIGN) == DataAlign_Left))
            /**
              * @}
              */

              /** @defgroup ADC_ScanConv_Mode
                * @{
                */

#define	ScanMode_Enable 												 (0x1)
#define ScanMode_Disable												 (0x0)
#define	IS_ADC_ScanConv_Mode(Mode) (((Mode) == ScanMode_Enable) || \
																		 (Mode) == ScanMode_Disable))

                /** @defgroup ADC_ExternalTrigConv
                  * @{
                  */
#define External_Enable													 (0x1)
#define External_Disable												 (0x0)

#define	IS_ADC_External_TrigConv (((TrigConv) == External_Enable) || \
																	((TrigConv) == External_Disable))

                  /** @defgroup ADC_interrupts_definition
                    * @{
                    */
#define ADC_IT_EOCIE_Enable 												((uint32_t)0x00000002)
#define ADC_IT_EOCIE_Disable												((uint32_t)0x00000000)
                    //#define IS_ADC_IT(IT) ((IT) == ADC_IT_EOCIE)


#define ADC_START_Enable 														 ((uint32_t)0x00000001)
#define ADC_START_Disable														 ((uint32_t)0x00000000)


#define EXTSEL_Timer0 													 (0x0)
#define EXTSEL_Pin															 (0x1)
#define EXTSEL_Reserved_0												 (0x2)
#define EXTSEL_Reserved_1												 (0x3)
#define	IS_ADC_EXT_INJEC_TRIG (((INJTRIG) == EXTSEL_Timer0)     || \
															 ((INJTRIG) == EXTSEL_Pin)			  || \
															 ((INJTRIG) == EXTSEL_Reserved_0) || \
														   ((INJTRIG) == EXTSEL_Reserved_1))
/**
  * @}
  */


  /** @defgroup ADC_channels
    * @{
    */

#define Channel_0                                (0x0)		// Available ADC_IN0
#define Channel_1                                (0x1)   // Available ADC_IN1
#define Channel_2                                (0x2)   // Available ADC_IN0
#define Channel_3                                (0x3)   // Available ADC_IN1
#define Channel_4                                (0x4)   // Available ADC_IN0
#define Channel_5                                (0x5)   // Available ADC_IN1
#define Channel_6                                (0x6)   // Available ADC_IN0
#define Channel_7                                (0x7)   // Available ADC_IN1

#define IS_ADC_CHANNEL(CHANNEL) 	 (((CHANNEL) == _Channel_1) || \
																		((CHANNEL) == _Channel_2) || \
																		((CHANNEL) == _Channel_3) || \
																		((CHANNEL) == _Channel_4) || \
																		((CHANNEL) == _Channel_5) || \
																		((CHANNEL) == _Channel_6) || \
																		((CHANNEL) == _Channel_7))
    /**
      * @}
      */

      /** @defgroup ADC_Exported_Functions
        * @{
        */
  void ADC_DeInit(CM3DS_MPS2_ADC_TypeDef* CM3DS_MPS2_ADCx);

  void ADC_StructInit(CM3DS_MPS2_ADC_TypeDef* CM3DS_MPS2_ADCx, ADC_InitTypeDef* ADC_InitStruct);
  void ADC_Init(CM3DS_MPS2_ADC_TypeDef* CM3DS_MPS2_ADCx, ADC_InitTypeDef* ADC_InitStruct);

  void ADC_Cmd(CM3DS_MPS2_ADC_TypeDef* CM3DS_MPS2_ADCx);

  void ADC_ITConfig(CM3DS_MPS2_ADC_TypeDef* CM3DS_MPS2_ADCx, FunctionalState NewState);
  void ADC_SoftwareStartConvCmd(CM3DS_MPS2_ADC_TypeDef* CM3DS_MPS2_ADCx, FunctionalState NewState);
  FlagStatus ADC_GetSoftwareStartConvStatus(CM3DS_MPS2_ADC_TypeDef* CM3DS_MPS2_ADCx);
  uint16_t ADC_GetConversionValue(CM3DS_MPS2_ADC_TypeDef* CM3DS_MPS2_ADCx);

  void ADC_ClockConfig(CM3DS_MPS2_ADC_TypeDef* CM3DS_MPS2_ADCx, uint16_t Freq);
  void ADC_START(CM3DS_MPS2_ADC_TypeDef* CM3DS_MPS2_ADCx, FunctionalState NewState);
  void ADC_STOP(CM3DS_MPS2_ADC_TypeDef* CM3DS_MPS2_ADCx);
  void ADC_ContinuousTransform(CM3DS_MPS2_ADC_TypeDef* CM3DS_MPS2_ADCx, FunctionalState NewState);
  void ADC_ExternalTrigInjectedConvConfig(CM3DS_MPS2_ADC_TypeDef* CM3DS_MPS2_ADCx, uint32_t ADC_ExternalTrigInjecConv);
  void ADC_EXTI_ClearFlag(CM3DS_MPS2_ADC_TypeDef* CM3DS_MPS2_ADCx);

  uint16_t ADC_GetValueFromDR(CM3DS_MPS2_ADC_TypeDef* CM3DS_MPS2_ADCx);
  void ADC_GetValueFromDBR(CM3DS_MPS2_ADC_TypeDef* CM3DS_MPS2_ADCx, uint32_t* ADC_buf);
  uint16_t ADC_GetValueChannel_2(CM3DS_MPS2_ADC_TypeDef* CM3DS_MPS2_ADCx);
  uint16_t ADC_GetValueChannel_1(CM3DS_MPS2_ADC_TypeDef* CM3DS_MPS2_ADCx);
  /**
    * @}
    */

  void ADC_Channel_Select(CM3DS_MPS2_ADC_TypeDef* CM3DS_MPS2_ADCx, uint8_t Channel);

  void ADC_StartConversion(void);
  void ADC_StopConversion(void);
#ifdef __cplusplus
}
#endif

#endif /* __CM3DS_ADC_H */

