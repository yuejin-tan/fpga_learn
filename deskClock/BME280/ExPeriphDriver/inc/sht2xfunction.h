/******************************************************************************/
/** ģ�����ƣ���չ��������                                                   **/
/** �ļ����ƣ�sht2xfunction.h                                                **/
/** ��    ����V1.0.1                                                         **/
/** ��    �飺����ʵ��SHT2X��ʪ�ȼƵĲ���                                    **/
/**           Ĭ�Ϸֱ���14bit(�¶�)��12bit(ʪ��)����ͨ���û��Ĵ����޸�       **/
/**           ���ʪ�ȵļ��㹫ʽ��RH=-6+125*SRH/Pow(2,16)���������Һ̬ˮ��  **/
/**           ���ʪ�ȣ������ڱ������ʪ�ȿ��Լ���õ���                     **/
/**           RHi=RHw*exp��17.62*t/(243.12+t))/exp(22.46*t/(272.62+t));      **/
/**           �¶ȵļ��㹫ʽ��T=-46.85+175.72*ST/Pow(2,16);                  **/
/**           ��ͬ�ֱ�����ADCת��ʱ�䣺                                      **/
/**           +------+--------+--------+-------+-------+----+                **/
/**           |�ֱ���|RH����ֵ|RH���ֵ|T����ֵ|T���ֵ|��λ|                **/
/**           +------+--------+--------+-------+-------+----+                **/
/**           | 14bit| ����   | ����   |  66   |  85   | ms |                **/
/**           +------+--------+--------+-------+-------+----+                **/
/**           | 13bit| ����   | ����   |  33   |  43   | ms |                **/
/**           +------+--------+--------+-------+-------+----+                **/
/**           | 12bit|   22   |   29   |  17   |  22   | ms |                **/
/**           +------+--------+--------+-------+-------+----+                **/
/**           | 11bit|   12   |   15   |   9   |  11   | ms |                **/
/**           +------+--------+--------+-------+-------+----+                **/
/**           | 10bit|   7    |    9   | ����  | ����  | ms |                **/
/**           +------+--------+--------+-------+-------+----+                **/
/**           | 8bit |   3    |    4   | ����  | ����  | ms |                **/
/**           +------+--------+--------+-------+-------+----+                **/
/**           SHT2x������룺                                                **/
/**           +------------+----------+----------+                           **/
/**           |    ����    |   ����   | ������� |                           **/
/**           +------------+----------+----------+                           **/
/**           | ����T����  | �������� | 11100011 |                           **/
/**           +------------+----------+----------+                           **/
/**           | ����RH���� | �������� | 11100101 |                           **/
/**           +------------+----------+----------+                           **/
/**           | ����T����  |�Ǳ�������| 11110011 |                           **/
/**           +------------+----------+----------+                           **/
/**           | ����RH���� |�Ǳ�������| 11110101 |                           **/
/**           +------------+----------+----------+                           **/
/**           |д�û��Ĵ���|          | 11100110 |                           **/
/**           +------------+----------+----------+                           **/
/**           |���û��Ĵ���|          | 11100111 |                           **/
/**           +------------+----------+----------+                           **/
/**           |   ��λ   |          | 11111110 |                           **/
/**           +------------+----------+----------+                           **/
/**--------------------------------------------------------------------------**/
/**ʹ��˵����                                                                **/
/**    1������SHT2xDevice����ʵ�壬�����ú���SHT2xInitialization��ʼ������   **/
/**       ʵ�塣SHT2x�豸��ַ�̶�Ϊ0x80                                      **/
/**    2��ʵ������void f(uint8_t devAddress,uint8_t *rData,uint16_t rSize)�� **/
/**       �����������丳ֵ��SHT2xDevice����ʵ���Receive����ָ�롣ʵ�����ݽ� **/
/**       �ա�                                                               **/
/**    3��ʵ������void f(uint8_t devAddress,uint8_t *tData,uint16_t tSize)�� **/
/**       �����������丳ֵ��SHT2xDevice����ʵ���Transmit����ָ�롣ʵ������  **/
/**       ���͡�                                                             **/
/**    4��ʵ������void f(volatile uint32_t nTime)�ĺ����������丳ֵ��        **/
/**       SHT2xDevice����ʵ���Delay����ָ�롣ʵ�ֲ�����ʱ����λ����         **/
/**    5��������Ӧ�ĺ���ʵ����Ҫ�Ĳ�����                                     **/
/**--------------------------------------------------------------------------**/
/** �޸ļ�¼��                                                               **/
/**     �汾      ����              ����              ˵��                   **/
/**     V1.0.0  2017-07-17          ľ��              �����ļ�               **/
/**     V1.0.1  2018-04-17          ľ��              ���SHT2x�����岢��  **/
/**                                                   �ĸ������β�           **/
/**                                                                          **/
/******************************************************************************/ 

#ifndef __SHT2XFUNCTION_H
#define __SHT2XFUNCTION_H

#include "stdint.h"
#include "stdbool.h"

/* ������������ */
#define MEASURE_RH_COMMAND_HOST         0XE5//����ģʽ��ȡ���ʪ��
#define MEASURE_T_COMMAND_HOST          0XE3//����ģʽ���¶�
#define MEASURE_RH_COMMAND_NOHOST       0XF5//������ģʽ�����ʪ��
#define MEASURE_T_COMMAND_NOHOST        0XF3//������ģʽ���¶�
#define READ_USER_REGISTER              0XE7//���û��Ĵ���
#define WRITE_USER_REGISTER             0XE6//д�û��Ĵ���
#define SOFT_RESET                      0XFE//��λ

/* ����SHT2X�����ֱ���ö�� */
typedef enum SHT2xDPI {
  SHT2x_DPI_RH12_T14,	//ʪ��12λ�¶�14λ����
  SHT2x_DPI_RH8_T13,	//ʪ��8λ�¶�13λ����
  SHT2x_DPI_RH10_T12,	//ʪ��10λ�¶�12λ����
  SHT2x_DPI_RH11_T11	//ʪ��11λ�¶�11λ����
}SHT2xDPIType;

/* ����SHT2X��ؽ���״̬ö�� */
typedef enum SHT2xBattery {
  SHT2x_End_High,			//���״̬VDD>2.25
  SHT2x_End_Low				//���״̬VDD<2.25
}SHT2xBatteryType;

/* ����SHT2X������״̬ö�� */
typedef enum SHT2xHeater {
  SHT2xHEATERDISABLE,    //����Ƭ�ڼ���
  SHT2xHEATERENABLE   	 //����Ƭ�ڼ���
}SHT2xHeaterType;

/* ����SHT2X OTP״̬ö�� */
typedef enum SHT2xOTP {
  SHT2xOTPENABLE,    //������OTP����
  SHT2xOTPDISABLE    //��������OTP����
}SHT2xOTPType;

/*����SHT2x����*/
typedef struct SHT2xObject{
  uint8_t userReg;      //�û��Ĵ���
  uint8_t devAddress;   //�豸��ַ
  uint8_t sn[8];        //�豸���к�
  uint16_t tempCode;    //�¶ȵ���ֵ��
  uint16_t humiCode;    //ʪ�ȵ���ֵ��
  void (*Delayms)(volatile uint32_t nTime);       //������ʱ����ָ��
  void (*Transmit)(struct SHT2xObject *sht,uint8_t *tData,uint16_t tSize);   //�������ݲ���ָ��
  void (*Receive)(struct SHT2xObject *sht,uint8_t *rData,uint16_t rSize);    //�������ݲ���ָ��
}SHT2xObjectType;

/* ������ʱ����ָ������ */
typedef void (*SHT2xDelayms)(volatile uint32_t nTime);
/* �������ݺ���ָ������ */
typedef void (*SHT2xTransmit)(struct SHT2xObject *sht,uint8_t *tData,uint16_t tSize);
/* �������ݺ���ָ������ */
typedef void (*SHT2xReceive)(struct SHT2xObject *sht,uint8_t *rData,uint16_t rSize);

/*��ȡSHT2x���¶�����*/
float GetSHT2xTemperatureValue(SHT2xObjectType *sht,uint8_t cmd);

/*��ȡSHT2x��ʪ������*/
float GetSHT2xHumidityValue(SHT2xObjectType *sht,uint8_t cmd);

/*�����λ*/
void SoftResetSHT2x(SHT2xObjectType *sht);

/* ��ʼ������SHT2x */
void SHT2xInitialization(SHT2xObjectType *sht,          //SHT2X�������
                         SHT2xDPIType dpi,              //�����ֱ�������
                         SHT2xBatteryType endBat,       //��ؽ���״̬����
                         SHT2xHeaterType heater,        //�������Ƿ���������
                         SHT2xOTPType otp,              //�Ƿ����OTP����
                         SHT2xTransmit write,           //д����ָ��
                         SHT2xReceive read,             //������ָ��
                         SHT2xDelayms delayms);         //������ʱָ��

#endif
/*********** (C) COPYRIGHT 1999-2019 Moonan Technology *********END OF FILE****/
