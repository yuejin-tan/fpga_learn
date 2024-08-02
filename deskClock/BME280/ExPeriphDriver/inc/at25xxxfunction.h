/******************************************************************************/
/** ģ�����ƣ���չ��������                                                   **/
/** �ļ����ƣ�at25xxxfunction.h                                              **/
/** ��    ����V1.0.0                                                         **/
/** ��    �飺����ʵ��SPI���нӿ�EEPROM AT25XXXϵ�еĲ�������1K��2K��4K��8K��**/
/**           16K��32K��64K��128K��256K��512K��1M��2M�ȶ�����������ͬ������  **/
/**           ���õ��豸��ַλ���Ĵ�����ַλ���ڲ��죬ÿһҳ���������ֽ���   **/
/**           Ҳ��һ���������������£�                                       **/
/**           +----------+---------------+-----------------+--------+        **/
/**           |   �ͺ�   |   �����ṹ    |    �Ĵ�����ַ   |ÿҳ�ֽ�|        **/
/**           +----------+---------------+-----------------+--------+        **/
/**           | AT25010B | 128x8(1K)     | 7λ(1���Ĵ���)  |  8�ֽ� |        **/
/**           +----------+---------------+-----------------+--------+        **/
/**           | AT25020B | 256x8(2K)     | 8λ(1���Ĵ���)  |  8�ֽ� |        **/
/**           +----------+---------------+-----------------+--------+        **/
/**           | AT25040B | 512x8(4K)     | 9λ(1���Ĵ���)  |  8�ֽ� |        **/
/**           +----------+---------------+-----------------+--------+        **/
/**           | AT25080B | 1024x8(8K)    | 10λ(1���Ĵ���) | 32�ֽ� |        **/
/**           +----------+---------------+-----------------+--------+        **/
/**           | AT25160B | 2048x8(16K)   | 11λ(1���Ĵ���) | 32�ֽ� |        **/
/**           +----------+---------------+-----------------+--------+        **/
/**           | AT25320B | 4096x8(32K)   | 12λ(2���Ĵ���) | 32�ֽ� |        **/
/**           +----------+---------------+-----------------+--------+        **/
/**           | AT25640B | 8192x8(64K)   | 13λ(2���Ĵ���) | 32�ֽ� |        **/
/**           +----------+---------------+-----------------+--------+        **/
/**           | AT25128B | 16384x8(128K) | 14λ(2���Ĵ���) | 64�ֽ� |        **/
/**           +----------+---------------+-----------------+--------+        **/
/**           | AT25256B | 32768x8(256K) | 15λ(2���Ĵ���) | 64�ֽ� |        **/
/**           +----------+---------------+-----------------+--------+        **/
/**           | AT25512  | 65536x8(512K) | 16λ(2���Ĵ���) | 128�ֽ�|        **/
/**           +----------+---------------+-----------------+--------+        **/
/**           | AT25M01  | 131072x8(1M)  | 17λ(3���Ĵ���) | 256�ֽ�|        **/
/**           +----------+---------------+-----------------+--------+        **/
/**           | AT25M02  | 262144x8(2M)  | 18λ(3���Ĵ���) | 256�ֽ�|        **/
/**           +----------+---------------+-----------------+--------+        **/
/**           AT25040B��Ҫ9λ�Ĵ�����ַ����ֻ����һ����ַ�ֽڣ����λ��ַ����**/
/**           ���ǲ�������ĵ�3λ��ʵ�ֵġ�                                  **/
/**--------------------------------------------------------------------------**/
/** �޸ļ�¼��                                                               **/
/**     �汾      ����              ����              ˵��                   **/
/**     V1.0.0  2017-07-17          ľ��              �����ļ�               **/
/**                                                                          **/
/******************************************************************************/ 

#ifndef __AT25XXXFUNCTION_H
#define __AT25XXXFUNCTION_H

#include "stdint.h"

/* ��������� */
#define AT25_WREN       0x06		//дʹ��
#define AT25_WRDI       0x04		//дʧ��
#define AT25_RDSR       0x05		//��״̬�Ĵ���
#define AT25_WRSR       0x01		//д״̬�Ĵ���
#define AT25_READ       0x03		//���洢����
#define AT25_WRITE      0x02		//д�洢����

#define AT25_WPEN       0x80	//д����ʹ��
#define AT25_BPNONE     0x00	//�ޱ�������
#define AT25_BPQUARTER  0x04	//�����ķ�֮һ����
#define AT25_BPHALF     0x08	//����һ������
#define AT25_BPALL      0x0C	//����ȫ������

/*����AT25XXX����ö��*/
typedef enum At25Mode {
  AT25010B,
  AT25020B,
  AT25040B,
  AT25080B,
  AT25160B,
  AT25320B,
  AT25640B,
  AT25128B,
  AT25256B,
  AT25512,
  AT25M01,
  AT25M02,
  AT25Number
}At25ModeType;

/*����洢���Ĵ�����ַ�ֽ�ö��*/
typedef enum At25MemAddLength {
  AT258BitMemAdd,
  AT2516BitMemAdd,
  AT2524BitMemAdd
}At25MemAddLengthType;

/* ����Ƭѡ�ź�ö�� */
typedef enum AT25xxxCS
{
  AT25CS_Enable,
  AT25CS_Disable
}AT25xxxCSType;

/* ����д��������ö�� */
typedef enum FM25WP {
  AT25WP_Enable,
  AT25WP_Disable
}AT25WPType;

/* ����Ƭѡ�ź�ö�� */
typedef enum AT25Hold {
  AT25Hold_Enable,
  AT25Hold_Disable
}AT25HoldType;

/*����AT25XXX��������*/
typedef struct At25Object {
  uint8_t status;       //״̬�Ĵ���
  At25ModeType mode;    //�豸����
  At25MemAddLengthType memAddLength;    //�Ĵ�����ַ����
  void (*Read)(uint8_t *rData,uint16_t rSize);  //�����ݲ���ָ��
  void (*Write)(uint8_t *wData,uint16_t wSize); //д���ݲ���ָ��
  void (*Delayms)(volatile uint32_t nTime);     //������ʱ����ָ��
  void (*ChipSelect)(AT25xxxCSType cs); //ʹ��SPI�ӿ�ʱ��Ƭѡ����
  void (*WP)(AT25WPType wp);            //д��������
  void (*Hold)(AT25HoldType hold);      //�����ź�
}At25ObjectType;

/* ��������ݲ�������ָ������ */
typedef void (*AT25Read)(uint8_t *rData,uint16_t rSize);
/* ����д���ݲ�������ָ������ */
typedef void (*AT25Write)(uint8_t *wData,uint16_t wSize);
/* ������ʱ��������ָ������ */
typedef void (*AT25Delayms)(volatile uint32_t nTime);
/* ����ʹ��SPI�ӿ�ʱ��Ƭѡ��������ָ������ */
typedef void (*AT25ChipSelect)(AT25xxxCSType cs);
/*д��������*/
typedef void (*AT25WP)(AT25WPType wp);
/*�����ź�*/
typedef void (*AT25Hold)(AT25HoldType hold);

/*��AT25XXX��ȡ�����ֽ�,�������ַ��ȡ*/
uint8_t ReadByteFromAT25xxx(At25ObjectType *at,uint32_t regAddress);

/*��AT25XXXд�뵥���ֽ�*/
void WriteByteToAT25xxx(At25ObjectType *at,uint32_t regAddress,uint8_t data);

/* AT25XXX����дʹ��������*/
void SetWriteEnableLatchForAT25xxx(At25ObjectType *at);

/* AT25XXX��λдʹ��������*/
void ResetWriteEnableLatchForAT25xxx(At25ObjectType *at);

/*��AT25xxx״̬�Ĵ���*/
void ReadStatusForAT25xxx(At25ObjectType *at);

/*дAT25xxx״̬�Ĵ���*/
void WriteStatusForAT25xxx(At25ObjectType *at,uint8_t cmd);

/*��AT25XXX��ȡ����ֽڣ���ָ����ַ��ൽ����ҳ�Ľ�β*/
void ReadBytesFromAT25xxx(At25ObjectType *at,uint32_t regAddress,uint8_t *rData,uint16_t rSize);

/*��AT25XXXд�����ֽڣ���ָ����ַ��ൽ����ҳ�Ľ�β*/
void WriteBytesToAT25xxx(At25ObjectType *at,uint32_t regAddress,uint8_t *wData,uint16_t wSize);

/* ��ʼ��AT25XXX���� */
void At25xxxInitialization(At25ObjectType *at,  //AT25XXX����ʵ��
                           At25ModeType mode,   //AT25XXX��������
                           AT25Read read,       //��AT25XXX�������ָ��
                           AT25Write write,     //дAT25XXX�������ָ��
                           AT25Delayms delayms, //��ʱ����ָ��
                           AT25ChipSelect cs    //Ƭѡ��������ָ��
                          );

#endif
/*********** (C) COPYRIGHT 1999-2017 Moonan Technology *********END OF FILE****/
