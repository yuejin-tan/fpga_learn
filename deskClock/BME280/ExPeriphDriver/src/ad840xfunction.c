/******************************************************************************/
/** ģ�����ƣ���չ��������                                                   **/
/** �ļ����ƣ�ad840xfunction.c                                               **/
/** ��    ����V1.0.0                                                         **/
/** ��    �飺�����Ͷ���ad8400���ֵ�λ��оƬ��صĸ��ֺ����Ͳ���             **/
/**           ����SPI�ӿڣ�֧��SPIģʽ0                                      **/
/**--------------------------------------------------------------------------**/
/** �޸ļ�¼��                                                               **/
/**     �汾      ����              ����              ˵��                   **/
/**     V1.0.0  2016-11-08          ľ��              �����ļ�               **/
/**                                                                          **/
/******************************************************************************/ 

#include "stddef.h"
#include "ad840xfunction.h"

#define RESISTANCEINDEX (256) //�������ķֶ�
#define RESISTANCEINITIAL  (50) //���������ֶȵĵ���

/*����AD8400�α��λ��*/
void SetAD8400ResistorValue(AD840xObjectType *vr,uint16_t resistorValue,AD840xLdacType ldac)
{
  float mValue=0.0;
  uint16_t sendValue=0;
  uint8_t txData[2];
  
  if((resistorValue<50)||(resistorValue>vr->nominalValue))
  {
    return;
  }
	
  if((vr->type==AD8400)&&(ldac!=AD840x_VR1))
  {
    return;
  }
		
  if((vr->type==AD8402)&&(ldac>AD840x_VR2))
  {
    return;
  }
	
  mValue=((float)resistorValue-(float)RESISTANCEINITIAL)/(float)vr->nominalValue;
  sendValue=(uint8_t)(mValue*RESISTANCEINDEX);
	
  sendValue=sendValue||(ldac<<8);
  
  txData[0]=(sendValue>>2);
  txData[1]=(sendValue<<6);
  vr->Write(txData[0]);
  vr->Write(txData[1]);
}

/* ��ʼ��AD840x���� */
void AD840xInitialization(AD840xObjectType *vr,AD840xType type,AD840xWriteByte write,AD840xNRType nr)
{
  float nValue[4]={1000,10000,50000,100000};
		
  if((vr==NULL)||(write==NULL))
  {
    return;
  }
	
  vr->type=type;
  
  vr->Write=write;
  
  vr->nominalValue=nValue[nr];
}

/*********** (C) COPYRIGHT 1999-2017 Moonan Technology *********END OF FILE****/
