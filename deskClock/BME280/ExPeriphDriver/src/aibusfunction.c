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

#include "stddef.h"
#include "aibusfunction.h"

/*����AIBUS��ָ����*/
#define READ_INSTRUCTION 0x52
#define WRITE_INSTRUCTION 0x43

/*����ָ������ݳ���*/
#define INSTRUCTION_LENGTH 8 //��дָ��ĳ��Ⱦ�Ϊ8�ֽ�
#define RETURNING_DATA_LENGTH 10 //�������ݾ�Ϊ10���ֽ�


/*��ȡĿ���豸�Ĳ���ֵ*/
void ReadAiBusDeviceParameter(AIbusObjectType *aibus,uint8_t paraAddr)
{
  uint8_t readCommand[INSTRUCTION_LENGTH];
  uint16_t index=0;
  readCommand[index++]=0x80+aibus->deviceAddr;
  readCommand[index++]=0x80+aibus->deviceAddr;
  readCommand[index++]=READ_INSTRUCTION;
  readCommand[index++]=paraAddr;
  readCommand[index++]=0x0;
  readCommand[index++]=0x0;
  
  uint16_t checkSum=(uint16_t)paraAddr*256+READ_INSTRUCTION+(uint16_t)aibus->deviceAddr;
  
  readCommand[index++]=checkSum;
  readCommand[index++]=(checkSum>>8);
  
  aibus->SendBytes(readCommand,INSTRUCTION_LENGTH);
}

/*����Ŀ���豸�Ĳ���ֵ*/
void WriteAiBusDeviceParameter(AIbusObjectType *aibus,uint8_t paraAddr,uint16_t data)
{
  uint8_t writeCommand[INSTRUCTION_LENGTH];
  uint16_t index=0;
  writeCommand[index++]=0x80+aibus->deviceAddr;
  writeCommand[index++]=0x80+aibus->deviceAddr;
  writeCommand[index++]=WRITE_INSTRUCTION;
  writeCommand[index++]=paraAddr;
  writeCommand[index++]=data;
  writeCommand[index++]=(data>>8);
  
  uint16_t checkSum=(uint16_t)paraAddr*256+WRITE_INSTRUCTION+(uint16_t)aibus->deviceAddr+data;
  
  writeCommand[index++]=checkSum;
  writeCommand[index++]=(checkSum>>8);
  
  aibus->SendBytes(writeCommand,INSTRUCTION_LENGTH);
}

/*������������,����ֵΪ������д�Ĳ���ֵ*/
int ParsingReturnData(AIbusObjectType *aibus,uint8_t *receiveData,uint16_t *returnData,uint16_t deviceNum)
{
  int status=-1;
  
  uint16_t pValue=0;
  uint16_t sValue=0;
  uint16_t mValue=0;
  uint16_t alarmStatus=0;
  uint16_t paraValue=0;
  uint16_t checkSum=0;
  
  pValue=receiveData[0]+receiveData[1]*256;
  sValue=receiveData[2]+receiveData[3]*256;
  mValue=(uint16_t)receiveData[4];
  alarmStatus=(uint16_t)receiveData[5];
  paraValue=receiveData[6]+receiveData[7]*256;
  checkSum=receiveData[8]+receiveData[9]*256;
  
  uint16_t chk=pValue+sValue+alarmStatus*256+mValue+paraValue;
  
  for(int i=0;i<deviceNum;i++)
  {
    if(checkSum==chk+aibus[i].deviceAddr)
    {
      status=i;
      returnData[0]=pValue;
      returnData[1]=sValue;
      returnData[2]=mValue;
      returnData[3]=alarmStatus;
      returnData[4]=paraValue;
      break;
    }
  }
	
  aibus[status].status=alarmStatus;
	
  return status;
}

/* AI-BUS�����ʼ�� */
void AIbusInitialization(AIbusObjectType *aibus,uint8_t addr,AiBusSendBytes send)
{
  if((aibus==NULL)||(send==NULL))
  {
    return;
  }
	
  aibus->deviceAddr=addr;
  aibus->SendBytes=send;
}
/*********** (C) COPYRIGHT 1999-2019 Moonan Technology *********END OF FILE****/
