/******************************************************************************/
/** ģ�����ƣ���չ��������                                                   **/
/** �ļ����ƣ�bmp280function.c                                               **/
/** ��    ����V1.1.0                                                         **/
/** ��    �飺����ʵ��BMP280ѹ�����¶ȴ������Ĳ���                           **/
/**           BMP280��37���ɲ����Ĵ���������26��У׼���ݣ���ַ���£�         **/
/**  +----------+----+----+----+----+----+----+----+----+----+--------+----+ **/
/**  |�Ĵ�����  |��ַ|bit7|bit6|bit5|bit4|bit3|bit2|bit1|bit0|��λ״̬|��д| **/
/**  +----------+----+----+----+----+----+----+----+----+----+--------+----+ **/
/**  |temp_xlsb |0xFC|    temp_xlsb<7:4> | 0  | 0  | 0  | 0  |  0x00  |ֻ��| **/
/**  +----------+----+----+----+----+----+----+----+----+----+--------+----+ **/
/**  |temp_lsb  |0xFB|              temp_lsb<7:0>            |  0x00  |ֻ��| **/
/**  +----------+----+----+----+----+----+----+----+----+----+--------+----+ **/
/**  |temp_msb  |0xFA|              temp_msb<7:0>            |  0x80  |ֻ��| **/
/**  +----------+----+----+----+----+----+----+----+----+----+--------+----+ **/
/**  |press_xlsb|0xF9|   press_xlsb<7:4> | 0  | 0  | 0  | 0  |  0x00  |ֻ��| **/
/**  +----------+----+----+----+----+----+----+----+----+----+--------+----+ **/
/**  |press_lsb |0xF8|             press_lsb<7:0>            |  0x00  |ֻ��| **/
/**  +----------+----+----+----+----+----+----+----+----+----+--------+----+ **/
/**  |press_msb |0xF7|             press_msb<7:0>            |  0x80  |ֻ��| **/
/**  +----------+----+----+----+----+----+----+----+----+----+--------+----+ **/
/**  |config    |0xF5|   t_sb[2:0]  |  filter[2:0] |    |e[0]|  0x00  |��д| **/
/**  +----------+----+----+----+----+----+----+----+----+----+--------+----+ **/
/**  |ctrl_meas |0xF4|  osrs_t[2:0] |  osrs_p[2:0] |mode[1:0]|  0x00  |��д| **/
/**  +----------+----+----+----+----+----+----+----+----+----+--------+----+ **/
/**  | status   |0xF3|                   |m[0]|         |u[0]|  0x00  |ֻ��| **/
/**  +----------+----+----+----+----+----+----+----+----+----+--------+----+ **/
/**  | reset    |0xE0|             reset[7:0]                |  0x00  |ֻд| **/
/**  +----------+----+----+----+----+----+----+----+----+----+--------+----+ **/
/**  |   id     |0xD0|             chip_id[7:]               |  0x58  |ֻ��| **/
/**  +----------+----+----+----+----+----+----+----+----+----+--------+----+ **/
/**  |calib25   |0xA1|        calibration data[��26]         |�����趨|ֻ��| **/
/**  +----------+----+----+----+----+----+----+----+----+----+--------+----+ **/
/**  |calib00   |0x88|        calibration data[��26]         |�����趨|ֻ��| **/
/**  +----------+----+----+----+----+----+----+----+----+----+--------+----+ **/
/**  ���Ʋ����Ĵ���ѹ���������¶Ȳ��������ã�                                **/
/**    +-----------+----+------------+    +-----------+----+-------------+   **/
/**    |osrs_p[2:0]|����|    ����    |    |osrs_t[2:0]|����|     ����    |   **/
/**    +-----------+----+------------+    +-----------+----+-------------+   **/
/**    |   000     |  - |      -     |    |   000     |  - |     -       |   **/
/**    +-----------+----+------------+    +-----------+----+-------------+   **/
/**    |   001     | x1 |16bit/2.62Pa|    |   001     | x1 |16bit/0.0050C|   **/
/**    +-----------+----+------------+    +-----------+----+-------------+   **/
/**    |   010     | x2 |17bit/1.31Pa|    |   010     | x2 |17bit/0.0025C|   **/
/**    +-----------+----+------------+    +-----------+----+-------------+   **/
/**    |   011     | x4 |18bit/0.66Pa|    |   011     | x4 |18bit/0.0012C|   **/
/**    +-----------+----+------------+    +-----------+----+-------------+   **/
/**    |   100     | x8 |19bit/0.33Pa|    |   100     | x8 |19bit/0.0006C|   **/
/**    +-----------+----+------------+    +-----------+----+-------------+   **/
/**    |101,110,111| x16|20bit/0.16Pa|    |101,110,111| x16|20bit/0.0003C|   **/
/**    +-----------+----+------------+    +-----------+----+-------------+   **/
/**ʹ��˵����                                                                **/
/**    1������BMP280ObjectType����ʵ�壬�����ú���BMP280Initialization��ʼ�� **/
/**       ����ʵ�塣��ʼ��ʱ����Ҫ�������²�����                             **/
/**       bmpAddress,����I2C�ӿڱ�����豸��ַ��0xEC��0xEE��SPI�ӿ�ʱ����Ҫ  **/
/**       port,ͨѶ�ӿ����ͣ�I2C����SPI                                      **/
/**       t_sb,������ڣ����üĴ������ò���                                  **/
/**       filter,�������˲����ã����üĴ������ò���                          **/
/**       spi3W_en,�Ƿ�����3��SPI���ƣ����üĴ������ò���                    **/
/**       osrs_t,�¶Ȳ����������ã��������ƼĴ������ò���                    **/
/**       osrs_p,ѹ���������ȣ��������ƼĴ������ò���                        **/
/**       mode,��Դģʽ���������ƼĴ������ò���                              **/
/**       Read,�����ݲ���ָ�룬�亯�����ͼ���������                          **/
/**       Write,д���ݲ���ָ�룬�亯�����ͼ���������                         **/
/**       Delayms,��ʱ����ָ�룬�亯�����ͼ���������                         **/
/**       ChipSelect,Ƭѡ����ָ�룬SPI�ӿڱ��衣I2C�ӿڲ���Ҫ������NULL      **/
/**    2��ʵ������void f(struct BMP280Object *bmp,uint8_t regAddress,        **/
/**       uint8_t *rData,uint16_t rSize)�ĺ����������丳ֵ��BMP280ObjectType **/
/**       ����ʵ���Read����ָ�롣                                           **/
/**    3��ʵ������void f(struct BMP280Object *bmp,uint8_t regAddress,        **/
/**       uint8_t command)�ĺ����������丳ֵ��BMP280ObjectType����ʵ��       **/
/**       ��Write����ָ�롣                                                  **/
/**    4��ʵ������void f(volatile uint32_t nTime)�ĺ����������丳ֵ��        **/
/**       BMP280ObjectType����ʵ���Delayms����ָ�롣ʵ�ֺ�����ʱ��          **/
/**    5��ʵ������void f(bool en)�ĺ����������丳ֵBMP280ObjectType����ʵ��  **/
/**       ��ChipSelcet����ָ�롣                                             **/
/**    6��������Ӧ�ĺ���ʵ����Ҫ�Ĳ�����                                     **/
/**--------------------------------------------------------------------------**/
/** �޸ļ�¼��                                                               **/
/**     �汾      ����              ����              ˵��                   **/
/**     V1.0.0  2017-07-17          ľ��              �����ļ�               **/
/**     V1.0.1  2018-05-20          ľ��              ���豸����Ϊ�ṹ����   **/
/**     V1.1.0  2019-05-30          ľ��              �޸Ĳ��������Ͷ���     **/
/**                                                                          **/
/******************************************************************************/ 

#include "stddef.h"
#include "bmp280function.h"

/*�Ĵ�����ַ����*/
#define REG_TEMP_XLSB	0xFC	/*�¶�ֵ�Ĵ�������ֽ�*/
#define REG_TEMP_LSB	0xFB	/*�¶�ֵ�Ĵ������ֽ�*/
#define REG_TEMP_MSB	0xFA	/*�¶�ֵ�Ĵ������ֽ�*/
#define REG_PRESS_XLSB	0xF9	/*ѹ��ֵ�Ĵ�������ֽ�*/
#define REG_PRESS_LSB	0xF8	/*ѹ��ֵ�Ĵ������ֽ�*/
#define REG_PRESS_MSB	0xF7	/*ѹ��ֵ�Ĵ������ֽ�*/
#define REG_CONFIG	0xF5	/*���üĴ���*/
#define REG_CTRL_MEAS	0xF4	/*�������ƼĴ���*/
#define REG_STATUS	0xF3	/*״̬�Ĵ���*/
#define REG_RESET	0xE0	/*��λ�Ĵ���*/
#define REG_BMP280_ID   0xD0	/*�豸ID�Ĵ���*/

/*����У׼���ݼĴ�����ַ*/
#define REG_DIG_T1 0x88         /*�¶�У׼ϵ��1���޷���16λ����*/
#define REG_DIG_T2 0x8A         /*�¶�У׼ϵ��2���з���16λ����*/
#define REG_DIG_T3 0x8C         /*�¶�У׼ϵ��3���з���16λ����*/
#define REG_DIG_P1 0x8E         /*ѹ��У׼ϵ��1���޷���16λ����*/
#define REG_DIG_P2 0x90         /*ѹ��У׼ϵ��2���з���16λ����*/
#define REG_DIG_P3 0x92         /*ѹ��У׼ϵ��3���з���16λ����*/
#define REG_DIG_P4 0x94         /*ѹ��У׼ϵ��4���з���16λ����*/
#define REG_DIG_P5 0x95         /*ѹ��У׼ϵ��5���з���16λ����*/
#define REG_DIG_P6 0x98         /*ѹ��У׼ϵ��6���з���16λ����*/
#define REG_DIG_P7 0x9A         /*ѹ��У׼ϵ��7���з���16λ����*/
#define REG_DIG_P8 0x9C         /*ѹ��У׼ϵ��8���з���16λ����*/
#define REG_DIG_P9 0x9E         /*ѹ��У׼ϵ��9���з���16λ����*/

/*�ж϶����Ƿ���Ч*/
static bool ObjectIsValid(BMP280ObjectType *bmp);
/*����ʵ���¶�ֵ,����0.01GegC*/
static double CompensateTemperature(BMP280ObjectType *bmp,uint32_t adcCode);
/*����ʵ�ʵ�ѹ��ֵ��������ΪQ24.8��ʽ*/
static double CompensatePressure(BMP280ObjectType *bmp,uint32_t adcCode);
/*��ȡУ׼����*/
static void GetBMP280CalibrationData(BMP280ObjectType *bmp);
/*��ȡBMP280�Ĵ���*/
static uint8_t ReadBMP280Register(BMP280ObjectType *bmp,uint8_t regAddress);
/* ��BMP280�Ĵ���дһ���ֽ� */
static void WriteBMP280Register(BMP280ObjectType *bmp,uint8_t regAddress,uint8_t command);
/*BMP280�����λ*/
static void BMP280SoftReset(BMP280ObjectType *bmp);

/* ��ȡѹ�����¶����� */
void GetBMP280Measure(BMP280ObjectType *bmp)
{
  uint8_t regAddress[]={REG_TEMP_XLSB,REG_TEMP_LSB,REG_TEMP_MSB,
                        REG_PRESS_XLSB,REG_PRESS_LSB,REG_PRESS_MSB};
  uint8_t mData[6];
  uint32_t adcTemp=0;
  uint32_t adcPres=0;
  
  if(!ObjectIsValid(bmp))
  {
    return;
  }
  
  /*��ȡ״̬���ADת���Ƿ����*/
  uint8_t status=0xFF;
  status=ReadBMP280Register(bmp,REG_STATUS);
  while(status&0x08)
  {
    status=ReadBMP280Register(bmp,REG_STATUS);
  }
  
  /*��ȡ�Ĵ���ֵ*/
  for(int i=0;i<6;i++)
  {
    mData[i]=ReadBMP280Register(bmp,regAddress[i]);
  }

  /*����ѹ�����¶ȵ�ADCֵ*/
  for(int i=0;i<3;i++)
  {
    adcTemp=(adcTemp<<8)+mData[2-i];
    adcPres=(adcPres<<8)+mData[5-i];
  }
  
  adcTemp=(adcTemp>>4);
  adcPres=(adcPres>>4);
  
  /*����ѹ�����¶ȵ�������ֵ*/
  bmp->temperature=CompensateTemperature(bmp,adcTemp);
  
  bmp->pressure=CompensatePressure(bmp,adcPres);
}

/* ʵ��BMP280��ʼ������ */
void BMP280Initialization(BMP280ObjectType *bmp,                //BMP280����
                          uint8_t bmpAddress,                   //I2C�ӿ����豸��ַ
                          BMP280PortType port,                  //�ӿ�ѡ��
                          BMP280TimeStandbyType t_sb,           //�������
                          BMP280IIRFilterCoeffType filter,      //������
                          BMP280UseSPI3wType spi3W_en,          //3��SPI����
                          BMP280TemperatureSampleType osrs_t,   //�¶Ⱦ���
                          BMP280PressureSampleType osrs_p,      //ѹ������
                          BMP280PowerModeType mode,             //��Դģʽ
                          BMP280Read Read,                      //�����ݲ���ָ��
                          BMP280Write Write,                    //д���ݲ���ָ��
                          BMP280Delayms Delayms,                //��ʱ����ָ��
                          BMP280ChipSelect ChipSelect           //Ƭѡ����ָ��
                         )
{
  uint8_t try_count = 5;
  uint8_t regAddress=0;
  uint8_t command=0; 
  
  if((bmp==NULL)||(Read==NULL)||(Write==NULL)||(Delayms==NULL))
  {
    return;
  }
  bmp->Read=Read;
  bmp->Write=Write;
  bmp->Delayms=Delayms;
  
  bmp->chipID=0x00;
  bmp->pressure=0.0;
  bmp->temperature=0.0;
  bmp->bmpAddress=0x00;
  bmp->port=port;
  if(bmp->port==BMP280_I2C)
  {
    if((bmpAddress==0xEC)||(bmpAddress==0xEE))
    {
      bmp->bmpAddress=bmpAddress;
    }
    bmp->ChipSelect=NULL;
  }
  else
  {
    if(ChipSelect!=NULL)
    {
      bmp->ChipSelect=ChipSelect;
    }
    else
    {
      
    }
  }
  
  bmp->caliPara.t_fine=0;
	
  if(!ObjectIsValid(bmp))
  {
    return;
  }
  
  while(try_count--)
  {
    bmp->chipID=ReadBMP280Register(bmp,REG_BMP280_ID);
    if(0x58==bmp->chipID)
    {
      BMP280SoftReset(bmp);
      
      break;
    }
  }
  
  if(try_count)
  {
    /*�������üĴ���:�������0.5ms��IIR�˲�ϵ��16����ʹ��SPI3��ͨѶ*/
    regAddress=REG_CONFIG;
    command=(uint8_t)t_sb|(uint8_t)filter|(uint8_t)spi3W_en;
    WriteBMP280Register(bmp,regAddress,command);
  
    /*���ò������ƼĴ���:�¶�20λ��ѹ��20λ����Դ����ģʽ*/
    regAddress=REG_CTRL_MEAS;
    command=(uint8_t)osrs_t|(uint8_t)osrs_p|(uint8_t)mode;
    WriteBMP280Register(bmp,regAddress,command);
  
    bmp->Delayms(10);
    bmp->config=ReadBMP280Register(bmp,REG_CONFIG);
    bmp->Delayms(10);
    bmp->ctrlMeas=ReadBMP280Register(bmp,REG_CTRL_MEAS);
    bmp->Delayms(10);
    /*��ȡУ׼ֵ*/
    GetBMP280CalibrationData(bmp);
  }
}

/*��ȡУ׼����*/
static void GetBMP280CalibrationData(BMP280ObjectType *bmp)
{
  uint8_t pData[2];
  
  if(!ObjectIsValid(bmp))
  {
    return;
  }
  
  if(bmp->port==BMP280_SPI)
  {
    bmp->ChipSelect(BMP280CS_Enable);
    bmp->Delayms(1);
  }
	
  bmp->Read(bmp,REG_DIG_T1,pData,2);
  bmp->caliPara.dig_t1=(uint16_t)(((uint16_t)pData[1]<<8)+((uint16_t)pData[0]));
  
  bmp->Read(bmp,REG_DIG_T2,pData,2);
  bmp->caliPara.dig_t2=(int16_t)(((int16_t)pData[1]<<8)+((int16_t)pData[0]));
  
  bmp->Read(bmp,REG_DIG_T3,pData,2);
  bmp->caliPara.dig_t3=(int16_t)(((int16_t)pData[1]<<8)+((int16_t)pData[0]));
  
  bmp->Read(bmp,REG_DIG_P1,pData,2);
  bmp->caliPara.dig_p1=(uint16_t)(((uint16_t)pData[1]<<8)+((uint16_t)pData[0]));
  
  bmp->Read(bmp,REG_DIG_P2,pData,2);
  bmp->caliPara.dig_p2=(int16_t)(((int16_t)pData[1]<<8)+((int16_t)pData[0]));
  
  bmp->Read(bmp,REG_DIG_P3,pData,2);
  bmp->caliPara.dig_p3=(int16_t)(((int16_t)pData[1]<<8)+((int16_t)pData[0]));
  
  bmp->Read(bmp,REG_DIG_P4,pData,2);
  bmp->caliPara.dig_p4=(int16_t)(((int16_t)pData[1]<<8)+((int16_t)pData[0]));
  
  bmp->Read(bmp,REG_DIG_P5,pData,2);
  bmp->caliPara.dig_p5=(int16_t)(((int16_t)pData[1]<<8)+((int16_t)pData[0]));
  
  bmp->Read(bmp,REG_DIG_P6,pData,2);
  bmp->caliPara.dig_p6=(int16_t)(((int16_t)pData[1]<<8)+((int16_t)pData[0]));
  
  bmp->Read(bmp,REG_DIG_P7,pData,2);
  bmp->caliPara.dig_p7=(int16_t)(((int16_t)pData[1]<<8)+((int16_t)pData[0]));
  
  bmp->Read(bmp,REG_DIG_P8,pData,2);
  bmp->caliPara.dig_p8=(int16_t)(((int16_t)pData[1]<<8)+((int16_t)pData[0]));
  
  bmp->Read(bmp,REG_DIG_P9,pData,2);
  bmp->caliPara.dig_p9=(int16_t)(((int16_t)pData[1]<<8)+((int16_t)pData[0]));

  if(bmp->port==BMP280_SPI)
  {
    bmp->Delayms(1);
    bmp->ChipSelect(BMP280CS_Disable);
  }
}

/*��BMP280�Ĵ�����ȡһ���ֽ�*/
static uint8_t ReadBMP280Register(BMP280ObjectType *bmp,uint8_t regAddress)
{
  uint8_t regValue=0xFF;
  
  if(ObjectIsValid(bmp))
  {
    if(bmp->port==BMP280_SPI)
    {
      regAddress |= 0x80;
      bmp->ChipSelect(BMP280CS_Enable);
      bmp->Delayms(1);
      bmp->Read(bmp,regAddress,&regValue,1);
      bmp->Delayms(1);
      bmp->ChipSelect(BMP280CS_Disable);
    }
    else
    {
      bmp->Read(bmp,regAddress,&regValue,1);
    }
  }

  return regValue;
}

/* ��BMP280�Ĵ���дһ���ֽ� */
static void WriteBMP280Register(BMP280ObjectType *bmp,uint8_t regAddress,uint8_t command)
{
  if(ObjectIsValid(bmp))
  {
    if(bmp->port==BMP280_SPI)
    {
      regAddress&=0x7F;
      bmp->ChipSelect(BMP280CS_Enable);
      bmp->Delayms(1);
      bmp->Write(bmp,regAddress,command);
      bmp->Delayms(1);
      bmp->ChipSelect(BMP280CS_Disable);
    }
    else
    {
      bmp->Write(bmp,regAddress,command);
    }
  }
}

/*BMP280�����λ*/
static void BMP280SoftReset(BMP280ObjectType *bmp)
{
  uint8_t command=0xB6;
  
  if(ObjectIsValid(bmp))
  {
    WriteBMP280Register(bmp,REG_RESET,command);
  }
}

/*����ʵ�ʵ�ѹ��ֵ��������ΪQ24.8��ʽ*/
static double CompensatePressure(BMP280ObjectType *bmp,uint32_t adcCode)
{
  double var1,var2,pres;
  
  pres=0.0;
  
  var1=((double)bmp->caliPara.t_fine/2.0)-64000.0;
  var2=var1*var1*((double)bmp->caliPara.dig_p6)/32768.0;
  var2=var2+var1*((double)bmp->caliPara.dig_p5)*2.0;
  var2=(var2/4.0)+(((double)bmp->caliPara.dig_p4)*65536.0);
  var1=(((double)bmp->caliPara.dig_p3)*var1*var1/524288.0+((double)bmp->caliPara.dig_p2)*var1)/524288.0;
  var1=(1.0+var1/32768.0)*((double)bmp->caliPara.dig_p1);
  pres=1048576.0-(double)adcCode;

  if(var1 != 0)
  {
    pres=(pres-(var2/4096.0))*6250/var1;
    var1=((double)bmp->caliPara.dig_p9)*pres*pres/2147483648.0;
    var2=pres*((double)bmp->caliPara.dig_p8)/32768.0;
    pres=pres+(var1+var2+((double)bmp->caliPara.dig_p7))/16.0;
  }
  return pres;
}

/*����ʵ���¶�ֵ,����0.01GegC*/
static double CompensateTemperature(BMP280ObjectType *bmp,uint32_t adcCode)
{
  double var1,var2;
  double temp;
 
  var1=(((double)adcCode)/16384.0-((double)bmp->caliPara.dig_t1)/1024.0)*((double)bmp->caliPara.dig_t2);
  var2=((((double)adcCode)/131072.0-((double)bmp->caliPara.dig_t1)/8192.0)
       *(((double)adcCode)/131072.0-((double)bmp->caliPara.dig_t1)/8192.0))
       *((double)bmp->caliPara.dig_t3);
  bmp->caliPara.t_fine=(int32_t)((var1+var2));
  temp=(double)((var1+var2)/5120.0);
  
  return temp;
}

/*�ж϶����Ƿ���Ч*/
static bool ObjectIsValid(BMP280ObjectType *bmp)
{
  bool valid=true;
  
  if((bmp==NULL)||(bmp->Delayms==NULL)||(bmp->Read==NULL)||(bmp->Write==NULL))
  {
    valid=false;
  }
  
  if((bmp->port==BMP280_SPI)&&(bmp->ChipSelect==NULL))
  {
    valid=false;
  }
	
  return valid;
}

/*********** (C) COPYRIGHT 1999-2019 Moonan Technology *********END OF FILE****/
