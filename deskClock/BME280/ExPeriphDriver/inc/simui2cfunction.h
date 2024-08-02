/******************************************************************************/
/** ģ�����ƣ��Զ���ͨ�ù���                                                 **/
/** �ļ����ƣ�simui2cfunction.h                                              **/
/** ��    ����V1.0.0                                                         **/
/** ��    �飺����ʹ��GPIOģ��I2CӲ���ӿ�ͨѶ                                **/
/**           ����C���Ա�д��������ͨ��MCU                                   **/
/**           SCL��������Ϊ�������                                          **/
/**           SDA��������Ϊ��©������ڶ�ȡʱ����Ϊ�ߵ�ƽ                    **/
/**           �ٶȿ����ø���0K������400K��������Ĭ��ֵΪ100K                 **/
/**--------------------------------------------------------------------------**/
/**ʹ��˵����                                                                **/
/**    1������GPIOģ��I2C����ʵ�壨�磺SimuI2CTypeDef si2c���������ú���     **/
/**       SimuI2CInitialization��ʼ������ʵ�塣��ʼ��ʱ����������Ƶ��1-500K  **/
/**       ��kHzΪ��λ����Сʼ������Ϊ2΢�룬���Ϊ500k΢�롣                 **/
/**    2��ʵ������void f(SimuI2CPinValue op)�ĺ����������丳ֵ               **/
/**       ��SimuI2CTypeDef����ʵ���SetSCLPin����ָ�롣���Բ���SCL���š�     **/
/**    3��ʵ������void f(SimuI2CPinValue op)�ĺ����������丳ֵ               **/
/**       ��SimuI2CTypeDef����ʵ���SetSDAPin����ָ�롣���Բ���SDA���š�     **/
/**    4��ʵ������uint8_t f(void)�ĺ����������丳ֵ��SimuI2CTypeDef����ʵ��  **/
/**       ��ReadSDAPin����ָ�롣���Զ�ȡSDA���š�                            **/
/**    5��ʵ������void f(volatile uint32_t period)�ĺ����������丳ֵ         **/
/**       ��SimuI2CTypeDef����ʵ���Delayus����ָ�롣����������ʱ����λΪ΢��**/
/**    6��������Ӧ�ĺ���ʵ����Ҫ�Ĳ�����                                     **/
/**--------------------------------------------------------------------------**/
/** �޸ļ�¼��                                                               **/
/**     �汾      ����              ����              ˵��                   **/
/**     V1.0.0  2017-05-15          ľ��              �����ļ�               **/
/**     V1.0.1  2018-08-28          ľ��              �޸�Ϊ�������         **/
/**                                                                          **/
/******************************************************************************/ 

#ifndef __SIMUI2C_FUNCTION_H
#define __SIMUI2C_FUNCTION_H

#include "stdint.h"
#include "stdbool.h"

typedef enum SimuI2CPinValue{
  Set=1,
  Reset=(!Set)
}SimuI2CPinValue;

typedef enum SimuI2CPin{
  SCL=0,
  SDA=1
}SimuI2CPin;

typedef enum SimuI2CStatus{
  I2C_OK=0,
  I2C_ERROR=1,
}SimuI2CStatus;

typedef struct SimuI2CObject{
  uint32_t period;                              //ȷ���ٶ�Ϊ����0KС�ڵ���400K��������Ĭ��Ϊ100K
  void (*SetSCLPin)(SimuI2CPinValue op);        //����SCL����
  void (*SetSDAPin)(SimuI2CPinValue op);        //����SDA����
  uint8_t (*ReadSDAPin)(void);                  //��ȡSDA����λ
  void (*Delayus)(volatile uint32_t period);    //�ٶ���ʱ����
}SimuI2CObjectType;

typedef void (*SimuI2CSetPin)(SimuI2CPinValue op);      //����SDA����
typedef uint8_t (*SimuI2CReadSDAPin)(void);             //��ȡSDA����λ
typedef void (*SimuI2CDelayus)(volatile uint32_t period);       //�ٶ���ʱ����

/* GPIOģ��I2CͨѶ��ʼ�� */
void SimuI2CInitialization(SimuI2CObjectType *simuI2CInstance,
                           uint32_t speed,
                           SimuI2CSetPin setSCL,
                           SimuI2CSetPin setSDA,
                           SimuI2CReadSDAPin readSDA,
                           SimuI2CDelayus delayus);

/* ͨ��ģ��I2C���վд���� */
SimuI2CStatus WriteDataBySimuI2C(SimuI2CObjectType *simuI2CInstance,uint8_t deviceAddress,uint8_t *wData,uint16_t wSize);

/* ͨ��ģ��I2C�Դ�վ������ */
SimuI2CStatus ReadDataBySimuI2C(SimuI2CObjectType *simuI2CInstance,uint8_t deviceAddress,uint8_t *rData, uint16_t rSize);

/* ͨ��ģ��I2Cʵ�ֶԴ�վ��д���ݽ��Ӷ�������ϲ��� */
SimuI2CStatus WriteReadDataBySimuI2C(SimuI2CObjectType *simuI2CInstance,uint8_t deviceAddress, uint8_t *wData,uint16_t wSize,uint8_t *rData, uint16_t rSize);

#endif  /*__SIMUI2C_FUNCTION_H ����*/

/*********** (C) COPYRIGHT 1999-2018 Moonan Technology *********END OF FILE****/
