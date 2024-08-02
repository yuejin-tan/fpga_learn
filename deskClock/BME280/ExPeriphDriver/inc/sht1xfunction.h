/******************************************************************************/
/** ģ�����ƣ���չ��������                                                   **/
/** �ļ����ƣ�sht1xfunction.h                                                **/
/** ��    ����V1.1.0                                                         **/
/** ��    �飺����ʵ��SHT1X��ʪ�ȼƵĲ�������������I2C��ͨѶ��ʽ             **/
/**           ����SHT10,SHT11��SHT15�Լ�SHT7x                                **/
/**           Ĭ�Ϸֱ���14bit(�¶�)��12bit(ʪ��)���Ա�����Ϊ12��8bit         **/
/**           �¶�ת����ʽ��T=d1+d2*SOT������SOTΪ���������TΪ�¶�ֵ        **/
/**           d1��d2��ȡֵ���£�                                             **/
/**           VDD               d1 (��C)         d1 (��F)                    **/
/**           5V                -40.1           -40.2                        **/
/**           4V                -39.8           -39.6                        **/
/**           3.5V              -39.7           -39.5                        **/
/**           3V                -39.6           -39.3                        **/
/**           2.5V              -39.4           -38.9                        **/
/**                                                                          **/
/**           SOT               d2 (��C)         d2 (��F)                    **/
/**           14bit             0.01            0.018                        **/
/**           12bit             0.04            0.072                        **/
/**           ʪ�����ݵ�ת����ʽ��RHlinear=c1+c2*SORH+c3*SORH*SORH��         **/
/**           ����SORHΪ���������RHlinearΪת������ֶ�ʪ��                 **/
/**           SORH	  c1	          c2	          c3                 **/
/**           12bit	-2.0468         0.0367          -1.5955E-6           **/
/**           8bit	-2.0468         0.5872          -4.0845E-4           **/
/**           ʪ���¶Ȳ�����ʽ��RHtrue=(T-25)*(t1+t2*SORH)+RHlinear          **/
/**           ����RHtrueΪ�¶Ȳ���������ʪ��                               **/
/**           SORH	  t1	  t2                                         **/
/**           12bit	0.01	0.00008                                      **/
/**           8bit	0.01	0.00128                                      **/
/**--------------------------------------------------------------------------**/
/**ʹ��˵����                                                                **/
/**    1������Sht1xObjectType����ʵ�壬�����ú���SHT1xInitialization��ʼ��   **/
/**       ����ʵ�塣�����豸�Ĺ�����Դ��ѹVDD�Լ��¶ȵ�λ�����϶Ȼ��϶ȣ�  **/
/**    2��ʵ����������void f(BusPinValue value)��������������������ֱ��    **/
/**       ��SCK��SDA��������BusPinOperation���͵ĺ���ָ�����飬SCK�Ĳ�����   **/
/**       ����Ϊ��һ��Ԫ�أ�SDA�Ĳ���������Ϊ�ڶ���Ԫ�ء���������ָ�������  **/
/**       ָ�븳ֵ��Sht1xObjectType����ʵ���SetBusPin����ָ�롣ʵ�ֶ�SCK��  **/
/**       �ź�SDA���ŵĲ�����                                                **/
/**    3��ʵ������uint8_t f(void)�ĺ����������丳ֵ��Sht1xObjectType����ʵ�� **/
/**       ��ReadSDABit����ָ�롣ʵ�����ݵĶ�ȡ��                             **/
/**    4��ʵ������void f(IODirection direction);�ĺ����������丳ֵ��         **/
/**       Sht1xObjectType����ʵ���SetSDADirection����ָ�롣ʵ�ֶ�̬�ı�SDA��**/
/**       �ŵ������������                                                   **/
/**    5��ʵ������void f(volatile uint32_t period)�ĺ����������丳ֵ��       **/
/**       Sht1xObjectType����ʵ���Delayus����ָ�롣ʵ�ֲ�����ʱ����λ΢��   **/
/**    6��ʵ������void f(volatile uint32_t nTime)�ĺ����������丳ֵ��        **/
/**       Sht1xObjectType����ʵ���Delayms����ָ�롣ʵ�ֲ�����ʱ����λ����   **/
/**    7��������Ӧ�ĺ���ʵ����Ҫ�Ĳ�����                                     **/
/**--------------------------------------------------------------------------**/
/** �޸ļ�¼��                                                               **/
/**     �汾      ����              ����              ˵��                   **/
/**     V1.0.0  2017-01-13          ľ��              �����ļ�               **/
/**     V1.1.0  2019-05-19          ľ��              �޸�Ϊ�������         **/
/**                                                                          **/
/******************************************************************************/ 

#ifndef _sht1xfunction_h
#define _sht1xfunction_h

#include "stdint.h"
#include "stdbool.h"

/* ����SHT1X�������ŵ�����ֵö�� */
typedef enum SHT1xPinValue{
  SHT1xSet=1,
  SHT1xReset=(!SHT1xSet)
}SHT1xPinValueType;

/* ����SHT1X����IO����ö�� */
typedef enum SHT1xIOMode{
  SHT1xOut=1,
  SHT1xIn=(!SHT1xOut)
}SHT1xIOModeType;

/* ����SHT1X��������ö�� */
typedef enum SHT1XPin{
  SckPin=0,
  DataPin=1
}SHT1XPinType;

/* �����¶ȵ�λö�� */
typedef enum SHT1xTempUnit{
  DegreeCentigrade,	//���϶�
  DegreeFahrenheit	//���϶�
}SHT1xTempUnitType;

/* ����SHT1X�ڲ����ȿ���ö�� */
typedef enum SHT1xHeater {
  SHT1xHeaterDisable,
  SHT1xHeaterEbable
}SHT1xHeaterType;

/* ����SHT1X OTP����ö�� */
typedef enum SHT1xOTP {
  SHT1xOTPEbable,
  SHT1xOTPDisable	
}SHT1xOTPType;

/* ����SHT1X��������ö�� */
typedef enum SHT1xResolution {
  SHT1xHighResolution,
  SHT1xLowResolution
}SHT1xResolutionType;

/* ����GPIO������������ĺ���ָ�� */
typedef void(*SHT1xSetBusPin)(SHT1xPinValueType value);
/* ���������ߺ��� */
typedef uint8_t (*SHT1xReadSDABit)(void);
/* �������߷�����ƺ��� */
typedef void (*SHT1xSDADirection)(SHT1xIOModeType direction);
/* ΢����ʱ���� */
typedef void (*SHT1xDelay)(volatile uint32_t period);

/* ����SHT1x�������� */
typedef struct Sht1xObject {
  uint8_t statusReg;            //״̬�Ĵ���
  SHT1xTempUnitType tempUnit;   //�¶ȵ�λ
  uint32_t period;              //SCKʱ������
  float vdd;                    //������ѹ
  float temperature;            //�¶�
  float humidity;               //ʪ��
  float dewPoint;               //¶��
  SHT1xSetBusPin *SetBusPin;    //���߲�������
  uint8_t (*ReadSDABit)(void);	//���������ߺ���
  void (*SDADirection)(SHT1xIOModeType direction);      //�������߷�����ƺ���
  void (*Delayus)(volatile uint32_t period);    //΢����ʱ����
  void (*Delayms)(volatile uint32_t nTime);     //��������ʱ����
}Sht1xObjectType;

/* ��ʼ��SHT1x���� */
void SHT1xInitialization(Sht1xObjectType *sht,          //SHT1X�������
                         uint32_t sck,                  //SCKʱ��Ƶ��
                         float vdd,                     //������ѹ
                         SHT1xTempUnitType uint,        //�¶ȵ�λ
                         SHT1xHeaterType heater,        //�Ƿ����ü���������
                         SHT1xOTPType otp,              //�Ƿ����OTP����
                         SHT1xResolutionType resolution,//�����ֱ�������
                         SHT1xSetBusPin setSckPin,      //SCK���Ų�������
                         SHT1xSetBusPin setDataPin,     //DATA���Ų�������
                         SHT1xReadSDABit readSDA,       //��DATA���ź���
                         SHT1xSDADirection direction,   //DATA���ŷ������ú���
                         SHT1xDelay delayus,            //΢����ʱ����
                         SHT1xDelay delayms);           //������ʱ����

/* ��ȡSHT1x�������� */
void GetSht1xMeasureValue(Sht1xObjectType *sht);

/*��ȡSHT1X��ʪ��ֵ*/
float GetSht1xHumidityValue(Sht1xObjectType *sht);

/*��ȡSHT1X���¶�ֵ*/
float GetSht1xTemperatureValue(Sht1xObjectType *sht);

/*SHT1XͨѶ��λ*/
void ResetSHT1XCommunication(Sht1xObjectType *sht);

/*��SHT1Xʵ�������λ*/
uint8_t Sht1xSoftwareReset(Sht1xObjectType *sht);

#endif
/*********** (C) COPYRIGHT 1999-2017 Moonan Technology *********END OF FILE****/
