/******************************************************************************/
/** ģ�����ƣ���չ��������                                                   **/
/** �ļ����ƣ�hlptfunction.h                                                 **/
/** ��    ����V1.0.0                                                         **/
/** ��    �飺����ʵ��TSEV01CL55�����¶ȴ�������ͨѶ                         **/
/**           ����I2CͨѶͨѶ�ӿ�                                            **/
/**--------------------------------------------------------------------------**/
/**ʹ��˵����                                                                **/
/**    1������HLPTObjectType����ʵ�壬�����ú���HLPTInitialization��ʼ��     **/
/**       ����ʵ�塣��ʼ��ʱ����������ĵ�ַ��                               **/
/**    2��ʵ������void f(struct HLPTObject *hlpt,uint8_t *rData,             **/
/**       uint16_t rSize)�ĺ����������丳ֵ��HLPTObjectType����ʵ���Receive **/
/**       ����ָ�롣ʵ�ֶ����ݵĲ�����                                       **/
/**    3��ʵ������void f(struct HLPTObject *hlpt,uint8_t wData)�ĺ���������  **/
/**       �丳ֵ��HLPTObjectType����ʵ���Transmit����ָ�롣ʵ�ַ���������� **/
/**    4��ʵ������oid f(volatile uint32_t nTime)�ĺ����������丳ֵ��         **/
/**       HLPTObjectType����ʵ���Delay����ָ�롣ʵ����ʱ��������λΪ���롣  **/
/**    5��������Ӧ�ĺ���ʵ����Ҫ�Ĳ�����                                     **/
/**--------------------------------------------------------------------------**/
/** �޸ļ�¼��                                                               **/
/**     �汾      ����              ����              ˵��                   **/
/**     V1.0.0  2019-02-26          ľ��              �����ļ�               **/
/**                                                                          **/
/******************************************************************************/ 

#ifndef __HLPT_FUNCTION_H
#define __HLPT_FUNCTION_H

#include "stdint.h"

//����TSEV01CL55�����¶ȴ�������������
typedef struct HLPTObject{
  uint8_t devAddress;           //����ĵ�ַ
  float tempObject;             //�����¶�ֵ
  float tempAmbient;            //�����¶�
  void (*Delayms)(volatile uint32_t nTime);       //��ʱ����ָ��
  void (*Receive)(struct HLPTObject *hlpt,uint8_t *rData,uint16_t rSize);		//�������ݲ���ָ��
  void (*Transmit)(struct HLPTObject *hlpt,uint8_t *wData,uint16_t wSize);		//�������ݲ���ָ��
}HLPTObjectType;

/*��ʱ����ָ������*/
typedef void (*HLPTDelayms)(volatile uint32_t nTime);
/*�������ݲ���ָ������*/
typedef void (*HLPTReceive)(struct HLPTObject *hlpt,uint8_t *rData,uint16_t rSize);
/*�������ݲ���ָ������*/
typedef void (*HLPTTransmit)(struct HLPTObject *hlpt,uint8_t *wData,uint16_t wSize);

//��ȡ�¶�ֵ
void GetHLPTemperature(HLPTObjectType *hlpt);

/* �����¶ȴ����������ʼ�� */
void HLPTInitialization(HLPTObjectType *hlpt,   //��ʼ���Ķ������
                        uint8_t address,        //�豸I2C��ַ
                        HLPTReceive receive,    //���պ���ָ��
                        HLPTTransmit transmit,  //���ͺ���ָ��
                        HLPTDelayms delayms     //������ʱ����ָ��
                       );

#endif

/*********** (C) COPYRIGHT 1999-2019 Moonan Technology *********END OF FILE****/
