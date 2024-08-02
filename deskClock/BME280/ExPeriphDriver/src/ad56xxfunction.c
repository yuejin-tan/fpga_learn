/******************************************************************************/
/** ģ�����ƣ���չ��������                                                   **/
/** �ļ����ƣ�ad56xxfunction.c                                               **/
/** ��    ����V2.0.0                                                         **/
/** ��    �飺�����Ͷ���������ADI��˾AD56xxϵ����ģת��оƬ�ĺ����Ͳ�����    **/
/**           ����SPI�ӿ�����������ص��Ǿ��߱�24λ����Ĵ�����������ͬ��    **/
/**           �����ʽ�����õ������У�                                       **/
/**           AD5662����ͨ��16λ��ģת����                                   **/
/**           AD5623��˫ͨ��12λ��ģת����                                   **/
/**           AD5643��˫ͨ��14λ��ģת����                                   **/
/**           AD5663��˫ͨ��16λ��ģת����                                   **/
/**           AD5624����ͨ��12λ��ģת����                                   **/
/**           AD5644����ͨ��14λ��ģת����                                   **/
/**           AD5664����ͨ��16λ��ģת����                                   **/
/**                                                                          **/
/**     ���У�AD5662��24λ��λ�Ĵ������ݸ�ʽ���£�                           **/
/**     +-+-+-+-+-+-+---+---+---+---+---+---+-------+--+--+--+--+            **/
/**     |  ------   |  ģʽ |                ����λ             |            **/
/**     +-+-+-+-+-+-+---+---+---+---+---+---+-------+--+--+--+--+            **/
/**     |x|x|x|x|x|x|PD1|PD0|D15|D14|D13|D12| ......|D3|D2|D1|D0|            **/
/**     +-+-+-+-+-+-+---+---+---+---+---+---+-------+--+--+--+--+            **/
/**                                                                          **/
/**     ���У�AD5663��AD5664��24λ��λ�Ĵ������ݸ�ʽ���£�                   **/
/**     +-+-+--+--+--+--+--+--+---+---+---+---+-------+--+--+--+--+          **/
/**     | - | ����λ | ��ַλ |                ����λ             |          **/
/**     +-+-+--+--+--+--+--+--+---+---+---+---+-------+--+--+--+--+          **/
/**     |x|x|C2|C1|C0|A2|A1|A0|D15|D14|D13|D12|.......|D3|D2|D1|D0|          **/
/**     +-+-+--+--+--+--+--+--+---+---+---+---+-------+--+--+--+--+          **/
/**                                                                          **/
/**     ���У�AD5643��AD5644��24λ��λ�Ĵ������ݸ�ʽ���£�                   **/
/**     +-+-+--+--+--+--+--+--+---+---+---+---+-------+--+--+--+--+-+-+      **/
/**     | - | ����λ | ��ַλ |                ����λ             | - |      **/
/**     +-+-+--+--+--+--+--+--+---+---+---+---+-------+--+--+--+--+-+-+      **/
/**     |x|x|C2|C1|C0|A2|A1|A0|D13|D12|D11|D10|.......|D3|D2|D1|D0|x|x|      **/
/**     +-+-+--+--+--+--+--+--+---+---+---+---+-------+--+--+--+--+-+-+      **/
/**                                                                          **/
/**     ���У�AD5623��AD5624��24λ��λ�Ĵ������ݸ�ʽ���£�                   **/
/**     +-+-+--+--+--+--+--+--+---+---+--+--+-------+--+--+--+--+-+-+-+-+    **/
/**     | - | ����λ | ��ַλ |                ����λ           | ----- |    **/
/**     +-+-+--+--+--+--+--+--+---+---+--+--+-------+--+--+--+--+-+-+-+-+    **/
/**     |x|x|C2|C1|C0|A2|A1|A0|D11|D10|D9|D8|.......|D3|D2|D1|D0|x|x|x|x|    **/
/**     +-+-+--+--+--+--+--+--+---+---+--+--+-------+--+--+--+--+-+-+-+-+    **/
/**--------------------------------------------------------------------------**/
/**ʹ��˵����                                                                **/
/**    1������AD56xx����ʵ�壬�����ú���AD56xxInitialization��ʼ������ʵ�塣 **/
/**    ��ʼ��ʱ��ָ���豸���ͣ�DACTypeDef��                                  **/
/**    2��ʵ������void f(uint8_t *tData,uint16_t tSize)�ĺ����������丳ֵ    **/
/**    ��AD56xx����ʵ���WriteDataToDAC����ָ�롣                            **/
/**    3��ʵ������void f(bool en)�ĺ����������丳ֵAD56xx����ʵ���ChipSelcet**/
/**    ����ָ�롣                                                            **/
/**    4��������Ӧ�ĺ���ʵ����Ҫ�Ĳ�����                                     **/
/**--------------------------------------------------------------------------**/
/** �޸ļ�¼��                                                               **/
/**     �汾      ����              ����              ˵��                   **/
/**     V1.0.0  2015-07-28          ľ��              �����ļ�               **/
/**     V1.0.1  2017-03-17          ľ��              ����Ӧ���޸�           **/
/**     V1.5.0  2018-01-05          ľ��              �޸�ʹ������ͬ������   **/
/**     V2.0.0  2018-05-13          ľ��              �޸�Ϊ�����弰����   **/
/**                                                                          **/
/******************************************************************************/ 

#include "stddef.h"
#include "ad56xxfunction.h"

/*�����*/
#define Write_to_Input_Register         0x000000
#define Update_DAC_Register             0x080000
#define Software_LDAC                   0x100000
#define WriteTo_Update_DAC_Channel      0x180000
#define Power_Down                      0x200000
#define RESET                           0x280000
#define LDAC_Register_Setup             0x300000
#define Reference_Set                   0x380000

/*��ַģʽ,ѡ��DACͨ��*/
#define DAC_Channel_A                   0x000000
#define DAC_Channel_B                   0x010000
#define DAC_Channel_C                   0x020000
#define DAC_Channel_D                   0x030000
#define DAC_Channel_ALL                 0x070000

/*power downģʽѡ��*/
#define Normal_Operation                0x000000
#define _1K_GND                         0x000010
#define _100K_GND                       0x000020
#define Three_State                     0x000030

/*�����λģʽ*/
#define Register_Reset_Software         0x000000
#define Register_Reset_Poweron          0x000001

/*power downģʽͨ������LDACģʽ����ѡ��*/
#define DAC_None                        0x00000000
#define DAC_A                           0x00000001
#define DAC_B                           0x00000002
#define DAC_C                           0x00000004
#define DAC_D                           0x00000008
#define DAC_ALL                         0x0000000F

/* �ڲ��ο���ѹԴ���� */
#define Reference_OFF   0x00; //�ڲ��ο���ѹԴ�ر�
#define Reference_ON    0x01; //�ڲ��ο���ѹԴ����

/* Ĭ��Ƭѡ�������� */
static void DefaultChipSelect(AD56xxCSType cs);

/* ��AD56xx���������λ */
void Ad56xxSoftwareReset(AD56xxObjectType *dacObj,AD56xxResetType resetMode)
{
  uint32_t inputShiftData=0;
  
  if(resetMode==ResetSoftware)
  {
    inputShiftData=RESET|Register_Reset_Software;
  }
  
  if(resetMode==ResetPoweron)
  {
    inputShiftData=RESET|Register_Reset_Poweron;
  }
  uint8_t txData[3];
  txData[0]=inputShiftData>>16;
  txData[1]=inputShiftData>>8;
  txData[2]=inputShiftData;
  
  dacObj->ChipSelcet(AD56xxCS_Enable);
  dacObj->WriteDataToDAC(txData,3);
  dacObj->ChipSelcet(AD56xxCS_Disable);
}

/* ����AD56xx�ϵ�/���繤��ģʽ */
void Ad56xxPowerUpDownMode(AD56xxObjectType *dacObj,AD56xxChannelType channel,AD56xxPowerdownType powerdownType)
{
  uint32_t inputShiftData=0;
  uint32_t pdc=0;
  uint32_t pdm=0;
  uint32_t cmd=Power_Down;
   
  uint32_t pdChannel[]={DAC_A,DAC_B,DAC_C,DAC_D,DAC_ALL,DAC_None};
  
  pdc=pdChannel[channel];
  
  uint32_t pdMode[]={Normal_Operation,_1K_GND,_100K_GND,Three_State};
  
  pdm=pdMode[powerdownType];
  
  if(dacObj->objectType==AD5662)
  {
    pdc=DAC_None;
    pdm=(pdm<<12);
    cmd=Write_to_Input_Register;
  }
  
  inputShiftData=cmd|pdc|pdm;
   
  uint8_t txData[3];
  txData[0]=inputShiftData>>16;
  txData[1]=inputShiftData>>8;
  txData[2]=inputShiftData;
  
  dacObj->ChipSelcet(AD56xxCS_Enable);
  dacObj->WriteDataToDAC(txData,3);
  dacObj->ChipSelcet(AD56xxCS_Disable);
}

/* ����AD56xx��ͬ������LDAC���� */
void SetAd56xxLdacFunction(AD56xxObjectType *dacObj,AD56xxChannelType channel)
{
  uint32_t inputShiftData=0;
  
  uint32_t pdChannel[]={DAC_A,DAC_B,DAC_C,DAC_D,DAC_ALL,DAC_None};
  
  inputShiftData=pdChannel[channel];
  
  inputShiftData=inputShiftData|LDAC_Register_Setup;
  
  uint8_t txData[3];
  txData[0]=(uint8_t)(inputShiftData>>16);
  txData[1]=(uint8_t)(inputShiftData>>8);
  txData[2]=(uint8_t)inputShiftData;
  
  dacObj->ChipSelcet(AD56xxCS_Enable);
  dacObj->WriteDataToDAC(txData,3);
  dacObj->ChipSelcet(AD56xxCS_Disable);
}

/* ������ر��ڲ��ο���ѹԴ */
void SetInternalReference(AD56xxObjectType *dacObj,AD56xxRefType ref)
{
  uint32_t inputShiftData=0;
	
  inputShiftData=Reference_Set;
	
  if(ref==AD56xxRef_ON)
  {
    inputShiftData=inputShiftData|Reference_ON;
  }
	
  uint8_t txData[3];
  txData[0]=(uint8_t)(inputShiftData>>16);
  txData[1]=(uint8_t)(inputShiftData>>8);
  txData[2]=(uint8_t)inputShiftData;
  
  dacObj->ChipSelcet(AD56xxCS_Enable);
  dacObj->WriteDataToDAC(txData,3);
  dacObj->ChipSelcet(AD56xxCS_Disable);
}

/* ����DAͨ����ֵ */
AD56xxErrorType SetAD56xxChannelValue(AD56xxObjectType *dacObj,AD56xxChannelType channel,uint16_t data)
{
  uint32_t inputShiftData=0;
  uint32_t dac=0;
  uint32_t cmd=WriteTo_Update_DAC_Channel;
  
  uint32_t dacChannel[]={DAC_Channel_A,DAC_Channel_B,DAC_Channel_C,DAC_Channel_D,DAC_Channel_ALL};
  
  uint32_t shiftV[]={0,4,2,0,4,0};
  
  if(channel>=ChannelNone)
  {
    return AD56xx_ChannelError;
  }
  
  dac=dacChannel[channel];
  
  if(dacObj->objectType==AD5662)
  {
    dac=DAC_Channel_A;
    cmd=Write_to_Input_Register;
  }

  inputShiftData=dac|cmd|(data<<shiftV[dacObj->objectType]);
   
  uint8_t txData[3];
  txData[0]=(uint8_t)(inputShiftData>>16);
  txData[1]=(uint8_t)(inputShiftData>>8);
  txData[2]=(uint8_t)inputShiftData;
  
  dacObj->ChipSelcet(AD56xxCS_Enable);
  dacObj->WriteDataToDAC(txData,3);
  dacObj->ChipSelcet(AD56xxCS_Disable);
	
  return AD56xx_OK;
}

/* ��ʼ��AD56xx���� */
AD56xxErrorType AD56xxInitialization(AD56xxObjectType *dacObj,AD56xxType objectType,AD56xxWrite write,AD56xxChipSelcet cs)
{
  if((dacObj==NULL)||(write==NULL))
  {
    return AD56xx_InitError;
  }
  dacObj->WriteDataToDAC=write;
  
  if(cs!=NULL)
  {
    dacObj->ChipSelcet=cs;
  }
  else
  {
    dacObj->ChipSelcet=DefaultChipSelect;
  }
  
  if(objectType<TypeNumber)
  {
    dacObj->objectType=objectType;
  }

  return AD56xx_OK;
}

/* Ĭ��Ƭѡ�������� */
static void DefaultChipSelect(AD56xxCSType cs)
{
  return;
}
/*********** (C) COPYRIGHT 1999-2018 Moonan Technology *********END OF FILE****/
