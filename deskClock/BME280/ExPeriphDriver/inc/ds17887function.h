/******************************************************************************/
/** ģ�����ƣ���չ��������                                                   **/
/** �ļ����ƣ�ds17887function.h                                              **/
/** ��    ����V1.1.0                                                         **/
/** ��    �飺ʵ��ʵʱʱ��ģ��DS17887�Ĳ���                                  **/
/**--------------------------------------------------------------------------**/
/** �޸ļ�¼��                                                               **/
/**     �汾      ����              ����              ˵��                   **/
/**     V1.0.0  2012-07-28          ľ��              �����ļ�               **/
/**     V1.1.0  2019-08-07          ľ��              �޸�Ϊ��������Ĳ���   **/
/**                                                                          **/
/******************************************************************************/ 

#include "stdint.h"

#define  DS17887_Base   0x00     //����ʱ��оƬ��Ƭѡ��ַ

#define  DS17887_Second   DS17887_Base+0x00  // ��
#define  DS17887_Minute   DS17887_Base+0x02  // ��
#define  DS17887_Hour     DS17887_Base+0x04  // ʱ
#define  DS17887_Date     DS17887_Base+0x07  // ����
#define  DS17887_Month    DS17887_Base+0x08  //�·�
#define  DS17887_Year     DS17887_Base+0x09  //��

#define  DS17887_Reg_A DS17887_Base+0x0A //���ƼĴ���A
#define  DS17887_Reg_B DS17887_Base+0x0B //���ƼĴ���B
#define  DS17887_Reg_C DS17887_Base+0x0C //���ƼĴ���C
#define  DS17887_Reg_D DS17887_Base+0x0D //���ƼĴ���D

/* ����DS17887���ƼĴ���ö�� */
typedef enum Ds17887CtlReg{
  Reg_A,
  Reg_B,
  Reg_C,
  Reg_D
}Ds17887CtlRegType;

/* ����DS17887���ߵķ������� */
typedef enum Ds17887BusDirection{
  DS17887_Out=1,
  DS17887_In=!DS17887_Out,
}Ds17887BusDirectionType;

/* ����DS17887�������ŵ����� */
typedef enum Ds17887CtlPins{
  DS17887_CS,
  DS17887_WR,
  DS17887_RD,
  DS17887_ALE,
  DS17887_KS,
  DS17887_RCLR  
}Ds17887CtlPinsType;

/* ����DS17887�����趨ֵ */
typedef enum Ds17887PinValue{
  DS17887_Set=1,
  DS17887_Reset=(!DS17887_Set)
}Ds17887PinValueType;

/* ����DS17887�������� */
typedef struct Ds17887Object{
  uint8_t ctlReg[4];    //���ƼĴ���
  uint8_t dateTime[6];  //��ȡ��ϵͳʱ��
  void (*SetCtlPin[6])(Ds17887PinValueType value);      //�������Ų���
  void (*WriteByte)(uint16_t data);     //дһ���ֽ�
  uint16_t (*ReadByte)(void);           //��һ���ֽ�
  void (*SetBusDirection)(Ds17887BusDirectionType direction);   //�������߷���
  void (*Delayus)(volatile uint32_t nTime);     //��ʱms����ָ��
}Ds17887ObjectType;

/* ����DS17887�������Ų�������ָ�� */
typedef void (*DS17887CtlPinOperationType)(Ds17887PinValueType value);
/* ����DS17887д���ݲ�������ָ�� */
typedef void (*WriteByteToDs17887Type)(uint16_t data);
/* ����DS17887�����ݲ�������ָ�� */
typedef uint16_t (*ReadByteFromDs17887Type)(void);
/* �����������ݵ�ַ���߷�����ָ�� */
typedef void (*Ds17887SetBusDirectionType)(Ds17887BusDirectionType direction);
/* ������ʱ��������ָ������ */
typedef void (*Ds17887DelayusType)(volatile uint32_t nTime);

/* ��ʵʱʱ��ģ���ȡʱ�� */
void GetDateTimeFromDs17887(Ds17887ObjectType *ds17887);
/* У׼DS17887��ʱ�� */
void CalibrationDs17887DateTime(Ds17887ObjectType *ds17887,uint16_t * dateTime);
/* ��DS17887���г�ʼ������ */
void Ds17887Initialization(Ds17887ObjectType *ds17887,
                           DS17887CtlPinOperationType *SetCtlPin,
                           WriteByteToDs17887Type WriteByte,
                           ReadByteFromDs17887Type ReadByte,
                           Ds17887SetBusDirectionType SetBusDirection,
                           Ds17887DelayusType Delayus);
/*********** (C) COPYRIGHT 1999-2019 Moonan Technology *********END OF FILE****/
