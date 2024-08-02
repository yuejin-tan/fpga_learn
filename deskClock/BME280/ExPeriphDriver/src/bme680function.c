/******************************************************************************/
/** ģ�����ƣ���չ��������                                                   **/
/** �ļ����ƣ�bme680function.c                                               **/
/** ��    ����V1.0.0                                                         **/
/** ��    �飺����ʵ��BME280ѹ�����¶ȼ�ʪ�ȴ������Ĳ���                     **/
/**           BME280��55���ɲ����Ĵ���������26��У׼���ݣ���ַ���£�         **/
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
/**    1������bme680ObjectType����ʵ�壬�����ú���BME680Initialization��ʼ�� **/
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

#include "stdio.h"
#include "bme680function.h"

/*������ƼĴ�����ַ*/
#define REG_RESET       0xE0	//��λ�Ĵ���
#define REG_BME680_ID   0xD0	//�豸ID�Ĵ���
#define REG_CONFIG      0x75	//���üĴ���
#define REG_CTRL_MEAS   0x74	//�������ƼĴ���
#define REG_STATUS      0x73	//�ڴ�ҳ���üĴ���
#define REG_CTRL_HUM    0x72	//ʪ�Ȳ������ƼĴ���
#define REG_CTRL_GAS1   0x71	//������ƼĴ���1
#define REG_CTRL_GAS0   0x70	//������ƼĴ���0
#define REG_GAS_WAIT0   0x64	//������ȵȴ�ʱ��Ĵ���0
#define REG_GAS_WAIT1   0x65	//������ȵȴ�ʱ��Ĵ���1
#define REG_GAS_WAIT2   0x66	//������ȵȴ�ʱ��Ĵ���2
#define REG_GAS_WAIT3   0x67	//������ȵȴ�ʱ��Ĵ���3
#define REG_GAS_WAIT4   0x68	//������ȵȴ�ʱ��Ĵ���4
#define REG_GAS_WAIT5   0x69	//������ȵȴ�ʱ��Ĵ���5
#define REG_GAS_WAIT6   0x6A	//������ȵȴ�ʱ��Ĵ���6
#define REG_GAS_WAIT7   0x6B	//������ȵȴ�ʱ��Ĵ���7
#define REG_GAS_WAIT8   0x6C	//������ȵȴ�ʱ��Ĵ���8
#define REG_GAS_WAIT9   0x6D	//������ȵȴ�ʱ��Ĵ���9
#define REG_RES_HEAT_0  0x5A	//�������������Ĵ���0
#define REG_RES_HEAT_1  0x5B	//�������������Ĵ���1
#define REG_RES_HEAT_2  0x5C	//�������������Ĵ���2
#define REG_RES_HEAT_3  0x5D	//�������������Ĵ���3
#define REG_RES_HEAT_4  0x5E	//�������������Ĵ���4
#define REG_RES_HEAT_5  0x5F	//�������������Ĵ���5
#define REG_RES_HEAT_6  0x60	//�������������Ĵ���6
#define REG_RES_HEAT_7  0x61	//�������������Ĵ���7
#define REG_RES_HEAT_8  0x62	//�������������Ĵ���8
#define REG_RES_HEAT_9  0x63	//�������������Ĵ���9
#define REG_IDAC_HEAT_0 0x50	//������DAC�������0�Ĵ���
#define REG_IDAC_HEAT_1 0x51	//������DAC�������1�Ĵ���
#define REG_IDAC_HEAT_2 0x52	//������DAC�������2�Ĵ���
#define REG_IDAC_HEAT_3 0x53	//������DAC�������3�Ĵ���
#define REG_IDAC_HEAT_4 0x54	//������DAC�������4�Ĵ���
#define REG_IDAC_HEAT_5 0x55	//������DAC�������5�Ĵ���
#define REG_IDAC_HEAT_6 0x56	//������DAC�������6�Ĵ���
#define REG_IDAC_HEAT_7 0x57	//������DAC�������7�Ĵ���
#define REG_IDAC_HEAT_8 0x58	//������DAC�������8�Ĵ���
#define REG_IDAC_HEAT_9 0x59	//������DAC�������9�Ĵ���

/*����״̬�Ĵ�����ַ*/
#define REG_EAS_STATUS_0 0x1D	//״̬�Ĵ�����ַ

/*�������ݼĴ�����ַ*/
#define REG_TEMP_MSB 	0x22	//�¶�ֵ�Ĵ������ֽ�
#define REG_TEMP_LSB 	0x23	//�¶�ֵ�Ĵ������ֽ�
#define REG_TEMP_XLSB   0x24	//�¶�ֵ�Ĵ�������ֽ�

#define REG_HUMI_LSB	0x26	//ʪ��ֵ�Ĵ������ֽ�
#define REG_HUMI_MSB	0x25	//ʪ��ֵ�Ĵ������ֽ�

#define REG_PRESS_XLSB	0x21	//ѹ��ֵ�Ĵ�������ֽ�
#define REG_PRESS_LSB   0x20	//ѹ��ֵ�Ĵ������ֽ�
#define REG_PRESS_MSB   0x1F	//ѹ��ֵ�Ĵ������ֽ�

#define REG_GAS_MSB	0x2A				//�������ֵ�Ĵ������ֽ�
#define REG_GAS_LSB	0x2B				//�������ֵ�Ĵ������ֽ�
#define REG_GAS_RANGE	0x2B			//���巶Χֵ�Ĵ������ֽ�
#define REG_RANGE_SW_ERROR 0x04	//���巶Χת������Ĵ���
#define REG_RES_HEAT_RANGE 0x02	//���������跶Χ�Ĵ���
#define REG_RES_HEAT_VAL 0x00		//������ֵ�Ĵ���

/*����У׼���ݼĴ�����ַ,calib00-calib25:0x88-0xA1��26��;calib26-calib41:0xE1-0xF0��16��*/
#define REG_PAR_T2_LSB	0x8A         //�¶�У׼ϵ��2���з���16λ����
#define REG_PAR_T2_MSB	0x8B         //�¶�У׼ϵ��2���з���16λ����
#define REG_PAR_T3      0x8C         //�¶�У׼ϵ��3���з���16λ����
#define REG_PAR_P1_LSB	0x8E         //ѹ��У׼ϵ��1���޷���16λ����
#define REG_PAR_P1_MSB	0x8F         //ѹ��У׼ϵ��1���޷���16λ����
#define REG_PAR_P2_LSB	0x90         //ѹ��У׼ϵ��2���з���16λ����
#define REG_PAR_P2_MSB	0x91         //ѹ��У׼ϵ��2���з���16λ����
#define REG_PAR_P3      0x92         //ѹ��У׼ϵ��3���з���16λ����
#define REG_PAR_P4_LSB	0x94         //ѹ��У׼ϵ��4���з���16λ����
#define REG_PAR_P4_MSB	0x95         //ѹ��У׼ϵ��4���з���16λ����
#define REG_PAR_P5_LSB	0x96         //ѹ��У׼ϵ��5���з���16λ����
#define REG_PAR_P5_MSB	0x97         //ѹ��У׼ϵ��5���з���16λ����
#define REG_PAR_P7      0x98         //ѹ��У׼ϵ��7���з���16λ����
#define REG_PAR_P6      0x99         //ѹ��У׼ϵ��6���з���16λ����
#define REG_PAR_P8_LSB	0x9C         //ѹ��У׼ϵ��8���з���16λ����
#define REG_PAR_P8_MSB	0x9D         //ѹ��У׼ϵ��8���з���16λ����
#define REG_PAR_P9_LSB	0x9E         //ѹ��У׼ϵ��9���з���16λ����
#define REG_PAR_P9_MSB	0x9F         //ѹ��У׼ϵ��9���з���16λ����
#define REG_PAR_P10     0xA0         //ѹ��У׼ϵ��10���з���16λ����

#define REG_PAR_H2_MSB          0xE1         //ʪ��У׼ϵ��2���з���16λ����
#define REG_PAR_H1H2_LSB        0xE2         //ʪ��У׼ϵ��2���з���16λ����
#define REG_PAR_H1_MSB		0xE3         //ʪ��У׼ϵ��1���޷���8λ����
#define REG_PAR_H3              0xE4         //ʪ��У׼ϵ��3���޷���8λ����
#define REG_PAR_H4              0xE5         //ʪ��У׼ϵ��4���з���16λ����
#define REG_PAR_H5              0xE6         //ʪ��У׼ϵ��5���з���16λ����
#define REG_PAR_H6              0xE7         //ʪ��У׼ϵ��6���з���8λ����
#define REG_PAR_H7              0xE8         //ʪ��У׼ϵ��7���з���8λ����
#define REG_PAR_T1_LSB		0xE9         //�¶�У׼ϵ��1���޷���16λ����
#define REG_PAR_T1_MSB		0xEA         //�¶�У׼ϵ��1���޷���16λ����
#define REG_PAR_G2_LSB		0xEB         //����У׼ϵ��1���޷���16λ����
#define REG_PAR_G2_MSB		0xEC         //����У׼ϵ��1���޷���16λ����
#define REG_PAR_G1              0xED         //����У׼ϵ��1���޷���16λ����
#define REG_PAR_G3              0xEE         //����У׼ϵ��1���޷���16λ����

#define REG_CALIB_START_ADDR1	0x8A            //��һ��У׼���ݵ���ʼ��ַ
#define REG_CALIB_START_ADDR2	0xE1		//�ڶ���У׼���ݵ���ʼ��ַ

/*����У׼���ݼĴ���ö��*/
enum calib1 {
  PAR_T2_LSB,           //�¶�У׼ϵ��2���з���16λ����
  PAR_T2_MSB,           //�¶�У׼ϵ��2���з���16λ����
  PAR_T3,               //�¶�У׼ϵ��3���з���16λ����
  PAR_SPARE_1,          //ϵͳ����
  PAR_P1_LSB,           //ѹ��У׼ϵ��1���޷���16λ����
  PAR_P1_MSB,           //ѹ��У׼ϵ��1���޷���16λ����
  PAR_P2_LSB,           //ѹ��У׼ϵ��2���з���16λ����
  PAR_P2_MSB,           //ѹ��У׼ϵ��2���з���16λ����
  PAR_P3,               //ѹ��У׼ϵ��3���з���16λ����
  PAR_SPARE_2,          //ϵͳ����
  PAR_P4_LSB,           //ѹ��У׼ϵ��4���з���16λ����
  PAR_P4_MSB,           //ѹ��У׼ϵ��4���з���16λ����
  PAR_P5_LSB,           //ѹ��У׼ϵ��5���з���16λ����
  PAR_P5_MSB,           //ѹ��У׼ϵ��5���з���16λ����
  PAR_P7,               //ѹ��У׼ϵ��7���з���16λ����
  PAR_P6,               //ѹ��У׼ϵ��6���з���16λ����
  PAR_SPARE_3,          //ϵͳ����
  PAR_SPARE_4,          //ϵͳ����
  PAR_P8_LSB,           //ѹ��У׼ϵ��8���з���16λ����
  PAR_P8_MSB,           //ѹ��У׼ϵ��8���з���16λ����
  PAR_P9_LSB,           //ѹ��У׼ϵ��9���з���16λ����
  PAR_P9_MSB,           //ѹ��У׼ϵ��9���з���16λ����
  PAR_P10,              //ѹ��У׼ϵ��10���з���16λ����
  REG_CALIB_LENGTH1     //��һ��У׼���ݵĳ���
};

/*����У׼���ݼĴ���ö��*/
enum calib2 {
  PAR_H2_MSB,             //ʪ��У׼ϵ��2���з���16λ����
  PAR_H1H2_LSB,           //ʪ��У׼ϵ��2���з���16λ����
  PAR_H1_MSB,             //ʪ��У׼ϵ��1���޷���8λ����
  PAR_H3,                 //ʪ��У׼ϵ��3���޷���8λ����
  PAR_H4,                 //ʪ��У׼ϵ��4���з���16λ����
  PAR_H5,                 //ʪ��У׼ϵ��5���з���16λ����
  PAR_H6,                 //ʪ��У׼ϵ��6���з���8λ����
  PAR_H7,                 //ʪ��У׼ϵ��7���з���8λ����
  PAR_T1_LSB,             //�¶�У׼ϵ��1���޷���16λ����
  PAR_T1_MSB,             //�¶�У׼ϵ��1���޷���16λ����
  PAR_G2_LSB,             //����У׼ϵ��1���޷���16λ����
  PAR_G2_MSB,             //����У׼ϵ��1���޷���16λ����
  PAR_G1,                 //����У׼ϵ��1���޷���16λ����
  PAR_G3,                 //����У׼ϵ��1���޷���16λ����
  REG_CALIB_LENGTH2       //�ڶ���У׼���ݵĳ���
};

/*����������ݼĴ���ö��*/
enum tphMeas {
  PRESS_MSB,      //ѹ��ֵ�Ĵ������ֽ�
  PRESS_LSB,      //ѹ��ֵ�Ĵ������ֽ�
  PRESS_XLSB,     //ѹ��ֵ�Ĵ�������ֽ�
  TEMP_MSB,       //�¶�ֵ�Ĵ������ֽ�
  TEMP_LSB,       //�¶�ֵ�Ĵ������ֽ�
  TEMP_XLSB,      //�¶�ֵ�Ĵ�������ֽ�
  HUMI_MSB,       //ʪ��ֵ�Ĵ������ֽ�
  HUMI_LSB,       //ʪ��ֵ�Ĵ������ֽ�
  REG_TPH_LENGTH  //TPH���ݼĴ����ֽڳ���
};

/*����������ݼĴ���ö��*/
enum gasMeas {
  GAS_MSB,        //�������ֵ���ֽڼĴ���
  GAS_LSB,        //�������ֵ���ֽڼĴ���
  REG_GAS_LENGTH  //����Ĵ����ֽڳ���
};

/*�ж϶����Ƿ���Ч*/
static bool ObjectIsValid(BME680ObjectType *bme);
/*��BME680�Ĵ���дһ���ֽ�*/
static void WriteBME680Register(BME680ObjectType *bme,uint8_t regAddress,uint8_t command);
/*��BME680�Ĵ�����ȡ����*/
static uint8_t ReadBME680Register(BME680ObjectType *bme,uint8_t regAddress,uint8_t *rDatas,uint16_t rSize);
/*BME680�����λ*/
static void BME680SoftReset(BME680ObjectType *bme);
/*��ȡУ׼����*/
static void GetBME680CalibrationData(BME680ObjectType *bme);
/*ȱʡƬѡ������*/
static void BME680ChipSelectDefault(BME680CSType cs);
/*��SPIģʽ�£���ȡ��ǰ�ڴ�ҳ*/
static void GetMemeryPageNumber(BME680ObjectType *bme);
/*��SPIģʽ�£����õ�ǰ�ڴ�ҳ*/
static void SetMemeryPageNumber(BME680ObjectType *bme,uint8_t regAdd);
/*�����¶ȡ�ѹ����ʪ�ȿ��ƼĴ���*/
static void ConfigControlRegister(BME680ObjectType *bme,                //BMP280����
                                  BME680IIRFilterType filter,           //������
                                  BME680SPI3wUseType spi3W_en,          //3��SPI����
                                  BME680TempSampleType osrs_t,          //�¶Ⱦ���
                                  BME680PresSampleType osrs_p,          //ѹ������
                                  BME680SPI3wIntType spi3wint_en,       //3��SPI�жϿ���
                                  BME680HumiSampleType osrs_h,          //ʪ�Ⱦ���
                                  BME680GasRunType run_gas,             //������������
                                  BME680HeaterSPType nb_conv,           //�������趨��ѡ��
                                  BME680HeaterOffType heat_off,         //�������ر�
                                  uint8_t waitTime,                     //�ȴ�ʱ�䣬ȡֵ0��63��factorΪ�䱶��
                                  uint8_t tempTarget                    //��������Ŀ���¶�
                                 );

#if BME680_COMPENSATION_SELECTED > (0)
/*����ʵ���¶�ֵ,����0.01GegC*/
static int32_t CompensateTemperature(BME680ObjectType *bme,uint32_t adcCode);
/*����ʵ�ʵ�ѹ��ֵ*/
static int32_t CompensatePressure(BME680ObjectType *bme,uint32_t adcCode);
/*����ʵ�ʵ�ʪ��ֵ*/
static int32_t CompensateHumidity(BME680ObjectType *bme,uint32_t adcCode);
/*����ʵ�ʵ��������ֵ*/
static int32_t CompensateGasResistance(BME680ObjectType *bme,uint32_t adcCode,uint16_t gasRange);
#else
/*����ʵ���¶�ֵ,����0.01GegC*/
static float CompensateTemperature(BME680ObjectType *bme,uint32_t adcCode);
/*����ʵ�ʵ�ѹ��ֵ��������ΪQ24.8��ʽ*/
static float CompensatePressure(BME680ObjectType *bme,uint32_t adcCode);
/*����ʵ�ʵ�ʪ��ֵ��������ΪQ22.10��ʽ*/
static float CompensateHumidity(BME680ObjectType *bme,uint32_t adcCode);
/*����ʵ�ʵ��������ֵ*/
static float CompensateGasResistance(BME680ObjectType *bme,uint32_t adcCode,uint16_t gasRange);
#endif
/*�������������ֵ,���õ�res_wait_x�Ĵ�����ֵ*/
static uint8_t CompensateHeaterResistance(BME680ObjectType *bme,uint16_t tempTarget);
/*����������ȴ�ʱ�䣬�赽gas_wait_x�Ĵ�����ֵ*/
static uint8_t CalcHeaterWaitTime(uint16_t waitTime);
/*��������������Ĵ���*/
static void ConfigGasHeater(BME680ObjectType *bme,BME680HeaterSPType nbconv,uint16_t tempTarget,uint16_t waitTime);
/*������ȵȴ�ʱ��*/
static uint16_t CalcProfileDuration(BME680ObjectType *bme,
                                    uint16_t duration,                  //TPHG����ѭ������
                                    BME680TempSampleType osrs_t,        //�¶Ⱦ���
                                    BME680PresSampleType osrs_p,        //ѹ������
                                    BME680HumiSampleType osrs_h         //ʪ�Ⱦ���
                                   );

/*���ô�������Դģʽ*/
static uint8_t SetSensorPowerMode(BME680ObjectType *bme,BME680PowerModeType powerMode);
/*��ȡ��������Դģʽ*/
static uint8_t GetSensorPowerMode(BME680ObjectType *bme);


/*��ȡѹ�����¶�����*/
void GetBME680Measure(BME680ObjectType *bme)
{
  uint8_t regAddress;
  uint8_t tphDatas[8];
  uint8_t gasDatas[8];
  
  uint32_t adcTemp=0;
  uint32_t adcPres=0;
  uint32_t adcHumi=0;
  uint32_t adcGas=0;
  uint16_t gasRange;		//���������Χ
	
  if(!ObjectIsValid(bme))
  {
    return;
  }
  
  /*��ȡ״̬���ADת���Ƿ����*/
  uint8_t status=0xFF;
  ReadBME680Register(bme,REG_EAS_STATUS_0,&status,1);
	
  if(status&0x80)
  {
    regAddress=REG_PRESS_MSB;
    ReadBME680Register(bme,regAddress,tphDatas,REG_TPH_LENGTH);
    
    regAddress=REG_GAS_MSB;
    ReadBME680Register(bme,regAddress,gasDatas,REG_GAS_LENGTH);

    /*�����¶ȡ�ѹ����ʪ�ȵ�ADCֵ*/
    adcTemp=((uint32_t)tphDatas[TEMP_MSB]<<16)+((uint32_t)tphDatas[TEMP_LSB]<<8)+(uint32_t)tphDatas[TEMP_XLSB];
    adcPres=((uint32_t)tphDatas[PRESS_MSB]<<16)+((uint32_t)tphDatas[PRESS_LSB]<<8)+(uint32_t)tphDatas[PRESS_XLSB];
    adcHumi=((uint32_t)tphDatas[HUMI_MSB]<<8)+(uint32_t)tphDatas[HUMI_LSB];
    
    adcGas=((uint32_t)gasDatas[GAS_MSB]<<8)+(uint32_t)gasDatas[GAS_LSB];
  
    gasRange=(uint16_t)(gasDatas[GAS_LSB]&0x0F);
	
    adcTemp=(adcTemp>>4);
    adcPres=(adcPres>>4);
    adcGas=(adcGas>>6);
  
    /*����ѹ�����¶ȵ�������ֵ*/
    bme->temperature=CompensateTemperature(bme,adcTemp);
  
    bme->pressure=CompensatePressure(bme,adcPres);
  
    bme->humidity=CompensateHumidity(bme,adcHumi);
	
    bme->gasResistence=CompensateGasResistance(bme,adcGas,gasRange);
  }
}

/*ʵ��BME680��ʼ������*/
void BME680Initialization(BME680ObjectType *bme,                //BMP280����
                          uint8_t bmeAddress,                   //I2C�ӿ����豸��ַ
                          BME680PortType port,                  //�ӿ�ѡ��
                          BME680IIRFilterType filter,           //������
                          BME680SPI3wUseType spi3W_en,          //3��SPI����
                          BME680TempSampleType osrs_t,          //�¶Ⱦ���
                          BME680PresSampleType osrs_p,          //ѹ������
                          BME680SPI3wIntType spi3wint_en,       //3��SPI�жϿ���
                          BME680HumiSampleType osrs_h,		//ʪ�Ⱦ���
                          BME680GasRunType run_gas,             //������������
                          BME680HeaterSPType nb_conv,           //�������趨��ѡ��
                          BME680HeaterOffType heat_off,         //�������ر�
                          uint16_t duration,                    //TPHG����ѭ�����ڣ�ms��λ
                          uint8_t tempTarget,                   //��������Ŀ���¶�
                          BME680Read Read,                      //�����ݲ���ָ��
                          BME680Write Write,                    //д���ݲ���ָ��
                          BME680Delayms Delayms,                //��ʱ����ָ��
                          BME680ChipSelect ChipSelect           //Ƭѡ����ָ��
                         )
{
  uint8_t try_count = 5;
  uint8_t regValue=0;
	
  if((bme==NULL)||(Read==NULL)||(Write==NULL)||(Delayms==NULL))
  {
    return;
  }
  bme->Read=Read;
  bme->Write=Write;
  bme->Delayms=Delayms;
	
  bme->port=port;
  if(bme->port==BME680_I2C)
  {
    if((bmeAddress==0xEC)||(bmeAddress==0xEE))
    {
      bme->bmeAddress=bmeAddress;
    }
    else if((bmeAddress==0x76)||(bmeAddress==0x77))
    {
      bme->bmeAddress=(bmeAddress<<1);
    }
    else
    {
      return;
    }
    bme->ChipSelect=NULL;
  }
  else
  {
    if(ChipSelect!=NULL)
    {
      bme->ChipSelect=ChipSelect;
    }
    else
    {
      bme->ChipSelect=BME680ChipSelectDefault;
    }
  }
	
  bme->chipID=0x00;
  bme->pressure=0.0;
  bme->temperature=25.0;
  bme->humidity=0.0;
  bme->bmeAddress=0x00;
  bme->caliPara.t_fine=0;
		
  if(!ObjectIsValid(bme))
  {
    return;
  }
  	
  while(try_count--)
  {
		ReadBME680Register(bme,REG_BME680_ID,&regValue,1);
    bme->chipID=regValue;
    if(0x61==bme->chipID)
    {
      BME680SoftReset(bme);
      
      break;
    }
  }
  
  if(try_count)
  {
    uint8_t waitTime;
    waitTime=CalcProfileDuration(bme,duration,osrs_t,osrs_p,osrs_h);
		
    //���ƼĴ�������
    ConfigControlRegister(bme,filter,spi3W_en,osrs_t,osrs_p,spi3wint_en,osrs_h,run_gas,nb_conv,heat_off,waitTime,tempTarget);
		
    //��ȡУ׼ֵ
    GetBME680CalibrationData(bme);
  }
}

/*��ȡУ׼����*/
static void GetBME680CalibrationData(BME680ObjectType *bme)
{
  uint8_t calib1Data[REG_CALIB_LENGTH1];
  uint8_t calib2Data[REG_CALIB_LENGTH2];
  
  if(!ObjectIsValid(bme))
  {
    return;
  }
	
  ReadBME680Register(bme,REG_CALIB_START_ADDR1,calib1Data,REG_CALIB_LENGTH1);
  ReadBME680Register(bme,REG_CALIB_START_ADDR2,calib2Data,REG_CALIB_LENGTH2);
	

  bme->caliPara.dig_t1=(uint16_t)(((uint16_t)calib2Data[PAR_T1_MSB]<<8)+((uint16_t)calib2Data[PAR_T1_LSB]));
  bme->caliPara.dig_t2=(int16_t)(((int16_t)calib1Data[PAR_T2_MSB]<<8)+((int16_t)calib1Data[PAR_T2_LSB]));
  bme->caliPara.dig_t3=(int16_t)calib1Data[PAR_T3];
  
  bme->caliPara.dig_p1=(uint16_t)(((uint16_t)calib1Data[PAR_P1_MSB]<<8)+((uint16_t)calib1Data[PAR_P1_LSB]));
  bme->caliPara.dig_p2=(int16_t)(((int16_t)calib1Data[PAR_P2_MSB]<<8)+((int16_t)calib1Data[PAR_P2_LSB]));
  bme->caliPara.dig_p3=(int16_t)calib1Data[PAR_P3];
  bme->caliPara.dig_p4=(int16_t)(((int16_t)calib1Data[PAR_P4_MSB]<<8)+((int16_t)calib1Data[PAR_P4_LSB]));
  bme->caliPara.dig_p5=(int16_t)(((int16_t)calib1Data[PAR_P5_MSB]<<8)+((int16_t)calib1Data[PAR_P5_LSB]));
  bme->caliPara.dig_p6=(int16_t)calib1Data[PAR_P6];
  bme->caliPara.dig_p7=(int16_t)calib1Data[PAR_P7];
  bme->caliPara.dig_p8=(int16_t)(((int16_t)calib1Data[PAR_P8_MSB]<<8)+((int16_t)calib1Data[PAR_P8_LSB]));
  bme->caliPara.dig_p9=(int16_t)(((int16_t)calib1Data[PAR_P9_MSB]<<8)+((int16_t)calib1Data[PAR_P9_LSB]));
  bme->caliPara.dig_p10=(int16_t)calib1Data[PAR_P10];

  bme->caliPara.dig_h1=(int16_t)(((int16_t)calib2Data[PAR_H1_MSB]<<4)+(((int16_t)calib2Data[PAR_H1H2_LSB])&0x0F));
  bme->caliPara.dig_h2=(int16_t)(((int16_t)calib2Data[PAR_H2_MSB]<<4)+((int16_t)calib2Data[PAR_H1H2_LSB]>>4));
  bme->caliPara.dig_h3=calib2Data[PAR_H3];
  bme->caliPara.dig_h4=calib2Data[PAR_H4];
  bme->caliPara.dig_h5=calib2Data[PAR_H5];
  bme->caliPara.dig_h6=calib2Data[PAR_H6];
  bme->caliPara.dig_h7=calib2Data[PAR_H7];
  
  bme->caliPara.dig_g1=calib2Data[PAR_G1];
  bme->caliPara.dig_g2=(int16_t)(((int16_t)calib2Data[PAR_G2_MSB]<<8)+((int16_t)calib2Data[PAR_G2_LSB]));
  bme->caliPara.dig_g3=calib2Data[PAR_G3];
	
  uint8_t regValue;
	
  ReadBME680Register(bme,REG_RANGE_SW_ERROR,&regValue,1);
  bme->caliPara.range_sw_err=regValue;
  
  ReadBME680Register(bme,REG_RES_HEAT_VAL,&regValue,1);
  bme->caliPara.res_heat_val=regValue;
  
  ReadBME680Register(bme,REG_RES_HEAT_RANGE,&regValue,1);
  bme->caliPara.res_heat_range=regValue&0x30;
}

/*�����¶ȡ�ѹ����ʪ�ȿ��ƼĴ���*/
static void ConfigControlRegister(BME680ObjectType *bme,                //BMP280����
                                  BME680IIRFilterType filter,           //������
                                  BME680SPI3wUseType spi3W_en,          //3��SPI����
                                  BME680TempSampleType osrs_t,          //�¶Ⱦ���
                                  BME680PresSampleType osrs_p,          //ѹ������
                                  BME680SPI3wIntType spi3wint_en,       //3��SPI�жϿ���
                                  BME680HumiSampleType osrs_h,          //ʪ�Ⱦ���
                                  BME680GasRunType run_gas,             //������������
                                  BME680HeaterSPType nb_conv,           //�������趨��ѡ��
                                  BME680HeaterOffType heat_off,         //�������ر�
                                  uint8_t waitTime,                     //�ȴ�ʱ�䣬ȡֵ0��63��factorΪ�䱶��
                                  uint8_t tempTarget                    //��������Ŀ���¶�
                                 )
{
  uint8_t command=0; 
  uint8_t regValue[6];
  BME680PowerModeType mode;
	
  if(!ObjectIsValid(bme))
  {
    return;
  }
	
  //����1�����ò���ģʽΪSLEEP MODE
  do
  {
  mode=(BME680PowerModeType)SetSensorPowerMode(bme,BME680_POWER_SLEEP_MODE);
  }while(mode!=BME680_POWER_SLEEP_MODE);
	
  //����2�����ò������ƼĴ���:�¶�20λ��ѹ��20λ����Դ����ģʽ
  command=(uint8_t)osrs_t|(uint8_t)osrs_p|(uint8_t)mode;
  WriteBME680Register(bme,REG_CTRL_MEAS,command);
  
  //����2������ʪ�Ȳ������ƼĴ�����3��SPI�жϲ����ã�ʪ�Ⱦ���16λ
  command=(uint8_t)spi3wint_en|(uint8_t)osrs_h;
  WriteBME680Register(bme,REG_CTRL_HUM,command);
	
  //����3���������üĴ���:IIR�˲�ϵ��16����ʹ��SPI3��ͨѶ
  command=(uint8_t)filter|(uint8_t)spi3W_en;
  WriteBME680Register(bme,REG_CONFIG,command);
	
  //����4����������Ĵ���0���������Ƿ�����
  command=heat_off;
  WriteBME680Register(bme,REG_CTRL_GAS0,command);
	
  //����5������������ƼĴ���1���������к��趨��
  command=(uint8_t)run_gas|(uint8_t)nb_conv;
  WriteBME680Register(bme,REG_CTRL_GAS1,command);
	
  //����6����������������Ĵ���
  ConfigGasHeater(bme,nb_conv,tempTarget,waitTime);
	
  bme->Delayms(10);
	
  //����7�����ò���ģʽΪFORCED MODE
  do
  {
    mode=(BME680PowerModeType)SetSensorPowerMode(bme,BME680_POWER_FORCED_MODE);
  }while(mode!=BME680_POWER_FORCED_MODE);
	
  bme->Delayms(10);
	
  //ͬʱ��ȡ�������1��0x70�����������1��0x71����ʪ�ȿ��ƣ�0x72����״̬��0x73�����������ƣ�0x74�������ã�0x75���Ĵ���ֵ
  ReadBME680Register(bme,REG_CTRL_GAS0,regValue,0);
  bme->ctrlGas0=regValue[0];
  bme->ctrlGas1=regValue[1];
  bme->ctrlHumi=regValue[2];
  bme->memeryPage=regValue[3];
  bme->ctrlMeas=regValue[4];
  bme->config=regValue[5];	
}

/*BME680�����λ*/
static void BME680SoftReset(BME680ObjectType *bme)
{
  uint8_t command=0xB6;
  
  if(ObjectIsValid(bme))
  {
    WriteBME680Register(bme,REG_RESET,command);
  }
	
  GetMemeryPageNumber(bme);
}

/*��SPIģʽ�£���ȡ��ǰ�ڴ�ҳ*/
static void GetMemeryPageNumber(BME680ObjectType *bme)
{
  uint8_t status=0xEF;
  if(bme->port==BME680_SPI)
  {
    ReadBME680Register(bme,REG_STATUS,&status,1);
    status=status&0x10;
  }
	
  bme->memeryPage=status;
}

/*��SPIģʽ�£����õ�ǰ�ڴ�ҳ*/
static void SetMemeryPageNumber(BME680ObjectType *bme,uint8_t regAdd)
{
  uint8_t status=0xFF;
  uint8_t setPage=0xFF;
  
  if(regAdd>0x7F)
  {
    setPage=BME680_MEMERY_PAGE0;
  }
  else
  {
    setPage=BME680_MEMERY_PAGE1;
  }
  
  GetMemeryPageNumber(bme);
  
  if(setPage!=bme->memeryPage)
  {
    if(bme->port==BME680_SPI)
    {
      ReadBME680Register(bme,REG_STATUS,&status,1);
      status=status&0xEF;
    }
		
    setPage=status|(setPage&0x10);
		
    WriteBME680Register(bme,REG_STATUS,setPage);
  }
  
  GetMemeryPageNumber(bme);
}

/*��BME680�Ĵ�����ȡ����*/
static uint8_t ReadBME680Register(BME680ObjectType *bme,uint8_t regAddress,uint8_t *rDatas,uint16_t rSize)
{
  uint8_t bmeError=0xFF;
  
  if(ObjectIsValid(bme))
  {
    if(bme->port==BME680_SPI)
    {
      bme->ChipSelect(BME680CS_Enable);
      bme->Delayms(1);
      SetMemeryPageNumber(bme,regAddress);
      regAddress |= 0x80;
      bme->Delayms(1);
      bme->Read(bme,regAddress,rDatas,rSize);
      bme->Delayms(1);
      bme->ChipSelect(BME680CS_Disable);
    }
    else
    {
      bme->Read(bme,regAddress,rDatas,rSize);
    }
  
    bmeError=0x00;
  }

  return bmeError;
}

/* ��BME680�Ĵ���дһ���ֽ� */
static void WriteBME680Register(BME680ObjectType *bme,uint8_t regAddress,uint8_t command)
{
  if(ObjectIsValid(bme))
  {
    if(bme->port==BME680_SPI)
    {
      bme->ChipSelect(BME680CS_Enable);
      bme->Delayms(1);
      SetMemeryPageNumber(bme,regAddress);
      regAddress&=0x7F;
      bme->Delayms(1);
      bme->Write(bme,regAddress,command);
      bme->Delayms(1);
      bme->ChipSelect(BME680CS_Disable);
    }
    else
    {
      bme->Write(bme,regAddress,command);
    }
  }
}

/*������ȵȴ�ʱ��*/
static uint16_t CalcProfileDuration(BME680ObjectType *bme,
                                    uint16_t duration,  //TPHG����ѭ������
                                    BME680TempSampleType osrs_t,        //�¶Ⱦ���
                                    BME680PresSampleType osrs_p,        //ѹ������
                                    BME680HumiSampleType osrs_h //ʪ�Ⱦ���
                                   )
{
  uint32_t tphDur;
  uint32_t measCycles;
  uint8_t osrsMeasCycles[6] = {0, 1, 2, 4, 8, 16};
  uint16_t heatDur;

  measCycles=osrsMeasCycles[osrs_t>>5];
  measCycles+=osrsMeasCycles[osrs_p>>2];
  measCycles+=osrsMeasCycles[osrs_h];

  /* TPH�������� */
  tphDur = measCycles * 1963;
  tphDur += 477 * 4;	//TPH����
  tphDur += 477 * 5;	//�������
  tphDur += 500;			//��������
  tphDur /= 1000; 		//תΪ����

  tphDur += 1;				//1ms����ʱ��

  heatDur=duration-(uint16_t)tphDur;	//ʣ��δ����ʱ��
	
  return heatDur;
}

/*��������������Ĵ���*/
static void ConfigGasHeater(BME680ObjectType *bme,BME680HeaterSPType nbconv,uint16_t tempTarget,uint16_t waitTime)
{
  uint8_t regAdd; 
  uint8_t regValue;
	
  uint8_t gasWaitAdd[10]={REG_GAS_WAIT0,REG_GAS_WAIT1,
                          REG_GAS_WAIT2,REG_GAS_WAIT3,
                          REG_GAS_WAIT4,REG_GAS_WAIT5,
                          REG_GAS_WAIT6,REG_GAS_WAIT7,
                          REG_GAS_WAIT8,REG_GAS_WAIT9};
  uint8_t resHeatAdd[10]={REG_RES_HEAT_0,REG_RES_HEAT_1,
                          REG_RES_HEAT_2,REG_RES_HEAT_3,
                          REG_RES_HEAT_4,REG_RES_HEAT_5,
                          REG_RES_HEAT_6,REG_RES_HEAT_7,
                          REG_RES_HEAT_8,REG_RES_HEAT_9};
  
  regAdd=resHeatAdd[nbconv];
  regValue=CompensateHeaterResistance(bme,tempTarget);
  WriteBME680Register(bme,regAdd,regValue);
  
  regAdd=gasWaitAdd[nbconv];
  regValue=CalcHeaterWaitTime(waitTime);
  WriteBME680Register(bme,regAdd,regValue);
  
  ReadBME680Register(bme,resHeatAdd[nbconv],&regValue,1);
  bme->resHeat=regValue;
  
  ReadBME680Register(bme,gasWaitAdd[nbconv],&regValue,1);
  bme->gasWait=regValue;
}

/*���ô�������Դģʽ*/
static uint8_t SetSensorPowerMode(BME680ObjectType *bme,BME680PowerModeType powerMode)
{
  uint8_t currentMode;
  uint8_t regValue;
  uint8_t regAddr = REG_CTRL_MEAS;
  
  currentMode=GetSensorPowerMode(bme);
  
  if(powerMode!=currentMode)
  {
    regValue=(bme->ctrlMeas&0xFC)|powerMode;
    WriteBME680Register(bme,regAddr,regValue);
    bme->Delayms(10);
    currentMode=GetSensorPowerMode(bme);
  }

  return currentMode;
}

/*��ȡ��������Դģʽ*/
static uint8_t GetSensorPowerMode(BME680ObjectType *bme)
{
  uint8_t mode;
  uint8_t regValue;
  
  ReadBME680Register(bme,REG_CTRL_MEAS,&regValue,1);
  
  bme->ctrlMeas=regValue;
  mode=regValue&0x03;
  
  return mode;
}

/*����������ȴ�ʱ�䣬�赽gas_wait_x��ֵ*/
static uint8_t CalcHeaterWaitTime(uint16_t waitTime)
{
  uint8_t factor=0;
  uint8_t waitValue;

  if (waitTime >= 0xFC0)
  {
    waitValue = 0xFF;
  }
  else
  {
    while (waitTime > 0x3F)
    {
      waitTime=waitTime/4;
      factor+=1;
    }
    waitValue = (uint8_t) (waitTime + (factor * 64));
  }

  return waitValue;
}

/*�ж϶����Ƿ���Ч*/
static bool ObjectIsValid(BME680ObjectType *bme)
{
  bool valid=true;
  
  if((bme==NULL)||(bme->Delayms==NULL)||(bme->Read==NULL)||(bme->Write==NULL))
  {
    valid=false;
  }

  return valid;
}

/*ȱʡƬѡ������*/
static void BME680ChipSelectDefault(BME680CSType cs)
{
  //������SPIͨѶʱ��Ƭѡ�ź�Ӳ����·ѡ�е����
  return;
}

#if BME680_COMPENSATION_SELECTED > (0)
/*����ʵ���¶�ֵ,����0.01GegC*/
static int32_t CompensateTemperature(BME680ObjectType *bme,uint32_t adcCode)
{
  int64_t var1;
  int64_t var2;
  int64_t var3;
  int32_t temperature;
  int32_t temperature_min = -40000;
  int32_t temperature_max = 85000;

  var1=((int32_t)adcCode>>3)-((int32_t)bme->caliPara.dig_t1<<1);
  var2=(var1*(int32_t)bme->caliPara.dig_t2)>>11;
  var3=((var1>>1)*(var1>>1))>>12;
  var3 = ((var3)*((int32_t)bme->caliPara.dig_t3<<4))>>14;
  bme->caliPara.t_fine = (int32_t) (var2 + var3);
  temperature = (int32_t) (((bme->caliPara.t_fine * 5) + 128) >> 8);
	
  if (temperature < temperature_min)
  {
    temperature = temperature_min;
  }
  else if (temperature > temperature_max)
  {
    temperature = temperature_max;
  }
	
  return temperature;
}

/*����ʵ�ʵ�ѹ��ֵ*/
static int32_t CompensatePressure(BME680ObjectType *bme,uint32_t adcCode)
{
  int32_t var1;
  int32_t var2;
  int32_t var3;
  int32_t pressure;
//  int32_t pressure_min = 30000.0;
//  int32_t pressure_max = 110000.0;

  var1=(((int32_t)bme->caliPara.t_fine)>>1)-64000;
  var2=((((var1>>2)*(var1>>2))>>11)*(int32_t)bme->caliPara.dig_p6)>>2;
  var2=var2+((var1*(int32_t)bme->caliPara.dig_p5)<<1);
  var2=(var2>>2)+((int32_t)bme->caliPara.dig_p4 <<16);
  var1=(((((var1>>2)*(var1>>2))>>13)*((int32_t)bme->caliPara.dig_p3<<5))>>3)+(((int32_t)bme->caliPara.dig_p2*var1)>>1);
  var1=var1>>18;
  var1 =((32768+var1)*(int32_t)bme->caliPara.dig_p1)>>15;
  pressure=1048576- adcCode;
  pressure=(int32_t)((pressure-(var2>>12))*((uint32_t)3125));
  
  if(pressure>=0x40000000)
  {
    pressure=((pressure/var1)<<1);
  }
  else
  {
    pressure=((pressure<<1)/var1);
  }
  
  var1=((int32_t)bme->caliPara.dig_p9*(int32_t)(((pressure>>3)*(pressure>>3))>>13))>>12;
  var2=((int32_t)(pressure>>2)*(int32_t)bme->caliPara.dig_p8)>>13;
  var3=((int32_t)(pressure>>8)*(int32_t)(pressure>>8)*(int32_t)(pressure>>8)*(int32_t)bme->caliPara.dig_p10)>>17;

  pressure=(int32_t)(pressure)+((var1+var2+var3+((int32_t)bme->caliPara.dig_p7<<7))>>4);

  return pressure;
}

/*����ʵ�ʵ�ʪ��ֵ*/
static int32_t CompensateHumidity(BME680ObjectType *bme,uint32_t adcCode)
{
  int32_t humidity;
  int32_t humidity_min = 0;
  int32_t humidity_max = 100000;
  int32_t var1;
  int32_t var2;
  int32_t var3;
  int32_t var4;
  int32_t var5;
  int32_t var6;
  int32_t temp_scaled;

  temp_scaled=(((int32_t)bme->caliPara.t_fine*5)+128)>>8;
  var1=(int32_t)(adcCode-((int32_t)((int32_t)bme->caliPara.dig_h1*16)))-(((temp_scaled*(int32_t)bme->caliPara.dig_h3)/((int32_t)100))>>1);
  var2=((int32_t)bme->caliPara.dig_h2* (((temp_scaled * (int32_t) bme->caliPara.dig_h4)/((int32_t)100))
			+(((temp_scaled*((temp_scaled*(int32_t) bme->caliPara.dig_h5)/((int32_t)100)))>>6)/((int32_t)100))+(int32_t)(1<<14)))>>10;
  var3=var1*var2;
  var4=(int32_t)bme->caliPara.dig_h6<<7;
  var4=((var4)+((temp_scaled*(int32_t)bme->caliPara.dig_h7)/((int32_t)100)))>>4;
  var5=((var3>>14)*(var3>>14))>>10;
  var6=(var4*var5)>>1;
  humidity=(((var3+var6)>>10)*((int32_t)1000))>>12;

  if(humidity > humidity_max)
  {
    humidity = humidity_max;
  }
  else if (humidity < humidity_min)
  {
    humidity = humidity_min;
  }
  
  return humidity;
}

/*����ʵ�ʵ��������ֵ*/
static int32_t CompensateGasResistance(BME680ObjectType *bme,uint32_t adcCode,uint16_t gasRange)
{
  int32_t gasRes;
  int64_t var1 =0;
  int64_t var2 =0;

  /* �����ⳣ������ */
  uint32_t gasConstantInt[2][16]={{2147483647,2147483647,2147483647,2147483647,
                                   2147483647,2126008810,2147483647,2130303777,
                                   2147483647,2147483647,2143188679,2136746228,
                                   2147483647,2126008810,2147483647,2147483647},
                                   {4096000000,2048000000,1024000000,512000000,
                                   255744255,127110228,64000000,32258064,
                                   16016016,8000000,4000000,2000000,
                                   1000000,500000,250000,125000}};
	
  var1=(int64_t)(((1340+(5*(int64_t)bme->caliPara.range_sw_err))*((int64_t)gasConstantInt[0][gasRange]))>>16);
  var2=(int64_t)(adcCode<<15)-(int64_t)(1<<24)+var1;
  gasRes =(int32_t)((((int64_t)(gasConstantInt[1][gasRange]*var1)>>9)+(var2>>1))/var2);
	
  return gasRes;
}

/*�������������ֵ,���õ�res_wait_x�Ĵ�����ֵ*/
static uint8_t CompensateHeaterResistance(BME680ObjectType *bme,uint16_t tempTarget)
{
  uint8_t heatRes;
  int32_t var1;
  int32_t var2;
  int32_t var3;
  int32_t var4;
  int32_t var5;
  int32_t heaterResx100;

  if (tempTarget > 400)
  {
    tempTarget = 400;
  }
	
  var1 = (((int32_t)bme->temperature*bme->caliPara.dig_g3) / 1000) * 256;
  var2 = (bme->caliPara.dig_g1 + 784) * (((((bme->caliPara.dig_g2 + 154009) * tempTarget * 5) / 100) + 3276800) / 10);
  var3 = var1 + (var2 / 2);
  var4 = (var3 / (bme->caliPara.res_heat_range + 4));
  var5 = (131 * bme->caliPara.res_heat_val) + 65536;
  heaterResx100 = (int32_t) (((var4 / var5) - 250) * 34);
  heatRes = (uint8_t) ((heaterResx100 + 50) / 100);

  return heatRes;
}
#else
/*����ʵ���¶�ֵ,����0.01GegC*/
static float CompensateTemperature(BME680ObjectType *bme,uint32_t adcCode)
{
  double var1;
  double var2;
  double temperature;
  double temperature_min = -40;
  double temperature_max = 85;

  var1 = ((double)adcCode) / 16384.0 - ((double)bme->caliPara.dig_t1) / 1024.0;
  var1 = var1 * ((double)bme->caliPara.dig_t2);
  var2 = (((double)adcCode) / 131072.0 - ((double)bme->caliPara.dig_t1) / 8192.0);
  var2 = (var2 * var2) * ((double)bme->caliPara.dig_t3);
  bme->caliPara.t_fine = (int32_t)(var1 + var2);
  temperature = (var1 + var2) / 5120.0;

  if(temperature < temperature_min)
  {
    temperature = temperature_min;
  }
  else if (temperature > temperature_max)
  {
    temperature = temperature_max;
  }
  return (float)temperature;
}

/*����ʵ�ʵ�ѹ��ֵ��������ΪQ24.8��ʽ*/
static float CompensatePressure(BME680ObjectType *bme,uint32_t adcCode)
{
  double var1;
  double var2;
  double var3;
  double pressure;
  double pressure_min = 30000.0;
  double pressure_max = 110000.0;

  var1 = ((double)bme->caliPara.t_fine / 2.0) - 64000.0;
  var2 = var1 * var1 * ((double)bme->caliPara.dig_p6) / 131072.0;
  var2 = var2 + var1 * ((double)bme->caliPara.dig_p5) * 2.0;
  var2 = (var2 / 4.0) + (((double)bme->caliPara.dig_p4) * 65536.0);
  var1 = ((double)bme->caliPara.dig_p3) * var1 * var1 / 16384.0;
  var1 = (var1 + ((double)bme->caliPara.dig_p2) * var1) / 524288.0;
  var1 = (1.0 + var1 / 32768.0) * ((double)bme->caliPara.dig_p1);
  
  /*��������쳣 */
  if (var1)
  {
    pressure = 1048576.0 - (double)adcCode;
    pressure = ((pressure - (var2 / 4096.0)) * 6250.0 )/ var1;
    var1 = ((double)bme->caliPara.dig_p9 * pressure * pressure )/ 2147483648.0;
    var2 = pressure * ((double)bme->caliPara.dig_p8) / 32768.0;
    var3 = ((pressure  / 256.0f) * (pressure  / 256.0f) * (pressure  / 256.0f)
			* ((double)bme->caliPara.dig_p10 / 131072.0f));
    pressure = pressure + (var1 + var2 +var3+ ((double)bme->caliPara.dig_p7*128.0)) / 16.0;

    if (pressure < pressure_min)
    {
      pressure = pressure_min;
    }
    
    if (pressure > pressure_max)
    {
      pressure = pressure_max;
    }
  }
  else
  {
    pressure = pressure_min;
  }

  return (float)pressure;
}

/*����ʵ�ʵ�ʪ��ֵ��������ΪQ22.10��ʽ*/
static float CompensateHumidity(BME680ObjectType *bme,uint32_t adcCode)
{
  double humidity;
  double humidity_min = 0.0;
  double humidity_max = 100.0;
  double var1;
  double var2;
  double var3;
  double var4;
  double temp;

  temp=((double)bme->caliPara.t_fine)/5120.0;
  var1=(double)((double)adcCode)-(((double)bme->caliPara.dig_h1*16.0f)+(((double)bme->caliPara.dig_h3/2.0f)*temp));
  var2=var1*((double)(((double)bme->caliPara.dig_h2/262144.0f)*(1.0f + (((double)bme->caliPara.dig_h4/16384.0f)*temp)+(((double)bme->caliPara.dig_h5/1048576.0f)*temp*temp))));
  var3 = (double) bme->caliPara.dig_h6 / 16384.0f;
  var4 = (double) bme->caliPara.dig_h7 / 2097152.0f;
  humidity = var2 + ((var3 + (var4 * temp)) * var2 * var2);

  if (humidity > humidity_max)
  {
    humidity = humidity_max;
  }
  
  if (humidity < humidity_min)
  {
    humidity = humidity_min;
  }

  return (float)humidity;
}

/*����ʵ�ʵ��������ֵ*/
static float CompensateGasResistance(BME680ObjectType *bme,uint32_t adcCode,uint16_t gasRange)
{
  double gasRes;
  double var1 =0.0;
  /* �����ⳣ������ */
  float gasConstantFloat[2][16]={{1,1,1,1,1,0.99,1,0.992,1,1,0.998,0.995,1,0.99,1,1},
                                 {8000000,4000000,2000000,1000000,499500.4995,248262.1648,
                                 125000,63004.03226,31281.28128,15625,7812.5,3906.25,
                                 1953.125,976.5625,488.28125,244.140625}};

  var1 = (1340.0f + (5.0f * bme->caliPara.range_sw_err))*gasConstantFloat[0][gasRange];
  gasRes =var1*gasConstantFloat[1][gasRange]/(adcCode-512.0f+var1);
	
  return (float)gasRes;
}

/*�������������ֵ,���õ�res_wait_x�Ĵ�����ֵ*/
static uint8_t CompensateHeaterResistance(BME680ObjectType *bme,uint16_t tempTarget)
{
  double var1=0.0;
  double var2=0.0;
  double var3=0.0;
  double var4=0.0;
  double var5=0.0;
  uint8_t heatRes=0.0;

  if (tempTarget > 400)
  {
    tempTarget = 400;
  }
	
  var1 = (((double)bme->caliPara.dig_g1 / (16.0f)) + 49.0f);
  var2 = ((((double)bme->caliPara.dig_g2 / (32768.0f)) * (0.0005f)) + 0.00235f);
  var3 = ((double)bme->caliPara.dig_g3 / (1024.0f));
  var4 = (var1 * (1.0f + (var2 * (double)tempTarget)));
  var5 = (var4 + (var3 * (double)bme->temperature));
  heatRes=(uint8_t)(3.4f*((var5*(4.0/(4.0+(double)bme->caliPara.res_heat_range))*(1.0/(1.0+((double)bme->caliPara.res_heat_val*0.002f))))-25.0));

  return heatRes;
}
#endif
/*********** (C) COPYRIGHT 1999-2019 Moonan Technology *********END OF FILE****/
