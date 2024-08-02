/******************************************************************************/
/** ģ�����ƣ���չ��������                                                   **/
/** �ļ����ƣ�ad527xfunction.c                                               **/
/** ��    ����V1.0.2                                                         **/
/** ��    �飺�����Ͷ���AD527xϵ�����ֵ�λ��оƬ��صĸ��ֺ����Ͳ���         **/
/**           �����������AD5270��AD5271��AD5272��AD5274оƬ                 **/
/**           ���У�AD5270��AD5271����SPI�ӿ�(CPOL = 0, CPHA = 1)            **/
/**                 AD5272��AD5274����I2C�ӿ�                                **/
/**           ����һλ�Ĵ����ĸ�ʽ���£�                                     **/
/**           +---+---+--+--+--+--+--+--+--+--+--+--+--+--+--+--+            **/
/**           |δ���� |  ����λ   |          ����λ             |            **/
/**           +---+---+--+--+--+--+--+--+--+--+--+--+--+--+--+--+            **/
/**           | 0 | 0 |C3|C2|C1|C0|D9|D8|D7|D6|D5|D4|D3|D2|D1|D0|            **/
/**           +---+---+--+--+--+--+--+--+--+--+--+--+--+--+--+--+            **/
/**--------------------------------------------------------------------------**/
/**ʹ��˵����                                                                **/
/**    1������AD527x����ʵ�壬�����ú���AD527xInitialization��ʼ������ʵ�塣 **/
/**    2����ʼ��ʱ������������ΪAD5272��AD5274������豸��ַ���Ա�I2CͨѶ��  **/
/**       ����������ΪAD5270��AD5271��ʵ������void f(bool en)�ĺ�����������  **/
/**       ��ֵAD527x����ʵ���ChipSelcet����ָ�롣�Ա�SPIͨѶ��              **/
/**    3��ʵ������void f(struct AD527xObject *rx,uint8_t *rData,             **/
/**       uint16_t rSize)�ĺ����������丳ֵ��AD527x����ʵ���Receive����     **/
/**       ָ�롣��������ݲ���                                               **/
/**    4��ʵ������void f(struct AD527xObject *rx,uint8_t *wData,             **/
/**       uint16_t wSize)�ĺ����������丳ֵ��AD527x����ʵ���Transmit����    **/
/**       ָ�롣���д���ݲ���                                               **/
/**    5��ʵ������void f(volatile uint32_t nTime)��ʱ�����������丳ֵ��      **/
/**       AD527x����ʵ���Delay����ָ�롣��λΪ���롣                        **/
/**    6��������Ӧ�ĺ���ʵ����Ҫ�Ĳ�����                                     **/
/**--------------------------------------------------------------------------**/
/** �޸ļ�¼��                                                               **/
/**     �汾      ����              ����              ˵��                   **/
/**     V1.0.0  2019-04-01          ľ��              �����ļ�               **/
/**                                                                          **/
/******************************************************************************/ 

#include "stddef.h"
#include "ad527xfunction.h"

/* ����������� */
#define COMMAND_NOP                     (0x00<<10)
#define COMMAND_W_RDAC                  (0x01<<10)
#define COMMAND_R_RDAC                  (0x02<<10)
#define COMMAND_STORE_RDAC_50TP         (0x03<<10)
#define COMMAND_SOFTWARE_RESET          (0x04<<10)
#define COMMAND_R_50TP_NEXT_FRAME       (0x05<<10)
#define COMMAND_R_LAST_50TP_LOCATION    (0x06<<10)
#define COMMAND_W_CONTROL               (0x07<<10)
#define COMMAND_R_CONTROL               (0x08<<10)
#define COMMAND_SOFTWARE_SHUTDOWN       (0x09<<10)

/* ����д���ƼĴ������� */
#define PROGRAM_50TP_DISABLE		0x00	//0 = 50-TP��̽���(Ĭ��) 
#define PROGRAM_50TP_ENABLE			0x01	//1 = ʹ����������50-TP���
#define PROGRAM_RDAC_DISABLE		0x00	//0 = �α�λ�ö�����50-TP�洢���е�ֵ(Ĭ��)
#define PROGRAM_RDAC_ENABLE			0x02	//1 = ����ͨ�����ֽӿڸ����α�λ��
#define RDAC_RESISTANCE_ENABLE	0x00	//0 = RDAC�����ݲ�У׼ʹ��(Ĭ��) 
#define RDAC_RESISTANCE_DISABLE	0x04	//1 = RDAC�����ݲ�У׼����

/* ��������ض�ģʽ */
#define SOFT_NORMAL_MODE				0x00	//����ģʽ
#define SOFT_SHUTOFF_MODE				0x01	//�ض�ģʽ

/* ��ȡ���ƼĴ�����ֵ */
static void ReadControlRegister(AD527xObjectType *rx);
/* ���ÿ��ƼĴ���*/
static void SetControlRegister(AD527xObjectType *rx,uint16_t value);
/* ��������ض�ģʽ */
static void SetSoftShutMode(AD527xObjectType *rx,uint16_t mode);
/* Ĭ��ƬѮ�������� */
static void DefaultChipSelect(AD527xCSType en);
/* д�Ĵ������� */
static void AD527xWriteRegister(AD527xObjectType *rx,uint16_t cmd);
/* ���Ĵ������� */
static void AD527xReadRegister(AD527xObjectType *rx,uint16_t cmd,uint8_t *rData);
	
/* ����AD527x�α�λ�� */
void SetRDACForAd527x(AD527xObjectType *rx,uint16_t data)
{
  uint16_t temp=0;
  
  if((rx->type==AD5271)||(rx->type==AD5274))	//256��
  {
    temp=data>255?255:data;
  }
  else if((rx->type==AD5270)||(rx->type==AD5272))	//1024��
  {
    temp=data>1023?1023:data;
  }
	
  temp=COMMAND_W_RDAC|temp;
	
  if(((rx->conreg)&0x02)!=0x02)
  {
    SetControlRegister(rx,PROGRAM_RDAC_ENABLE|rx->conreg);
  }
	
  AD527xWriteRegister(rx,temp);
}

/* ��ʼ��AD527x����,I2C�ӿڱ����ʼ��devAddress��SPI�ӿڱ����ʼ��void (*ChipSelcet)(bool) */
void AD527xInitialization(AD527xObjectType *rx,
                          uint8_t address,
                          AD527xType type,
                          AD527xReceive recieve,
                          AD527xTransmit transmit,
                          AD527xChipSelect cs,
                          AD527xDelayms delayms)
{
  if((rx==NULL)||(recieve==NULL)||(transmit==NULL)||(delayms==NULL))
  {
    return;
  }
	
  if((type==AD5270)||(type==AD5271))	//ʹ��SPI�ӿ�
  {
    if(cs==NULL)	//Ӳ����·ʵ��Ƭѡ
    {
      rx->ChipSelect=DefaultChipSelect;
    }
    else
    {
      rx->ChipSelect=cs;
    }
    rx->devAddress=0x00;
  }
  else	//ʹ��I2C�ӿ�
  {
    if((address==0x58)||(address==0x5C)||(address==0x5E))
    {
      rx->devAddress=address;
    }
    else if((address==0x2C)||(address==0x2E)||(address==0x2F))
    {
      rx->devAddress=(address<<1);
    }
    else
    {
      rx->devAddress=0x00;
    }
  
    rx->ChipSelect=NULL;
  }	
  
  rx->type=type;
	
  rx->conreg=0x00;
  rx->rdac=0x0000;
	
  rx->Receive=recieve;
  rx->Transmit=transmit;
  rx->Delayms=delayms;
	
  ReadControlRegister(rx);
	
  SetSoftShutMode(rx,SOFT_NORMAL_MODE);
}

/* ��ȡRDAC�α�Ĵ��������� */
uint16_t ReadRDACFromAd527x(AD527xObjectType *rx)
{
  uint8_t rData[2];

  uint16_t cmd=COMMAND_R_RDAC;

  AD527xReadRegister(rx,cmd,rData);

  rx->rdac=(rData[0]<<8)+rData[1];
  
  return rx->rdac;
}

/* �洢�α����ã���RDAC���ô洢��50-TP�� */
void StoreRDACTo50TP(AD527xObjectType *rx)
{
  uint16_t cmd=COMMAND_STORE_RDAC_50TP;
	
  if(((rx->conreg)&0x01)!=0x01)
  {
    SetControlRegister(rx,PROGRAM_50TP_ENABLE|rx->conreg);
  }
	
  AD527xWriteRegister(rx,cmd);
}

/* �����λ */
void AD527xSoftwareReset(AD527xObjectType *rx)
{
  uint16_t cmd=COMMAND_SOFTWARE_RESET;

  AD527xWriteRegister(rx,cmd);
}

/* ��ָ���洢λ�õ����� */
uint16_t ReadGivenAddressValue(AD527xObjectType *rx,uint8_t address)
{
  uint8_t rData[2];
  uint16_t cmd=COMMAND_R_50TP_NEXT_FRAME|address;
	
  AD527xReadRegister(rx,cmd,rData);
	
  return (rData[0]<<8)+rData[1];
}

/* ��ȡ���һ��50-TP��̴洢��λ�õĵ�ַ */
uint8_t ReadLast50TPAddress(AD527xObjectType *rx)
{
  uint8_t rData[2];
  uint16_t cmd=COMMAND_R_LAST_50TP_LOCATION;
	
  AD527xReadRegister(rx,cmd,rData);
	
  return rData[1];
}

/* ��������ض�ģʽ */
static void SetSoftShutMode(AD527xObjectType *rx,uint16_t mode)
{
  uint16_t cmd=COMMAND_SOFTWARE_SHUTDOWN|mode;
	
  AD527xWriteRegister(rx,cmd);
}

/* ���ÿ��ƼĴ���*/
static void SetControlRegister(AD527xObjectType *rx,uint16_t value)
{
  uint16_t cmd=COMMAND_W_CONTROL|value;
	
  AD527xWriteRegister(rx,cmd);
	
  ReadControlRegister(rx);
}

/* ��ȡ���ƼĴ�����ֵ */
static void ReadControlRegister(AD527xObjectType *rx)
{
  uint8_t rData[2];

  uint16_t cmd=COMMAND_R_CONTROL;
  
  AD527xReadRegister(rx,cmd,rData);
	
  rx->conreg=rData[1];
}

/* д�Ĵ������� */
static void AD527xWriteRegister(AD527xObjectType *rx,uint16_t cmd)
{
  uint8_t tData[2];
	
  tData[0]=(uint8_t)(cmd>>8);
  tData[1]=(uint8_t)cmd;
	
  if((rx->type==AD5270)||(rx->type==AD5271))	//SPI�ӿ�
  {
    rx->ChipSelect(AD527xCS_ENABLE);
    rx->Delayms(1);
  }

  rx->Transmit(rx,tData,2);
	
  if((rx->type==AD5270)||(rx->type==AD5271))	//SPI�ӿ�
  {
    rx->Delayms(1);
    rx->ChipSelect(AD527xCS_DISABLE);
  }
}

/* ���Ĵ������� */
static void AD527xReadRegister(AD527xObjectType *rx,uint16_t cmd,uint8_t *rData)
{
  uint8_t tData[2];
	
  if((rx->type==AD5270)||(rx->type==AD5271))	//SPI�ӿ�
  {
    rx->ChipSelect(AD527xCS_ENABLE);
    rx->Delayms(1);
  }
	
  rx->Transmit(rx,tData,2);

  rx->Receive(rx,rData,2);
	
  if((rx->type==AD5270)||(rx->type==AD5271))	//SPI�ӿ�
  {
    rx->Delayms(1);
    rx->ChipSelect(AD527xCS_DISABLE);
  }
}

/* Ĭ��Ƭѡ�������� */
static void DefaultChipSelect(AD527xCSType en)
{
  return;
}

/*********** (C) COPYRIGHT 1999-2019 Moonan Technology *********END OF FILE****/
