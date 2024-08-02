/******************************************************************************/
/** ģ�����ƣ���չ��������                                                   **/
/** �ļ����ƣ�luxfunction.h                                                  **/
/** ��    ����V1.0.0                                                         **/
/** ��    �飺�����Ͷ���S1336-5BQ������������Ϊ��ȼƵĸ��ֺ����Ͳ���        **/
/**--------------------------------------------------------------------------**/
/** �޸ļ�¼��                                                               **/
/**     �汾      ����              ����              ˵��                   **/
/**     V1.0.0  2017-09-01          ľ��              �����ļ�               **/
/**                                                                          **/
/******************************************************************************/ 

#ifndef __LUXFUNCTION_H
#define __LUXFUNCTION_H

#include "stdint.h"

/* �����ȼ��������� */
typedef struct LuxObject {
  float isc100lux;      //ÿ100����ȱ仯����Ӧ�ĵ����仯
  float rnf;            //���������ֵ
  float vref;           //�ο���ѹ
  float lux;            //���ֵ
}LuxObjectType;

/*�������ǿ��*/
float CalcLxIllumination(LuxObjectType *lm,float mVoltage);

/* ��ȼ������ʼ�� */
void LuxInitialization(LuxObjectType *lm,float isc,float vref,float rnf);

#endif
/*********** (C) COPYRIGHT 1999-2017 Moonan Technology *********END OF FILE****/
