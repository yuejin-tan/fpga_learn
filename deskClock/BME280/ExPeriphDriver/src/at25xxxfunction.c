/******************************************************************************/
/** ģ�����ƣ���չ��������                                                   **/
/** �ļ����ƣ�at25xxxfunction.c                                              **/
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
/**           | AT25080B | 1024x8(8K)    | 10λ(2���Ĵ���) | 32�ֽ� |        **/
/**           +----------+---------------+-----------------+--------+        **/
/**           | AT25160B | 2048x8(16K)   | 11λ(2���Ĵ���) | 32�ֽ� |        **/
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

#include "stddef.h"
#include "at25xxxfunction.h"

static uint16_t pageBytes[AT25Number]={8,8,8,32,32,32,32,64,64,128,256,256};
static uint16_t regAddMask[AT25Number]={0x07,0x07,0x07,0x1F,0x1F,0x1F,0x1F,
                                         0x3F,0x3F,0x7F,0xFF,0xFF};
	
/*ȱʡƬѡ������*/
static void AT25ChipSelectDefault(AT25xxxCSType cs);
																	
/*��AT25XXX��ȡ�����ֽ�,�������ַ��ȡ*/
uint8_t ReadByteFromAT25xxx(At25ObjectType *at,uint32_t regAddress)
{
  uint8_t rData;

  ReadBytesFromAT25xxx(at,regAddress,&rData,1);
	  
  return rData;
}

/*��AT25XXXд�뵥���ֽ�*/
void WriteByteToAT25xxx(At25ObjectType *at,uint32_t regAddress,uint8_t data)
{
  WriteBytesToAT25xxx(at,regAddress,&data,1);
}

/* AT25XXX����дʹ��������*/
void SetWriteEnableLatchForAT25xxx(At25ObjectType *at)
{
  uint8_t opCode=AT25_WREN;
	
  at->ChipSelect(AT25CS_Enable);
  at->Write(&opCode,1);
  at->ChipSelect(AT25CS_Enable);
	
  ReadStatusForAT25xxx(at);
}

/* AT25XXX��λдʹ��������*/
void ResetWriteEnableLatchForAT25xxx(At25ObjectType *at)
{
  uint8_t opCode=AT25_WRDI;
  
  at->ChipSelect(AT25CS_Enable);
  at->Write(&opCode,1);
  at->ChipSelect(AT25CS_Enable);
	
  ReadStatusForAT25xxx(at);
}

/*��AT25xxx״̬�Ĵ���*/
void ReadStatusForAT25xxx(At25ObjectType *at)
{
  uint8_t opCode=AT25_RDSR;
  uint8_t status;
  
  at->ChipSelect(AT25CS_Enable);
  at->Write(&opCode,1);
  at->Delayms(1);
  at->Read(&status,1);
  at->ChipSelect(AT25CS_Enable);
  
  at->status=status;
}

/*дAT25xxx״̬�Ĵ���*/
void WriteStatusForAT25xx(At25ObjectType *at,uint8_t cmd)
{
  uint8_t data[2];
	
  data[0]=AT25_WRSR;
  data[1]=cmd;
	
  if(((at->status)&0x02)!=0x02)
  {
    SetWriteEnableLatchForAT25xxx(at);
  }
	
  if((((at->status)&AT25_WPEN)!=AT25_WPEN)&&(at->WP!=NULL))
  {
    at->WP(AT25WP_Disable);
  }
	
  at->ChipSelect(AT25CS_Enable);
  at->Write(data,2);
  at->ChipSelect(AT25CS_Disable);
	
  ReadStatusForAT25xxx(at);
	
  if(at->WP!=NULL)
  {
    at->WP(AT25WP_Enable);
  }
}

/*��AT25xxx��ȡ����*/
void ReadBytesFromAT25xxx(At25ObjectType *at,uint32_t regAddress,uint8_t *rData,uint16_t rSize)
{
  uint8_t data[4];
  uint16_t index=0;
  uint8_t temp;
  uint16_t size=0;
	
  data[index++]=AT25_READ;
	
  if(at->memAddLength==AT258BitMemAdd)
  {
    data[index++]=(uint8_t)regAddress;
    
    if(at->mode==AT25040B)
    {
      temp=(uint8_t)(regAddress>>8);
      data[0]|=((temp&0x01)<<3);
    }
  }
  else if(at->memAddLength==AT2516BitMemAdd)
  {
    data[index++]=(uint8_t)(regAddress>>8);
    data[index++]=(uint8_t)regAddress;
  }
  else
  {
    data[index++]=(uint8_t)(regAddress>>16);
    data[index++]=(uint8_t)(regAddress>>8);
    data[index++]=(uint8_t)regAddress;
  }

  temp=(uint8_t)(regAddress&regAddMask[at->mode]);
  if((rSize<=pageBytes[at->mode])&&(rSize<=(pageBytes[at->mode]-temp)))
  {
    size=rSize;
  }
  else
  {
    size=pageBytes[at->mode]-temp;
  }
	
  at->ChipSelect(AT25CS_Enable);
  at->Write(data,index);
  at->Delayms(1);
  at->Read(rData,size);
  at->ChipSelect(AT25CS_Disable);
}

/*��AT25xxxд������*/
void WriteBytesToAT25xxx(At25ObjectType *at,uint32_t regAddress,uint8_t *wData,uint16_t wSize)
{
  uint8_t data[128];
  uint16_t index=0;
  uint8_t temp;
  uint16_t size=0;
  
  data[index++]=AT25_WRITE;
  
  if(at->memAddLength==AT258BitMemAdd)
  {
    data[index++]=(uint8_t)regAddress;
		
    if(at->mode==AT25040B)
    {
      temp=(uint8_t)(regAddress>>8);
      data[0]|=((temp&0x01)<<3);
    }
  }
  else if(at->memAddLength==AT2516BitMemAdd)
  {
    data[index++]=(uint8_t)(regAddress>>8);
    data[index++]=(uint8_t)regAddress;
  }
  else
  {
    data[index++]=(uint8_t)(regAddress>>16);
    data[index++]=(uint8_t)(regAddress>>8);
    data[index++]=(uint8_t)regAddress;
  }

  temp=(uint8_t)(regAddress&regAddMask[at->mode]);
  if((wSize<=pageBytes[at->mode])&&(wSize<=(pageBytes[at->mode]-temp)))
  {
    size=wSize;
  }
  else
  {
    size=pageBytes[at->mode]-temp;
  }

  for(int i=0;i<size;i++)
  {
    data[index++]=wData[i];
  }
	
  if(((at->status)&0x02)!=0x02)
  {
    SetWriteEnableLatchForAT25xxx(at);
  }
	
  if(((at->status)&0x0C)!=0x00)
  {
    WriteStatusForAT25xx(at,at->status|AT25_BPNONE);
  }
	
  at->ChipSelect(AT25CS_Enable);
  at->Write(data,index);
  at->ChipSelect(AT25CS_Disable);
  
  WriteStatusForAT25xx(at,at->status|AT25_BPALL);
}

/* ��ʼ��AT25XXX���� */
void At25xxxInitialization(At25ObjectType *at,  //AT25XXX����ʵ��
                           At25ModeType mode,   //AT25XXX��������
                           AT25Read read,       //��AT25XXX�������ָ��
                           AT25Write write,     //дAT25XXX�������ָ��
                           AT25Delayms delayms, //��ʱ����ָ��
                           AT25ChipSelect cs    //Ƭѡ��������ָ��
                          )
{
  if((at==NULL)||(read==NULL)||(write==NULL)||(delayms==NULL))
  {
    return;
  }
  at->Read=read;
  at->Write=write;
  at->Delayms=delayms;
	
  if(cs!=NULL)
  {
    at->ChipSelect=cs;
  }
  else
  {
    at->ChipSelect=AT25ChipSelectDefault;
  }

  if(mode>=AT25Number)
  {
    return;
  }
  at->mode=mode;
	
  if(mode<AT25080B)
  {
    at->memAddLength=AT258BitMemAdd;
  }
  else if(mode<AT25M01)
  {
    at->memAddLength=AT2516BitMemAdd;
  }
  else
  {
    at->memAddLength=AT2524BitMemAdd;
  }
	
  ReadStatusForAT25xxx(at);
	
  //д����
  SetWriteEnableLatchForAT25xxx(at);
	
  uint8_t cmd;
  //ʹ��д����������ȫ������
  cmd=at->status|AT25_WPEN|AT25_BPALL;
  WriteStatusForAT25xx(at,cmd);
	
  ReadStatusForAT25xxx(at);
}

/*ȱʡƬѡ������*/
static void AT25ChipSelectDefault(AT25xxxCSType cs)
{
  //������SPIͨѶʱ��Ƭѡ�ź�Ӳ����·ѡ�е����
  return;
}
/*********** (C) COPYRIGHT 1999-2019 Moonan Technology *********END OF FILE****/
