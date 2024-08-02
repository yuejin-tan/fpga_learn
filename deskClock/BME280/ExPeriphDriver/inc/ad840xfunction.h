/******************************************************************************/
/** ģ�����ƣ����ݼ���봦��                                                 **/
/** �ļ����ƣ�ad840xfunction.h                                               **/
/** ��    ����V1.0.0                                                         **/
/** ��    �飺�����Ͷ���ad8400���ֵ�λ��оƬ��صĸ��ֺ����Ͳ���             **/
/**           ����SPI�ӿڣ�֧��SPIģʽ0                                      **/
/**--------------------------------------------------------------------------**/
/** �޸ļ�¼��                                                               **/
/**     �汾      ����              ����              ˵��                   **/
/**     V1.0.0  2016-11-08          ľ��              �����ļ�               **/
/**                                                                          **/
/******************************************************************************/ 

#ifndef __AD840XFUNCTION_H
#define __AD840XFUNCTION_H

#include <stdint.h>

/* ����AD840x����ö�� */
typedef enum AD840x{
  AD8400,
  AD8402,
  AD8403
}AD840xType;

/* ����AD840xͨ��ѡ��ö�� */
typedef enum AD840xLdac{
  AD840x_VR1=0x00,
  AD840x_VR2=0x01,
  AD840x_VR3=0x02,
  AD840x_VR4=0x03
}AD840xLdacType;

/* ����AD840x��Ƶ���ö�� */
typedef enum AD840xNR{
  AD840x_NR1k,		//��Ƶ���Ϊ1K
  AD840x_NR10k,		//��Ƶ���Ϊ10K
  AD840x_NR50k,		//��Ƶ���Ϊ50K
  AD840x_NR100k		//��Ƶ���Ϊ100K
}AD840xNRType;

/* ����AD840x�������� */
typedef struct AD840xObject{
  AD840xType type;		//AD840x��������
  float nominalValue;	//��Ƶ���ֵ
  void (*Write)(uint8_t rdac);	//д���ݲ�������ָ��
}AD840xObjectType;

/* ����д���ݲ�������ָ������ */
typedef void (*AD840xWriteByte)(uint8_t rdac);

/*����AD8400�α��λ��*/
void SetAD8400ResistorValue(AD840xObjectType *vr,uint16_t resistorValue,AD840xLdacType ldac);

/* ��ʼ��AD840x���� */
void AD840xInitialization(AD840xObjectType *vr,AD840xType type,AD840xWriteByte write,AD840xNRType nr);

#endif

/*********** (C) COPYRIGHT 2016 ���������ز�ؼ������޹�˾ *****END OF FILE****/
