/******************************************************************************/
/** ģ�����ƣ���չ��������                                                   **/
/** �ļ����ƣ�ms5837function.h                                               **/
/** ��    ����V1.0.0                                                         **/
/** ��    �飺����ʵ��ѹ����������MS5837������ز���                         **/
/**           MS5837ѹ��������ʹ��I2C�ӿ�ͨѶ��ʽ                            **/
/**           MS5837ͨѶ�������ʽ���£�                                     **/
/**           +-+--------------+-+-+--------------+-+-+                      **/
/**           |S|Device Address|W|A|    Command   |A|P|                      **/
/**           +-+--------------+-+-+--------------+-+-+                      **/
/**           �����ڴ�Ĵ������ݵı��ĸ�ʽ���£�                             **/
/**           +-+--------------+-+-+--------------+-+--------------+-+-+     **/
/**           |S|Device Address|R|A|Menory bit15-8|A|Menory bit15-8|N|P|     **/
/**           +-+--------------+-+-+--------------+-+--------------+-+-+     **/
/**           ADC���ݽ��յı��ĸ�ʽ���£�                                    **/
/**      +-+--------------+-+-+------------+-+-----------+-+----------+-+-+  **/
/**      |S|Device Address|R|A| Data 23-16 |A| Data 15-8 |A| Data 7-0 |N|P|  **/
/**      +-+--------------+-+-+------------+-+-----------+-+----------+-+-+  **/
/**           S=Start Condition   W=Write   A=Acknowledge                    **/
/**           P=Stop Condition    R=Read    N=Not Acknowledge                **/
/**           ����Device AddressΪ7λ��CommandΪ8λ                          **/
/**--------------------------------------------------------------------------**/
/**ʹ��˵����                                                                **/
/**    1������MS5837ObjectType����ʵ�壬�����ú���MS5837Initialization��ʼ�� **/
/**       ����ʵ�塣�����豸��ַ������ȡУ׼����                             **/
/**    2��ʵ������uint8_t f(struct MS5837Object *ms,uint8_t command)�ĺ����� **/
/**       �����丳ֵ��MS5837ObjectType����ʵ���SendCommand����ָ�롣ʵ����  **/
/**       ��ķ��͡�                                                         **/
/**    3��ʵ������void f(struct MS5837Object *ms,uint8_t *rData,             **/
/**       uint16_t rSize)�ĺ����������丳ֵ��MS5837ObjectType����ʵ���      **/
/**       GetDatas����ָ�롣ʵ�����ݵĶ�ȡ                                   **/
/**    4��ʵ������void f(volatile uint32_t nTime)�ĺ����������丳ֵ��        **/
/**       MS5837ObjectType����ʵ���Delayms����ָ�롣ʵ�ֲ�����ʱ����λ����  **/
/**    5��������Ӧ�ĺ���ʵ����Ҫ�Ĳ�����                                     **/
/**--------------------------------------------------------------------------**/
/** �޸ļ�¼��                                                               **/
/**     �汾      ����              ����              ˵��                   **/
/**     V1.0.0  2017-01-16          ľ��              �����ļ�               **/
/**                                                                          **/
/******************************************************************************/ 

#ifndef __MS5837FUNCTION_H
#define __MS5837FUNCTION_H

#include "stdint.h"
#include "math.h"

/* ����ת������ö�� */
typedef enum MS5837OSR{
  MS5837_OSR256,
  MS5837_OSR512,
  MS5837_OSR1024,
  MS5837_OSR2048,
  MS5837_OSR4096,
  MS5837_OSR8192
}MS5837OSRType;

/* ����MS5837�������� */
typedef struct MS5837Object {
  uint8_t devAddress;   //�豸��ַ
  uint16_t caliData[6]; //У׼����
  float temperature;
  float pressure;
  void (*Write)(struct MS5837Object *ms,uint8_t command);//��MS5837�·�ָ�ָ���ʽ��Ϊ1���ֽ�
  void (*Read)(struct MS5837Object *ms,uint8_t *rData,uint16_t rSize);//��MS5837��ȡ����ֽ����ݵ�ֵ
  void (*Delayms)(volatile uint32_t nTime);     //��������ʱ����
}MS5837ObjectType;

/*��MS5837�·�ָ�ָ���ʽ��Ϊ1���ֽ�*/
typedef void (*MS5837Write)(struct MS5837Object *ms,uint8_t command);
/*��MS5837��ȡ����ֽ����ݵ�ֵ*/
typedef void (*MS5837Read)(struct MS5837Object *ms,uint8_t *rData,uint16_t rSize);
/*��������ʱ����*/
typedef void (*MS5837Delayms)(volatile uint32_t nTime);

/*��ȡת��ֵ�������¶Ⱥ�ѹ��*/
void GetMS5837ConversionValue(MS5837ObjectType *ms,MS5837OSRType pOSR,MS5837OSRType tOSR);

/*��λMS5837����*/
void ResetForMs5837(MS5837ObjectType *ms);

/* ��ʼ��MS5837���� */
void MS5837Initialization(MS5837ObjectType *ms, //MS5837����
                          MS5837Write write,    //��MS5837д���ݺ���ָ��
                          MS5837Read read,      //��MS5837�����ݺ���ָ��
                          MS5837Delayms delayms //������ʱ����ָ��
                         );
#endif
/*********** (C) COPYRIGHT 1999-2017 Moonan Technology *********END OF FILE****/
