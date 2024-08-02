/******************************************************************************/
/** ģ�����ƣ���չ��������                                                   **/
/** �ļ����ƣ�adxl345function.c                                              **/
/** ��    ����V1.1.0                                                         **/
/** ��    �飺����ʵ��adxl345 3�����ּ��ٶȼƵĲ���������I2C��SPIͨѶ        **/
/**           CS����������VDD��I2Cģʽʹ�ܡ�                                 **/
/**           SPIģʽ�£� CS�����������������ơ�                             **/
/**           �Ĵ�����ַ�������£�                                           **/
/**           ����SPIͨѶ�ӿ�ʱ�����SPIʱ���ٶ�Ϊ5 MHz��ʱ�򷽰�����ʱ�Ӽ�  **/
/**           ��(CPOL)= 1��ʱ����λ(CPHA)= 1ִ�С�                           **/
/**           ����I2CͨѶ�ӿ�ʱ��ALT ADDRESS���Ŵ��ڸߵ�ƽ��������7λI2C��ַ **/
/**           ��0x1D�����ΪR/Wλ����ת��Ϊ0x3Aд�룬0x3B��ȡ��              **/
/**           ͨ��ALT ADDRESS����(����12)�ӵأ�����ѡ����I2C��ַ0x53(��    **/
/**           ��ΪR/Wλ)����ת��Ϊ0xA6д�룬0xA7��ȡ������Ӧ��ʵ������       **/
/**           �Ĵ�����ַ�������£�                                           **/
/**  +--------+------+--------------+----+--------+------------------------+ **/
/**  |ʮ������|ʮ����|     ����     |����| ��λֵ | ����                   | **/
/**  +--------+------+--------------+----+--------+------------------------+ **/
/**  |  0x00  |   0  |    DEVID     | R  |11100101|����ID                  | **/
/**  +--------+------+--------------+----+--------+------------------------+ **/
/**  |  0x1D  |  29  |  THRESH_TAP  | R/W|00000000|�û���ֵ                | **/
/**  +--------+------+--------------+----+--------+------------------------+ **/
/**  |  0x1E  |  30  |     OFSX     | R/W|00000000|X��ƫ��                 | **/
/**  +--------+------+--------------+----+--------+------------------------+ **/
/**  |  0x1F  |  31  |     OFSY     | R/W|00000000|Y��ƫ��                 | **/
/**  +--------+------+--------------+----+--------+------------------------+ **/
/**  |  0x20  |  32  |     OFSZ     | R/W|00000000|Z��ƫ��                 | **/
/**  +--------+------+--------------+----+--------+------------------------+ **/
/**  |  0x21  |  33  |     DUR      | R/W|00000000|�û�����ʱ��            | **/
/**  +--------+------+--------------+----+--------+------------------------+ **/
/**  |  0x22  |  34  |    Latent    | R/W|00000000|�û��ӳ�                | **/
/**  +--------+------+--------------+----+--------+------------------------+ **/
/**  |  0x23  |  35  |    Window    | R/W|00000000|�û�����                | **/
/**  +--------+------+--------------+----+--------+------------------------+ **/
/**  |  0x24  |  36  |  THRESH_ACT  | R/W|00000000|���ֵ                | **/
/**  +--------+------+--------------+----+--------+------------------------+ **/
/**  |  0x25  |  37  | THRESH_INACT | R/W|00000000|��ֹ��ֵ                | **/
/**  +--------+------+--------------+----+--------+------------------------+ **/
/**  |  0x26  |  38  |  TIME_INACT  | R/W|00000000|��ֹʱ��                | **/
/**  +--------+------+--------------+----+--------+------------------------+ **/
/**  |  0x27  |  39  | ACT_INACT_CTL| R/W|00000000|��ʹ�ܿ��ƻ�;�ֹ���| **/
/**  +--------+------+--------------+----+--------+------------------------+ **/
/**  |  0x28  |  40  |   THRESH_FF  | R/W|00000000|����������ֵ            | **/
/**  +--------+------+--------------+----+--------+------------------------+ **/
/**  |  0x29  |  41  |   TIME_FF    | R/W|00000000|��������ʱ��            | **/
/**  +--------+------+--------------+----+--------+------------------------+ **/
/**  |  0x2A  |  42  |   TAP_AXES   | R/W|00000000|����/˫�������         | **/
/**  +--------+------+--------------+----+--------+------------------------+ **/
/**  |  0x2B  |  43  |ACT_TAP_STATUS| R  |00000000|����/˫��Դ             | **/
/**  +--------+------+--------------+----+--------+------------------------+ **/
/**  |  0x2C  |  44  |   BW_RATE    | R/W|00001010|�������ʼ�����ģʽ����  | **/
/**  +--------+------+--------------+----+--------+------------------------+ **/
/**  |  0x2D  |  45  |  POWER_CTL   | R/W|00000000|ʡ�����Կ���            | **/
/**  +--------+------+--------------+----+--------+------------------------+ **/
/**  |  0x2E  |  46  |  INT_ENABLE  | R/W|00000000|�ж�ʹ�ܿ���            | **/
/**  +--------+------+--------------+----+--------+------------------------+ **/
/**  |  0x2F  |  47  |   INT_MAP    | R/W|00000000|�ж�ӳ�����            | **/
/**  +--------+------+--------------+----+--------+------------------------+ **/
/**  |  0x30  |  48  |   INT_SOURCE | R  |00000010|�ж�Դ                  | **/
/**  +--------+------+--------------+----+--------+------------------------+ **/
/**  |  0x31  |  49  | DATA_FORMAT  | R/W|00000000|���ݸ�ʽ����            | **/
/**  +--------+------+--------------+----+--------+------------------------+ **/
/**  |  0x32  |  50  |    DATAX0    | R  |00000000|X������0                | **/
/**  +--------+------+--------------+----+--------+------------------------+ **/
/**  |  0x33  |  51  |    DATAX1    | R  |00000000|X������1                | **/
/**  +--------+------+--------------+----+--------+------------------------+ **/
/**  |  0x34  |  52  |    DATAY0    | R  |00000000|Y������0                | **/
/**  +--------+------+--------------+----+--------+------------------------+ **/
/**  |  0x35  |  53  |    DATAY1    | R  |00000000|Y������1                | **/
/**  +--------+------+--------------+----+--------+------------------------+ **/
/**  |  0x36  |  54  |    DATAZ0    | R  |00000000|Z������0                | **/
/**  +--------+------+--------------+----+--------+------------------------+ **/
/**  |  0x37  |  55  |    DATAZ1    | R  |00000000|Z������1                | **/
/**  +--------+------+--------------+----+--------+------------------------+ **/
/**  |  0x38  |  56  |   FIFO_CTL   | R/W|00000000|FIFO����                | **/
/**  +--------+------+--------------+----+--------+------------------------+ **/
/**  |  0x39  |  57  |  FIFO_STATUS | R  |00000000|FIFO״̬                | **/
/**  +--------+------+-------------------+--------+------------------------+ **/
/**--------------------------------------------------------------------------**/
/** �޸ļ�¼��                                                               **/
/**     �汾      ����              ����              ˵��                   **/
/**     V1.0.0  2017-07-17          ľ��              �����ļ�               **/
/**     V1.1.0  2019-08-07          ľ��              �޸�Ϊ���ڶ���Ĳ���   **/
/**                                                                          **/
/******************************************************************************/ 

#include "stddef.h"
#include "adxl345function.h"

/* ��ȡADXL345�ļĴ��� */
static uint8_t Adxl345ReadRegister(Adxl345ObjectType *adxl,uint8_t regAdd);
/* дADXL345�ļĴ��� */
static void Adxl345WriteRegister(Adxl345ObjectType *adxl,uint8_t regAdd,uint8_t wData);
/* ��ȡ����Ĵ�����ֵ */
static void Adxl345ReadMultiReg(Adxl345ObjectType *adxl,uint8_t startRegAdd,uint8_t *rData,uint16_t rSize);
/* ����һ��Ĭ�ϵ�Ƭѡ���������Ա���Ӳ��ʹ����ʹ�� */
static void Adxl345ChipSelect(Adxl345CSType en);

/*��ȡ����ֵ���ֱ���(3.9 mg/LSB)*/
void GetValueFromAdxl345(Adxl345ObjectType *adxl)
{
  uint8_t devID = 0;
  uint8_t dataTemp[6];

  /*��ȡ�豸ID����ÿ�β���ǰ��һ��*/
  devID=Adxl345ReadRegister(adxl,REG_DEVID);
  if(adxl->devID!=devID)
  {
    return;
  }
  adxl->Delayus(200);
  
  /*��ȡ��������ֵ*/
  Adxl345ReadMultiReg(adxl,REG_DATAX0,dataTemp,6);
  
  /*���ݽ���*/
  adxl->incidence_X = (int16_t)(dataTemp[0] + ((uint16_t)dataTemp[1] << 8));
  adxl->incidence_Y = (int16_t)(dataTemp[2] + ((uint16_t)dataTemp[3] << 8));
  adxl->incidence_Z = (int16_t)(dataTemp[4] + ((uint16_t)dataTemp[5] << 8));
	
  adxl->incidence_Xf = (float)(adxl->incidence_X * 0.0039);
  adxl->incidence_Yf = (float)(adxl->incidence_Y * 0.0039);
  adxl->incidence_Zf = (float)(adxl->incidence_Z * 0.0039);
}

/*��ADXL345���г�ʼ������*/
void Adxl345Initialization(Adxl345ObjectType *adxl,uint8_t devAdd,
                           Adxl345PortType port,
                           Adxl345ReadBytesType read,
                           Adxl345WriteBytesType write,
                           Adxl345ChipSelectType cs,
                           Adxl345DelayType delay)
{
  uint8_t devID=0;
  uint8_t setValue=0;
	
  if((adxl==NULL)||(read==NULL)||(write==NULL)||(delay==NULL))
  {
    return;
  }
	
  if(port==ADXL345_SPI)
  {
    if(cs==NULL)
    {
      adxl->ChipSelect=Adxl345ChipSelect;
    }
    else
    {
      adxl->ChipSelect=cs;
    }
    adxl->devAddress=0x00;
  }
  else
  {
    if((devAdd==0xA6)||(devAdd==0x3A))
    {
      adxl->devAddress=devAdd;
    }
    else if((devAdd==0x53)||(devAdd==0x1D))
    {
      adxl->devAddress=(devAdd<<1);
    }
    else
    {
      adxl->devAddress=0x00;
    }
    adxl->ChipSelect=NULL;
  }
	
  adxl->port=port;
  adxl->devID=0xE5;
  adxl->incidence_X=0;
  adxl->incidence_Xf=0.0;
  adxl->incidence_Y=0;
  adxl->incidence_Yf=0.0;
  adxl->incidence_Z=0;
  adxl->incidence_Zf=0.0;
	
  adxl->ReadBytes=read;
  adxl->WriteBytes=write;
  adxl->Delayus=delay;
	
  /*��ȡ�豸ID����ÿ�β���ǰ��һ��*/
  devID=Adxl345ReadRegister(adxl,REG_DEVID);
  if(adxl->devID!=devID)
  {
    return;
  }
  adxl->Delayus(300);
  
  /*�������ݸ�ʽ*/
  setValue = 0x2B;
  Adxl345WriteRegister(adxl,REG_DATA_FORMAT,setValue);
  adxl->Delayus(50);
    
  /*�����������ʼ�����ģʽ*/
  setValue = 0x0A;
  Adxl345WriteRegister(adxl,REG_BW_RATE,setValue);
  adxl->Delayus(50);
    
  /*���õ�Դ����*/
  setValue = 0x28;
  Adxl345WriteRegister(adxl,REG_POWER_CTL,setValue);
  adxl->Delayus(50);
    
  /*�����ж�ʹ��*/
  setValue = 0;
  Adxl345WriteRegister(adxl,REG_INT_ENABLE,setValue);
  adxl->Delayus(50);

  /*����X��ƫ��*/
  Adxl345WriteRegister(adxl,REG_OFSX,setValue);
  adxl->Delayus(50);

  /*����Y��ƫ��*/
  Adxl345WriteRegister(adxl,REG_OFSY,setValue);
  adxl->Delayus(50);

  /*����Z��ƫ��*/
  Adxl345WriteRegister(adxl,REG_OFSZ,setValue);
  adxl->Delayus(500);
}

/* ��ȡADXL345�ļĴ��� */
static uint8_t Adxl345ReadRegister(Adxl345ObjectType *adxl,uint8_t regAdd)
{
  uint8_t regValue=0;
	
  if(adxl->port==ADXL345_SPI)
  {
    adxl->ChipSelect(ADXL345CS_Enable);
    adxl->Delayus(50);
    adxl->ReadBytes(adxl,regAdd,&regValue,1);
    adxl->Delayus(50);
    adxl->ChipSelect(ADXL345CS_Disable);
  }
  else
  {
    adxl->ReadBytes(adxl,regAdd,&regValue,1);
  }
	
  return regValue;
}

/* дADXL345�ļĴ��� */
static void Adxl345WriteRegister(Adxl345ObjectType *adxl,uint8_t regAdd,uint8_t wData)
{
  if(adxl->port==ADXL345_SPI)
  {
    adxl->ChipSelect(ADXL345CS_Enable);
    adxl->Delayus(50);
    adxl->WriteBytes(adxl,regAdd,&wData,1);
    adxl->Delayus(50);
    adxl->ChipSelect(ADXL345CS_Disable);
  }
  else
  {
    adxl->WriteBytes(adxl,regAdd,&wData,1);
  }
}

/* ��ȡ����Ĵ�����ֵ */
static void Adxl345ReadMultiReg(Adxl345ObjectType *adxl,uint8_t startRegAdd,uint8_t *rData,uint16_t rSize)
{
  if(adxl->port==ADXL345_SPI)
  {
    adxl->ChipSelect(ADXL345CS_Enable);
    adxl->Delayus(50);
		
    for(int i=0;i<rSize;i++)
    {
      adxl->ReadBytes(adxl,startRegAdd+i,&rData[i],1);
    }
		
    adxl->Delayus(50);
    adxl->ChipSelect(ADXL345CS_Disable);
  }
  else
  {
    adxl->ReadBytes(adxl,startRegAdd,rData,rSize);
  }
}

/* ����һ��Ĭ�ϵ�Ƭѡ���������Ա���Ӳ��ʹ����ʹ�� */
static void Adxl345ChipSelect(Adxl345CSType en)
{
  return;
}
/*********** (C) COPYRIGHT 1999-2019 Moonan Technology *********END OF FILE****/
