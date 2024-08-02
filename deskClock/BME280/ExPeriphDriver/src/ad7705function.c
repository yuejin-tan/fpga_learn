/******************************************************************************/
/** ģ�����ƣ���չ��������                                                   **/
/** �ļ����ƣ�ad7705function.c                                               **/
/** ��    ����V1.1.0                                                         **/
/** ��    �飺�����Ͷ���ad7705ģ��ת��оƬ��صĸ��ֺ����Ͳ���               **/
/**         AD7705ӵ��8��Ƭ�ϼĴ���������ͨѶ�����á�ʱ�ӵȼĴ����ṹ���£�  **/
/**         +------+----+----+----+------+------+----+---+-----+             **/
/**         |�Ĵ���| DB7| DB6| DB5| DB4  |  DB3 | DB2|DB1| DB0 |             **/
/**         +------+----+----+----+------+------+----+---+-----+             **/
/**         | ͨѶ |DRDY| RS2| RS1|  RS0 |  R/W |STBY|CH1| CH0 |             **/
/**         +------+----+----+----+------+------+----+---+-----+             **/
/**         | ���� | MD1| MD0| G2 |  G1  |  G0  | B/U|BUF|FSYNC|             **/
/**         +------+----+----+----+------+------+----+---+-----+             **/
/**         | ʱ�� |ZERO|ZERO|ZERO|CLKDIS|CLKDIV| CLK|FS1| FS0 |             **/
/**         +------+----+----+----+------+------+----+---+-----+             **/
/**--------------------------------------------------------------------------**/
/** �޸ļ�¼��                                                               **/
/**     �汾      ����              ����              ˵��                   **/
/**     V1.0.0  2015-07-28          ľ��              �����ļ�               **/
/**     V1.1.0  2019-08-28          ľ��              ��Ϊ���ڶ���Ĳ���     **/
/**                                                                          **/
/******************************************************************************/ 

#include "stddef.h"
#include "ad7705function.h"

/* ͨѶ�Ĵ��������ú궨�� */
#define CommunicationRegister   (0x00<<4)
#define SetupRegister           (0x01<<4)
#define ClockRegister           (0x02<<4)
#define DataRegister            (0x03<<4)
#define TestRegister            (0x04<<4)
#define NoOperation             (0x05<<4)
#define OffsetRegister          (0x06<<4)
#define GainRegister            (0x07<<4)

#define WriteOperation          (0x00<<3)
#define ReadOperation           (0x01<<3)

#define OperatingMode           (0x00<<2)
#define StandbyMode             (0x01<<2)

#define AIN1P_AIN1N     0x00
#define AIN2P_AIN2N     0x01
#define AIN1N_AIN1N     0x02
#define AIN1N_AIN2N     0x03

/* ���üĴ��������ú궨�� */
#define NormalMode              (0x00<<6)
#define SelfCalibration         (0x01<<6)
#define ZeroSystemCalibration   (0x02<<6)
#define FullSystemCalibration   (0x03<<6)

#define GAIN1           (0x00<<3)
#define GAIN2           (0x01<<3)
#define GAIN4           (0x02<<3)
#define GAIN8           (0x03<<3)
#define GAIN16          (0x04<<3)
#define GAIN32          (0x05<<3)
#define GAIN64          (0x06<<3)
#define GAIN128         (0x07<<3)

#define Bipolar         (0x00<<2)
#define Unipolar        (0x01<<2)

#define BufferDisable   (0x00<<1)
#define BufferEnable    (0x01<<1)

#define FSYNCEnable     0x00
#define FSYNCDisable    0x01

/* ʱ�ӼĴ��������ú궨�� */
#define CLKEnable       (0x00<<4)
#define CLKDisable      (0x01<<4)

#define CLKDIVDisable   (0x00<<3)
#define CLKDIVEnable    (0x01<<3)

#define UpdateRate20Hz  0x00	//ʱ��Ϊ2.4576 MHz
#define UpdateRate25Hz  0x01	//ʱ��Ϊ2.4576 MHz
#define UpdateRate100Hz 0x02	//ʱ��Ϊ2.4576 MHz
#define UpdateRate200Hz 0x03	//ʱ��Ϊ2.4576 MHz
#define UpdateRate50Hz  0x04	//ʱ��Ϊ1 MHz
#define UpdateRate60Hz  0x05	//ʱ��Ϊ1 MHz
#define UpdateRate250Hz 0x06	//ʱ��Ϊ1 MHz
#define UpdateRate500Hz 0x07	//ʱ��Ϊ1 MHz

//uint8_t regCode[8]={CommunicationRegister,
//										SetupRegister,
//										ClockRegister,
//										DataRegister,
//										TestRegister,
//										NoOperation,
//										OffsetRegister,
//										GainRegister};

uint8_t channels[4]={AIN1P_AIN1N,AIN2P_AIN2N,AIN1N_AIN1N,AIN1N_AIN2N};

//uint8_t workMode[4]={NormalMode,SelfCalibration,ZeroSystemCalibration,FullSystemCalibration};

uint8_t gains[8]={GAIN1,GAIN2,GAIN4,GAIN8,GAIN16,GAIN32,GAIN64,GAIN128};

uint8_t updateRate[8]={UpdateRate20Hz,
                       UpdateRate25Hz,
                       UpdateRate100Hz,
                       UpdateRate200Hz,
                       UpdateRate50Hz,
                       UpdateRate60Hz,
                       UpdateRate250Hz,
                       UpdateRate500Hz};

/*AD7705ͨ����ʼ��*/
static void AD7705ChannelConfig(AD7705ObjectType *ad,AD7705ChannelType channel);
/* Ĭ��Ƭѡ�������� */
static void DefaultChipSelect(AD7705CSType en);

//��ȡAD7705��ͨ����ֵ
uint16_t GetAD7705ChannelValue(AD7705ObjectType *ad,AD7705ChannelType channel)
{
	ad->ChipSelect(AD7705CS_Enable);
	
  //��ʼ��ͨ��
  AD7705ChannelConfig(ad,channel);
  ad->Delayms(20);
  
//  //ѡ��CH1���ݼĴ����� 
//  if(channel==Channel1)
//  {
//    ad->ReadWriteByte(0x38);
//  }

//  //ѡ��CH2���ݼĴ�����
//  if(channel==Channel2)
//  {
//    ad->ReadWriteByte(0x39); 
//  }
	
  ad->registers[REG_COMM]=DataRegister|ReadOperation|OperatingMode|channels[channel];
  ad->ReadWriteByte(ad->registers[REG_COMM]);
	
  //�ȴ�����׼���� 
  while(ad->CheckDataIsReady()==1)    
  { 
  }
   
  uint16_t dataLowByte;
  uint16_t dataHighByte;
  dataHighByte = ad->ReadWriteByte(0xFF); 	//�����ݼĴ���
  ad->Delayus(200);
  dataLowByte = ad->ReadWriteByte(0xFF);  	//�����ݼĴ��� 
  ad->Delayus(200); 
  
  dataHighByte = dataHighByte << 8;
  uint16_t value;
  value  =  dataHighByte | dataLowByte;  
  
  ad->ChipSelect(AD7705CS_Disable);
	
  return value;
}

/*AD7705ͨ����ʼ��*/
static void AD7705ChannelConfig(AD7705ObjectType *ad,AD7705ChannelType channel)
{
  for(uint8_t i = 0; i < 100; i++)
  { 
    ad->ReadWriteByte(0xFF);      //����DIN�ߵ�ƽд�������ָ�AD7705�ӿ�
  }
//  if(channel==Channel1)
//  {
//    ad->ReadWriteByte(0x20);        //дͨѶ�Ĵ���ѡ��chnanel 1 
//    ad->ReadWriteByte(0x03);        //0x03 2.4576MHzʱ�Ӫ�200Hz���ݸ�������  
//    ad->ReadWriteByte(0x10);        //ѡ�����üĴ�����ʹ��chnanel 1
//    ad->ReadWriteByte(0x44);        //д���üĴ��������óɵ����ԡ��޻��塢����Ϊ1���˲�����������У׼ 
//  }
//  if(channel==Channel2)
//  {
//    ad->ReadWriteByte(0x21);        //дͨѶ�Ĵ���ѡ��channel2
//    ad->ReadWriteByte(0x03);        //0x03  2.4576MHzʱ�Ӫ�200Hz���ݸ�������  
//    ad->ReadWriteByte(0x11);        //ѡ�����üĴ�����ʹ��chnanel2
//    ad->ReadWriteByte(0x44);        //д���üĴ��������óɵ����ԡ��޻��塢����Ϊ1���˲�����������У׼ 
//  }
	
  ad->registers[REG_COMM]=ClockRegister|WriteOperation|OperatingMode|channels[channel];
  ad->ReadWriteByte(ad->registers[REG_COMM]);
  ad->ReadWriteByte(ad->registers[REG_CLOCK]);
  ad->registers[REG_COMM]=SetupRegister|WriteOperation|OperatingMode|channels[channel];
  ad->ReadWriteByte(ad->registers[REG_COMM]);
  ad->ReadWriteByte(ad->registers[REG_SETUP]);
}

/* AD7705�����ʼ������ */
void AD7705Initialization(AD7705ObjectType *ad,
                          AD7705GainType gain,
                          AD7705MclkType mclk,
                          AD7705OutRateType rate,
                          AD7705ReadWriteByteType spiReadWrite,
                          AD7705CheckDataIsReadyType checkReady,
                          AD7705ChipSelect cs,
                          AD7705Delay msDelay,
                          AD7705Delay usDelay)
{
  if((ad==NULL)||(spiReadWrite==NULL)||(checkReady==NULL)||(msDelay==NULL)||(usDelay==NULL))
  {
    return;
  }
	
  ad->CheckDataIsReady=checkReady;
  ad->ReadWriteByte=spiReadWrite;
  ad->Delayms=msDelay;
  ad->Delayus=usDelay;
	
  if(cs==NULL)	//Ӳ����·ʵ��Ƭѡ
  {
    ad->ChipSelect=DefaultChipSelect;
  }
  else
  {
  ad->ChipSelect=cs;
  }
	
  //���óɵ����ԡ��޻��塢����Ϊ1���˲�����������У׼
  ad->registers[REG_SETUP]=SelfCalibration|Unipolar|BufferDisable|FSYNCEnable|gains[gain];
  
  ad->registers[REG_CLOCK]=CLKEnable; //Ĭ����ʱ�����
  
  if((mclk==Mclk4915200)||(mclk==Mclk2000000))
  {
    ad->registers[REG_CLOCK]|=CLKDIVEnable;
  }
  else
  {
  ad->registers[REG_CLOCK]|=CLKDIVDisable;
  }
	
  if(((mclk<=Mclk4915200)&&(rate<=Rate200Hz))||((mclk>=Mclk1000000)&&(rate>=Rate50Hz)))
  {
    ad->registers[REG_CLOCK]|=updateRate[rate];
  }
  else
  {
    ad->registers[REG_CLOCK]=0x00;
    return;
  }	
}

/* Ĭ��Ƭѡ�������� */
static void DefaultChipSelect(AD7705CSType en)
{
  return;
}

/*********** (C) COPYRIGHT 1999-2019 Moonan Technology *********END OF FILE****/
