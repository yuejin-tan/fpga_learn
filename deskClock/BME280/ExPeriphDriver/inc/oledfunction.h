/******************************************************************************/
/** ģ�����ƣ���չ��������                                                   **/
/** �ļ����ƣ�oledfunction.h                                                 **/
/** ��    ����V1.0.0                                                         **/
/** ��    �飺Ӧ����ʵ��OLED��ʾ���Ĳ���                                     **/
/**--------------------------------------------------------------------------**/
/** �޸ļ�¼��                                                               **/
/**     �汾      ����              ����              ˵��                   **/
/**     V1.0.0  2017-07-17          ľ��              �����ļ�               **/
/**                                                                          **/
/******************************************************************************/ 

#ifndef __OLEDFUNCTION_H
#define __OLEDFUNCTION_H

#include "stdint.h"

/*������ʾ�������С*/
typedef enum OledFontSize{
  OLED_FONT_6x8,
  OLED_FONT_8x16
}OledFontSizeType;

/*OLED�Ľӿ�����*/
typedef enum OledPort{
  OLED_SPI,
  OLED_I2C
}OledPortType;

/* ����OLEDƬѡ�ź�ö�� */
typedef enum OledCS {
  OLEDCS_Enable,
  OLEDCS_Disable
}OledCSType;

/* ����OLEDDC�ź�ö�� */
typedef enum OledDC {
  OLEDDC_Command,
  OLEDDC_Data
}OledDCType;

/* ����RST�ź�ö�� */
typedef enum OledRST {
  OLED_RESET,
  OLED_WORK
}OledRSTType;

/*����OLED��������*/
typedef struct OledObject {
  uint8_t devAddress;
  OledPortType port;
  void (*Write)(struct OledObject *oled,uint8_t *wData,uint16_t wSize);
  void (*ChipSelcet)(OledCSType en);
  void (*DCSelcet)(OledDCType dc);
  void (*ChipReset)(OledRSTType rst);
  void (*Delayms)(volatile uint32_t nTime);
}OledObjectType;

/*��MS5803�·�ָ�ָ���ʽ��Ϊ1���ֽ�*/
typedef void (*OledWrite)(OledObjectType *oled,uint8_t *wData,uint16_t wSize);
/*��λ�źŲ�������ָ��*/
typedef void (*OledChipReset)(OledRSTType rst);
/*�����������SPI�ӿ�*/
typedef void (*OledDCSelcet)(OledDCType dc);
/*Ƭѡ�ź�,����SPI�ӿ�*/
typedef void (*OledChipSelcet)(OledCSType en);     
/*��������ʱ����*/
typedef void (*OledDelayms)(volatile uint32_t nTime);   


/*OLED��ʾ�������ʼ��*/
void OledInitialization(OledObjectType *oled,           //OLED����
                        OledPortType port,              //ͨѶ�˿�
                        uint8_t address,                //I2C�豸��ַ
                        OledWrite write,                //д���ݺ���
                        OledChipReset rst,              //��λ�źŲ�������ָ��
                        OledDCSelcet dc,                //DC�źſ��ƺ���ָ��
                        OledChipSelcet cs,              //SPIƬѡ�źź���ָ��
                        OledDelayms delayms             //������ʱ����ָ��
                       );

/*��ʾһ��128x64��ͼƬ*/
void OledShowPicture(OledObjectType *oled,uint8_t *sData);

/*��ʾ32x32��32��32�У����ַ����纺��*/
void OledShow32x32Char(OledObjectType *oled,uint8_t page,uint8_t seg,uint8_t *sData);

/*��ʾ16x16��16��16�У����ַ����纺��*/
void OledShow16x16Char(OledObjectType *oled,uint8_t page,uint8_t seg,uint8_t *sData);

/*��ʾ8x16��16��8�У����ַ�����ASCII���ַ���*/
void OledShow8x16Char(OledObjectType *oled,uint8_t page,uint8_t seg,uint8_t *sData);

/*��ʾ6x8��8��6�У����ַ�����ASCII���ַ�*/
void OledShow6x8Char(OledObjectType *oled,uint8_t page,uint8_t seg,uint8_t *sData);

/*��ʾ�ַ���*/
void OledShowString(OledObjectType *oled,OledFontSizeType fontSize,uint8_t page,uint8_t seg,char *fmt,...);

#endif
/*********** (C) COPYRIGHT 1999-2017 Moonan Technology *********END OF FILE****/
