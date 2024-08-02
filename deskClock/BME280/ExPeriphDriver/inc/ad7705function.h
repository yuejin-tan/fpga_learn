/******************************************************************************/
/** ģ�����ƣ����ݼ���봦��                                                 **/
/** �ļ����ƣ�ad7705function.h                                               **/
/** ��    ����V1.1.0                                                         **/
/** ��    �飺�����Ͷ���ad7705ģ��ת��оƬ��صĸ��ֺ����Ͳ���               **/
/**         AD7705ӵ��8��Ƭ�ϼĴ���������ͨѶ�����á�ʱ�ӵȼĴ����ṹ���£�  **/
/**         +------+----+----+----+------+------+----+---+-----+             **/
/**         |�Ĵ���| DB7| DB6| DB5| DB4  |  DB3 | DB2|DB1| DB0 |             **/
/**         +------+----+----+----+------+------+----+---+-----+             **/
/**         | ͨѶ |DRDY| RS2| RS1|  RS0 |  R/W |STBY|CH1| CH0 |             **/
/**         +------+----+----+----+------+------+----+---+-----+             **/
/**         | ���� | MD1| MD0| G2 |  G1  |  G0  | B/U|BUF|FSYNC|             **/
/**         +------+----+----+----+------+------+----+---+-----+             **/
/**         | ʱ�� |ZERO|ZERO|ZERO|CLKDIS|CLKDIV| CLK|FS1| FS0 |             **/
/**         +------+----+----+----+------+------+----+---+-----+             **/
/**--------------------------------------------------------------------------**/
/** �޸ļ�¼��                                                               **/
/**     �汾      ����              ����              ˵��                   **/
/**     V1.0.0  2015-07-28          ľ��              �����ļ�               **/
/**     V1.1.0  2019-08-28          ľ��              ��Ϊ���ڶ���Ĳ���     **/
/**                                                                          **/
/******************************************************************************/ 

#ifndef __ad7705function_h
#define __ad7705function_h

#include "stdint.h"

/* ����AD7705�Ĵ���ö�� */
typedef enum AD7705Reg {
  REG_COMM,
  REG_SETUP,
  REG_CLOCK,
  REG_DATA,
  REG_TEST,
  REG_NOUSE,
  REG_ZERO,
  REG_FULL
}AD7705RegType;

/* ����AD7705ͨ��ö�� */
typedef enum AD7705Channel {
  Channel1,
  Channel2
}AD7705ChannelType;

/* ����AD7705����ģʽö�� */
typedef enum AD7705Mode {
  Normal,
  SelfCali,
  ZeroCali,
  FullCali
}AD7705ModeType;

/* ����AD7705����ö�� */
typedef enum AD7705Gain {
  Gain_1,       //1������
  Gain_2,       //2������
  Gain_4,       //4������
  Gain_8,       //8������
  Gain_16,      //16������
  Gain_32,      //32������
  Gain_64,      //64������
  Gain_128      //128������
}AD7705GainType;

/* ����AD77705Ƭѡ�ź�ö�� */
typedef enum AD7705CS {
  AD7705CS_Enable,
  AD7705CS_Disable
}AD7705CSType;

/* ����AD7705���Ƶ��ö�� */
typedef enum AD7705OutRate {
  Rate20Hz,
  Rate25Hz,
  Rate100Hz,
  Rate200Hz,
  Rate50Hz,
  Rate60Hz,
  Rate250Hz,
  Rate500Hz
}AD7705OutRateType;

/* ����AD7705�ⲿʱ��ö�� */
typedef enum AD7705Mclk {
  Mclk2457600,  //2.4576MHz
  Mclk4915200,  //4.9152MHz
  Mclk1000000,  //1MHz
  Mclk2000000   //2MHz
}AD7705MclkType;

/* ����AD7705�������� */
typedef struct AD7705Object {
  uint8_t registers[3]; //���ڴ洢ͨѶ�����ú�ʱ�ӼĴ���
  uint8_t (*ReadWriteByte)(uint8_t data);       //��д����
  uint8_t (*CheckDataIsReady)(void);            //�����źż��
  void (*ChipSelect)(AD7705CSType cs);          //ʵ��Ƭѡ
  void (*Delayms)(volatile uint32_t nTime);     //ʵ��ms��ʱ����
  void (*Delayus)(volatile uint32_t nTime);     //ʵ��us��ʱ����
}AD7705ObjectType;

/*�����дAD7705����ָ������*/
typedef uint8_t (*AD7705ReadWriteByteType)(uint8_t data);
/*���������⺯��ָ������*/
typedef uint8_t (*AD7705CheckDataIsReadyType)(void);
/*����Ƭѡ�źź���ָ������*/
typedef void (*AD7705ChipSelect)(AD7705CSType cs);
/*������ʱ��������ָ������*/
typedef void (*AD7705Delay)(volatile uint32_t nTime);

//��ȡAD7705��ͨ����ֵ
uint16_t GetAD7705ChannelValue(AD7705ObjectType *ad,AD7705ChannelType channel);

/* AD7705�����ʼ������ */
void AD7705Initialization(AD7705ObjectType *ad,
                          AD7705GainType gain,
                          AD7705MclkType mclk,
                          AD7705OutRateType rate,
                          AD7705ReadWriteByteType spiReadWrite,
                          AD7705CheckDataIsReadyType checkReady,
                          AD7705ChipSelect cs,
                          AD7705Delay msDelay,
                          AD7705Delay usDelay);

#endif
/*********** (C) COPYRIGHT 1999-2019 Moonan Technology *********END OF FILE****/
