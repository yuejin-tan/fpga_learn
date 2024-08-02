/******************************************************************************/
/** ģ�����ƣ���չ��������                                                   **/
/** �ļ����ƣ�sht3xfunction.c                                                **/
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

#include "stddef.h"
#include "sht3xfunction.h"

const uint16_t SHT3xPOLYNOMIAL = 0x31;      //����У�����ʽP(x) = x^8 + x^5 + x^4 + 1 = 100110001

/*����ָ���Ķ���ʽ����CRCУ��*/
static SHT3xErrorType CheckCRC8ForSHT3x(uint8_t *data, uint8_t numOfBytes, uint8_t checksum);
/* ��ȡSHT3x��������к�*/
static SHT3xErrorType SHT3xReadSerialNumber(SHT3xObjectType *sht);
/* ��SHT3x�������� */
static void SHT3xWriteCommand(SHT3xObjectType *sht,SHT3xCommands cmd);
/* ���������¶�����ֵ*/
static float CalcTemperatureValue(uint16_t code);
/* ����ʪ������ֵ */
static float CalcHumidityValue(uint16_t code);

/* ��ȡһ���Բɼ� */
SHT3xErrorType SHT3xGetSingleShotData(SHT3xObjectType *sht,SHT3xRepeatability repeatability,SHT3xMode mode)
{
  SHT3xErrorType error=SHT3X_NO_ERROR;
  uint8_t data[6];
  uint16_t tempCode;
  uint16_t humiCode;
  
  SHT3xCommands commands[2][3]={{CMD_MEAS_CLOCKSTR_H,  // �������ݲɼ�ģʽ��ʱ����չ�����ظ���
                                 CMD_MEAS_CLOCKSTR_M,  // �������ݲɼ�ģʽ��ʱ����չ�����ظ���
                                 CMD_MEAS_CLOCKSTR_L,  // �������ݲɼ�ģʽ��ʱ����չ�����ظ���
                                },
                                {CMD_MEAS_POLLING_H,   // �������ݲɼ�ģʽ����ѯ�����ظ���
                                 CMD_MEAS_POLLING_M,   // �������ݲɼ�ģʽ����ѯ�����ظ���
                                 CMD_MEAS_POLLING_L,   // �������ݲɼ�ģʽ����ѯ�����ظ���
                                }};
  
  SHT3xWriteCommand(sht,commands[mode][repeatability]);
  
  if(mode==MODE_CLKSTRETCH)
  {
    sht->Delayms(1);
  }
  else if(mode==MODE_POLLING)
  {
    sht->Delayms(20);
  }
  
  sht->Receive(sht,data,6);
  
  error|=CheckCRC8ForSHT3x(&data[0],2,data[2]);
  
  error|=CheckCRC8ForSHT3x(&data[3],2,data[5]);
  
  if(error==SHT3X_NO_ERROR)
  {
    tempCode=(data[0]<<8)+data[1];
    humiCode=(data[3]<<8)+data[4];
    
    sht->temperature=CalcTemperatureValue(tempCode);
    sht->humidity=CalcHumidityValue(humiCode);
  }

  return error;
}

/* �������������ݲɼ� */
void SHT3xStartPeriodicMeasurment(SHT3xObjectType *sht,SHT3xRepeatability repeatability,SHT3xFrequency frequency)
{
  SHT3xCommands commands[5][3]={{CMD_MEAS_PERI_05_H,   // �������ݲɼ�ģʽ��0.5 mps, ���ظ���
                                 CMD_MEAS_PERI_05_M,   // �������ݲɼ�ģʽ��0.5 mps, ���ظ���
                                 CMD_MEAS_PERI_05_L,   // �������ݲɼ�ģʽ��0.5 mps, ���ظ���
                                },
                                {CMD_MEAS_PERI_1_H,    // �������ݲɼ�ģʽ��1 mps, ���ظ���
                                 CMD_MEAS_PERI_1_M,    // �������ݲɼ�ģʽ��1 mps, ���ظ���
                                 CMD_MEAS_PERI_1_L,    // �������ݲɼ�ģʽ��1 mps, ���ظ���
                                },
                                {CMD_MEAS_PERI_2_H,    // �������ݲɼ�ģʽ��2 mps, ���ظ���
                                 CMD_MEAS_PERI_2_M,    // �������ݲɼ�ģʽ��2 mps, ���ظ���
                                 CMD_MEAS_PERI_2_L,    // �������ݲɼ�ģʽ��2 mps, ���ظ���
                                },
                                {CMD_MEAS_PERI_4_H,    // �������ݲɼ�ģʽ��4 mps, ���ظ���
                                 CMD_MEAS_PERI_4_M,    // �������ݲɼ�ģʽ��4 mps, ���ظ���
                                 CMD_MEAS_PERI_4_L,    // �������ݲɼ�ģʽ��4 mps, ���ظ���
                                },
                                {CMD_MEAS_PERI_10_H,   // �������ݲɼ�ģʽ��10 mps, ���ظ���
                                 CMD_MEAS_PERI_10_M,   // �������ݲɼ�ģʽ��10 mps, ���ظ���
                                 CMD_MEAS_PERI_10_L,   // �������ݲɼ�ģʽ��10 mps, ���ظ���
                                }};

  SHT3xWriteCommand(sht,commands[frequency][repeatability]);
}

/* ��ȡ�����Բɼ������� */
SHT3xErrorType SHT3xFetchPeriodicMeasurmentData(SHT3xObjectType *sht)
{
  SHT3xErrorType error=SHT3X_NO_ERROR;
  uint8_t data[6];
  uint16_t tempCode;
  uint16_t humiCode;

  SHT3xWriteCommand(sht,CMD_FETCH_DATA);
  
  sht->Delayms(1);
  
  sht->Receive(sht,data,6);
  
  error|=CheckCRC8ForSHT3x(&data[0],2,data[2]);
  
  error|=CheckCRC8ForSHT3x(&data[3],2,data[5]);
  
  if(error==SHT3X_NO_ERROR)
  {
    tempCode=(data[0]<<8)+data[1];
    humiCode=(data[3]<<8)+data[4];
    
    sht->temperature=CalcTemperatureValue(tempCode);
    sht->humidity=CalcHumidityValue(humiCode);
  }

  return error;
}

/* �������ڲɼ�ʹ��ART */
void SHT3xARTCommand(SHT3xObjectType *sht)
{
  SHT3xWriteCommand(sht,CMD_ART);
}

/* ֹͣ���ڲɼ�ģʽ*/
void SHT3xBreakCommand(SHT3xObjectType *sht)
{
  SHT3xWriteCommand(sht,CMD_BREAK_STOP);
}


/* SHT3x�ӿڸ�λ */
void SHT3xInterfaceReset(SHT3xObjectType *sht)
{
  //SDA���Ͳ�����9��ʱ�����ڵĵ͵�ƽ
  uint8_t cmdWrite[2];
  cmdWrite[0]=0x00;
  cmdWrite[1]=0x00;
  
  sht->Transmit(sht,cmdWrite,2);
}

/* SHT3x�㲥��λ */
void SHT3xGeneralCallReset(SHT3xObjectType *sht)
{
  uint8_t cmd=0x06;
  sht->Transmit(0x00,&cmd,1);
}

/* SHT3x�����λ */
void SHT3xSoftReset(SHT3xObjectType *sht)
{
  SHT3xWriteCommand(sht,CMD_SOFT_RESET);
}

/* SHT3x���ü����� */
void SHT3xEnableHeater(SHT3xObjectType *sht)
{
  SHT3xWriteCommand(sht,CMD_HEATER_ENABLE);
}

/* SHT3x���ü����� */
void SHT3xDisableHeater(SHT3xObjectType *sht)
{
  SHT3xWriteCommand(sht,CMD_HEATER_DISABLE);
}

/* ��ȡ״̬�Ĵ�����ֵ */
SHT3xErrorType SHT3xReadStatusRegister(SHT3xObjectType *sht,SHT3xStatusRegister *status)
{
  SHT3xErrorType error=SHT3X_NO_ERROR;
  uint8_t sta[3];

  SHT3xWriteCommand(sht,CMD_READ_STATUS);
  
  sht->Delayms(1);
  
  sht->Receive(sht,sta,3);
  
  error|=CheckCRC8ForSHT3x(&sta[0],2,sta[2]);
  
  if(error==SHT3X_NO_ERROR)
  {
    status->word=(sta[0]<<8)+sta[1];
  }
  else
  {
    status->word=0;
  }
  
  return error;
}

/* ���״̬�Ĵ�����״̬��־ */
void SHT3xClearStatusRegister(SHT3xObjectType *sht)
{
  SHT3xWriteCommand(sht,CMD_CLEAR_STATUS);
}

/* ��SHT3x�������� */
static void SHT3xWriteCommand(SHT3xObjectType *sht,SHT3xCommands cmd)
{
  uint8_t cmdWrite[2];
  cmdWrite[0]=(uint8_t)(cmd>>8);
  cmdWrite[1]=(uint8_t)cmd;
  
  sht->Transmit(sht,cmdWrite,2);
}

/* ��ȡSHT3x��������к�*/
static SHT3xErrorType SHT3xReadSerialNumber(SHT3xObjectType *sht)
{
  SHT3xErrorType error=SHT3X_NO_ERROR;
  uint8_t sn[6];

  SHT3xWriteCommand(sht,CMD_READ_SERIALNBR);
  
  sht->Delayms(1);
  
  sht->Receive(sht,sn,6);
  
  error|=CheckCRC8ForSHT3x(&sn[0],2,sn[2]);
  
  error|=CheckCRC8ForSHT3x(&sn[3],2,sn[5]);
  
  if(error==SHT3X_NO_ERROR)
  {
    sht->serialNumber=(sn[0]<<24)+(sn[1]<<16)+(sn[3]<<8)+sn[4];
  }
  else
  {
    sht->serialNumber=0;
  }

  return error;
}

/* SHT3x�����ʼ�� */
SHT3xErrorType SHT3xInitialization(SHT3xObjectType *sht,        //����ʼ����SHT3X
                                   uint8_t address,             //�豸��ַ
                                   SHT3xReceive receive,        //�������ݺ���ָ��
                                   SHT3xTransmit transmit,      //�������ݺ���ָ��
                                   SHT3xDelayms delayms         //������ʱ����ָ��
                                  )
{
  SHT3xErrorType error=SHT3X_NO_ERROR;
  
  if((sht==NULL)||(receive==NULL)||(transmit==NULL)||(delayms==NULL))
  {
    return SHT3X_INIT_ERROR;
  }
  sht->Receive=receive;
  sht->Transmit=transmit;
  sht->Delayms=delayms;
	
  sht->temperature=0.0;
  sht->humidity=0.0;
  
  if((address==0x44)||(address==0x45))
  {
    sht->devAddress=(address<<1);
  }
  else if((address==0x88)||(address==0x8A))
  {
    sht->devAddress=address;
  }
  else
  {
    sht->devAddress=0;
    error|=SHT3X_PARM_ERROR;
  }
  
  if(error==SHT3X_NO_ERROR)
  {
    error|=SHT3xReadSerialNumber(sht);
  }
  
  return error;
}

/*����ָ���Ķ���ʽ����CRCУ��*/
static SHT3xErrorType CheckCRC8ForSHT3x(uint8_t *data, uint8_t numOfBytes, uint8_t checksum)
{
  uint8_t crc = 0xFF;
  uint8_t bit;
  SHT3xErrorType error=SHT3X_NO_ERROR;

  for(uint8_t i = 0; i < numOfBytes; i++)
  {
    crc ^= (data[i]);
    for ( bit = 8; bit > 0; --bit)
    {
      if (crc & 0x80)
      {
        crc = (crc << 1) ^ SHT3xPOLYNOMIAL;
      }
      else
      {
        crc = (crc << 1);
      }
    }
  }
  
  if(crc != checksum)
  {
    error|=SHT3X_CHECKSUM_ERROR;
  }

  return error;
}

/* ����ʪ������ֵ */
static float CalcHumidityValue(uint16_t code)
{
  float result=0.0;
  result=code/65535.0*100.0;
  return result;
}

/* ���������¶�����ֵ*/
static float CalcTemperatureValue(uint16_t code)
{
  float result=0.0;
  result=code/65535.0*175.0-45.0;
  return result;
}

/*********** (C) COPYRIGHT 1999-2018 Moonan Technology *********END OF FILE****/
