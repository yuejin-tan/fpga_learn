/******************************************************************************/
/** ģ�����ƣ���չ��������                                                   **/
/** �ļ����ƣ�dht11function.h                                                **/
/** ��    ����V1.0.0                                                         **/
/** ��    �飺����ʵ��DHT11��ʪ�ȴ�������ͨѶ                                **/
/**           ���õ�����ͨѶ��ʽ�����ݸ�ʽ���£�                             **/
/**           ʪ������+ʪ��С��+�¶�����+�¶�С��+У���                     **/
/**--------------------------------------------------------------------------**/
/** �޸ļ�¼��                                                               **/
/**     �汾      ����              ����              ˵��                   **/
/**     V1.0.0  2017-03-07          ľ��              �����ļ�               **/
/**                                                                          **/
/******************************************************************************/ 

#include "stddef.h"
#include "dht11function.h"

/*��DHT11��ȡһ��λ,����ֵ��1/0*/
static uint8_t ReadBitFromDHT11(Dht11ObjectType *dht);
/*��DHT11��ȡһ���ֽ�,����ֵ������������*/
static uint8_t ReadByteFromDHT11(Dht11ObjectType *dht);
/*��λDHT11*/
static void ResetDHT11(Dht11ObjectType *dht);
/*�ȴ�DHT11�Ļ�Ӧ������1��δ��⵽DHT11�Ĵ��ڣ�����0������*/
static DHT11ErrorType CheckDHT11Status(Dht11ObjectType *dht);

/*��DHT11��ȡ����,temp:�¶�ֵ(0-50),humi:ʪ��ֵ(20%-90%),����ֵ��0,����;1,ʧ��*/
DHT11ErrorType GetProcessValueFromDHT11(Dht11ObjectType *dht)    
{
  DHT11ErrorType error=DHT11_None;
  uint8_t readBuffer[5];
  
  ResetDHT11(dht);
  if(CheckDHT11Status(dht)==DHT11_NoError)
  {
    for(int i=0;i<5;i++)
    {
      readBuffer[i]=ReadByteFromDHT11(dht);
    }
		
    uint8_t checkSum=0;
    checkSum=readBuffer[0]+readBuffer[1]+readBuffer[2]+readBuffer[3];
		error=DHT11_DataError;
    if(checkSum==readBuffer[4])
    {
      dht->temperature=(float)readBuffer[0];
      dht->humidity=(float)readBuffer[2];
      error=DHT11_NoError;
    }
  }
  return error;
}

/*DHT11��ʼ������*/
DHT11ErrorType InitializeDHT11(Dht11ObjectType *dht,    //��Ҫ��ʼ������
                               Dht11SetPinOutValueType setPinStatus,    //�����������ֵ
                               Dht11ReadPinBitType getPinStatus,        //��ȡ��������ֵ
                               Dht11SetPinModeType mode,        //�������ߵ��������ģʽ
                               Dht11DelayType delayms,  //������ʱ
                               Dht11DelayType delayus   //΢����ʱ
                              )
{
  if((dht==NULL)||(setPinStatus==NULL)||(getPinStatus==NULL)||(mode==NULL)||(delayms==NULL)||(delayus==NULL))
  {
    return DHT11_InitError;
  }
  dht->SetPinOutValue=setPinStatus;
  dht->ReadPinBit=getPinStatus;
  dht->SetPinMode=mode;
  dht->Delayms=delayms;
  dht->Delayus=delayus;
	
  dht->humidity=0.0;
  dht->temperature=0.0;
	
  ResetDHT11(dht);
  return CheckDHT11Status(dht);
}

/*��λDHT11����ʼͨѶ*/
static void ResetDHT11(Dht11ObjectType *dht)
{
  dht->SetPinMode(DHT11_Out);   //����Ϊ�����ʽ
  dht->SetPinOutValue(DHT11_Reset);     //�����ŵ�λ����
  dht->Delayms(20);     //��������18ms
  dht->SetPinOutValue(DHT11_Set);       //����
  dht->Delayus(30);     //��������20��40us
}

/*�ȴ�DHT11�Ļ�Ӧ������1��δ��⵽DHT11�Ĵ��ڣ�����0������*/
static DHT11ErrorType CheckDHT11Status(Dht11ObjectType *dht)
{
  uint8_t retry=0;
  dht->SetPinMode(DHT11_In);    //����Ϊ���뷽ʽ
  while(dht->ReadPinBit()&&(retry<100))
  {
    retry++;
    dht->Delayus(1);
  }
  if(retry>=100)
  {
    return DHT11_None;
  }
  retry=0;
  while(!dht->ReadPinBit()&&(retry<100))
  {
    retry++;
    dht->Delayus(1);
  }
  if(retry>=100)
  {
    return DHT11_None;
  }
  return DHT11_NoError;  
}

/*��DHT11��ȡһ��λ,����ֵ��1/0*/
static uint8_t ReadBitFromDHT11(Dht11ObjectType *dht)			 
{
  uint8_t retry=0;
  /*�ȴ���Ϊ�͵�ƽ*/
  while(dht->ReadPinBit()&&(retry<100))
  {
    retry++;
    dht->Delayus(1);
  }
  retry=0;
  /*�ȴ���ߵ�ƽ*/
  while(!dht->ReadPinBit()&&(retry<100))
  {
    retry++;
    dht->Delayus(1);
  }
  dht->Delayus(40);     //��ʱ�жϴ�λ��0����1
  
  return dht->ReadPinBit();
}

/*��DHT11��ȡһ���ֽ�,����ֵ������������*/
static uint8_t ReadByteFromDHT11(Dht11ObjectType *dht)
{
  uint8_t data=0;
  for(int i=0;i<8;i++)
  {
    data<<=1;
    data|=ReadBitFromDHT11(dht);
  }
  
  return data;
}

/*********** (C) COPYRIGHT 1999-2019 Moonan Technology *********END OF FILE****/
