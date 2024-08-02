/******************************************************************************/
/** ģ�����ƣ���չ��������                                                   **/
/** �ļ����ƣ�mlx90614function.h                                             **/
/** ��    ����V1.0.0                                                         **/
/** ��    �飺����ʵ��MLX90614�����¶ȴ�������ͨѶ                           **/
/**           ����SMBusͨѶͨѶ�ӿ�                                          **/
/**--------------------------------------------------------------------------**/
/**ʹ��˵����                                                                **/
/**    SMBusͨѶͨѶ�ӿڵĶ��������I2C�ӿڶ�����ͬ�����Բ���Ӳ��I2C�ӿں�   **/
/**    ���ģ��I2C�ӿ�ʵ��ͨѶ��                                             **/
/**    1������MLX90614����ʵ�壬�����ú���MLXInitialization��ʼ������ʵ�塣  **/
/**       ��ʼ��ʱ����������ĵ�ַ��                                         **/
/**    2��ʵ������void f(struct MLXObject *mlx,uint8_t cmd,uint8_t *rData,   **/
/**       uint16_t rSize)�ĺ����������丳ֵ��MLX90614����ʵ���Read����ָ�롣**/
/**       ʵ�����ݵĶ�ȡ������                                               **/
/**    3��ʵ������void f(struct MLXObject *mlx,uint8_t cmd,uint8_t *wData,   **/
/**       uint16_t wSize)�ĺ����������丳ֵ��MLX90614����ʵ���Write����ָ   **/
/**       �롣ʵ�����ݵ�д������                                             **/
/**    4��ʵ������oid f(volatile uint32_t nTime)�ĺ����������丳ֵ��MLX90614t**/
/**       ����ʵ���Delay����ָ�롣ʵ����ʱ������ʱ�䵥λΪ���롣            **/
/**    5��������Ӧ�ĺ���ʵ����Ҫ�Ĳ�����                                     **/
/**--------------------------------------------------------------------------**/
/** �޸ļ�¼��                                                               **/
/**     �汾      ����              ����              ˵��                   **/
/**     V1.0.0  2019-05-05          ľ��              �����ļ�               **/
/**                                                                          **/
/******************************************************************************/ 

#ifndef __MLX90614FUNCTION_H
#define __MLX90614FUNCTION_H

#include "stdint.h"

/*����MLX90614��������*/
typedef struct MLXObject {
  uint8_t devAddress;           //����ĵ�ַ
  uint8_t flags;                //����״̬��־
  uint16_t pwmctrl;             //PWM���ƼĴ���
  uint16_t ConfigRegister;      //���üĴ���
  uint16_t ID[4];               //�����IDֵ
  float tempAmbient;            //�¶�ֵ
  float tempObject1;            //�¶�ֵ
  float tempObject2;            //�¶�ֵ
  void (*Read)(struct MLXObject *mlx,uint8_t cmd,uint8_t *rData,uint16_t rSize);    //�����ݲ���ָ��
  void (*Write)(struct MLXObject *mlx,uint8_t cmd,uint8_t *wData,uint16_t wSize);   //д���ݲ���ָ��
  void (*Delayus)(volatile uint32_t nTime);       //��ʱ����ָ��
}MLXObjectType;

/*�����MLX90614���ݲ���ָ������*/
typedef void (*MLXRead)(struct MLXObject *mlx,uint8_t cmd,uint8_t *rData,uint16_t rSize);
/*����дMLX90614���ݲ���ָ������*/
typedef void (*MLXWrite)(struct MLXObject *mlx,uint8_t cmd,uint8_t *wData,uint16_t wSize);
/*����΢����ʱ����ָ������*/
typedef void (*MLXDelayus)(volatile uint32_t nTime);

/*��ȡ�¶�ֵ*/
void GetMLXTemperature(MLXObjectType *mlx);

/* ��״̬ */
uint16_t ReadFlagFromMLX(MLXObjectType *mlx);

/* ʹ�豸��������״̬ */
void EnterSleepModeForMLX(MLXObjectType *mlx);

/* ����PWM���� */
void SetPWMControll(MLXObjectType *mlx,uint16_t data);

/* �������üĴ��� */
void SetConfigRegister(MLXObjectType *mlx,uint16_t data);

/* �޸��豸��ַ */
void ModifyDeviceAddress(MLXObjectType *mlx,uint16_t address);

/* �����¶ȴ����������ʼ�� */
void MLXInitialization(MLXObjectType *mlx,      //MLX90614����
                       uint8_t address,         //�豸��ַ
                       MLXRead read,            //�����ݺ���ָ��
                       MLXWrite write,          //д���ݺ���ָ��
                       MLXDelayus delayus       //΢����ʱ����ָ��
                      );

#endif
/*********** (C) COPYRIGHT 1999-2019 Moonan Technology *********END OF FILE****/
