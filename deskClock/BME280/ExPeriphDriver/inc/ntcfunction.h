/******************************************************************************/
/** ģ�����ƣ���չ��������                                                   **/
/** �ļ����ƣ�ntcfunction.h                                                  **/
/** ��    ����V1.0.0                                                         **/
/** ��    �飺�����Ͷ��帺�¶�ϵ���ȵ�����¼���ĸ��ֺ����Ͳ���             **/
/**           NTC������������Bֵһ����2000K��6000K֮�䡣10K�ĳ���Bֻ��3435�� **/
/**           3380��3370��3950��100K�ĳ���Bֵ4100��Bֵ��NTC�����ṩ��        **/
/**--------------------------------------------------------------------------**/
/** �޸ļ�¼��                                                               **/
/**     �汾      ����              ����              ˵��                   **/
/**     V1.0.0  2017-09-01          ľ��              �����ļ�               **/
/**                                                                          **/
/******************************************************************************/ 

#ifndef __NTCFUNCTION_H
#define __NTCFUNCTION_H

#include "math.h"
#include "stdint.h"

/* ����NTC������¶��� */
typedef struct NTCObject{
  float BValue;         //NTC��B����
  float nominalT;       //NTC����¶ȣ����϶ȣ�
  float nominalR;       //NTC��Ƶ���
}NTCObjectType;

/*��ʽ������NTC�¶�ֵ*/
float NTCTemperature(NTCObjectType *ntc,float resistance);

/* NTC�����ʼ������ */
void NTCInitialization(NTCObjectType *ntc,float bValue,float nt,float nr);

#endif
/*********** (C) COPYRIGHT 1999-2017 Moonan Technology *********END OF FILE****/
