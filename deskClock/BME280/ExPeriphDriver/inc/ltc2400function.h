/******************************************************************************/
/** ģ�����ƣ���չ��������                                                   **/
/** �ļ����ƣ�ltc2400function.h                                              **/
/** ��    ����V1.0.0                                                         **/
/** ��    �飺����ʵ��LTC2400 ADC�����ݻ�ȡ                                  **/
/**           LTC2400����SPI�����ӿ�                                         **/
/**           ������ݵĽṹ���£�                                           **/
/**           Bit31 Bit30 Bit29 Bit28 Bit27 �� Bit4 Bit3-0                    **/
/**           EOC   DMY   SIG   EXR   MSB      LSB  SUB LSBs                 **/
/**           0     0     0/1   0/1   0/1      0/1  X                        **/
/**--------------------------------------------------------------------------**/
/** �޸ļ�¼��                                                               **/
/**     �汾      ����              ����              ˵��                   **/
/**     V1.0.0  2017-01-18          ľ��              �����ļ�               **/
/**                                                                          **/
/******************************************************************************/ 

#ifndef _ltc2400function_h
#define _ltc2400function_h

#include "stdint.h"

/* ����LTC2400Ƭѡ�ź�ö�� */
typedef enum LTC2400CS {
  LTC2400CS_Enable,
  LTC2400CS_Disable
}LTC2400CSType;

/* ����LTC2400ʱ���ź� */
typedef enum LTC2400Clock {
  INTERNAL_CLOCK50Hz,
  INTERNAL_CLOCK60Hz,
  EXTERNAL_CLOCK
}LTC2400ClockType;

/* ����LTC2400�������� */
typedef struct Ltc2400Object {
  LTC2400ClockType clock;       //ʹ�õ�ʱ��
  uint32_t dataCode;            //���ݱ���
  void (*Receive)(uint8_t *rData);      //��������
  void (*ChipSelect)(LTC2400CSType cs); //ʵ��Ƭѡ
  void (*Delayms)(volatile uint32_t nTime);     //ʵ��ms��ʱ����
}Ltc2400ObjectType;

/*����������ݺ���ָ������*/
typedef void (*LTC2400Receive)(uint8_t *rData);
/*����Ƭѡ�źź���ָ������*/
typedef void (*LTC2400ChipSelect)(LTC2400CSType cs);
/*������ʱ��������ָ������*/
typedef void (*LTC2400Delay)(volatile uint32_t nTime);

/* ��ȡLTC2400ת������,�����������ݵı���ֵ */
float GetLtc2400Data(Ltc2400ObjectType *ltc);

/* LTC2400�����ʼ������ */
void LTC2400Initialization(Ltc2400ObjectType *ltc,
                           LTC2400ClockType clock,
                           LTC2400Receive receive,
                           LTC2400ChipSelect cs,
                           LTC2400Delay msDelay);

#endif
/*********** (C) COPYRIGHT 1999-2019 Moonan Technology *********END OF FILE****/
