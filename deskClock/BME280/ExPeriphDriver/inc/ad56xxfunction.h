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

#ifndef __ad5663function_h
#define __ad5663function_h

#include "stdint.h"

/* ����AD56XXϵ��DAC������������ */
typedef enum AD56xxError {
  AD56xx_OK,            //�޴���
  AD56xx_InitError,     //��ʼ������
  AD56xx_ChannelError,  //ͨ������
}AD56xxErrorType;

/*����DAC����������*/
typedef enum AD56xx{
  AD5662=0,
  AD5623=1,
  AD5643=2,
  AD5663=3,
  AD5624=4,
  AD5644=5,
  AD5664=6,
  TypeNumber,
}AD56xxType;

/*����AD5663ͨ��ö��*/
typedef enum AD56xxChannel {
  DAChannelA=0,
  DAChannelB=1,
  DAChannelC=2,
  DAChannelD=3,
  ChannelAll=4,
  ChannelNone=5
}AD56xxChannelType;

/*���������λģʽö��*/
typedef enum AD56xxReset{
  ResetSoftware=0,
  ResetPoweron=1
}AD56xxResetType;

/*�������ģʽö��*/
typedef enum AD56xxPowerdown{
  NormalOperation=0,
  R1K2GND=1,
  R100K2GND=2,
  ThreeState=3
}AD56xxPowerdownType;

/* ����AD56xxƬѡ�ź�ö�� */
typedef enum AD56xxCS {
  AD56xxCS_Enable,
  AD56xxCS_Disable
}AD56xxCSType;

/* �ڲ��ο���ѹԴ����ö�� */
typedef enum AD56xxRef{
  AD56xxRef_OFF,
  AD56xxRef_ON
}AD56xxRefType;

/* ����AD56XX�������� */
typedef struct AD56xxObject {
  AD56xxType objectType;        //DAC������
  void (*WriteDataToDAC)(uint8_t *tData,uint16_t tSize);        //��DAC��������
  void (*ChipSelcet)(AD56xxCSType cs);     //Ƭѡ�ź�
}AD56xxObjectType;

/* ��DAC�������ݺ���ָ������ */
typedef void (*AD56xxWrite)(uint8_t *tData,uint16_t tSize);
/* Ƭѡ��������ָ������ */
typedef void (*AD56xxChipSelcet)(AD56xxCSType cs);

/*����DAͨ����ֵ*/
AD56xxErrorType SetAD56xxChannelValue(AD56xxObjectType *dacObj,AD56xxChannelType channel,uint16_t data);

/*����AD56xx�ϵ�/���繤��ģʽ*/
void Ad56xxPowerUpDownMode(AD56xxObjectType *dacObj,AD56xxChannelType channel,AD56xxPowerdownType powerdownType);

/*��AD56xx���������λ*/
void Ad56xxSoftwareReset(AD56xxObjectType *dacObj,AD56xxResetType resetMode);

/* ������ر��ڲ��ο���ѹԴ */
void SetInternalReference(AD56xxObjectType *dacObj,AD56xxRefType ref);

/*����AD56xx��ͬ������LDAC����*/
void SetAd56xxLdacFunction(AD56xxObjectType *dacObj,AD56xxChannelType channel);

/* ��ʼ��AD56xx���� */
AD56xxErrorType AD56xxInitialization(AD56xxObjectType *dacObj,AD56xxType objectType,AD56xxWrite write,AD56xxChipSelcet cs);

#endif
/*********** (C) COPYRIGHT 1999-2017 Moonan Technology *********END OF FILE****/
