/******************************************************************************/
/** ģ�����ƣ���չ��������                                                   **/
/** �ļ����ƣ�ntcfunction.c                                                  **/
/** ��    ����V1.0.1                                                         **/
/** ��    �飺�����Ͷ��帺�¶�ϵ���ȵ�����¼���ĸ��ֺ����Ͳ���             **/
/**           NTC������������Bֵһ����2000K��6000K֮�䡣10K�ĳ���Bֻ��3435�� **/
/**           3380��3370��3950��100K�ĳ���Bֵ4100��Bֵ��NTC�����ṩ��        **/
/**--------------------------------------------------------------------------**/
/** �޸ļ�¼��                                                               **/
/**     �汾      ����              ����              ˵��                   **/
/**     V1.0.0  2017-09-01          ľ��              �����ļ�               **/
/**     V1.0.0  2019-07-23          ľ��              �޸�Ϊ�������         **/
/**                                                                          **/
/******************************************************************************/ 

#include "stddef.h"
#include "ntcfunction.h"

#define KELVIN_CONSTANT  273.15         /*�����¶ȳ���*/

/*��ʽ������NTC�¶�ֵ*/
float NTCTemperature(NTCObjectType *ntc,float resistance)
{
  float temp;
  float result=0.0;
  
  result=resistance/ntc->nominalR;
  result=(log(result)/ntc->nominalR)+(1/(ntc->nominalT+KELVIN_CONSTANT));
  temp=1/result-KELVIN_CONSTANT;
  
  return temp;
}

/* NTC�����ʼ������ */
void NTCInitialization(NTCObjectType *ntc,float bValue,float nt,float nr)
{
  if(ntc==NULL)
  {
    return;
  }
	
  ntc->BValue=bValue;
  ntc->nominalT=nt;
  ntc->nominalR=nr;
}

/*********** (C) COPYRIGHT 1999-2017 Moonan Technology *********END OF FILE****/
