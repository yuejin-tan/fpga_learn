/******************************************************************************/
/** ģ�����ƣ���չ��������                                                   **/
/** �ļ����ƣ�bme680function.h                                               **/
/** ��    ����V1.0.0                                                         **/
/** ��    �飺����ʵ��BME680ѹ�����¶ȼ�ʪ�ȴ������Ĳ���                     **/
/**           BME680��55���ɲ����Ĵ���������26��У׼���ݣ���ַ���£�         **/
/**  +----------+----+----+----+----+----+----+----+----+----+--------+----+ **/
/**  |�Ĵ�����  |��ַ|bit7|bit6|bit5|bit4|bit3|bit2|bit1|bit0|��λ״̬|��д| **/
/**  +----------+----+----+----+----+----+----+----+----+----+--------+----+ **/
/**  |calib41   |0xF0|        calibration data[��41]         |�����趨|ֻ��| **/
/**  +----------+----+----+----+----+----+----+----+----+----+--------+----+ **/
/**  |calib26   |0xE1|        calibration data[��41]         |�����趨|ֻ��| **/
/**  +----------+----+----+----+----+----+----+----+----+----+--------+----+ **/
/**  | reset    |0xE0|             reset[7:0]                |  0x00  |ֻд| **/
/**  +----------+----+----+----+----+----+----+----+----+----+--------+----+ **/
/**  |   id     |0xD0|             chip_id[7:0]              |  0x60  |ֻ��| **/
/**  +----------+----+----+----+----+----+----+----+----+----+--------+----+ **/
/**  |calib25   |0xA1|        calibration data[��41]         |�����趨|ֻ��| **/
/**  +----------+----+----+----+----+----+----+----+----+----+--------+----+ **/
/**  |calib00   |0x88|        calibration data[��41]         |�����趨|ֻ��| **/
/**  +----------+----+----+----+----+----+----+----+----+----+--------+----+ **/
/**  |config    |0x75|              |  filter[2:0] |    |e[0]|  0x00  |��д| **/
/**  +----------+----+----+----+----+----+----+----+----+----+--------+----+ **/
/**  |ctrl_meas |0x74|  osrs_t[2:0] |  osrs_p[2:0] |mode[1:0]|  0x00  |��д| **/
/**  +----------+----+----+----+----+----+----+----+----+----+--------+----+ **/
/**  | status   |0x73|              |m[0]|                   |  0x00  |��д| **/
/**  +----------+----+----+----+----+----+----+----+----+----+--------+----+ **/
/**  |ctrl_hum  |0x72|    |e[0]|              |  osrs_h[2:0] |  0x00  |��д| **/
/**  +----------+----+----+----+----+----+----+----+----+----+--------+----+ **/
/**  |ctrl_gas_1|0x71|              |r[0]|    nb_conv<3:0>   |  0x00  |��д| **/
/**  +----------+----+----+----+----+----+----+----+----+----+--------+----+ **/
/**  |ctrl_gas_0|0x70|                   |o[0]|              |  0x00  |��д| **/
/**  +----------+----+----+----+----+----+----+----+----+----+--------+----+ **/
/**  |gas_wait_9|0x6D|           gas_wait_x[��10]            |  0x00  |��д| **/
/**  +----------+----+----+----+----+----+----+----+----+----+--------+----+ **/
/**  |gas_wait_0|0x64|           gas_wait_x[��10]            |  0x00  |��д| **/
/**  +----------+----+----+----+----+----+----+----+----+----+--------+----+ **/
/**  |res_heat_9|0x63|           res_heat_x[��10]            |  0x00  |��д| **/
/**  +----------+----+----+----+----+----+----+----+----+----+--------+----+ **/
/**  |res_heat_0|0x5A|           res_heat_x[��10]            |  0x00  |��д| **/
/**  +----------+----+----+----+----+----+----+----+----+----+--------+----+ **/
/**  |idac_heat9|0x59|           idac_heat_x[��10]           |  0x00  |��д| **/
/**  +----------+----+----+----+----+----+----+----+----+----+--------+----+ **/
/**  |idac_heat0|0x50|           idac_heat_x[��10]           |  0x00  |��д| **/
/**  +----------+----+----+----+----+----+----+----+----+----+--------+----+ **/
/**  |gas_lsb   |0x2B| hum_lsb |v[0]|s[0]|   gas_range<4:0>  |  0x00  |ֻ��| **/
/**  +----------+----+----+----+----+----+----+----+----+----+--------+----+ **/
/**  |gas_msb   |0x2A|               gas_msb<7:0>            |  0x00  |ֻ��| **/
/**  +----------+----+----+----+----+----+----+----+----+----+--------+----+ **/
/**  |hum_lsb   |0x26|               hum_lsb<7:0>            |  0x00  |ֻ��| **/
/**  +----------+----+----+----+----+----+----+----+----+----+--------+----+ **/
/**  |hum_msb   |0x25|               hum_msb<7:0>            |  0x80  |ֻ��| **/
/**  +----------+----+----+----+----+----+----+----+----+----+--------+----+ **/
/**  |temp_xlsb |0x24|    temp_xlsb<7:4> | 0  | 0  | 0  | 0  |  0x00  |ֻ��| **/
/**  +----------+----+----+----+----+----+----+----+----+----+--------+----+ **/
/**  |temp_lsb  |0x23|              temp_lsb<7:0>            |  0x00  |ֻ��| **/
/**  +----------+----+----+----+----+----+----+----+----+----+--------+----+ **/
/**  |temp_msb  |0x22|              temp_msb<7:0>            |  0x80  |ֻ��| **/
/**  +----------+----+----+----+----+----+----+----+----+----+--------+----+ **/
/**  |press_xlsb|0x21|   press_xlsb<7:4> | 0  | 0  | 0  | 0  |  0x00  |ֻ��| **/
/**  +----------+----+----+----+----+----+----+----+----+----+--------+----+ **/
/**  |press_lsb |0x20|             press_lsb<7:0>            |  0x00  |ֻ��| **/
/**  +----------+----+----+----+----+----+----+----+----+----+--------+----+ **/
/**  |press_msb |0x1F|             press_msb<7:0>            |  0x80  |ֻ��| **/
/**  +----------+----+----+----+----+----+----+----+----+----+--------+----+ **/
/**  |eas_status|0x1D|n[0]|m[0]|m[0]|    |     index<3:0>    |  0x00  |ֻ��| **/
/**  +----------+----+----+----+----+----+----+----+----+----+--------+----+ **/
/**  ���Ʋ����Ĵ���ѹ���������¶Ȳ��������ã�                                **/
/**    +-----------+----+------------+    +-----------+----+-------------+   **/
/**    |osrs_p[2:0]|����|    ����    |    |osrs_t[2:0]|����|     ����    |   **/
/**    +-----------+----+------------+    +-----------+----+-------------+   **/
/**    |   000     |  - |      -     |    |   000     |  - |     -       |   **/
/**    +-----------+----+------------+    +-----------+----+-------------+   **/
/**    |   001     | x1 |16bit/2.62Pa|    |   001     | x1 |16bit/0.0050C|   **/
/**    +-----------+----+------------+    +-----------+----+-------------+   **/
/**    |   010     | x2 |17bit/1.31Pa|    |   010     | x2 |17bit/0.0025C|   **/
/**    +-----------+----+------------+    +-----------+----+-------------+   **/
/**    |   011     | x4 |18bit/0.66Pa|    |   011     | x4 |18bit/0.0012C|   **/
/**    +-----------+----+------------+    +-----------+----+-------------+   **/
/**    |   100     | x8 |19bit/0.33Pa|    |   100     | x8 |19bit/0.0006C|   **/
/**    +-----------+----+------------+    +-----------+----+-------------+   **/
/**    |101,110,111| x16|20bit/0.16Pa|    |101,110,111| x16|20bit/0.0003C|   **/
/**    +-----------+----+------------+    +-----------+----+-------------+   **/
/**--------------------------------------------------------------------------**/
/**ʹ��˵����                                                                **/
/**    1������BME680ObjectType����ʵ�壬�����ú���BME680Initialization��ʼ�� **/
/**       ����ʵ�塣��ʼ��ʱ����Ҫ�������²�����                             **/
/**       bmpAddress,����I2C�ӿڱ�����豸��ַ��0xEC��0xEE��SPI�ӿ�ʱ����Ҫ  **/
/**       port,ͨѶ�ӿ����ͣ�I2C����SPI                                      **/
/**       t_sb,������ڣ����üĴ������ò���                                  **/
/**       filter,�������˲����ã����üĴ������ò���                          **/
/**       spi3W_en,�Ƿ�����3��SPI���ƣ����üĴ������ò���                    **/
/**       osrs_t,�¶Ȳ����������ã��������ƼĴ������ò���                    **/
/**       osrs_p,ѹ���������ȣ��������ƼĴ������ò���                        **/
/**       mode,��Դģʽ���������ƼĴ������ò���                              **/
/**       osrs_h,ʪ�Ȳ����������ã�ʪ�Ȳ������ƼĴ������ò���                **/
/**       Read,�����ݲ���ָ�룬�亯�����ͼ���������                          **/
/**       Write,д���ݲ���ָ�룬�亯�����ͼ���������                         **/
/**       Delayms,��ʱ����ָ�룬�亯�����ͼ���������                         **/
/**       ChipSelect,Ƭѡ����ָ�룬SPI�ӿڱ��衣I2C�ӿڲ���Ҫ������NULL      **/
/**    2��ʵ������void f(struct BME680Object *bmp,uint8_t regAddress,        **/
/**       uint8_t *rData,uint16_t rSize)�ĺ����������丳ֵ��BME680ObjectType **/
/**       ����ʵ���Read����ָ�롣                                           **/
/**    3��ʵ������void f(struct BME680Object *bmp,uint8_t regAddress,        **/
/**       uint8_t command)�ĺ����������丳ֵ��BME680ObjectType����ʵ��       **/
/**       ��Write����ָ�롣                                                  **/
/**    4��ʵ������void f(volatile uint32_t nTime)�ĺ����������丳ֵ��        **/
/**       BME680ObjectType����ʵ���Delayms����ָ�롣ʵ�ֺ�����ʱ��          **/
/**    5��ʵ������void f(bool en)�ĺ����������丳ֵBME680ObjectType����ʵ��  **/
/**       ��ChipSelcet����ָ�롣                                             **/
/**    6������GetBME680Measure����ʵ�����ݵĶ�ȡ��                           **/
/**--------------------------------------------------------------------------**/
/** �޸ļ�¼��                                                               **/
/**     �汾      ����              ����              ˵��                   **/
/**     V1.0.0  2019-06-01          ľ��              �����ļ�               **/
/**                                                                          **/
/******************************************************************************/ 

#ifndef __BME680FUNCTION_H
#define __BME680FUNCTION_H


#include "stdint.h"
#include "stdbool.h"

//��ѹ����������õ��������ͣ�0Ϊ�����ͣ�1Ϊ32λ����
#define BME680_COMPENSATION_SELECTED (0)

/* ����ѹ�������趨ö������ */
typedef enum BME680PresSample {
  BME680_PRES_SAMPLE_X0=0x00,    //ѹ��������
  BME680_PRES_SAMPLE_X1=0x04,    //ѹ������1�������˲�ʱ16λ
  BME680_PRES_SAMPLE_X2=0x08,    //ѹ������2�������˲�ʱ17λ
  BME680_PRES_SAMPLE_X4=0x0C,    //ѹ������4�������˲�ʱ18λ
  BME680_PRES_SAMPLE_X8=0x10,    //ѹ������8�������˲�ʱ19λ
  BME680_PRES_SAMPLE_X16=0x14    //ѹ������16�������˲�ʱ20λ
}BME680PresSampleType;

/* �����¶Ȳ����趨ö������ */
typedef enum BME680TempSample {
  BME680_TEMP_SAMPLE_X0=0x00,    //�¶Ȳ�����
  BME680_TEMP_SAMPLE_X1=0x20,    //�¶Ȳ���1�������˲�ʱ16λ
  BME680_TEMP_SAMPLE_X2=0x40,    //�¶Ȳ���2�������˲�ʱ17λ
  BME680_TEMP_SAMPLE_X4=0x60,    //�¶Ȳ���4�������˲�ʱ18λ
  BME680_TEMP_SAMPLE_X8=0x80,    //�¶Ȳ���8�������˲�ʱ19λ
  BME680_TEMP_SAMPLE_X16=0xA0    //�¶Ȳ���16�������˲�ʱ20λ
}BME680TempSampleType;

/* ����ʪ�Ȳ����趨ö������ */
typedef enum BME680HumiSample {
  BME680_HUMI_SAMPLE_X0=0x00,    //ʪ�Ȳ�����
  BME680_HUMI_SAMPLE_X1=0x01,    //ʪ�Ȳ���1��
  BME680_HUMI_SAMPLE_X2=0x02,    //ʪ�Ȳ���2��
  BME680_HUMI_SAMPLE_X4=0x03,    //ʪ�Ȳ���4��
  BME680_HUMI_SAMPLE_X8=0x04,    //ʪ�Ȳ���8��
  BME680_HUMI_SAMPLE_X16=0x05    //ʪ�Ȳ���16��
}BME680HumiSampleType;

/* ����IIR�˲�ϵ���趨ö������ */
typedef enum BME680IIRFilter {
  BME680_IIR_FILTER_COEFF_OFF=0x00,     //�ر��˲���0
  BME680_IIR_FILTER_COEFF_X1=0x04,      //�˲���ϵ��1
  BME680_IIR_FILTER_COEFF_X3=0x08,      //�˲���ϵ��3
  BME680_IIR_FILTER_COEFF_X7=0x0C,      //�˲���ϵ��7
  BME680_IIR_FILTER_COEFF_X15=0x10,     //�˲���ϵ��15
  BME680_IIR_FILTER_COEFF_X31=0x14,     //�˲���ϵ��31
  BME680_IIR_FILTER_COEFF_X63=0x18,     //�˲���ϵ��63
  BME680_IIR_FILTER_COEFF_X127=0x1C     //�˲���ϵ��127
}BME680IIRFilterType;

/* ����3��SPIʹ��ö������ */
typedef enum BME680SPI3wUse {
  BME680_SPI3W_DISABLE=0x00,   //������3��SPI
  BME680_SPI3W_ENABLE=0x01     //����3��SPI
}BME680SPI3wUseType;

/* ����ȴ�ʱ���趨ö������ */
typedef enum BME680GasWaitTime {
  BME680_GAS_WAIT_TIME1=0x00,   //���崫�����ȴ�ʱ��1��
  BME680_GAS_WAIT_TIME4=0x40,   //���崫�����ȴ�ʱ��4��
  BME680_GAS_WAIT_TIME16=0x80,  //���崫�����ȴ�ʱ��16��
  BME680_GAS_WAIT_TIME64=0xC0   //���崫�����ȴ�ʱ��64��
}BME680GasWaitTimeType;

/* ��������������趨�� */
typedef enum BME680HeaterSP {
  BME680_HEATER_SP0=0x00,       //�����������趨��0
  BME680_HEATER_SP1=0x01,       //�����������趨��1
  BME680_HEATER_SP2=0x02,       //�����������趨��2
  BME680_HEATER_SP3=0x03,       //�����������趨��3
  BME680_HEATER_SP4=0x04,       //�����������趨��4
  BME680_HEATER_SP5=0x05,       //�����������趨��5
  BME680_HEATER_SP6=0x06,       //�����������趨��6
  BME680_HEATER_SP7=0x07,       //�����������趨��7
  BME680_HEATER_SP8=0x08,       //�����������趨��8
  BME680_HEATER_SP9=0x09        //�����������趨��9
}BME680HeaterSPType;

/* ����SPIѡ���ڴ�ҳ��ö�� */
typedef enum BME680MemeryPage {
  BME680_MEMERY_PAGE0=0x00,     //SPI�ڴ�ҳ��0
  BME680_MEMERY_PAGE1=0x01      //SPI�ڴ�ҳ��1
}BME680MemeryPageType;

/* �����Դģʽ�趨ö������ */
typedef enum BME680PowerMode {
  BME680_POWER_SLEEP_MODE=0x00,         //˯��ģʽ
  BME680_POWER_FORCED_MODE=0x01,        //ǿ��ģʽ
  BME680_POWER_NORMAL_MODE=0x03         //����ģʽ
}BME680PowerModeType;

/* ����3��SPI�������ж�ʹ��ö������ */
typedef enum BME680SPI3wInt {
  BME680_SPI3W_INT_DISABLE=0x00,        //������3��SPI�������ж�
  BME680_SPI3W_INT_ENABLE=0x40          //����3��SPI�������ж�
}BME680SPI3wIntType;

/* �������������ֹͣö������ */
typedef enum BME680HeaterOff {
  BME680_HEATER_DISABLE=0x00,   //��ʹ�ܼ�����OFF
  BME680_HEATER_ENABLE=0x04     //ʹ�ܼ�����OFF
}BME680HeaterOffType;

/* �������崫��������ö������ */
typedef enum BME680GasRun {
  BME680_GAS_RUN_DISABLE=0x00,  //��������������
  BME680_GAS_RUN_ENABLE=0x10    //������������
}BME680GasRunType;

/* ����BMP280ͨѶ�ӿ�ö�� */
typedef enum BME680Port {
  BME680_I2C,
  BME680_SPI
}BME680PortType;

/* ������������������������ */
typedef struct BME680CalibParam {
  uint16_t dig_t1;      //�¶�����ϵ��1
  int16_t dig_t2;       //�¶�����ϵ��2
  int8_t dig_t3;        //�¶�����ϵ��3
  uint16_t dig_p1;      //ѹ������ϵ��1
  int16_t dig_p2;       //ѹ������ϵ��2
  int8_t dig_p3;        //ѹ������ϵ��3
  int16_t dig_p4;       //ѹ������ϵ��4
  int16_t dig_p5;       //ѹ������ϵ��5
  int8_t dig_p6;        //ѹ������ϵ��6
  int8_t dig_p7;        //ѹ������ϵ��7
  int16_t dig_p8;       //ѹ������ϵ��8
  int16_t dig_p9;       //ѹ������ϵ��9
  uint8_t dig_p10;      //ѹ������ϵ��10
  uint16_t dig_h1;      //ʪ������ϵ��1	
  uint16_t dig_h2;      //ʪ������ϵ��2
  int8_t dig_h3;        //ʪ������ϵ��3	
  int8_t dig_h4;        //ʪ������ϵ��4
  int8_t dig_h5;        //ʪ������ϵ��5
  uint8_t dig_h6;       //ʪ������ϵ��6
  int8_t dig_h7;        //ʪ������ϵ��7
  int8_t dig_g1;        //������������ϵ��1
  int16_t dig_g2;       //������������ϵ��2
  int8_t dig_g3;        //������������ϵ��3
  
#if BME680_COMPENSATION_SELECTED > (0)
  int32_t  t_fine;      //����ѹ���������¶�����,���β�������
#else
  float t_fine;         //����ѹ���������¶����ݣ����㲹������
#endif

  uint8_t res_heat_range;	//���������跶Χ
  int8_t res_heat_val;		//����������ֵ
  int8_t range_sw_err;		//ת������Χ
	
}BME680CalibParamType;

/* ����Ƭѡ�ź�ö�� */
typedef enum BME680CS {
  BME680CS_Enable,
  BME680CS_Disable
}BME680CSType;

/*����BME680��������*/
typedef struct BME680Object{
  uint8_t chipID;       //оƬID
  uint8_t bmeAddress;   //I2CͨѶʱ���豸��ַ
  uint8_t memeryPage;   //������SPI�ӿ�ʱ��¼��ǰ�������ڴ�ҳ
  uint8_t config;       //���üĴ���
  uint8_t ctrlMeas;     //�������ƼĴ���
  uint8_t ctrlHumi;     //ʪ�Ȳ������ƼĴ���
  uint8_t ctrlGas0;     //������ƼĴ���0
  uint8_t ctrlGas1;     //������ƼĴ���1
  uint8_t resHeat;
  uint8_t gasWait;
  
  BME680PortType port;  //�ӿ�ѡ��
  BME680CalibParamType caliPara;        //У׼����

#if BME680_COMPENSATION_SELECTED > (0)
  int32_t temperature;          //�¶�ֵ
  int32_t pressure;             //ѹ��ֵ
  int32_t humidity;             //ʪ��ֵ
  int32_t gasResistence;        //������������ֵ
  int32_t iaq;                  //��������ˮƽ
#else
  float temperature;            //�¶�ֵ
  float pressure;               //ѹ��ֵ
  float humidity;               //ʪ��ֵ
  float gasResistence;          //������������ֵ
  float iaq;                    //��������ˮƽ
#endif

  void (*Read)(struct BME680Object *bme,uint8_t regAddress,uint8_t *rData,uint16_t rSize);       //�����ݲ���ָ��
  void (*Write)(struct BME680Object *bme,uint8_t regAddress,uint8_t command);    //л���ݲ���ָ��
  void (*Delayms)(volatile uint32_t nTime);       //��ʱ����ָ��
  void (*ChipSelect)(BME680CSType cs);	//ʹ��SPI�ӿ�ʱ��Ƭѡ����
}BME680ObjectType;

/* ��������ݲ�������ָ������ */
typedef void (*BME680Read)(struct BME680Object *bme,uint8_t regAddress,uint8_t *rData,uint16_t rSize);
/* ����д���ݲ�������ָ������ */
typedef void (*BME680Write)(struct BME680Object *bme,uint8_t regAddress,uint8_t command);
/* ������ʱ��������ָ������ */
typedef void (*BME680Delayms)(volatile uint32_t nTime);
/* ����ʹ��SPI�ӿ�ʱ��Ƭѡ��������ָ������ */
typedef void (*BME680ChipSelect)(BME680CSType cs);

/*��ȡѹ�����¶�����*/
void GetBME680Measure(BME680ObjectType *bme);

/*ʵ��BME680��ʼ������*/
void BME680Initialization(BME680ObjectType *bme,                //BMP680����
                          uint8_t bmeAddress,                   //I2C�ӿ����豸��ַ
                          BME680PortType port,                  //�ӿ�ѡ��
                          BME680IIRFilterType filter,           //������
                          BME680SPI3wUseType spi3W_en,          //3��SPI����
                          BME680TempSampleType osrs_t,          //�¶Ⱦ���
                          BME680PresSampleType osrs_p,          //ѹ������
                          BME680SPI3wIntType spi3wint_en,       //3��SPI�жϿ���
                          BME680HumiSampleType osrs_h,          //ʪ�Ⱦ���
                          BME680GasRunType run_gas,             //������������
                          BME680HeaterSPType nb_conv,           //�������趨��ѡ��
                          BME680HeaterOffType heat_off,         //�������ر�
                          uint16_t duration,                    //TPHG����ѭ�����ڣ�ms��λ
                          uint8_t tempTarget,                   //��������Ŀ���¶�
                          BME680Read Read,                      //�����ݲ���ָ��
                          BME680Write Write,                    //д���ݲ���ָ��
                          BME680Delayms Delayms,                //��ʱ����ָ��
                          BME680ChipSelect ChipSelect           //Ƭѡ����ָ��
                         );

#endif
/*********** (C) COPYRIGHT 1999-2019 Moonan Technology *********END OF FILE****/
