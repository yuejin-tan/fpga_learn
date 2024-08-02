/******************************************************************************/
/** ģ�����ƣ���չ��������                                                   **/
/** �ļ����ƣ�ms5803function.h                                               **/
/** ��    ����V1.0.0                                                         **/
/** ��    �飺����ʵ��ѹ����������MS5803������ز���                         **/
/**           MS5803ѹ��������ʹ��I2C��SPI�ӿ�ͨѶ��ʽ����Ӳ�����߾���       **/
/**           MS5803����SPIͨѶʱ��֧��Mode0��Mode3                          **/
/**           MS5803ͨѶ�������ʽ���£�                                     **/
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
/**           ʹ��I2CͨѶʱ������2̨����ַΪ0xEC��0xEE                     **/
/**--------------------------------------------------------------------------**/
/**ʹ��˵����                                                                **/
/**    1������MS5803ObjectType����ʵ�壬�����ú���MS5803Initialization��ʼ�� **/
/**       ����ʵ�塣��Ҫ�������ͣ�������enum MS5803Model���塣����ͨѶ�ӿڣ� **/
/**       ͨѶ�ӿ���enum MS5803Port���塣���ͨѶ�ӿ�ΪI2C����Ҫ�����豸��   **/
/**       ַ����ΪSPI�ӿ���Ӧ��ֵChipSelcetָ�롣����ȡУ׼����              **/
/**    2��ʵ������uint8_t f(struct MS5803Object *ms,uint8_t command)�ĺ����� **/
/**       �����丳ֵ��MS5803ObjectType����ʵ���SendCommand����ָ�롣ʵ����  **/
/**       ��ķ��͡�                                                         **/
/**    3��ʵ������void f(struct MS5803Object *ms,uint8_t *rData,             **/
/**       uint16_t rSize)�ĺ����������丳ֵ��MS5803ObjectType����ʵ���      **/
/**       GetDatas����ָ�롣ʵ�����ݵĶ�ȡ                                   **/
/**    4����ʹ��SPI�˿ڣ���ʵ������void f(bool en)�ĺ����������丳ֵ��       **/
/**       MS5803ObjectType����ʵ���ChipSelcet����ָ�롣ʵ��Ƭѡ�źš�����   **/
/**       ��I2C�ӿڣ���ChipSelcet����ָ����Զ���ֵΪNULL��                  **/
/**    5��ʵ������void f(volatile uint32_t nTime)�ĺ����������丳ֵ��        **/
/**       MS5837ObjectType����ʵ���Delayms����ָ�롣ʵ�ֲ�����ʱ����λ����  **/
/**    6��������Ӧ�ĺ���ʵ����Ҫ�Ĳ�����                                     **/
/**--------------------------------------------------------------------------**/
/** �޸ļ�¼��                                                               **/
/**     �汾      ����              ����              ˵��                   **/
/**     V1.0.0  2017-01-16          ľ��              �����ļ�               **/
/**     V1.1.0  2019-05-26          ľ��              �޸�Ϊ�������         **/
/**                                                                          **/
/******************************************************************************/ 

#ifndef _MS5803function_h
#define _MS5803function_h

#include "stdint.h"
#include "stdbool.h"
#include "math.h"
#include "stddef.h"

/*MS5803������������*/
typedef enum MS5803Model{
  MS580301BA,
  MS580302BA,
  MS580305BA,
  MS580314BA,
  MS580330BA
}MS5803ModelType;

/*MS5803�Ľӿ�����*/
typedef enum MS5803Port{
  SPI,
  I2C
}MS5803PortType;

/*MS5803��ADCת����������*/
typedef enum MS5803OSR{
  MS5803_OSR256,
  MS5803_OSR512,
  MS5803_OSR1024,
  MS5803_OSR2048,
  MS5803_OSR4096
}MS5803OSRType;

/* ����MS5803Ƭѡ�ź�ö�� */
typedef enum MS5803CS {
  MS5803CS_Enable,
  MS5803CS_Disable
}MS5803CSType;

typedef struct MS5803Object {
  uint8_t devAddress;           //�豸��ַ
  MS5803PortType port;          //ͨѶ�˿�Э��
  MS5803ModelType model;        //�豸������
  uint16_t caliData[6];         //У׼����
  float temperature;
  float pressure;
  void (*Write)(struct MS5803Object *ms,uint8_t command);       //��MS5803д��Ϣ
  void (*Read)(struct MS5803Object *ms,uint8_t *rData,uint16_t rSize);  //��MS5803������
  void (*ChipSelcet)(MS5803CSType en);  //Ƭѡ�ź�,����SPI�ӿ�
  void (*Delayms)(volatile uint32_t nTime);     //��������ʱ����
}MS5803ObjectType;

/*��MS5803�·�ָ�ָ���ʽ��Ϊ1���ֽ�*/
typedef void (*MS5803Write)(MS5803ObjectType *ms,uint8_t command);
/*��MS5803��ȡ����ֽ����ݵ�ֵ*/
typedef void (*MS5803Read)(MS5803ObjectType *ms,uint8_t *rData,uint16_t rSize);
/*Ƭѡ�ź�,����SPI�ӿ�*/
typedef void (*MS5803ChipSelcet)(MS5803CSType en);     
/*��������ʱ����*/
typedef void (*MS5803Delayms)(volatile uint32_t nTime);     

/*��ȡת��ֵ�������¶Ⱥ�ѹ��*/
void GetMS5803ConversionValue(MS5803ObjectType *ms,MS5803OSRType osrT,MS5803OSRType osrP);

/*��λMS5803����*/
void ResetForMS5803(MS5803ObjectType *ms);

/* MS5803�����ʼ�� */
void MS5803Initialization(MS5803ObjectType *ms,         //MS5803����
                          MS5803ModelType model,        //����
                          MS5803PortType port,          //ͨѶ�˿�
                          uint8_t address,              //I2C�豸��ַ
                          MS5803Write write,            //д���ݺ���
                          MS5803Read read,              //�����ݺ���
                          MS5803ChipSelcet cs,          //SPIƬѡ�ź�
                          MS5803Delayms delayms         //������ʱ
                         );

#endif
/*********** (C) COPYRIGHT 1999-2019 Moonan Technology *********END OF FILE****/
