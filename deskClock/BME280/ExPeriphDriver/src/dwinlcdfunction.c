/******************************************************************************/
/** ģ�����ƣ���չ��������                                                   **/
/** �ļ���   dwinlcdfunction.c                                               **/
/** ��  ��   V1.1.0                                                          **/
/** ��  ��   ʵ�ֵ���LCD��ʾ����д����                                       **/
/**          ֡��ʽ��֡ͷ+���ݳ���+ָ��+����+CRCУ��                         **/
/**          ���У�֡ͷ2���ֽڣ��������ļ�����֡ͷ������                     **/
/**                ���ݳ���1���ֽڣ�����ָ����ݺ�У��                     **/
/**                ָ����5����0x80,0x81,0x82,0x83,0x84,��Ӧ��ͬ����          **/
/**                     0x80д�Ĵ���                                         **/
/**                     0x81���Ĵ���                                         **/
/**                     0x82д�����洢��                                     **/
/**                     0x83�ȱ����洢��                                     **/
/**                     0x84д������ʾ                                       **/
/**                ���ݵĳ������������                                      **/
/**                CRCУ���Ƿ����ã��������ļ����趨                         **/
/**          �Ĵ����ĵ�ַΪ1���ֽڣ������ĵ�ַΪ2���ֽ�                      **/
/**--------------------------------------------------------------------------**/
/** �޸ļ�¼��                                                               **/
/**     �汾      ����              ����              ˵��                   **/
/**     V1.0.0  2014-01-18          ľ��              �����ļ�               **/
/**     V1.1.0  2019-08-01          ľ��              �޸�Ϊ���ڶ���Ĳ���   **/
/**                                                                          **/
/******************************************************************************/ 

#include "stddef.h"
#include "dwinlcdfunction.h"

/*д�Ĵ������ݣ�һ���������д4���ֽڣ���length<=4*/
static void SetRegisterDataToDwinLCD(DwinObjectType *dwin,uint8_t regAddress,uint8_t *txData,uint16_t length);
/*���Ĵ�������*/
static void GetRegisterDataFromDwinLCD(DwinObjectType *dwin,uint8_t regAddress,uint8_t readByteLength);
/* CRC16У�飨X16+X15+X2+1��*/
static uint16_t CalcDwinCRC16(uint8_t *buf,uint16_t length);
/*�����յ������ݼ��뻺��*/
static void BufferDataEnQueue(DwinObjectType *dwin,uint8_t rData);
/*�ӻ����ж�ȡ����*/
static uint16_t BufferDataDeQueue(DwinObjectType *dwin,uint8_t *rxBuf);

/*д���ݱ����洢����һ���������д47���֣���length<=94*/
void WriteFlashDataToDwinLCD(DwinObjectType *dwin,uint16_t startAddress,uint8_t *txData,uint16_t length)
{
  /*����ĳ�����֡ͷ��2���ֽڣ�+���ݳ��ȣ�1���ֽڣ�+ָ�1���ֽڣ�+��ʼ��ַ��2���ֽڣ�+���ݣ�����Ϊlength��+CRCУ�飨2���ֽڣ�*/
  uint16_t cmd_Length=length+6;
  uint8_t cmd_VAR_Write[102];
  cmd_VAR_Write[0]=0x5A;
  cmd_VAR_Write[1]=0xA5;
  cmd_VAR_Write[2]=(uint8_t)(length+3);
  cmd_VAR_Write[3]= FC_VAR_Write;
  cmd_VAR_Write[4]=(uint8_t)(startAddress>>8);//��ʼ��ַ
  cmd_VAR_Write[5]=(uint8_t)startAddress;//��ʼ��ַ
  for(int dataIndex=0;dataIndex<length;dataIndex++)
  {
    cmd_VAR_Write[dataIndex+6]=txData[dataIndex];
  }
  
  if(dwin->checkMode>DwinNone)
  {
    uint16_t checkCode=CalcDwinCRC16(&cmd_VAR_Write[3],length+2);
    cmd_VAR_Write[length+6]=(uint8_t)checkCode;
    cmd_VAR_Write[length+7]=(uint8_t)(checkCode>>8);
    cmd_Length=cmd_Length+2;
  }
	
  dwin->SendData(cmd_VAR_Write,cmd_Length);
}

/*�������洢������*/
void ReadFlashDataFromDwinLCD(DwinObjectType *dwin,uint16_t startAddress,uint8_t readWordLength)
{
  /*����ĳ�����֡ͷ��2���ֽڣ�+���ݳ��ȣ�1���ֽڣ�+ָ�1���ֽڣ�+��ʼ��ַ��2���ֽڣ�+��ȡ���ֳ��ȣ�1���ֽڣ�+CRCУ�飨2���ֽڣ�*/
  uint16_t cmd_Length=7;
  uint8_t cmd_VAR_Read[]={0x5A,0xA5,0x04,FC_VAR_Read,0x00,0x00,0x00,0x00,0x00};//����������
  cmd_VAR_Read[4]=(uint8_t)(startAddress>>8);//��ʼ��ַ
  cmd_VAR_Read[5]=(uint8_t)startAddress;//��ʼ��ַ
  cmd_VAR_Read[6]=readWordLength;//��ȡ����
  	
  if(dwin->checkMode>DwinNone)
  {
    uint16_t checkCode=CalcDwinCRC16(&cmd_VAR_Read[3],4);
    cmd_VAR_Read[7]=(uint8_t)checkCode;
    cmd_VAR_Read[8]=(uint8_t)(checkCode>>8);
    cmd_Length=cmd_Length+2;
  }
	
  dwin->SendData(cmd_VAR_Read,cmd_Length);
}

/*д���߻�������һ���������д8���֣���length<=16*/
void WriteCurveToDwinLCD(DwinObjectType *dwin,uint8_t *txData,uint16_t length,uint8_t channelMode)
{
  /*����ĳ�����֡ͷ��2���ֽڣ�+���ݳ��ȣ�1���ֽڣ�+ָ�1���ֽڣ�+ͨ��ģʽ��1���ֽڣ�+���ݣ�length�����8���֣�+CRCУ�飨2���ֽڣ�*/
  uint16_t cmd_Length=length+5;
  uint8_t cmd_Curve_Write[23];//д���߻���������
  cmd_Curve_Write[0]=0x5A;
  cmd_Curve_Write[1]=0xA5;
  cmd_Curve_Write[2]=(uint8_t)(length+2);
  cmd_Curve_Write[3]= FC_Curve_Write;
  cmd_Curve_Write[4]=channelMode;
  for(int dataIndex=0;dataIndex<length;dataIndex++)
  {
    cmd_Curve_Write[dataIndex+5]=txData[dataIndex];
  }
  
  if(dwin->checkMode>DwinNone)
  {
    uint16_t checkCode=CalcDwinCRC16(&cmd_Curve_Write[3],length+2);
    cmd_Curve_Write[length+5]=(uint8_t)checkCode;
    cmd_Curve_Write[length+6]=(uint8_t)(checkCode>>8);
    cmd_Length=cmd_Length+2;
  }
	
  dwin->SendData(cmd_Curve_Write,cmd_Length);
}

/*��ȡLCDϵͳʱ��*/
void GetDateTimeFromDwinLCD(DwinObjectType *dwin)
{
  if(dwin->sort==DGUS)
  {
    uint8_t regAddress=0x20;      /*RTC�Ĵ�����ַΪ0x20*/
    uint8_t readByteLength=7;     /*���ڸ�ʽ��YY��MM��DD��WW��HH��MM��SS*/
  
    GetRegisterDataFromDwinLCD(dwin,regAddress,readByteLength);
  }
  else
  {
    uint16_t startAddress=0x0010;
    uint8_t readWordLength=0x04;
  
    ReadFlashDataFromDwinLCD(dwin,startAddress,readWordLength);
  }
}

/*У׼LCDϵͳʱ��*/
void CalibrationDateTimeForDwinLCD(DwinObjectType *dwin,uint8_t *dateTime)
{
  uint8_t txData[8];
  uint16_t length=8;
  
  if(dwin->sort==DGUS)
  {
    uint8_t regAddress=0x1F;

    txData[0]=0x5A;
    txData[1]=dateTime[0];
    txData[2]=dateTime[1];
    txData[3]=dateTime[2];
    txData[4]=0x00;
    txData[5]=dateTime[3];
    txData[6]=dateTime[4];
    txData[7]=dateTime[5];
    SetRegisterDataToDwinLCD(dwin,regAddress,txData,length);
  }
  else
  {
    uint16_t startAddress=0x0010;
    txData[0]=dateTime[0];
    txData[1]=dateTime[1];
    txData[2]=dateTime[2];
    txData[3]=0x00;
    txData[4]=dateTime[3];
    txData[5]=dateTime[4];
    txData[6]=dateTime[5];
    txData[7]=0x00;
    WriteFlashDataToDwinLCD(dwin,startAddress,txData,length);
  }
}

/*���ֲ��ſ���playNumΪ0ʱ��ʾֹͣ����*/
void HandleDwinLCDToPlayMusic(DwinObjectType *dwin,uint16_t playStart,uint16_t playNum,uint16_t volume)
{
  uint8_t regAddress=0x50;
  uint16_t length;
  uint8_t txData[5];
  
  if(playNum>0)
  {
    length=5;
    txData[0]=0x5A;
    txData[1]=playStart;
    txData[2]=playNum;
    txData[3]=0x5A;
    txData[4]=(uint8_t)(volume*64/100);
  }
  else
  {
    length=3;
    txData[0]=0x5A;
    txData[1]=playStart;
    txData[2]=0x00;
  }

  SetRegisterDataToDwinLCD(dwin,regAddress,txData,length);
}

/*��������ʾ����*/
void SetDwinLCDDisplay(DwinObjectType *dwin,uint16_t picID)
{
  uint8_t regAddress=0x03;      //������ʾ�Ĵ���
  uint16_t length=2;
  uint8_t txData[2];
  txData[0]=(picID>>8);
  txData[1]=picID;
  SetRegisterDataToDwinLCD(dwin,regAddress,txData,length);
}

/*д�Ĵ������ݣ�һ���������д16���ֽڣ���length<=16*/
static void SetRegisterDataToDwinLCD(DwinObjectType *dwin,uint8_t regAddress,uint8_t *txData,uint16_t length)
{
  /*����ĳ�����֡ͷ��2���ֽڣ�+���ݳ��ȣ�1���ֽڣ�+ָ�1���ֽڣ�+�Ĵ�����ַ��1���ֽڣ�+д������(���16�ֽ�)+CRCУ�飨2���ֽڣ�*/
  uint16_t cmd_Length=length+5;
  uint8_t cmd_Reg_Write[23];
  cmd_Reg_Write[0]=0x5A;
  cmd_Reg_Write[1]=0xA5;
  cmd_Reg_Write[2]=(uint8_t)(length+2);
  cmd_Reg_Write[3]= FC_REG_Write;
  cmd_Reg_Write[4]=regAddress;
  for(int dataIndex=0;dataIndex<length;dataIndex++)
  {
    cmd_Reg_Write[dataIndex+5]=txData[dataIndex];
  }
	
  if(dwin->checkMode>DwinNone)
  {
    uint16_t checkCode=CalcDwinCRC16(&cmd_Reg_Write[3],length+2);
    cmd_Reg_Write[length+5]=(uint8_t)checkCode;
    cmd_Reg_Write[length+6]=(uint8_t)(checkCode>>8);
    cmd_Length=cmd_Length+2;
  }
	
  dwin->SendData(cmd_Reg_Write,cmd_Length);
}

/*���Ĵ�������*/
static void GetRegisterDataFromDwinLCD(DwinObjectType *dwin,uint8_t regAddress,uint8_t readByteLength)
{
  /*����ĳ�����֡ͷ��2���ֽڣ�+���ݳ��ȣ�1���ֽڣ�+ָ�1���ֽڣ�+�Ĵ�����ַ��1���ֽڣ�+��ȡ�Ĵ������ֽڳ��ȣ�1���ֽڣ�+CRCУ�飨2���ֽڣ�*/
  uint16_t cmd_Length=6;
  uint8_t cmd_Reg_Read[]={0x5A,0xA5,0x03,FC_REG_Read,0x00,0x00,0x00,0x00};//����������
  cmd_Reg_Read[4]=regAddress;
  cmd_Reg_Read[5]=readByteLength;
	
  if(dwin->checkMode>DwinNone)
  {
    uint16_t checkCode=CalcDwinCRC16(&cmd_Reg_Read[3],3);
    cmd_Reg_Read[6]=(uint8_t)checkCode;
    cmd_Reg_Read[7]=(uint8_t)(checkCode>>8);
    cmd_Length=cmd_Length+2;
  }
	
  dwin->SendData(cmd_Reg_Read,cmd_Length);
}

/* CRC16У�飨X16+X15+X2+1��*/
static uint16_t CalcDwinCRC16(uint8_t *buf,uint16_t length)
{
  uint16_t crc16,data,val;
 
  crc16 = 0x0000;
 
  for(int i=0;i<length;i++)
  {
    if((i % 8) == 0)
    {
      data = (*buf++)<<8;
     }
    val = crc16 ^ data;
    crc16 = crc16<<1;
    data = data <<1;
    if(val&0x8000)
    {
      crc16 = crc16 ^ 0x8005;
    }
  }
  return crc16;
}

/* ��ʼ�����Ĵ��������� */
void DwinInitialization(DwinObjectType *dwin,
                        DwinCheckCodeType checkMode,
                        DwinSortType sort,
                        SendDataForDwinType SendData
                       )
{
  if((dwin==NULL)||(SendData==NULL))
  {
    return;
  }
  
  dwin->checkMode=checkMode;
  dwin->SendData=SendData;
  
  dwin->sort=sort;
	
  dwin->GetRegister=GetRegisterDataFromDwinLCD;
  dwin->SetRegister=SetRegisterDataToDwinLCD;
	
  dwin->rxBuffer.pRead=0;
  dwin->rxBuffer.pWrite=0;
  
  dwin->rxBuffer.DeQueue=BufferDataDeQueue;
  dwin->rxBuffer.EnQueue=BufferDataEnQueue;
  
  for(int i=0;i<RxBufferLength;i++)
  {
    dwin->rxBuffer.queue[i]=0x00;
  }
}

/*�ӻ����ж�ȡ����*/
static uint16_t BufferDataDeQueue(DwinObjectType *dwin,uint8_t *rxBuf)
{
  uint16_t length=0;
  uint8_t pTemp;
	
  if(dwin->rxBuffer.pRead==dwin->rxBuffer.pWrite)
  {
    length=0;
  }
  else
  {
    while((dwin->rxBuffer.queue[dwin->rxBuffer.pRead]!=0x5A)||(dwin->rxBuffer.queue[dwin->rxBuffer.pRead+1]!=0xA5))
    {
      if(++(dwin->rxBuffer.pRead)>=(uint8_t)RxBufferLength)
      {
        dwin->rxBuffer.pRead=0;
      }
      
      if(dwin->rxBuffer.pRead==dwin->rxBuffer.pWrite)
      {
        length=0;
        break;
      }
    }
    
    pTemp=dwin->rxBuffer.pRead;
    
    do
    {
      rxBuf[length++]=dwin->rxBuffer.queue[dwin->rxBuffer.pRead];
      
      if(++(dwin->rxBuffer.pRead)>=(uint8_t)RxBufferLength)
      {
        dwin->rxBuffer.pRead=0;
      }
      
      if(dwin->rxBuffer.pRead==dwin->rxBuffer.pWrite)
      {
        length=0;
        dwin->rxBuffer.pRead=pTemp;
        break;
      }
    }while((dwin->rxBuffer.queue[dwin->rxBuffer.pRead]!=0x5A)||(dwin->rxBuffer.queue[dwin->rxBuffer.pRead+1]!=0xA5));
      
  }
  return length;
}
	
/*�����յ������ݼ��뻺��*/
static void BufferDataEnQueue(DwinObjectType *dwin,uint8_t rData)
{
  dwin->rxBuffer.queue[dwin->rxBuffer.pWrite]=rData;

  if(++(dwin->rxBuffer.pWrite)>=(uint8_t)RxBufferLength)
  {
    dwin->rxBuffer.pWrite=0;
  }
}

/*********** (C) COPYRIGHT 1999-2019 Moonan Technology *********END OF FILE****/
