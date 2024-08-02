/******************************************************************************/
/** ģ�����ƣ���չ��������                                                   **/
/** �ļ����ƣ�sht3xfunction.h                                                **/
/** ��    ����V1.0.0                                                         **/
/** ��    �飺����ʵ��SHT3X������ʪ�ȼƵĲ���                                **/
/**           ���ζ�ȡ�������£�                                             **/
/**           +---------------+------------+                                 **/
/**           |     ����      |ʮ�����ƴ���|                                 **/
/**           +------+--------+------+-----+                                 **/
/**           |�ظ���|ʱ������| MSB  | LSB |                                 **/
/**           +------+--------+------+-----+                                 **/
/**           | High | enabled| 0x2C | 06  |                                 **/
/**           +------+--------+------+-----+                                 **/
/**           |Medium| enabled| 0x2C | 0D  |                                 **/
/**           +------+--------+------+-----+                                 **/
/**           |  Low | enabled| 0x2C | 10  |                                 **/
/**           +------+--------+------+-----+                                 **/
/**           | High |disabled| 0x24 | 00  |                                 **/
/**           +------+--------+------+-----+                                 **/
/**           |Medium|disabled| 0x24 | 0B  |                                 **/
/**           +------+--------+------+-----+                                 **/
/**           |  Low |disabled| 0x24 | 16  |                                 **/
/**           +------+--------+------+-----+                                 **/
/**           �����Զ�ȡ�������£�                                           **/
/**           +-------------------+------------+                             **/
/**           |        ����       |ʮ�����ƴ���|                             **/
/**           +------+------------+------+-----+                             **/
/**           |�ظ���|ÿ���������| MSB  | LSB |                             **/
/**           +------+------------+------+-----+                             **/
/**           | High |     0.5    | 0x20 |  32 |                             **/
/**           +------+------------+------+-----+                             **/
/**           |Medium|     0.5    | 0x20 |  24 |                             **/
/**           +------+------------+------+-----+                             **/
/**           | Low  |     0.5    | 0x20 |  2F |                             **/
/**           +------+------------+------+-----+                             **/
/**           | High |      1     | 0x21 |  30 |                             **/
/**           +------+------------+------+-----+                             **/
/**           |Medium|      1     | 0x21 |  26 |                             **/
/**           +------+------------+------+-----+                             **/
/**           | Low  |      1     | 0x21 |  2D |                             **/
/**           +------+------------+------+-----+                             **/
/**           | High |      2     | 0x22 |  36 |                             **/
/**           +------+------------+------+-----+                             **/
/**           |Medium|      2     | 0x22 |  20 |                             **/
/**           +------+------------+------+-----+                             **/
/**           | Low  |      2     | 0x22 |  2B |                             **/
/**           +------+------------+------+-----+                             **/
/**           | High |      4     | 0x23 |  34 |                             **/
/**           +------+------------+------+-----+                             **/
/**           |Medium|      4     | 0x23 |  22 |                             **/
/**           +------+------------+------+-----+                             **/
/**           | Low  |      4     | 0x23 |  29 |                             **/
/**           +------+------------+------+-----+                             **/
/**           | High |      10    | 0x27 |  37 |                             **/
/**           +------+------------+------+-----+                             **/
/**           |Medium|      10    | 0x27 |  21 |                             **/
/**           +------+------------+------+-----+                             **/
/**           | Low  |      10    | 0x27 |  2A |                             **/
/**           +------+------------+------+-----+                             **/
/**--------------------------------------------------------------------------**/
/**ʹ��˵����                                                                **/
/**    1������SHT3xObject����ʵ�壬�����ú���SHT3xInitialization��ʼ������   **/
/**       ʵ�塣��ʼ��ʱ��ָ���豸��ַ��0x44,0x45,0x88��0x8A��ʹ����Ӧ�ĺ�   **/
/**       ���壺I2CADDRESSA��I2CADDRESSB��I2CADDRESSC��I2CADDRESSD           **/
/**    2��ʵ������void f(uint8_t devAddress,uint8_t *rData,uint16_t rSize)�� **/
/**       �����������丳ֵ��SHT3xObject����ʵ���Receive����ָ�롣ʵ�����ݽ� **/
/**       �ա�                                                               **/
/**    3��ʵ������void f(uint8_t devAddress,uint8_t *tData,uint16_t tSize)�� **/
/**       �����������丳ֵ��SHT3xObject����ʵ���Transmit����ָ�롣ʵ������  **/
/**       ���͡�                                                             **/
/**    4��ʵ������void f(volatile uint32_t nTime)�ĺ����������丳ֵ��        **/
/**       SHT3xObject����ʵ���Delay����ָ�롣ʵ�ֲ�����ʱ����λ����         **/
/**    5��������Ӧ�ĺ���ʵ����Ҫ�Ĳ�����                                     **/
/**--------------------------------------------------------------------------**/
/** �޸ļ�¼��                                                               **/
/**     �汾      ����              ����              ˵��                   **/
/**     V1.0.0  2018-12-01          ľ��              �����ļ�               **/
/**                                                                          **/
/******************************************************************************/ 

#ifndef __SHT3XFUNCTION_H
#define __SHT3XFUNCTION_H

#include "stdint.h"

/* SHT3x��������������״̬���� */
typedef enum SHT3xError{
  SHT3X_NO_ERROR       = 0x00,  // �޴���
  SHT3X_ACK_ERROR      = 0x01,  // Ӧ��ȷ�ϴ���
  SHT3X_CHECKSUM_ERROR = 0x02,  // У�����
  SHT3X_TIMEOUT_ERROR  = 0x04,  // ��ʱ����
  SHT3X_PARM_ERROR     = 0x80,  // �������޴���
	SHT3X_INIT_ERROR		 = 0x03,	// SHT3X�����ʼ������
}SHT3xErrorType;

/* SHT3x�������������� */
typedef enum{
  CMD_MEAS_CLOCKSTR_H = 0x2C06,  // �������ݲɼ�ģʽ��ʱ����չ�����ظ���
  CMD_MEAS_CLOCKSTR_M = 0x2C0D,  // �������ݲɼ�ģʽ��ʱ����չ�����ظ���
  CMD_MEAS_CLOCKSTR_L = 0x2C10,  // �������ݲɼ�ģʽ��ʱ����չ�����ظ���
  CMD_MEAS_POLLING_H = 0x2400,   // �������ݲɼ�ģʽ����ѯ�����ظ���
  CMD_MEAS_POLLING_M = 0x240B,   // �������ݲɼ�ģʽ����ѯ�����ظ���
  CMD_MEAS_POLLING_L = 0x2416,   // �������ݲɼ�ģʽ����ѯ�����ظ���
  CMD_MEAS_PERI_05_H = 0x2032,   // �������ݲɼ�ģʽ��0.5 mps, ���ظ���
  CMD_MEAS_PERI_05_M = 0x2024,   // �������ݲɼ�ģʽ��0.5 mps, ���ظ���
  CMD_MEAS_PERI_05_L = 0x202F,   // �������ݲɼ�ģʽ��0.5 mps, ���ظ���
  CMD_MEAS_PERI_1_H = 0x2130,    // �������ݲɼ�ģʽ��1 mps, ���ظ���
  CMD_MEAS_PERI_1_M = 0x2126,    // �������ݲɼ�ģʽ��1 mps, ���ظ���
  CMD_MEAS_PERI_1_L = 0x212D,    // �������ݲɼ�ģʽ��1 mps, ���ظ���
  CMD_MEAS_PERI_2_H = 0x2236,    // �������ݲɼ�ģʽ��2 mps, ���ظ���
  CMD_MEAS_PERI_2_M = 0x2220,    // �������ݲɼ�ģʽ��2 mps, ���ظ���
  CMD_MEAS_PERI_2_L = 0x222B,    // �������ݲɼ�ģʽ��2 mps, ���ظ���
  CMD_MEAS_PERI_4_H = 0x2334,    // �������ݲɼ�ģʽ��4 mps, ���ظ���
  CMD_MEAS_PERI_4_M = 0x2322,    // �������ݲɼ�ģʽ��4 mps, ���ظ���
  CMD_MEAS_PERI_4_L = 0x2329,    // �������ݲɼ�ģʽ��4 mps, ���ظ���
  CMD_MEAS_PERI_10_H = 0x2737,   // �������ݲɼ�ģʽ��10 mps, ���ظ���
  CMD_MEAS_PERI_10_M = 0x2721,   // �������ݲɼ�ģʽ��10 mps, ���ظ���
  CMD_MEAS_PERI_10_L = 0x272A,   // �������ݲɼ�ģʽ��10 mps, ���ظ���
  CMD_FETCH_DATA = 0xE000,       // ��������ģʽ�Ĳ������
  CMD_ART=0x2B32,                // ������Ӧʱ������
  CMD_BREAK_STOP=0x3093,         // �ж������ֹͣ���ڲɼ�ģʽ
  CMD_SOFT_RESET = 0x30A2,       // �����λ
  CMD_GENERAL_CALL_RESET=0x0006, // �㲥��λ
  CMD_HEATER_ENABLE = 0x306D,    // ���ü�����
  CMD_HEATER_DISABLE = 0x3066,   // ���ü�����
  CMD_READ_STATUS = 0xF32D,      // ��״̬�Ĵ���
  CMD_CLEAR_STATUS = 0x3041,     // ��״̬�Ĵ���
  CMD_READ_SERIALNBR = 0x3780,   // �����к�
  CMD_R_AL_LIM_LS = 0xE102,      // ���������ƣ�������
  CMD_R_AL_LIM_LC = 0xE109,      // ���������ƣ������
  CMD_R_AL_LIM_HS = 0xE11F,      // ���������ƣ�������
  CMD_R_AL_LIM_HC = 0xE114,      // ���������ƣ������
  CMD_W_AL_LIM_HS = 0x611D,      // д�������ƣ�������
  CMD_W_AL_LIM_HC = 0x6116,      // д�������ƣ������
  CMD_W_AL_LIM_LS = 0x6100,      // д�������ƣ�������
  CMD_W_AL_LIM_LC = 0x610B,      // д�������ƣ������
  CMD_NO_SLEEP = 0x303E,         // ������
}SHT3xCommands;

/* SHT3x�����������ظ��� */
typedef enum SHT3xRepeatability{
  REPEATAB_HIGH,        // ���ظ���
  REPEATAB_MEDIUM,      // ���ظ���
  REPEATAB_LOW,         // ���ظ���
}SHT3xRepeatability;

/* SHT3x���������β���ģʽ */
typedef enum SHT3xMode{
  MODE_CLKSTRETCH,      // clock stretching
  MODE_POLLING,         // polling
}SHT3xMode;

/* ���������ݲɼ���Ƶ�ʶ��� */
typedef enum SHT3xFrequency{
  FREQUENCY_HZ5,        // ÿ��0.5��
  FREQUENCY_1HZ,        // ÿ��1.0��
  FREQUENCY_2HZ,        // ÿ��2.0��
  FREQUENCY_4HZ,        // ÿ��4.0��
  FREQUENCY_10HZ,       // ÿ��10.0��
}SHT3xFrequency;

/* ״̬�Ĵ�����ʽ���� */
typedef union {
  uint16_t word;
  struct{
    #ifdef LITTLE_ENDIAN        // ϵͳΪС��ģʽʱ��״̬�Ĵ�����λ�Ķ���
    uint16_t CrcStatus     : 1;     // д����У��״̬
    uint16_t CmdStatus     : 1;     // ����״̬
    uint16_t Reserve0      : 2;     // ����λ
    uint16_t ResetDetected : 1;     // ϵͳ��λ̽��
    uint16_t Reserve1      : 5;     // ����λ
    uint16_t T_Alert       : 1;     // �¶�׷�ٱ���
    uint16_t RH_Alert      : 1;     // ʪ��׷�ٱ���
    uint16_t Reserve2      : 1;     // ����λ
    uint16_t HeaterStatus  : 1;     // ������״̬
    uint16_t Reserve3      : 1;     // ����λ
    uint16_t AlertPending  : 1;     // ����δȷ��״̬ 
    #else                       // ϵͳΪ���ģʽʱ��״̬�Ĵ�����λ�Ķ���
    uint16_t AlertPending  : 1;     // ����δȷ��״̬ 
    uint16_t Reserve3      : 1;     // ����λ
    uint16_t HeaterStatus  : 1;     // ������״̬
    uint16_t Reserve2      : 1;     // ����λ
    uint16_t RH_Alert      : 1;     // ʪ��׷�ٱ���
    uint16_t T_Alert       : 1;     // �¶�׷�ٱ���
    uint16_t Reserve1      : 5;     // ����λ
    uint16_t ResetDetected : 1;     // ϵͳ��λ̽��
    uint16_t Reserve0      : 2;     // ����λ
    uint16_t CmdStatus     : 1;     // ����״̬
    uint16_t CrcStatus     : 1;     // д����У��״̬
    #endif
  }bit;
}SHT3xStatusRegister;

/* ����SHT3x�������� */
typedef struct SHT3xObject{
  uint8_t devAddress;           // SHT3x����ĵ�ַ
	uint16_t status;							//SHT3x״̬�����ڵ�ֵ
  uint32_t serialNumber;        // SHT3x��������к�
  float temperature;
  float humidity;
  void (*Delayms)(volatile uint32_t nTime);       //��ʱ����ָ��
  void (*Receive)(struct SHT3xObject *sht,uint8_t *rData,uint16_t rSize);    //�������ݲ���ָ��
  void (*Transmit)(struct SHT3xObject *sht,uint8_t *tData,uint16_t tSize);   //�������ݲ���ָ��
}SHT3xObjectType;

/* ������ʱ����ָ������ */
typedef void (*SHT3xDelayms)(volatile uint32_t nTime);
/* �������ݺ���ָ������ */
typedef void (*SHT3xReceive)(SHT3xObjectType *sht,uint8_t *rData,uint16_t rSize);
/* �������ݺ���ָ������ */
typedef void (*SHT3xTransmit)(SHT3xObjectType *sht,uint8_t *tData,uint16_t tSize);

/* SHT3x�����ʼ�� */
SHT3xErrorType SHT3xInitialization(SHT3xObjectType *sht,		//����ʼ����SHT3X
                                   uint8_t address,					//�豸��ַ
                                   SHT3xReceive receive,		//�������ݺ���ָ��
                                   SHT3xTransmit transmit,	//�������ݺ���ָ��
                                   SHT3xDelayms delayms			//������ʱ����ָ��
                                  );

/* ���״̬�Ĵ�����״̬��־ */
void SHT3xClearStatusRegister(SHT3xObjectType *sht);

/* ��ȡ״̬�Ĵ�����ֵ */
SHT3xErrorType SHT3xReadStatusRegister(SHT3xObjectType *sht,SHT3xStatusRegister *status);

/* SHT3x���ü����� */
void SHT3xDisableHeater(SHT3xObjectType *sht);

/* SHT3x���ü����� */
void SHT3xEnableHeater(SHT3xObjectType *sht);

/* SHT3x�����λ */
void SHT3xSoftReset(SHT3xObjectType *sht);

/* SHT3x�㲥��λ */
void SHT3xGeneralCallReset(SHT3xObjectType *sht);

/* SHT3x�ӿڸ�λ */
void SHT3xInterfaceReset(SHT3xObjectType *sht);

/* ֹͣ���ڲɼ�ģʽ*/
void SHT3xBreakCommand(SHT3xObjectType *sht);

/* �������ڲɼ�ʹ��ART */
void SHT3xARTCommand(SHT3xObjectType *sht);

/* �������������ݲɼ� */
void SHT3xStartPeriodicMeasurment(SHT3xObjectType *sht,SHT3xRepeatability repeatability,SHT3xFrequency frequency);

/* ��ȡ�����Բɼ������� */
SHT3xErrorType SHT3xFetchPeriodicMeasurmentData(SHT3xObjectType *sht);

/* ��ȡһ���Բɼ� */
SHT3xErrorType SHT3xGetSingleShotData(SHT3xObjectType *sht,SHT3xRepeatability repeatability,SHT3xMode mode);

#endif
/*********** (C) COPYRIGHT 1999-2019 Moonan Technology *********END OF FILE****/
