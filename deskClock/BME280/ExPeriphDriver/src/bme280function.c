/******************************************************************************/
/** ģ�����ƣ���չ��������                                                   **/
/** �ļ����ƣ�bme280function.c                                               **/
/** ��    ����V1.1.0                                                         **/
/** ��    �飺����ʵ��BME280ѹ�����¶ȼ�ʪ�ȴ������Ĳ���                     **/
/**           BME280��55���ɲ����Ĵ���������26��У׼���ݣ���ַ���£�         **/
/**  +----------+----+----+----+----+----+----+----+----+----+--------+----+ **/
/**  |�Ĵ�����  |��ַ|bit7|bit6|bit5|bit4|bit3|bit2|bit1|bit0|��λ״̬|��д| **/
/**  +----------+----+----+----+----+----+----+----+----+----+--------+----+ **/
/**  |hum_lsb   |0xFE|               hum_lsb<7:0>            |  0x00  |ֻ��| **/
/**  +----------+----+----+----+----+----+----+----+----+----+--------+----+ **/
/**  |hum_msb   |0xFD|               hum_msb<7:0>            |  0x80  |ֻ��| **/
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
/**  |ctrl_hum  |0xF2|                        |  osrs_h[2:0] |  0x00  |��д| **/
/**  +----------+----+----+----+----+----+----+----+----+----+--------+----+ **/
/**  |calib41   |0xF0|        calibration data[��41]         |�����趨|ֻ��| **/
/**  +----------+----+----+----+----+----+----+----+----+----+--------+----+ **/
/**  |calib26   |0xE1|        calibration data[��41]         |�����趨|ֻ��| **/
/**  +----------+----+----+----+----+----+----+----+----+----+--------+----+ **/
/**  | reset    |0xE0|             reset[7:0]                |  0x00  |ֻд| **/
/**  +----------+----+----+----+----+----+----+----+----+----+--------+----+ **/
/**  |   id     |0xD0|             chip_id[7:0]              |  0x60  |ֻ��| **/
/**  +----------+----+----+----+----+----+----+----+----+----+--------+----+ **/
/**  |calib25   |0xA1|        calibration data[��41]         |�����趨|ֻ��| **/
/**  +----------+----+----+----+----+----+----+----+----+----+--------+----+ **/
/**  |calib00   |0x88|        calibration data[��41]         |�����趨|ֻ��| **/
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
/**--------------------------------------------------------------------------**/
/**ʹ��˵����                                                                **/
/**    1������BME280ObjectType����ʵ�壬�����ú���BME280Initialization��ʼ�� **/
/**       ����ʵ�塣��ʼ��ʱ����Ҫ�������²�����                             **/
/**       bmpAddress,����I2C�ӿڱ�����豸��ַ��0xEC��0xEE��SPI�ӿ�ʱ����Ҫ  **/
/**       port,ͨѶ�ӿ����ͣ�I2C����SPI                                      **/
/**       t_sb,������ڣ����üĴ������ò���                                  **/
/**       filter,�������˲����ã����üĴ������ò���                          **/
/**       spi3W_en,�Ƿ�����3��SPI���ƣ����üĴ������ò���                    **/
/**       osrs_t,�¶Ȳ����������ã��������ƼĴ������ò���                    **/
/**       osrs_p,ѹ���������ȣ��������ƼĴ������ò���                        **/
/**       mode,��Դģʽ���������ƼĴ������ò���                              **/
/**       osrs_h,ʪ�Ȳ����������ã�ʪ�Ȳ������ƼĴ������ò���                **/
/**       Read,�����ݲ���ָ�룬�亯�����ͼ���������                          **/
/**       Write,д���ݲ���ָ�룬�亯�����ͼ���������                         **/
/**       Delayms,��ʱ����ָ�룬�亯�����ͼ���������                         **/
/**       ChipSelect,Ƭѡ����ָ�룬SPI�ӿڱ��衣I2C�ӿڲ���Ҫ������NULL      **/
/**    2��ʵ������void f(struct BME280Object *bmp,uint8_t regAddress,        **/
/**       uint8_t *rData,uint16_t rSize)�ĺ����������丳ֵ��BME280ObjectType **/
/**       ����ʵ���Read����ָ�롣                                           **/
/**    3��ʵ������void f(struct BME280Object *bmp,uint8_t regAddress,        **/
/**       uint8_t command)�ĺ����������丳ֵ��BME280ObjectType����ʵ��       **/
/**       ��Write����ָ�롣                                                  **/
/**    4��ʵ������void f(volatile uint32_t nTime)�ĺ����������丳ֵ��        **/
/**       BME280ObjectType����ʵ���Delayms����ָ�롣ʵ�ֺ�����ʱ��          **/
/**    5��ʵ������void f(bool en)�ĺ����������丳ֵBME280ObjectType����ʵ��  **/
/**       ��ChipSelcet����ָ�롣                                             **/
/**    6������GetBME280Measure����ʵ�����ݵĶ�ȡ��                           **/
/**--------------------------------------------------------------------------**/
/** �޸ļ�¼��                                                               **/
/**     �汾      ����              ����              ˵��                   **/
/**     V1.0.0  2017-07-17          ľ��              �����ļ�               **/
/**     V1.0.1  2018-05-20          ľ��              ���豸����Ϊ�ṹ����   **/
/**     V1.1.0  2018-06-01          ľ��              �޸����Ͷ��弰���ݷ��� **/
/**                                                                          **/
/******************************************************************************/ 

#include "stddef.h"
#include "bme280function.h"

/*�Ĵ�����ַ����*/
#define REG_HUMI_LSB	0xFE	/*ʪ��ֵ�Ĵ������ֽ�*/
#define REG_HUMI_MSB	0xFD	/*ʪ��ֵ�Ĵ������ֽ�*/
#define REG_TEMP_XLSB	0xFC	/*�¶�ֵ�Ĵ�������ֽ�*/
#define REG_TEMP_LSB	0xFB	/*�¶�ֵ�Ĵ������ֽ�*/
#define REG_TEMP_MSB	0xFA	/*�¶�ֵ�Ĵ������ֽ�*/
#define REG_PRESS_XLSB	0xF9	/*ѹ��ֵ�Ĵ�������ֽ�*/
#define REG_PRESS_LSB	0xF8	/*ѹ��ֵ�Ĵ������ֽ�*/
#define REG_PRESS_MSB	0xF7	/*ѹ��ֵ�Ĵ������ֽ�*/
#define REG_CONFIG	0xF5	/*���üĴ���*/
#define REG_CTRL_MEAS	0xF4	/*�������ƼĴ���*/
#define REG_STATUS	0xF3	/*״̬�Ĵ���*/
#define REG_CTRL_HUM	0xF2	/*ʪ�Ȳ������ƼĴ���*/
#define REG_RESET	0xE0	/*��λ�Ĵ���*/
#define REG_BME280_ID   0xD0	/*�豸ID�Ĵ���*/

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
#define REG_DIG_H1 0xA1         /*ʪ��У׼ϵ��1���޷���8λ����*/
#define REG_DIG_H2 0xE1         /*ʪ��У׼ϵ��2���з���16λ����*/
#define REG_DIG_H3 0xE3         /*ʪ��У׼ϵ��3���޷���8λ����*/
#define REG_DIG_H4 0xE4         /*ʪ��У׼ϵ��4���з���16λ����*/
#define REG_DIG_H5 0xE5         /*ʪ��У׼ϵ��5���з���16λ����*/
#define REG_DIG_H6 0xE7         /*ʪ��У׼ϵ��6���з���8λ����*/

/*�ж϶����Ƿ���Ч*/
static bool ObjectIsValid(BME280ObjectType *bme);
/*����ʵ���¶�ֵ,����0.01GegC*/
static double CompensateTemperature(BME280ObjectType *bme,uint32_t adcCode);
/*����ʵ�ʵ�ѹ��ֵ��������ΪQ24.8��ʽ*/
static double CompensatePressure(BME280ObjectType *bme,uint32_t adcCode);
/*����ʵ�ʵ�ʪ��ֵ��������ΪQ22.10��ʽ*/
static double CompensateHumidity(BME280ObjectType *bme,uint32_t adcCode);
/*��BME280�Ĵ���дһ���ֽ�*/
static void WriteBME280Register(BME280ObjectType *bme,uint8_t regAddress,uint8_t command);
/*��BME280�Ĵ�����ȡһ���ֽ�*/
static uint8_t ReadBME280Register(BME280ObjectType *bme,uint8_t regAddress);
/*BME280�����λ*/
static void BME280SoftReset(BME280ObjectType *bme);
/*��ȡУ׼����*/
static void GetBME280CalibrationData(BME280ObjectType *bme);
/*ȱʡƬѡ������*/
static void BME280ChipSelectDefault(BME280CSType cs);

/*��ȡѹ�����¶�����*/
void GetBME280Measure(BME280ObjectType *bme)
{
  uint8_t regAddress[]={REG_TEMP_XLSB,REG_TEMP_LSB,REG_TEMP_MSB,
                        REG_PRESS_XLSB,REG_PRESS_LSB,REG_PRESS_MSB,
                        REG_HUMI_LSB,REG_HUMI_MSB};
  uint8_t mData[8];
  uint32_t adcTemp=0;
  uint32_t adcPres=0;
  uint32_t adcHumi=0;
  
  if(!ObjectIsValid(bme))
  {
    return;
  }
  
  /*��ȡ״̬���ADת���Ƿ����*/
  uint8_t status=0xFF;
  status=ReadBME280Register(bme,REG_STATUS);
  while(status&0x08)
  {
    status=ReadBME280Register(bme,REG_STATUS);
  }
  
  /*��ȡ�Ĵ���ֵ*/
  for(int i=0;i<8;i++)
  {
    mData[i]=ReadBME280Register(bme,regAddress[i]);
  }

  /*����ѹ�����¶ȵ�ADCֵ*/
  for(int i=0;i<3;i++)
  {
    adcTemp=(adcTemp<<8)+mData[2-i];
    adcPres=(adcPres<<8)+mData[5-i];
  }
  adcHumi=((uint32_t)mData[6]<<8)+(uint32_t)mData[7];
  
  
  adcTemp=(adcTemp>>4);
  adcPres=(adcPres>>4);
  
  /*����ѹ�����¶ȵ�������ֵ*/
  bme->temperature=(float)CompensateTemperature(bme,adcTemp);
  
  bme->pressure=(float)CompensatePressure(bme,adcPres);
  
  bme->humidity=(float)CompensateHumidity(bme,adcHumi);
}


/*ʵ��BME280��ʼ������*/
void BME280Initialization(BME280ObjectType *bme,        //BMP280����
                          uint8_t bmeAddress,           //I2C�ӿ����豸��ַ
                          BME280PortType port,          //�ӿ�ѡ��
                          BME280TimeSBType t_sb,        //�������
                          BME280IIRFilterType filter,   //������
                          BME280SPI3wUseType spi3W_en,  //3��SPI����
                          BME280TempSampleType osrs_t,  //�¶Ⱦ���
                          BME280PresSampleType osrs_p,  //ѹ������
                          BME280PowerModeType mode,     //��Դģʽ
                          BME280HumiSampleType osrs_h,  //ʪ�Ⱦ���
                          BME280Read Read,              //�����ݲ���ָ��
                          BME280Write Write,            //д���ݲ���ָ��
                          BME280Delayms Delayms,        //��ʱ����ָ��
                          BME280ChipSelect ChipSelect   //Ƭѡ����ָ��
                         )
{
  uint8_t try_count = 5;
  uint8_t regAddress=0;
  uint8_t command=0; 
  
  if((bme==NULL)||(Read==NULL)||(Write==NULL)||(Delayms==NULL))
  {
		return;
  }
  bme->Read=Read;
  bme->Write=Write;
  bme->Delayms=Delayms;
  
  bme->chipID=0x00;
  bme->pressure=0.0;
  bme->temperature=0.0;
  bme->humidity=0.0;
  bme->bmeAddress=0x00;
  bme->port=port;
  if(bme->port==BME280_I2C)
  {
    if((bmeAddress==0xEC)||(bmeAddress==0xEE))
    {
      bme->bmeAddress=bmeAddress;
    }
    bme->ChipSelect=NULL;
  }
  else
  {
    if(ChipSelect!=NULL)
    {
      bme->ChipSelect=ChipSelect;
    }
    else
    {
      bme->ChipSelect=BME280ChipSelectDefault;
    }
  }
	
  bme->caliPara.t_fine=0;
		
  if(!ObjectIsValid(bme))
  {
    return;
  }
  	
  while(try_count--)
  {
    bme->chipID=ReadBME280Register(bme,REG_BME280_ID);
    if(0x60==bme->chipID)
    {
      BME280SoftReset(bme);
      
      break;
    }
  }
  
  if(try_count)
  {
    /*�������üĴ���:�������0.5ms��IIR�˲�ϵ��16����ʹ��SPI3��ͨѶ*/
    regAddress=REG_CONFIG;
    command=(uint8_t)t_sb|(uint8_t)filter|(uint8_t)spi3W_en;
    WriteBME280Register(bme,regAddress,command);
  
    /*���ò������ƼĴ���:�¶�20λ��ѹ��20λ����Դ����ģʽ*/
    regAddress=(uint8_t)(REG_CTRL_MEAS);
    command=(uint8_t)osrs_t|(uint8_t)osrs_p|(uint8_t)mode;
    WriteBME280Register(bme,regAddress,command);
  
    /*����ʪ�Ȳ������ƼĴ���*/
    regAddress=REG_CTRL_HUM;
    command=osrs_h;
    WriteBME280Register(bme,regAddress,command);
    
    bme->Delayms(10);
    bme->config=ReadBME280Register(bme,REG_CONFIG);
    bme->Delayms(10);
    bme->ctrlMeas=ReadBME280Register(bme,REG_CTRL_MEAS);
    bme->Delayms(10);
    bme->ctrlHumi=ReadBME280Register(bme,REG_CTRL_HUM);
    bme->Delayms(10);
		
    /*��ȡУ׼ֵ*/
    GetBME280CalibrationData(bme);
  }
}

/*��ȡУ׼����*/
static void GetBME280CalibrationData(BME280ObjectType *bme)
{
  uint8_t pData[2];
  
  if(!ObjectIsValid(bme))
  {
    return;
  }
	
  if(bme->port==BME280_SPI)
  {
    bme->ChipSelect(BME280CS_ENABLE);
    bme->Delayms(1);
  }
	
  bme->Read(bme,REG_DIG_T1,pData,2);
  bme->caliPara.dig_t1=(uint16_t)(((uint16_t)pData[1]<<8)+((uint16_t)pData[0]));
  
  bme->Read(bme,REG_DIG_T2,pData,2);
  bme->caliPara.dig_t2=(int16_t)(((int16_t)pData[1]<<8)+((int16_t)pData[0]));
  
  bme->Read(bme,REG_DIG_T3,pData,2);
  bme->caliPara.dig_t3=(int16_t)(((int16_t)pData[1]<<8)+((int16_t)pData[0]));
  
  bme->Read(bme,REG_DIG_P1,pData,2);
  bme->caliPara.dig_p1=(uint16_t)(((uint16_t)pData[1]<<8)+((uint16_t)pData[0]));
  
  bme->Read(bme,REG_DIG_P2,pData,2);
  bme->caliPara.dig_p2=(int16_t)(((int16_t)pData[1]<<8)+((int16_t)pData[0]));
  
  bme->Read(bme,REG_DIG_P3,pData,2);
  bme->caliPara.dig_p3=(int16_t)(((int16_t)pData[1]<<8)+((int16_t)pData[0]));
  
  bme->Read(bme,REG_DIG_P4,pData,2);
  bme->caliPara.dig_p4=(int16_t)(((int16_t)pData[1]<<8)+((int16_t)pData[0]));
  
  bme->Read(bme,REG_DIG_P5,pData,2);
  bme->caliPara.dig_p5=(int16_t)(((int16_t)pData[1]<<8)+((int16_t)pData[0]));
  
  bme->Read(bme,REG_DIG_P6,pData,2);
  bme->caliPara.dig_p6=(int16_t)(((int16_t)pData[1]<<8)+((int16_t)pData[0]));
  
  bme->Read(bme,REG_DIG_P7,pData,2);
  bme->caliPara.dig_p7=(int16_t)(((int16_t)pData[1]<<8)+((int16_t)pData[0]));
  
  bme->Read(bme,REG_DIG_P8,pData,2);
  bme->caliPara.dig_p8=(int16_t)(((int16_t)pData[1]<<8)+((int16_t)pData[0]));
  
  bme->Read(bme,REG_DIG_P9,pData,2);
  bme->caliPara.dig_p9=(int16_t)(((int16_t)pData[1]<<8)+((int16_t)pData[0]));
  
  bme->Read(bme,REG_DIG_H1,pData,1);
  bme->caliPara.dig_h1=pData[0];
  
  bme->Read(bme,REG_DIG_H2,pData,2);
  bme->caliPara.dig_h2=(int16_t)(((int16_t)pData[1]<<8)+((int16_t)pData[0]));
  
  bme->Read(bme,REG_DIG_H3,pData,1);
  bme->caliPara.dig_h3=pData[0];
  
  bme->Read(bme,REG_DIG_H4,pData,2);
  bme->caliPara.dig_h4=(int16_t)(((int16_t)pData[0]<<4)+(((int16_t)pData[1])&0x0F));
  
  bme->Read(bme,REG_DIG_H5,pData,2);
  bme->caliPara.dig_h5=(int16_t)(((int16_t)pData[1]<<4)+((int16_t)(pData[1]>>4)));
  
  bme->Read(bme,REG_DIG_H6,pData,1);
  bme->caliPara.dig_h6=pData[0];
	
  if(bme->port==BME280_SPI)
  {
    bme->Delayms(1);
    bme->ChipSelect(BME280CS_DISABLE);
  }
}

/*BME280�����λ*/
static void BME280SoftReset(BME280ObjectType *bme)
{
  uint8_t command=0xB6;
  
  if(ObjectIsValid(bme))
  {
    WriteBME280Register(bme,REG_RESET,command);
  }
}

/*��BMP280�Ĵ�����ȡһ���ֽ�*/
static uint8_t ReadBME280Register(BME280ObjectType *bme,uint8_t regAddress)
{
  uint8_t regValue=0xFF;
  
  if(ObjectIsValid(bme))
  {
    if(bme->port==BME280_SPI)
    {
      regAddress |= 0x80;
      bme->ChipSelect(BME280CS_ENABLE);
      bme->Delayms(1);
      bme->Read(bme,regAddress,&regValue,1);
      bme->Delayms(1);
      bme->ChipSelect(BME280CS_DISABLE);
    }
    else
    {
      bme->Read(bme,regAddress,&regValue,1);
    }
  }

  return regValue;
}

/* ��BME280�Ĵ���дһ���ֽ� */
static void WriteBME280Register(BME280ObjectType *bme,uint8_t regAddress,uint8_t command)
{
  if(ObjectIsValid(bme))
  {
    if(bme->port==BME280_SPI)
    {
      regAddress&=0x7F;
      bme->ChipSelect(BME280CS_ENABLE);
      bme->Delayms(1);
      bme->Write(bme,regAddress,command);
      bme->Delayms(1);
      bme->ChipSelect(BME280CS_DISABLE);
    }
    else
    {
      bme->Write(bme,regAddress,command);
    }
  }
}

/*����ʵ�ʵ�ѹ��ֵ��������ΪQ24.8��ʽ*/
static double CompensatePressure(BME280ObjectType *bme,uint32_t adcCode)
{
  double var1;
  double var2;
  double var3;
  double pressure;
  double pressure_min = 30000.0;
  double pressure_max = 110000.0;

  var1 = ((double)bme->caliPara.t_fine / 2.0) - 64000.0;
  var2 = var1 * var1 * ((double)bme->caliPara.dig_p6) / 32768.0;
  var2 = var2 + var1 * ((double)bme->caliPara.dig_p5) * 2.0;
  var2 = (var2 / 4.0) + (((double)bme->caliPara.dig_p4) * 65536.0);
  var3 = ((double)bme->caliPara.dig_p3) * var1 * var1 / 524288.0;
  var1 = (var3 + ((double)bme->caliPara.dig_p2) * var1) / 524288.0;
  var1 = (1.0 + var1 / 32768.0) * ((double)bme->caliPara.dig_p1);
  
  /*��������쳣 */
  if (var1)
  {
    pressure = 1048576.0 - (double)adcCode;
    pressure = (pressure - (var2 / 4096.0)) * 6250.0 / var1;
    var1 = ((double)bme->caliPara.dig_p9) * pressure * pressure / 2147483648.0;
    var2 = pressure * ((double)bme->caliPara.dig_p8) / 32768.0;
    pressure = pressure + (var1 + var2 + ((double)bme->caliPara.dig_p7)) / 16.0;

    if (pressure < pressure_min)
      pressure = pressure_min;
    else if (pressure > pressure_max)
      pressure = pressure_max;
  }
  else
  {
    pressure = pressure_min;
  }

  return pressure;
}

/*����ʵ���¶�ֵ,����0.01GegC*/
static double CompensateTemperature(BME280ObjectType *bme,uint32_t adcCode)
{
  double var1;
  double var2;
  double temperature;
  double temperature_min = -40;
  double temperature_max = 85;

  var1 = ((double)adcCode) / 16384.0 - ((double)bme->caliPara.dig_t1) / 1024.0;
  var1 = var1 * ((double)bme->caliPara.dig_t2);
  var2 = (((double)adcCode) / 131072.0 - ((double)bme->caliPara.dig_t1) / 8192.0);
  var2 = (var2 * var2) * ((double)bme->caliPara.dig_t3);
  bme->caliPara.t_fine = (int32_t)(var1 + var2);
  temperature = (var1 + var2) / 5120.0;

  if (temperature < temperature_min)
    temperature = temperature_min;
  else if (temperature > temperature_max)
    temperature = temperature_max;

  return temperature;
}

/*����ʵ�ʵ�ʪ��ֵ��������ΪQ22.10��ʽ*/
static double CompensateHumidity(BME280ObjectType *bme,uint32_t adcCode)
{
  double humidity;
  double humidity_min = 0.0;
  double humidity_max = 100.0;
  double var1;
  double var2;
  double var3;
  double var4;
  double var5;
  double var6;

  var1 = ((double)bme->caliPara.t_fine) - 76800.0;
  var2 = (((double)bme->caliPara.dig_h4) * 64.0 + (((double)bme->caliPara.dig_h5) / 16384.0) * var1);
  var3 = adcCode - var2;
  var4 = ((double)bme->caliPara.dig_h2) / 65536.0;
  var5 = (1.0 + (((double)bme->caliPara.dig_h3) / 67108864.0) * var1);
  var6 = 1.0 + (((double)bme->caliPara.dig_h6) / 67108864.0) * var1 * var5;
  var6 = var3 * var4 * (var5 * var6);
  humidity = var6 * (1.0 - ((double)bme->caliPara.dig_h1) * var6 / 524288.0);

  if (humidity > humidity_max)
    humidity = humidity_max;
  else if (humidity < humidity_min)
    humidity = humidity_min;

  return humidity;
}

/*�ж϶����Ƿ���Ч*/
static bool ObjectIsValid(BME280ObjectType *bme)
{
  bool valid=true;
  
  if((bme==NULL)||(bme->Delayms==NULL)||(bme->Read==NULL)||(bme->Write==NULL))
  {
    valid=false;
  }
  
  if((bme->port==BME280_SPI)&&(bme->ChipSelect==NULL))
  {
    valid=false;
  }
	
  return valid;
}

/*ȱʡƬѡ������*/
static void BME280ChipSelectDefault(BME280CSType cs)
{
  //������SPIͨѶʱ��Ƭѡ�ź�Ӳ����·ѡ�е����
  return;
}
/*********** (C) COPYRIGHT 1999-2019 Moonan Technology *********END OF FILE****/
