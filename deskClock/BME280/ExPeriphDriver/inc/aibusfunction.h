/******************************************************************************/
/** ģ�����ƣ���չ��������                                                   **/
/** �ļ����ƣ�aibusfunction.c                                                **/
/** ��    ����V1.1.0                                                         **/
/** ��    �飺����ʵ���������AIBUSͨѶЭ��                                  **/
/**           AIBUS����RS485�����ӿ�                                         **/
/**           ���ݸ�ʽ��1����ʼλ��8λ���ݣ���У��λ��1����2��ֹͣλ         **/
/**           �����ʿɵ�Ϊ4800~19200bit/S��ͨ������9600bit/S                 **/
/**           AIBUSͨѶЭ���������д2����                                   **/
/**           ������ַ����+52H��82��+Ҫ���Ĳ�������+0+0+                     **/
/**           д����ַ����+43H��67��+Ҫд�Ĳ�������+д�������ֽ�             **/
/**               +д�������ֽ�+У����                                       **/
/**--------------------------------------------------------------------------**/
/** �޸ļ�¼��                                                               **/
/**     �汾      ����              ����              ˵��                   **/
/**     V1.0.0  2017-01-15          ľ��              �����ļ�               **/
/**     V1.1.0  2019-07-27          ľ��              �޸�Ϊ�������         **/
/**                                                                          **/
/******************************************************************************/ 

#ifndef _aibusfunction_h
#define _aibusfunction_h

#include "stdint.h"

/* ����AI-BUS��ÿ����ö�� */
typedef enum AIbusDev{
  AIcontroller,         //AI������
  AIinspection,         //AIѲ����
  AIflowtotalizer,      //AI����������
  AIfreqmodulator,      //AIƵ�ʵ�����
  AIregulator           //PID������
}AIbusDevType;

/* ����AI-BUS�豸���� */
typedef struct AIbusObject {
  uint8_t deviceAddr;
  uint8_t status;
  void (*SendBytes)(uint8_t *cmd,uint16_t size);
}AIbusObjectType;

/*ͨ��AIBUS�����ֽ�����*/
typedef void (*AiBusSendBytes)(uint8_t *cmd,uint16_t size);

/*����Ŀ���豸�Ĳ���ֵ*/
void WriteAiBusDeviceParameter(AIbusObjectType *aibus,uint8_t paraAddr,uint16_t data);

/*��ȡĿ���豸�Ĳ���ֵ*/
void ReadAiBusDeviceParameter(AIbusObjectType *aibus,uint8_t paraAddr);

/*������������,����ֵΪ������д�Ĳ���ֵ*/
int ParsingReturnData(AIbusObjectType *aibus,uint8_t *receiveData,uint16_t *returnData,uint16_t deviceNum);

/* AI-BUS�����ʼ�� */
void AIbusInitialization(AIbusObjectType *aibus,uint8_t addr,AiBusSendBytes send);

#endif
/*********** (C) COPYRIGHT 1999-2019 Moonan Technology *********END OF FILE****/
