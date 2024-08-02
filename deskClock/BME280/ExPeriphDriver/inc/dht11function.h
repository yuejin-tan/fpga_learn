/******************************************************************************/
/** ģ�����ƣ���չ��������                                                   **/
/** �ļ����ƣ�dht11function.h                                                **/
/** ��    ����V1.0.0                                                         **/
/** ��    �飺����ʵ��DHT11��ʪ�ȴ�������ͨѶ                                **/
/**           ���õ�����ͨѶ��ʽ�����ݸ�ʽ���£�                             **/
/**           ʪ������+ʪ��С��+�¶�����+�¶�С��+У���                     **/
/**--------------------------------------------------------------------------**/
/** �޸ļ�¼��                                                               **/
/**     �汾      ����              ����              ˵��                   **/
/**     V1.0.0  2017-03-07          ľ��              �����ļ�               **/
/**                                                                          **/
/******************************************************************************/ 

#ifndef __DHT11FUNCTION_H
#define __DHT11FUNCTION_H 

#include "stdint.h"

/*����DHT11������Ϣö��*/
typedef enum DHT11Error{
  DHT11_NoError,        //û�д���
  DHT11_None,           //δ��⵽DHT11
  DHT11_InitError,      //��ʼ������
  DHT11_DataError       //ͨѶУ�����
}DHT11ErrorType;

/*���嵥���߷���ö��*/
typedef enum DHT11IOMode{
  DHT11_Out=1,
  DHT11_In=(!DHT11_Out)
}DHT11IOModeType;

/*���嵥���߲���ֵö��*/
typedef enum DhtPinValue{
  DHT11_Set=1,
  DHT11_Reset=(!DHT11_Set)
}DhtPinValueType;

/* ����DHT11�������� */
typedef struct Dht11Object {
  float temperature;            //�¶�ֵ
  float humidity;               //ʪ��ֵ
  
  void (*SetPinOutValue)(DhtPinValueType setValue);//����DHT11���ŵ����ֵ
  uint8_t (*ReadPinBit)(void);//��ȡ���ŵ�ƽ
  void (*SetPinMode)(DHT11IOModeType mode);//�������ŵ������������
  
  void (*Delayms)(volatile uint32_t nTime);     //ʵ��ms��ʱ����
  void (*Delayus)(volatile uint32_t nTime);     //ʵ��us��ʱ����
}Dht11ObjectType;

/*��������DHT11���ŵ����ֵ��������*/
typedef void (*Dht11SetPinOutValueType)(DhtPinValueType setValue);
/*�����ȡ���ŵ�ƽ��������*/
typedef uint8_t (*Dht11ReadPinBitType)(void);
/*�����������ŵ������������������*/
typedef void (*Dht11SetPinModeType)(DHT11IOModeType mode);
/*����ʵ��ms��ʱ������������*/
typedef void (*Dht11DelayType)(volatile uint32_t nTime);      

/*��DHT11��ȡ����,temp:�¶�ֵ(0-50),humi:ʪ��ֵ(20%-90%),����ֵ��0,����;1,ʧ��*/
DHT11ErrorType GetProcessValueFromDHT11(Dht11ObjectType *dht);

/*DHT11��ʼ������*/
DHT11ErrorType InitializeDHT11(Dht11ObjectType *dht,    //��Ҫ��ʼ������
                               Dht11SetPinOutValueType setPinStatus,    //�����������ֵ
                               Dht11ReadPinBitType getPinStatus,        //��ȡ��������ֵ
                               Dht11SetPinModeType mode,        //�������ߵ��������ģʽ
                               Dht11DelayType delayms,  //������ʱ
                               Dht11DelayType delayus   //΢����ʱ
                              );

#endif
/*********** (C) COPYRIGHT 1999-2019 Moonan Technology *********END OF FILE****/
