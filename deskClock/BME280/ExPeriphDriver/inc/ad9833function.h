/******************************************************************************/
/** ģ�����ƣ���չ��������                                                   **/
/** �ļ����ƣ�ad9833function.c                                               **/
/** ��    ����V1.0.0                                                         **/
/** ��    �飺�����Ͷ���AD9833�ɱ�̲��η�������صĸ��ֺ����Ͳ���           **/
/**           AD9833�ɱ�̲��η���������SPIͨѶ�ӿڣ��������ɲ�ͬƵ�ʺͷ�ֵ  **/
/**           �����Ҳ������ǲ��ͷ���������һ��16λ���ƼĴ������£�           **/
/**           ��λ�ֽ����£�                                                 **/
/**           +----+----+----+----+-------+-------+---+-----+                **/
/**           |DB15|DB14|DB13|DB12|  DB11 |  DB10 |DB9| DB8 |                **/
/**           +----+----+----+----+-------+-------+---+-----+                **/
/**           | 0  | 0  | B28| HLB|FSELECT|PSELECT| 0 |RESET|                **/
/**           +----+----+----+----+-------+-------+---+-----+                **/
/**           ��λ�ֽ����£�                                                 **/
/**           +------+-------+-------+---+----+---+----+---+                 **/
/**           |  DB7 |  DB6  |  DB5  |DB4| DB3|DB2| DB1|DB0|                 **/
/**           +------+-------+-------+---+----+---+----+---+                 **/
/**           |SLEEP1|SLEEP12|OPBITEN| 0 |DIV2| 0 |MODE| 0 |                 **/
/**           +------+-------+-------+---+----+---+----+---+                 **/
/**           ����DB12Ҫ��DB13���ʹ�ã�DB3��DB1Ҫ��DB5���ʹ�á�            **/
/**--------------------------------------------------------------------------**/
/**ʹ��˵����                                                                **/
/**    1������AD9833����ʵ�壬�����ú���AD9833Initialization��ʼ������ʵ�塣 **/
/**    ��ʼ��ʱ������ʼ��Ƶ��MCLK����λΪMHz��                               **/
/**    2��ʵ������void f(uint8_t *tData,uint16_t tSize)�ĺ����������丳ֵ    **/
/**    ��AD9833����ʵ���WriteDataToDAC����ָ�롣                            **/
/**    3��ʵ������void f(bool en)�ĺ����������丳ֵAD9833����ʵ���ChipSelcet**/
/**    ����ָ�롣                                                            **/
/**    4��������Ӧ�ĺ���ʵ����Ҫ�Ĳ�����                                     **/
/**--------------------------------------------------------------------------**/
/** �޸ļ�¼��                                                               **/
/**     �汾      ����              ����              ˵��                   **/
/**     V1.0.0  2019-05-16          ľ��              �����ļ�               **/
/**                                                                          **/
/******************************************************************************/ 

#ifndef __AD9833FUNCTION_H
#define __AD9833FUNCTION_H

#include "stdint.h"

/* ����AD9833���ģʽö�� */
typedef enum Ad9833Out {
  sinusoid=0,
  triangular,
  square_msb_2,
  square_msb
}Ad9833OutMode;

/* ����AD9833����ģʽö�� */
typedef enum Ad9833Sleep {
  NoSleep=0,
  DACTurnOff,
  MCLKTurnOff,
  DACMCLKTurnOff
}Ad9833SleepMode;

/* ����AD9833Ƶ�ʼĴ���ö�� */
typedef enum Ad9833Freq {
  FREQ0,
  FREQ1
}Ad9833FreqReg;

/* ����AD9833��λ�Ĵ���ö�� */
typedef enum Ad9833Phase {
  PHASE0,
  PHASE1
}Ad9833PhaseReg;

/*����Ƭѡ����ö��*/
typedef enum AD9833CS {
  AD9833CS_ENABLE,
  AD9833CS_DISABLE
}AD9833CSType;

/* �����дƵ�ʼĴ���ö�� */
typedef enum WriteAd9833Freq {
  FREQ0_B28,            //Ƶ�ʼĴ���0ȫ28λ
  FREQ0_B14_LSB,        //Ƶ�ʼĴ���0��14λ
  FREQ0_B14_MSB,        //Ƶ�ʼĴ���0��14λ
  FREQ1_B28,            //Ƶ�ʼĴ���1ȫ28λ
  FREQ1_B14_LSB,        //Ƶ�ʼĴ���1��14λ
  FREQ1_B14_MSB         //Ƶ�ʼĴ���1��14λ
}WriteAd9833FreqReg;

/* ����AD9833�������� */
typedef struct Ad9833Object{
  uint16_t ctlRegister;         //���ƼĴ���
  float freqConstant;           //Ƶ�ʼ��㳣��
  void (*WriteData)(uint8_t *tData,uint16_t tSize);     //��DAC��������
  void (*ChipSelcet)(AD9833CSType en);  //Ƭѡ�ź�
  void (*Delayms)(volatile uint32_t nTime);     //ms��ʱ����ָ��
}Ad9833ObjectType;

/* ����AD9833д����ָ������ */
typedef void (*AD9833WriteData)(uint8_t *tData,uint16_t tSize);
/* ����AD9833Ƭѡ����ָ������ */
typedef void (*AD9833ChipSelcet)(AD9833CSType en);
/* ����AD9833 ms��ʱ����ָ������ */
typedef void (*AD9833Delayms)(volatile uint32_t nTime);

/* ����AD9833���ƼĴ��������� */
#define AD9833_CTRLB28          (0x1 << 13)		//����Ƶ�ʼĴ�����д�뷽ʽ
#define AD9833_CTRLHLB          (0x1 << 12)		//Ƶ�ʼĴ����ߵ�Ϊѡ��
#define AD9833_CTRLFSEL         (0x1 << 11)		//ѡ��Ƶ�ʼĴ���
#define AD9833_CTRLPSEL         (0x1 << 10)		//ѡ����λ�Ĵ���
#define AD9833_CTRLRESET        (0x1 << 8)		//��λ�豸
#define AD9833_CTRLSLEEP1       (0x1 << 7)		//MCLK����
#define AD9833_CTRLSLEEP12      (0x1 << 6)		//DAC�������
#define AD9833_CTRLOPBITEN      (0x1 << 5)		//������ӷ�ʽѡ��
#define AD9833_CTRLDIV2         (0x1 << 3)		//���������Сѡ��
#define AD9833_CTRLMODE         (0x1 << 1)		//���ģʽѡ��

/* ����Ƶ�ʼĴ�������ζ�Ĵ�����ַ */
#define FREQ0_Address           (0x4000)			//Ƶ�ʼĴ���0�ĵ�ַ
#define FREQ1_Address           (0x8000)			//Ƶ�ʼĴ���1�ĵ�ַ
#define PHASE0_Address          (0xC000)			//��λ�Ĵ���0�ĵ�ַ
#define PHASE1_Address          (0xE000)			//��λ�Ĵ���1�ĵ�ַ

/* ����Ƶ�ʼĴ�����ֵ */
void SetAD9833FreqRegister(Ad9833ObjectType *dev,WriteAd9833FreqReg reg,uint32_t freqValue);
/* ������λ�Ĵ�����ֵ */
void SetAD9833PhaseRegister(Ad9833ObjectType *dev,Ad9833PhaseReg reg,float phaseValue);
/* Ƶ�ʼĴ���ѡ�� */
void SelectAD9833FregRegister(Ad9833ObjectType *dev,Ad9833FreqReg reg);
/* ��λ�Ĵ���ѡ�� */
void SelectAD9833PhaseRegister(Ad9833ObjectType *dev,Ad9833PhaseReg reg);
/* ��λAD9833���� */
void ResetAD9833Object(Ad9833ObjectType *dev);
/* ����AD9833����״̬ */
void SetAD9833SleepMode(Ad9833ObjectType *dev,Ad9833SleepMode mode);
/* ����AD9833�����ģʽ */
void SetAD9833OutputMode(Ad9833ObjectType *dev,Ad9833OutMode mode);
/* ��ʼ��AD9833���� */
void AD9833Initialization(Ad9833ObjectType *dev,
                          float mclk,
                          AD9833WriteData write,
                          AD9833ChipSelcet cs,
                          AD9833Delayms delayms);

#endif
/*********** (C) COPYRIGHT 1999-2019 Moonan Technology *********END OF FILE****/
