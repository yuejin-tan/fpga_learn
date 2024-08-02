/******************************************************************************/
/** ģ�����ƣ�������������                                                   **/
/** �ļ����ƣ�keysfunction.h                                                 **/
/** ��    ����V1.0.0                                                         **/
/** ��    �飺ʵ�ֶ԰�����ɨ�����ȡ                                         **/
/**--------------------------------------------------------------------------**/
/** �޸ļ�¼��                                                               **/
/**     �汾      ����              ����              ˵��                   **/
/**     V1.0.0  2012-07-28          ľ��              �����ļ�               **/
/******************************************************************************/ 

#ifndef __KEYSFUNCTION_H
#define __KEYSFUNCTION_H

#include "stdint.h"

#ifndef KEY_FIFO_SIZE
#define KEY_FIFO_SIZE 10        //��ֵ���е�Ĭ�ϴ�С
#endif

#define KEY_FILTER_TIME   5     //��������ʱ��50ms�����۰��»���
#define KEY_LONG_TIME     100   //��������ʱ��1s

/*���尴���ļ����ƽ*/
typedef enum KeyActiveLevel {
  KeyLowLevel,
  KeyHighLevel,
  KeyNoDefine
}KeyActiveLevelType;

/*�����ֵ�洢���е�����*/
typedef struct KeyStateQueue{
  uint8_t queue[KEY_FIFO_SIZE]; //��ֵ�洢����
  uint8_t pRead;		//������ָ��
  uint8_t pWrite;		//д����ָ��
}KeyStateQueueType;

/*���尴����������*/
typedef struct KeyObject {
  uint8_t id;                   //������ID
  uint8_t Count;                //�˲���������
  uint16_t LongCount;           //����������
  uint16_t LongTime;            //�������³���ʱ��, 0 ��ʾ����ⳤ��
  uint8_t  State;               //������ǰ״̬�����»��ǵ���
  uint8_t  RepeatPeriod;        //������������
  uint8_t  RepeatCount;         //��������������
  uint8_t ActiveLevel;          //�����ƽ
}KeyObjectType;

/*���尴��ȡֵö��*/
typedef enum KeyValue {
  KeyNone,
  KeyDown,
  KeyUP,
  KeyLong
}KeyValueType;

/*��������ɨ�����*/
void KeyValueDetect(KeyObjectType *pKey);

/*��ֵ�����г���*/
uint8_t KeyValueDeQueue(void);

/*�����ֵ���г���*/
void ClearKeyValueQueue(void);

/*��ֵ����г���*/
void KeyValueEnQueue(uint8_t keyCode);

/*������ȡ��ʼ��*/
void KeysInitialization(KeyObjectType *pKey,            //��������
                        uint8_t id,                     //����ID
                        uint16_t longTime,              //������Чʱ��
                        uint8_t repeatPeriod,           //�����������
                        KeyActiveLevelType level        //����������Ч��ƽ
                       );

/*���ĳ��ID�İ�����������ϼ����Ƿ���*/
uint8_t CheckKeyDown(KeyObjectType *pKey);

#endif
/*********** (C) COPYRIGHT 1999-2019 Moonan Technology *********END OF FILE****/
