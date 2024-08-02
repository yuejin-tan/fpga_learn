/******************************************************************************/
/** ģ�����ƣ���չ��������                                                   **/
/** �ļ����ƣ�esp8266function.h                                              **/
/** ��    ����V1.0.0                                                         **/
/** ��    �飺����ʵ��ESP8266����ͨѶ�Ĳ�����ESP8266EX֧��TCP/IPЭ�飬��ȫ   **/
/**           ��ѭ802.11 b/g/n/e/i WLAN MAC Э��� Wi-Fi Direct ��׼������   **/
/**           USART�ӿڣ�����ͨ��ATָ��ʵ�����ݽ�����                        **/
/**--------------------------------------------------------------------------**/
/** �޸ļ�¼��                                                               **/
/**     �汾      ����              ����              ˵��                   **/
/**     V1.0.0  2017-07-17          ľ��              �����ļ�               **/
/**                                                                          **/
/******************************************************************************/ 

#ifndef __ESP8266FUNCTION_H
#define __ESP8266FUNCTION_H

#include "stdint.h"

#define Esp8266RxBufferLength 50

/*�������״̬ö��*/
typedef enum Esp8266RxStatus {
  Esp8266_RxNone,       //δ��ʼ����
  Esp8266_RxWait,       //���ڽ�����
  Esp8266_RxFinish      //�������
}Esp8266RxStatusType;

/*�����������ͽ��ö��*/
typedef enum Esp8266TxStatus {
  Esp8266_TxFial,       //����ʧ��
  Esp8266_RxSucceed,    //���ͳɹ�
}Esp8266TxStatusType;

/*���崫��ģʽö��*/
typedef enum Esp8266CIPMode {
  Esp8266_NormalMode,   //����ģʽ
  Esp8266_TransMode     //͸��ģʽ
}Esp8266CIPModeType;

/*����ESP8266��WIFIģʽ*/
typedef enum Esp8266CWMode {
  Esp8266_StationMode,  //station ģʽ 
  Esp8266_SoftAPMode,   //softAP ģʽ 
  Esp8266_MixedMode     //softAP + station ģʽ 
}Esp8266CWModeType;

/*��������������Ϣö��*/
typedef enum Esp8266CIPStatus {
  Esp8266_Timeout=0,    //��ʱ
  Esp8266_Error=1,        //����
  Esp8266_GotIP=2,        //���IP��ַ
  Esp8266_Connected=3,    //��������
  Esp8266_Disconnect=4,   //�Ͽ�����
  Esp8266_NoWifi=5        //δ���ӵ� WiFi 
}Esp8266CIPStatusType;


/*����ESP8266����*/
typedef struct Esp8266Object {
  Esp8266CWModeType cwMode;     //WIFIģʽ
  Esp8266CIPModeType cipMode;   //����ģʽ��������͸��
  struct EspRxBuffer{
    uint8_t queue[Esp8266RxBufferLength];	//���ݴ洢����
    uint8_t lengthRecieving;			//���ڽ��յ����ݳ���
    uint8_t lengthRecieved;			//�Ѿ����յ����ݳ���
  }rxBuffer;
  void (*SendData)(uint8_t *sData,uint16_t sSize);//���ݷ��ͺ���ָ��
  void (*Delayms)(volatile uint32_t nTime);     //��ʱ����ָ��
}Esp8266ObjectObject;

/*����ESP8266���ݷ���ָ������*/
typedef void (*ESP8266SendDataType)(uint8_t *sData,uint16_t sSize);
/*��ʱ����ָ��*/
typedef void (*ESP8266DelaymsType)(volatile uint32_t nTime);     

/*ESP8266�����ʼ��*/
void Esp8266Initialization(Esp8266ObjectObject *esp,    //ESP8266����
                           Esp8266CWModeType cwMode,    //WIFIģʽ
                           Esp8266CIPModeType cipMode,  //����ģʽ��������͸��
                           char *wifiName,              //WIFI����
                           char *wifiPassword,          //WIFI����
                           ESP8266SendDataType send,    //���ͺ���ָ��
                           ESP8266DelaymsType delayms   //������ʱ����
                           );

/*ESP8266��������*/
void Esp8266SendData(Esp8266ObjectObject *esp,uint8_t *sData,uint16_t sSize);

/*���ģ��������Ƿ�����*/
Esp8266CIPStatusType CheckForConnection(Esp8266ObjectObject *esp,uint16_t timeOut);

#endif
/*********** (C) COPYRIGHT 1999-2019 Moonan Technology *********END OF FILE****/
