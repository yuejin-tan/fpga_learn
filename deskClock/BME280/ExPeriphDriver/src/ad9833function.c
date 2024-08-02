/******************************************************************************/
/** ģ�����ƣ���չ��������                                                   **/
/** �ļ����ƣ�ad9833function.c                                               **/
/** ��    ����V1.0.0                                                         **/
/** ��    �飺�����Ͷ���AD9833�ɱ�̲��η�������صĸ��ֺ����Ͳ���           **/
/**           AD9833�ɱ�̲��η���������SPIͨѶ�ӿڣ��������ɲ�ͬƵ�ʺͷ�ֵ  **/
/**           �����Ҳ������ǲ��ͷ���������һ��16λ���ƼĴ������£�           **/
/**           ��λ�ֽ����£�                                                 **/
/**           +----+----+----+----+-------+-------+---+-----+                **/
/**           |DB15|DB14|DB13|DB12|  DB11 |  DB10 |DB9| DB8 |                **/
/**           +----+----+----+----+-------+-------+---+-----+                **/
/**           | 0  | 0  | B28| HLB|FSELECT|PSELECT| 0 |RESET|                **/
/**           +----+----+----+----+-------+-------+---+-----+                **/
/**           ��λ�ֽ����£�                                                 **/
/**           +------+-------+-------+---+----+---+----+---+                 **/
/**           |  DB7 |  DB6  |  DB5  |DB4| DB3|DB2| DB1|DB0|                 **/
/**           +------+-------+-------+---+----+---+----+---+                 **/
/**           |SLEEP1|SLEEP12|OPBITEN| 0 |DIV2| 0 |MODE| 0 |                 **/
/**           +------+-------+-------+---+----+---+----+---+                 **/
/**           ����DB12Ҫ��DB13���ʹ�ã�DB3��DB1Ҫ��DB5���ʹ�á�            **/
/**--------------------------------------------------------------------------**/
/**ʹ��˵����                                                                **/
/**    1������AD9833����ʵ�壬�����ú���AD9833Initialization��ʼ������ʵ�塣 **/
/**    ��ʼ��ʱ������ʼ��Ƶ��MCLK����λΪMHz��                               **/
/**    2��ʵ������void f(uint8_t *tData,uint16_t tSize)�ĺ����������丳ֵ    **/
/**    ��AD9833����ʵ���WriteDataToDAC����ָ�롣                            **/
/**    3��ʵ������void f(bool en)�ĺ����������丳ֵAD9833����ʵ���ChipSelcet**/
/**    ����ָ�롣                                                            **/
/**    4��������Ӧ�ĺ���ʵ����Ҫ�Ĳ�����                                     **/
/**--------------------------------------------------------------------------**/
/** �޸ļ�¼��                                                               **/
/**     �汾      ����              ����              ˵��                   **/
/**     V1.0.0  2019-05-16          ľ��              �����ļ�               **/
/**                                                                          **/
/******************************************************************************/ 

#include "stddef.h"
#include "ad9833function.h"

/* ����һ��16λ���ݵ�AD9833 */
static void SendToAD9833(Ad9833ObjectType *dev,uint16_t data);
/* Ƶ�ʼĴ����Ĳ������ã���28λ��14λ�����ֶλ���ֶ� */
static void ConfigFreqRegisterStyle(Ad9833ObjectType *dev,WriteAd9833FreqReg reg);
/* Ĭ��Ƭѡ��������������Ӳ��Ƭѡʱ */
static void DefaultChipSelcet(AD9833CSType en);

/* ����Ƶ�ʼĴ�����ֵ */
void SetAD9833FreqRegister(Ad9833ObjectType *dev,WriteAd9833FreqReg reg,uint32_t freqValue)
{
  uint16_t msbFreq,lsbFreq;
  uint32_t freqReg;
	
  freqReg =(uint32_t)(dev->freqConstant*freqValue);
  lsbFreq = (freqReg & 0x0003FFF);
  msbFreq = ((freqReg & 0xFFFC000) >> 14);
	
  ConfigFreqRegisterStyle(dev,reg);
	
  switch(reg)
  {
    case FREQ0_B28:
    {
      lsbFreq |=FREQ0_Address;
      SendToAD9833(dev,lsbFreq);
      msbFreq |=FREQ0_Address;
      SendToAD9833(dev,msbFreq);
      break;
    }
    case FREQ0_B14_LSB:
    {
      lsbFreq |=FREQ0_Address;
      SendToAD9833(dev,lsbFreq);
      break;
    }
    case FREQ0_B14_MSB:
    {
      msbFreq |=FREQ0_Address;
      SendToAD9833(dev,msbFreq);
      break;
    }
    case FREQ1_B28:
    {
      lsbFreq |=FREQ1_Address;
      SendToAD9833(dev,lsbFreq);
      msbFreq |=FREQ1_Address;
      SendToAD9833(dev,msbFreq);
      break;
    }
    case FREQ1_B14_LSB:
    {
      lsbFreq |=FREQ1_Address;
      SendToAD9833(dev,lsbFreq);
      break;
    }
    case FREQ1_B14_MSB:
    {
      msbFreq |=FREQ1_Address;
      SendToAD9833(dev,msbFreq);
      break;
    }
    default:
    {
      break;
    }
  }
	
}
	
/* Ƶ�ʼĴ����Ĳ������ã���28λ��14λ�����ֶλ���ֶ� */
static void ConfigFreqRegisterStyle(Ad9833ObjectType *dev,WriteAd9833FreqReg reg)
{
  uint16_t regValue=dev->ctlRegister;
//	uint8_t wData[2];
  regValue&=(~(AD9833_CTRLB28|AD9833_CTRLHLB));
	
  switch(reg)
  {
    case FREQ0_B28:
    case FREQ1_B28:
    {
      regValue |=AD9833_CTRLB28;
      break;
    }
    case FREQ0_B14_MSB:
    case FREQ1_B14_MSB:
    {
      regValue |=AD9833_CTRLHLB;
      break;
    }
    default:
    {
      break;
    }
  }
	
  SendToAD9833(dev,regValue);
  dev->ctlRegister=regValue;
}
	
/* ������λ�Ĵ�����ֵ */
void SetAD9833PhaseRegister(Ad9833ObjectType *dev,Ad9833PhaseReg reg,float phaseValue)
{
  uint16_t phaseReg=0;
  float phaseConstant=651.8986469;
  
  phaseReg=(uint16_t)(phaseValue*phaseConstant);
  phaseReg&=0x0FFF;
	
  if(reg==PHASE0)
  {
    phaseReg|=PHASE0_Address;
  }
  else
  {
    phaseReg|=PHASE1_Address;
  }
	
  SendToAD9833(dev,phaseReg);
}
	
/* Ƶ�ʼĴ���ѡ�� */
void SelectAD9833FregRegister(Ad9833ObjectType *dev,Ad9833FreqReg reg)
{
  uint16_t regValue=dev->ctlRegister;

  regValue&=(~AD9833_CTRLFSEL);
	
  if(reg==FREQ1)
  {
    regValue|=AD9833_CTRLFSEL;
  }
	
  SendToAD9833(dev,regValue);
	
  dev->ctlRegister=regValue;
}
	
/* ��λ�Ĵ���ѡ�� */
void SelectAD9833PhaseRegister(Ad9833ObjectType *dev,Ad9833PhaseReg reg)
{
  uint16_t regValue=dev->ctlRegister;

  regValue&=(~AD9833_CTRLPSEL);
	
  if(reg==PHASE1)
  {
    regValue|=AD9833_CTRLPSEL;
  }
	
  SendToAD9833(dev,regValue);
	
  dev->ctlRegister=regValue;
}
	
/* ��λAD9833���� */
void ResetAD9833Object(Ad9833ObjectType *dev)
{
  uint16_t regValue=dev->ctlRegister;
	
  regValue|=AD9833_CTRLRESET;
  SendToAD9833(dev,regValue);
	
  dev->Delayms(1);
	
  regValue&=(~AD9833_CTRLRESET);
  SendToAD9833(dev,regValue);
	
  dev->ctlRegister=regValue;
}

/* ����AD9833����״̬ */
void SetAD9833SleepMode(Ad9833ObjectType *dev,Ad9833SleepMode mode)
{
  uint16_t regValue=dev->ctlRegister;

  regValue&=(~(AD9833_CTRLSLEEP1|AD9833_CTRLSLEEP12));
	
  switch(mode)
  {
    case DACTurnOff:
    {
      regValue|=AD9833_CTRLSLEEP12;
      break;
    }
    case MCLKTurnOff:
    {
      regValue|=AD9833_CTRLSLEEP1;
      break;
    }
    case DACMCLKTurnOff:
    {
      regValue|=(AD9833_CTRLSLEEP1|AD9833_CTRLSLEEP12);
      break;
    }
    default:
    {
      break;
    }
  }
  SendToAD9833(dev,regValue);
  
  dev->ctlRegister=regValue;
}
	
/* ����AD9833�����ģʽ */
void SetAD9833OutputMode(Ad9833ObjectType *dev,Ad9833OutMode mode)
{
  uint16_t regValue=dev->ctlRegister;
  
  regValue&=(~(AD9833_CTRLOPBITEN|AD9833_CTRLDIV2|AD9833_CTRLMODE));
	
  switch(mode)
  {
    case triangular:
    {
      regValue|=AD9833_CTRLMODE;
      break;
    }
    case square_msb_2:
    {
      regValue|=AD9833_CTRLOPBITEN;
      break;
    }
    case square_msb:
    {
      regValue|=(AD9833_CTRLOPBITEN|AD9833_CTRLDIV2);
      break;
    }
    default:
    {
      break;
    }
  }

  SendToAD9833(dev,regValue);
	
  dev->ctlRegister=regValue;
}

/* ��ʼ��AD9833���� */
void AD9833Initialization(Ad9833ObjectType *dev,
                          float mclk,
                          AD9833WriteData write,
                          AD9833ChipSelcet cs,
                          AD9833Delayms delayms)
{
  if((dev==NULL)||(write==NULL)||(delayms==NULL))
  {
    return;
  }
  dev->WriteData=write;
  dev->Delayms=delayms;
  
  dev->ctlRegister=0x0000;
  
  if(mclk>0)
  {
    dev->freqConstant=268.435456/mclk;
  }
  else
  {
    dev->freqConstant=10.73741824;	//Ĭ����25M
  }
	
  if(cs!=NULL)
  {
    dev->ChipSelcet=cs;
  }
  else
  {
    dev->ChipSelcet=DefaultChipSelcet;
  }
	
  ResetAD9833Object(dev);
}

/* ����һ��16λ���ݵ�AD9833 */
static void SendToAD9833(Ad9833ObjectType *dev,uint16_t data)
{
  uint8_t wData[2];
  
  wData[0]=(uint8_t)(data>>8);
  wData[1]=(uint8_t)data;
  
  dev->ChipSelcet(AD9833CS_ENABLE);
  dev->WriteData(wData,2);
  dev->ChipSelcet(AD9833CS_DISABLE);
}

/* Ĭ��Ƭѡ��������������Ӳ��Ƭѡʱ */
static void DefaultChipSelcet(AD9833CSType en)
{
  return;
}
	
/*********** (C) COPYRIGHT 1999-2019 Moonan Technology *********END OF FILE****/
