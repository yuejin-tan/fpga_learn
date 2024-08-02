/******************************************************************************/
/** ģ�����ƣ���չ��������                                                   **/
/** �ļ����ƣ�rtdfunction.c                                                  **/
/** ��    ����V1.0.0                                                         **/
/** ��    �飺����ʵ�ֲ��ȵ����¶Ȳ�������غ����Ͳ���                       **/
/**           ��������ȵ�����ѭGB/T 30121-2013(IEC 60751:2008)��׼          **/
/**           �������¶�ϵ��Ϊ0.003851�Ĳ��ȵ���                             **/
/**           �¶������Ĺ�ϵ���ʽ���£�                                   **/
/**               -200��0���϶ȣ�Rt=R0*[1+A*t+B*t^2+C*(t-100)*t^3]           **/
/**               0��850���϶ȣ�Rt=R0*(1+A*t+B*t^2)                          **/
/**           �������ʽ���¶ȵ�λ��Ϊ���϶�,ʽ�и�������ȡֵ���£�          **/
/**               A=3.9083*10^-3                                             **/
/**               B=-5.775*10^-7                                             **/
/**               C=-4.183*10^-13                                            **/
/**--------------------------------------------------------------------------**/
/** �޸ļ�¼��                                                               **/
/**     �汾      ����              ����              ˵��                   **/
/**     V1.0.0  2018-01-11          ľ��              �����ļ�               **/
/**                                                                          **/
/******************************************************************************/ 

#ifndef __RTDFUNCTION_H
#define __RTDFUNCTION_H

#include <stdint.h>
#include <math.h>

/* ����RTD����ö�� */
typedef enum RTDCategory {
  WZP,
  WZC,
  WZN
}RTDCategoryType;

/* ����RTD���� */
typedef struct RTDObject{
  float nominalR;       //RTD��Ƶ���
  float temperature;    //�����¶�
  RTDCategoryType type; //RTD����
}RTDObjectType;

/*�����ȵ����õ��¶�*/
float CalcRTDTemperature(RTDObjectType *rtd,float rt);

/* ��ʼ��RTD���� */
void RTDInitialization(RTDObjectType *rtd,RTDCategoryType type,float nr);
#endif
/*********** (C) COPYRIGHT 1999-2019 Moonan Technology *********END OF FILE****/
