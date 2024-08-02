/******************************************************************************/
/** ģ�����ƣ���չ��������                                                   **/
/** �ļ����ƣ�ds18b20function.h                                              **/
/** ��    ����V1.0.0                                                         **/
/** ��    �飺ʵ���¶ȼ��ģ��DS18B20�����ݶ�ȡ                              **/
/**--------------------------------------------------------------------------**/
/** �޸ļ�¼��                                                               **/
/**     �汾      ����              ����              ˵��                   **/
/**     V1.0.0  2012-07-28          ľ��              �����ļ�               **/
/**                                                                          **/
/******************************************************************************/ 

#ifndef _DS18B20FUNCTION_H
#define _DS18B20FUNCTION_H

#include "stdint.h"

/* ����DS18B20�������ֵö�� */
typedef enum Ds18b20PinValue{
  DS18B20_Set=1,
  DS18B20_Reset=(!DS18B20_Set)
}Ds18b20PinValueType;

/* ����DS18B20���ŷ���ö�� */
typedef enum Ds18b20IOMode{
  DS18B20_Out=1,
  DS18B20_In=(!DS18B20_Out)
}Ds18b20IOModeType;

/* ����DS18B20����״̬ö�� */
typedef enum Ds18b20Status{
  DS18B20_OK,   //����
  DS18B20_InitialError, //��ʼֵ����
  DS18B20_NoResponse    //�豸��Ӧ��
}Ds18b20StatusType;

/*����ֱ���ö��*/
typedef enum Ds18b20Resolution {
  BITS9,
  BITS10,
  BITS11,
  BITS12
}Ds18b20ResolutionType;

/* ����DS18B20�������� */
typedef struct Ds18b20Object {
  uint8_t sn[6];        //Ds18b20Ԫ�����к�
  float temperature;    //�¶�����
  void (*SetBit)(Ds18b20PinValueType vBit);     //д����λ��DS18B20
  uint8_t (*GetBit)(void);      //��DS18B20��ȡһλ����
  void (*SetPinMode)(Ds18b20IOModeType mode);   //����DS18B20���������ŵ��������ģʽ
  void (*Delayus)(volatile uint32_t nTime);     //��ʱus����ָ��
}Ds18b20ObjectType;

/*д����λ��DS18B20*/
typedef void (*Ds18b20SetBitType)(Ds18b20PinValueType vBit);
/*��DS18B20��ȡһλ����*/
typedef uint8_t (*Ds18b20GetBitType)(void);
/*����DS18B20���������ŵ��������ģʽ*/
typedef void (*Ds18b20SetPinModeType)(Ds18b20IOModeType mode);
/* ������ʱ��������ָ������ */
typedef void (*Ds18b20DelayType)(volatile uint32_t nTime);

/*�¶����ݻ�ȡ��ת������*/
float GetDS18b20TemperatureValue(Ds18b20ObjectType *ds18b20);

/*��DS18B20�������г�ʼ��*/
Ds18b20StatusType Ds18b20Initialization(Ds18b20ObjectType *ds18b20,     //����ʼ���Ķ������
                                        Ds18b20SetBitType setBit,       //������дһλ����
                                        Ds18b20GetBitType getBit,       //�����߶�һλ����
                                        Ds18b20SetPinModeType pinDirection,     //�����������ģʽ����
                                        Ds18b20DelayType delayus        //Ϊ����ʱ����
                                       );

#endif
/*********** (C) COPYRIGHT 1999-2017 Moonan Technology *********END OF FILE****/
