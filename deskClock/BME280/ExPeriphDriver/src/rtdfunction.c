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
/**           ����0�����ϵ��¶���Ҫ��һ��һԪ���η��̣����ڶ�����ϵ������0�� **/
/**           �����ߣ���������������ʱ�����غϣ�������������������ֲ������� **/
/**           �ࡣ���Ǽ��������غ�ʱ��ֵΪ3383.81������ȡֵ��Χ�����ƣ�ʵ����**/
/**           Զֻ����һ��������Ҫ������ֻ�����һ������                   **/
/**           ����0�����µ��¶�ʵ����Ҫ��һ��һԪ�Ĵη��̡�                  **/
/**--------------------------------------------------------------------------**/
/** �޸ļ�¼��                                                               **/
/**     �汾      ����              ����              ˵��                   **/
/**     V1.0.0  2018-01-11          ľ��              �����ļ�               **/
/**                                                                          **/
/******************************************************************************/ 

#include "stddef.h"
#include "rtdfunction.h"

/* ���㲬�����¶� */
static float CalcWzpTemperature(RTDObjectType *rtd,float rt);
/* ���㲬�����¶� */
static float CalcWzcTemperature(RTDObjectType *rtd,float rt);
/* �����������¶� */
static float CalcWznTemperature(RTDObjectType *rtd,float rt);

float (*CalcTemperature[])(RTDObjectType *rtd,float rt)={CalcWzpTemperature,CalcWzcTemperature,CalcWznTemperature};

/*�����ȵ����õ��¶�*/
float CalcRTDTemperature(RTDObjectType *rtd,float rt)
{
  float temp=0.0;
  
  temp=CalcTemperature[rtd->type](rtd,rt);

  return temp;
}

/* ���㲬�����¶� */
static float CalcWzpTemperature(RTDObjectType *rtd,float rt)
{
  float temp=0.0;
  float a=0.0039083;
	
  temp=((rt/rtd->nominalR)-1.0)/a;
  rtd->temperature=temp;
	
  return temp;
}

/* ����ͭ�����¶� */
static float CalcWzcTemperature(RTDObjectType *rtd,float rt)
{
  float temp=0.0;
  float alpha=0.00428;
	
  temp=((rt/rtd->nominalR)-1.0)/alpha;
  rtd->temperature=temp;
	
  return temp;
}

/* �����������¶� */
static float CalcWznTemperature(RTDObjectType *rtd,float rt)
{
  float temp=0.0;
  float a=0.005485;
	
  temp=((rt/rtd->nominalR)-1.0)/a;
  rtd->temperature=temp;
	
  return temp;
}

/* ��ʼ��RTD���� */
void RTDInitialization(RTDObjectType *rtd,RTDCategoryType type,float nr)
{
  if(rtd==NULL)
  {
    return;
  }
	
  rtd->temperature=0.0;
  rtd->type=type;
  rtd->nominalR=nr;
}
/*********** (C) COPYRIGHT 1999-2018 Moonan Technology *********END OF FILE****/
