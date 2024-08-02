/******************************************************************************/
/** ģ�����ƣ���̫��ͨѶ                                                     **/
/** �ļ����ƣ�w5500function.h                                                **/
/** ��    ����V1.0.0                                                         **/
/** ��    �飺����ʹ��W5500ʵ����̫��ͨѶ����ش���                          **/
/**--------------------------------------------------------------------------**/
/** �޸ļ�¼��                                                               **/
/**     �汾      ����              ����              ˵��                   **/
/**     V1.0.0  2015-07-30          ľ��              �����ļ�               **/
/**                                                                          **/
/******************************************************************************/ 


#ifndef __w5500function_h
#define __w5500function_h

#include "stdint.h"
#include "socket.h"

/* ����W5500�������� */
typedef struct W5500Object {
  wiz_NetInfo gWIZNETINFO;
  uint16_t (*DataParsing)(uint8_t *rxBuffer,uint16_t rxSize,uint8_t *txBuffer);//������Ϣ������������Ϣ���ɣ�����ֵΪ������Ϣ���ֽڳ���
  uint16_t (*RequestData)(uint8_t *rqBuffer);   //�õ��������һ�����ڿͻ��˷������
}W5500ObjectType;

/*����Socketö�٣���8��*/
typedef enum W5500Socket {
  Socket0=0,
  Socket1=1,
  Socket2=2,
  Socket3=3,
  Socket4=4,
  Socket5=5,
  Socket6=6,
  Socket7=7
}W5500SocketType;

/*�������յ�������*/
typedef uint16_t (*W5500DataParsingType)(uint8_t *rxBuffer,uint16_t rxSize,uint8_t *txBuffer);
/*�õ��������һ�����ڿͻ��˷������*/
typedef uint16_t (*W5500RequestDataType)(uint8_t *rqBuffer);   

/*����Ƭѡ���ٽ���������������*/
typedef void (*W5500CSCrisType)(void);
/*����SPI��һ���ֽں�������*/
typedef uint8_t (*W5500SPIReadByteTYpe)(void);
/*����SPIдһ���ֽں�������*/
typedef void (*W5500SPIWriteByteTYpe)(uint8_t wb);

/*TCP����������ͨѶ*/
int32_t W5500TCPServer(W5500ObjectType *w5500,W5500SocketType sn, uint16_t port);
/*TCP�ͻ�������ͨѶ*/
int32_t W5500TCPClient(W5500ObjectType *w5500,W5500SocketType sn,uint16_t lPort,uint8_t *rIP,uint16_t rPort);
/*UDP����������ͨѶ*/
int32_t W5500UDPServer(W5500ObjectType *w5500,W5500SocketType sn, uint16_t port,uint8_t *rIP,uint16_t rPort);
/*UDP�ͻ�������ͨѶ*/
int32_t W5500UDPClient(W5500ObjectType *w5500,W5500SocketType sn, uint16_t lPort,uint8_t *rIP,uint16_t rPort);

/*W5500�����ʼ������*/
void W5500Initialization(W5500ObjectType *w5500,
                         uint8_t mac[6],        //����Mac��ַ
                         uint8_t ip[4],         //����IP��ַ
                         uint8_t sn[4],         //��������
                         uint8_t gw[4],         //���ص�ַ
                         uint8_t dns[4],        //DNS��������ַ
                         dhcp_mode dhcp,        //DHCP����
                         W5500CSCrisType cris_en,
                         W5500CSCrisType cris_ex,
                         W5500CSCrisType cs_sel,
                         W5500CSCrisType cs_desel,
                         W5500SPIReadByteTYpe spi_rb,
                         W5500SPIWriteByteTYpe spi_wb,
                         W5500DataParsingType dataParse,
                         W5500RequestDataType requst
                        );

#endif
/*********** (C) COPYRIGHT 1999-2017 Moonan Technology *********END OF FILE****/
