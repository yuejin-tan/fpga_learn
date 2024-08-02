/******************************************************************************/
/** ģ�����ƣ���չ��������                                                   **/
/** �ļ����ƣ�ad527xfunction.h                                               **/
/** ��    ����V1.0.2                                                         **/
/** ��    �飺�����Ͷ���AD527xϵ�����ֵ�λ��оƬ��صĸ��ֺ����Ͳ���         **/
/**           �����������AD5270��AD5271��AD5272��AD5274оƬ                 **/
/**           ���У�AD5270��AD5271����SPI�ӿ�(CPOL = 0, CPHA = 1)            **/
/**                 AD5272��AD5274����I2C�ӿ�                                **/
/**           ����һλ�Ĵ����ĸ�ʽ���£�                                     **/
/**           +---+---+--+--+--+--+--+--+--+--+--+--+--+--+--+--+            **/
/**           |δ���� |  ����λ   |          ����λ             |            **/
/**           +---+---+--+--+--+--+--+--+--+--+--+--+--+--+--+--+            **/
/**           | 0 | 0 |C3|C2|C1|C0|D9|D8|D7|D6|D5|D4|D3|D2|D1|D0|            **/
/**           +---+---+--+--+--+--+--+--+--+--+--+--+--+--+--+--+            **/
/**--------------------------------------------------------------------------**/
/**ʹ��˵����                                                                **/
/**    1������AD527x����ʵ�壬�����ú���AD527xInitialization��ʼ������ʵ�塣 **/
/**    2����ʼ��ʱ������������ΪAD5272��AD5274������豸��ַ���Ա�I2CͨѶ��  **/
/**       ����������ΪAD5270��AD5271��ʵ������void f(bool en)�ĺ�����������  **/
/**       ��ֵAD527x����ʵ���ChipSelcet����ָ�롣�Ա�SPIͨѶ��              **/
/**    3��ʵ������void f(struct AD527xObject *rx,uint8_t *rData,             **/
/**       uint16_t rSize)�ĺ����������丳ֵ��AD527x����ʵ���Receive����     **/
/**       ָ�롣��������ݲ���                                               **/
/**    4��ʵ������void f(struct AD527xObject *rx,uint8_t *wData,             **/
/**       uint16_t wSize)�ĺ����������丳ֵ��AD527x����ʵ���Transmit����    **/
/**       ָ�롣���д���ݲ���                                               **/
/**    5��ʵ������void f(volatile uint32_t nTime)��ʱ�����������丳ֵ��      **/
/**       AD527x����ʵ���Delay����ָ�롣��λΪ���롣                        **/
/**    6��������Ӧ�ĺ���ʵ����Ҫ�Ĳ�����                                     **/
/**--------------------------------------------------------------------------**/
/** �޸ļ�¼��                                                               **/
/**     �汾      ����              ����              ˵��                   **/
/**     V1.0.0  2019-04-01          ľ��              �����ļ�               **/
/**                                                                          **/
/******************************************************************************/ 

#ifndef __AD5270_FUNCTION_H
#define __AD5270_FUNCTION_H

#include "stdint.h"
#include "stdbool.h"

/* ����AD527x����ö�� */
typedef enum AD527x {
  AD5270,
  AD5271,
  AD5272,
  AD5274
}AD527xType;

/*����Ƭѡ����ö��*/
typedef enum AD527xCS {
  AD527xCS_ENABLE,
  AD527xCS_DISABLE
}AD527xCSType;

/*��������SPI�ӿڵĶ�������*/
typedef struct AD527xObject {
  AD527xType type;      //�豸����
  uint8_t devAddress;   //�豸��ַ,����I2C�ӿ�
  uint8_t conreg;       //���ƼĴ���
  uint16_t rdac;        //�α�Ĵ�����ֵ
  void (*ChipSelect)(AD527xCSType en);		//Ƭѡ�źţ�����SPI�ӿ�
  void (*Receive)(struct AD527xObject *rx,uint8_t *rData,uint16_t rSize);
  void (*Transmit)(struct AD527xObject *rx,uint8_t *wData,uint16_t wSize);
  void (*Delayms)(volatile uint32_t nTime);       //ms��ʱ����ָ��
}AD527xObjectType;

/*����Ƭѡ�źź���ָ������*/
typedef void (*AD527xChipSelect)(AD527xCSType en);
/*����������ݺ���ָ������*/
typedef void (*AD527xReceive)(struct AD527xObject *rx,uint8_t *rData,uint16_t rSize);
/*���巢�����ݺ���ָ������*/
typedef void (*AD527xTransmit)(struct AD527xObject *rx,uint8_t *wData,uint16_t wSize);
/*����ms��ʱ����ָ��*/
typedef void (*AD527xDelayms)(volatile uint32_t nTime);       

/* ��AD527xд���� */
void SetRDACForAd527x(AD527xObjectType *rx,uint16_t data);

/* ��ȡRDAC�α�Ĵ��������� */
uint16_t ReadRDACFromAd527x(AD527xObjectType *rx);

/* �����λ */
void AD527xSoftwareReset(AD527xObjectType *rx);

/* �洢�α����ã���RDAC���ô洢��50-TP�� */
void StoreRDACTo50TP(AD527xObjectType *rx);

/* ��ָ���洢λ�õ����� */
uint16_t ReadGivenAddressValue(AD527xObjectType *rx,uint8_t address);

/* ��ȡ���һ��50-TP��̴洢��λ�õĵ�ַ */
uint8_t ReadLast50TPAddress(AD527xObjectType *rx);

/* ��ʼ��AD527x����,I2C�ӿڱ����ʼ��devAddress��SPI�ӿڱ����ʼ��void (*ChipSelcet)(bool) */
void AD527xInitialization(AD527xObjectType *rx,
                          uint8_t address,
                          AD527xType type,
                          AD527xReceive recieve,
                          AD527xTransmit transmit,
                          AD527xChipSelect cs,
                          AD527xDelayms delayms);

#endif  //__AD5270_FUNCTION_H

/*********** (C) COPYRIGHT 1999-2019 Moonan Technology *********END OF FILE****/
