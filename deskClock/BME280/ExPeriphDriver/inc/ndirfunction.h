/******************************************************************************/
/** ģ�����ƣ���չ��������                                                   **/
/** �ļ����ƣ�ndirfunction.c                                                 **/
/** ��    ����V1.0.0                                                         **/
/** ��    �飺ʵ����ķǷֹ����������ģ��ͨѶ��صĺ����Ͳ���             **/
/**           ���Schutz S-MODULE�Ƿֹ��������ģ��ͨѶ��                    **/
/**           �� Baud rate	������:		2400		             **/
/**           �� Data bits	����λ:		7		             **/
/**           �� Stop bits	ֹͣλ:		1		             **/
/**           �� Parity		��ż��:		Even/ż                      **/
/**           �� Timeout	��ʱʱ��:	1000ms		             **/
/**           �� Retries	�ظ�����:	3	                     **/
/**           ���Schutz S-MODULE�Ƿֹ��������ģ��Modbus������              **/
/**           0x00C0		Modbus_address	ģ�鵱ǰModbus��ַ  �ɶ�д   **/
/**           0x0080��0x0083	DeviceType      �豸���ͺ�          �ɶ�д   **/
/**           0x0084��0x0085	SoftwareVersion ����汾            ֻ��     **/
/**           0x0086��0x0089	Internal device number  �豸���к�  ֻ��     **/
/**           0x0005		MOD	����Ũ������ֵ	            ֻ��     **/
/**           0x000A		Concentration    ����Ũ��           ֻ��     **/
/**           0x0003		T_module (0.1x��C)   �������ڲ��¶� ֻ��     **/
/**           0x0045		Alarm_Level     ��������ֵ          �ɶ�д   **/
/**           0x0044		Warn_Level      Ԥ������ֵ          �ɶ�д   **/
/**           0x0047		IR_4tagneu      ����ǿ�Ȳ���      �ɶ�д   **/
/**           0x0009		Statusflags     ״̬��Ϣ            ֻ��     **/
/**                 Flag 0 Testflag ֵ��1����ʾ�������ڲ���״̬              **/
/**                 Flag 1 Warmup ֵ��1����ʾ�������Լ10��Ԥ��              **/
/**                 Flag 2 Syserr ֵ��1����ʾϵͳ����                        **/
/**                 Flag 3 Alarm ֵ��1����ʾ������������ʼ����               **/
/**                 Flag 4 Warn ֵ��1����ʾ����Ԥ������ʼ����                **/
/**                 Flag 5 Startup ֵ��1����ʾ���������׶Σ�����90�룩       **/
/**                 Flag 6 Korr ֵ��1����ʾS-MODULE�ṩ�¶Ȳ�������          **/
/**                 Flag 7 mw_ok ֵ��1����ʾ������趨                       **/
/**--------------------------------------------------------------------------**/
/** �޸ļ�¼��                                                               **/
/**     �汾      ����              ����              ˵��                   **/
/**     V1.0.0  2015-07-31          ľ��              �����ļ�               **/
/**                                                                          **/
/******************************************************************************/ 

#ifndef __ndirfunction_h
#define __ndirfunction_h

#include "stdint.h"

#define ReadRegisterFC    0x03    //�ӼĴ�����������
#define WriteRegisterFC   0x06    //���Ĵ���д������

/*�����ȡ�������͵�ö��*/
typedef enum NdirParameter{
  SoftVersion=0x0084,
  Concentration=0x000A,
  Temperature=0x0003,
  StatusFlags=0x0009
}NdirParameterType;

/*����NDIR��������*/
typedef struct NdirObject {
  uint8_t moduleAddress;
  uint16_t status;
  uint32_t softVersion;
  float concentration;
  float temperature;
  void (*SendByte)(uint8_t data);
  void (*Delayms)(volatile uint32_t nTime);
}NdirObjectType;

/*����һ���ֽڲ�������ָ������*/
typedef void (*NdirSendByteType)(uint8_t data);
/*������ʱ����ָ������*/
typedef void (*NdirDelaymsType)(volatile uint32_t nTime);

/*NDIR��ʼ�����ú���*/
void NdirInitialization(NdirObjectType *ndir,   //NDIR����
                        uint8_t moduleAddress,  //ģ���ַ
                        NdirSendByteType send,  //�������ݲ�������
                        NdirDelaymsType delayms //������ʱ��������
                        );

/*���ݽ��������Խ������յ���������Ϣ*/
void NdirParseReceiveData(NdirObjectType *ndir,uint8_t * receiveDataBuffer);

/*������汾*/
uint32_t ReadNDIRSoftVersion(NdirObjectType *ndir,uint8_t *receiveDataBuffer);

/*����ķǷֹ����������ģ���ȡŨ��ֵ*/
float ReadConcentrationData(NdirObjectType *ndir,uint8_t * receiveDataBuffer);

/*����ķǷֹ����������ģ���ȡ�ڲ��¶�ֵ*/
float ReadTemperatureData(NdirObjectType *ndir,uint8_t * receiveDataBuffer);

/*����ķǷֹ����������ģ���ȡ״̬��־*/
uint16_t ReadNDIRStatusflags(NdirObjectType *ndir,uint8_t * receiveDataBuffer);

#endif
/*********** (C) COPYRIGHT 1999-2019 Moonan Technology *********END OF FILE****/
