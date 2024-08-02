/******************************************************************************/
/** ģ�����ƣ���չ��������                                                   **/
/** �ļ����ƣ�expdconfig.h                                                   **/
/** ��    ����V1.1.0                                                         **/
/** ��    �飺ʵ�ַ�MCU���ɱ�׼������������������豸�Ĳ�������            **/
/**--------------------------------------------------------------------------**/
/** �޸ļ�¼��                                                               **/
/**     �汾      ����              ����              ˵��                   **/
/**     V1.0.0  2012-07-28          ľ��              �����ļ�               **/
/**     V1.0.1  2013-05-21          ľ��              ���PM25������         **/
/**     V1.0.2  2013-09-13          ľ��              ���EEROM����          **/
/**     V1.0.3  2014-08-08          ľ��              �����ʾ����           **/
/**     V1.0.4  2015-04-22          ľ��              ��Ӽ��ٶȼ�����       **/
/**     V1.0.5  2016-06-12          ľ��              ���AD7192����         **/
/**     V1.0.6  2017-09-17          ľ��              ��ӹ�����ȼ�����     **/
/**     V1.0.7  2018-08-01          ľ��              ���MS5536C����        **/
/**     V1.0.8  2018-08-28          ľ��              ���GPIOģ��I2C����    **/
/**     V1.0.9  2018-08-28          ľ��              ���SHT3x����������    **/
/**                                                                          **/
/******************************************************************************/ 

#ifndef __EXDCONFIG_H
#define __EXDCONFIG_H

/* ��������AD56xxϵ��DAC�����ĺ꣬1�����ã�0������ */
#ifndef EXPD_AD56XX_ENABLE
#define EXPD_AD56XX_ENABLE	(1)
#endif

/* ��������AD8400ϵ�����ֵ�λ�������ĺ꣬1�����ã�0������ */
#ifndef EXPD_AD8400_ENABLE
#define EXPD_AD8400_ENABLE      (1)
#endif

/* ��������AD527xϵ�����ֵ�λ�������ĺ꣬1�����ã�0������ */
#ifndef EXPD_AD527x_ENABLE
#define EXPD_AD527x_ENABLE      (1)
#endif

/* ��������AD9833���������������ĺ꣬1�����ã�0������ */
#ifndef EXPD_AD9833_ENABLE
#define EXPD_AD9833_ENABLE      (1)
#endif

/* ��������AD7705ϵ��ADC�����ĺ꣬1�����ã�0������ */
#ifndef EXPD_AD7705_ENABLE
#define EXPD_AD7705_ENABLE      (1)
#endif

/* ��������AD7192ϵ��ADC�����ĺ꣬1�����ã�0������ */
#ifndef EXPD_AD7192_ENABLE
#define EXPD_AD7192_ENABLE      (1)
#endif

/* ��������LTC2400ϵ��ADC�����ĺ꣬1�����ã�0������ */
#ifndef EXPD_LTC2400_ENABLE
#define EXPD_LTC2400_ENABLE	(1)
#endif

/* ��������GPIOģ��I2CͨѶ�ĺ꣬1�����ã�0������*/
#ifndef EXPD_SIMUI2C_ENABLE
#define EXPD_SIMUI2C_ENABLE	(1)
#endif

/* ��������SHT1X��ʪ�ȴ����������ĺ꣬1�����ã�0������ */
#ifndef EXPD_SHT1X_ENABLE
#define EXPD_SHT1X_ENABLE	(1)
#endif

/* ��������SHT2Xϵ����ʪ�ȴ����������ĺ꣬1�����ã�0������ */
#ifndef EXPD_SHT2X_ENABLE
#define EXPD_SHT2X_ENABLE	(1)
#endif

/* ��������SHT3Xϵ��������ʪ�ȴ����������ĺ꣬1�����ã�0������ */
#ifndef EXPD_SHT3X_ENABLE
#define EXPD_SHT3X_ENABLE	(1)
#endif

/* ��������TSEV01CL55�����¶ȴ����������ĺ꣬1�����ã�0������ */
#ifndef EXPD_HLPT_ENABLE
#define EXPD_HLPT_ENABLE	(1)
#endif

/* ��������MLX90614�����¶ȴ����������ĺ꣬1�����ã�0������ */
#ifndef EXPD_MLX_ENABLE
#define EXPD_MLX_ENABLE         (1)
#endif

/* ��������DS18B20�¶ȱ����������ĺ꣬1�����ã�0������ */
#ifndef EXPD_DS18B20_ENABLE
#define EXPD_DS18B20_ENABLE	(1)
#endif

/* ��������DHT11��ʪ�ȴ����������ĺ꣬1�����ã�0������ */
#ifndef EXPD_DHT11_ENABLE
#define EXPD_DHT11_ENABLE	(1)
#endif

/* ��������MS5536Cѹ�������������ĺ꣬1�����ã�0������ */
#ifndef EXPD_MS5536_ENABLE
#define EXPD_MS5536_ENABLE	(1)
#endif

/* ��������MS5803ѹ�������������ĺ꣬1�����ã�0������ */
#ifndef EXPD_MS5803_ENABLE
#define EXPD_MS5803_ENABLE	(1)
#endif

/* ��������MS5837ѹ�������������ĺ꣬1�����ã�0������ */
#ifndef EXPD_MS5837_ENABLE
#define EXPD_MS5837_ENABLE	(1)
#endif

/* ��������BMP280ѹ���¶ȴ����������ĺ꣬1�����ã�0������ */
#ifndef EXPD_BMP280_ENABLE
#define EXPD_BMP280_ENABLE	(1)
#endif

/* ��������BME280ѹ��ʪ���¶ȴ����������ĺ꣬1�����ã�0������ */
#ifndef EXPD_BME280_ENABLE
#define EXPD_BME280_ENABLE	(1)
#endif

/* ��������BME680���������������ĺ꣬1�����ã�0������ */
#ifndef EXPD_BME680_ENABLE
#define EXPD_BME680_ENABLE	(1)
#endif

/* ��������ADXL345�������ּ��ٶȼ������ĺ꣬1�����ã�0������ */
#ifndef EXPD_ADXL345_ENABLE
#define EXPD_ADXL345_ENABLE	(1)
#endif

/* ��������AT24Cxx�ⲿ�洢�������ĺ꣬1�����ã�0������ */
#ifndef EXPD_AT24CXX_ENABLE
#define EXPD_AT24CXX_ENABLE	(1)
#endif

/* ��������AT25xxx�ⲿ�洢�������ĺ꣬1�����ã�0������ */
#ifndef EXPD_AT25XXX_ENABLE
#define EXPD_AT25XXX_ENABLE	(0)
#endif

/* ��������FM24xxxFRAM�洢�������ĺ꣬1�����ã�0������ */
#ifndef EXPD_FM24XXX_ENABLE
#define EXPD_FM24XXX_ENABLE	(1)
#endif

/* ��������FM25xxxFRAM�洢�������ĺ꣬1�����ã�0������ */
#ifndef EXPD_FM25XXX_ENABLE
#define EXPD_FM25XXX_ENABLE	(1)
#endif

/* ��������nRF24L01����ͨѶ�����ĺ꣬1�����ã�0������ */
#ifndef EXPD_NRF24L01_ENABLE
#define EXPD_NRF24L01_ENABLE	(1)
#endif

/* ��������ESP8266����ͨѶ�����ĺ꣬1�����ã�0������ */
#ifndef EXPD_ESP8266_ENABLE
#define EXPD_ESP8266_ENABLE	(1)
#endif

/* ��������W5500��̫�������������ĺ꣬1�����ã�0������ */
#ifndef EXPD_W5500_ENABLE
#define EXPD_W5500_ENABLE	(1)
#endif

/* ��������DS17887ʵʱʱ�������ĺ꣬1�����ã�0������ */
#ifndef EXPD_DS17887_ENABLE
#define EXPD_DS17887_ENABLE	(1)
#endif

/* �����������AI-BUSͨѶ�����ĺ꣬1�����ã�0������ */
#ifndef EXPD_AIBUS_ENABLE
#define EXPD_AIBUS_ENABLE	(1)
#endif

/* �����������Զ�������崫���������ĺ꣬1�����ã�0������ */
#ifndef EXPD_NDIR_ENABLE
#define EXPD_NDIR_ENABLE	(1)
#endif

/* ��������HLPM025K3 PM2.5�����������ĺ꣬1�����ã�0������ */
#ifndef EXPD_HLPM_ENABLE
#define EXPD_HLPM_ENABLE	(1)
#endif

/* ��������LCD1602Һ����ʾ�������ĺ꣬1�����ã�0������ */
#ifndef EXPD_LCD1602_ENABLE
#define EXPD_LCD1602_ENABLE	(1)
#endif

/* ��������OLED��ʾ�������ĺ꣬1�����ã�0������ */
#ifndef EXPD_OLED_ENABLE
#define EXPD_OLED_ENABLE	(1)
#endif

/* �������õ��Ĵ����������ĺ꣬1�����ã�0������ */
#ifndef EXPD_DWLCD_ENABLE
#define EXPD_DWLCD_ENABLE	(1)
#endif

/* ��������NTC���¶�ϵ���ȵ�����������ĺ꣬1�����ã�0������ */
#ifndef EXPD_NTC_ENABLE
#define EXPD_NTC_ENABLE		(1)
#endif

/* ��������S1336-5BQ������������Ϊ��ȼ������ĺ꣬1�����ã�0������ */
#ifndef EXPD_LUX_ENABLE
#define EXPD_LUX_ENABLE		(1)
#endif

/* ��������RTD���ȵ�����������ĺ꣬1�����ã�0������ */
#ifndef EXPD_RTD_ENABLE
#define EXPD_RTD_ENABLE         (1)
#endif

/* �������ð������������ĺ꣬1�����ã�0������ */
#ifndef EXPD_KEY_ENABLE
#define EXPD_KEY_ENABLE         (1)
#endif


/*AD56xx ADI��˾SPI�ӿ�ϵ��DAC*/
#if EXPD_AD56XX_ENABLE > (0)
#include "ad56xxfunction.h"
#endif

/*AD8400���ֵ�λ��SPI�ӿ�*/
#if EXPD_AD8400_ENABLE > (0)
#include "ad840xfunction.h"
#endif

/*AD5270���ֵ�λ��SPI�ӿ�*/
#if EXPD_AD527x_ENABLE > (0)
#include "ad527xfunction.h"
#endif

/*AD9833����������SPI�ӿ�*/
#if EXPD_AD9833_ENABLE > (0)
#include "ad9833function.h"
#endif

/*AD7705˫ͨ��SPI�ӿ�ADC*/
#if EXPD_AD7705_ENABLE > (0)
#include "ad7705function.h"
#endif

/*AD7192��ͨ��SPI�ӿ�ADC*/
#if EXPD_AD7192_ENABLE > (0)
#include "ad7192function.h"
#endif

/*LTC2400��ͨ��SPI�ӿ�ADC*/
#if EXPD_LTC2400_ENABLE > (0)
#include "ltc2400function.h"
#endif

/* ����GPIOģ��I2CͨѶ*/
#if EXPD_SIMUI2C_ENABLE > (0)
#include "simui2cfunction.h"
#endif

/*SHT1Xϵ����ʪ�ȴ�����*/
#if EXPD_SHT1X_ENABLE > (0)
#include "sht1xfunction.h"
#endif

/*SHT2Xϵ����ʪ�ȴ�����*/
#if EXPD_SHT2X_ENABLE > (0)
#include "sht2xfunction.h"
#endif

/* ����SHT3Xϵ��������ʪ�ȴ�����*/
#if EXPD_SHT3X_ENABLE > (0)
#include "sht3xfunction.h"	
#endif

/* ����TSEV01CL55�����¶ȴ�����*/
#if EXPD_HLPT_ENABLE > (0)
#include "hlptfunction.h"	
#endif

/* ����MLX90614�����¶ȴ�����*/
#if EXPD_MLX_ENABLE > (0)
#include "mlx90614function.h"	
#endif

/*DS18B20�¶ȱ�����*/
#if EXPD_DS18B20_ENABLE > (0)
#include "ds18b20function.h"
#endif

/*DHT11��ʪ�ȴ�����*/
#if EXPD_DHT11_ENABLE > (0)
#include "dht11function.h"
#endif

/*MS5536Cѹ��������SPI�ӿ�*/
#if EXPD_MS5536_ENABLE > (0)
#include "ms5536function.h"
#endif

/*MS5803ѹ��������I2C�ӿ�*/
#if EXPD_MS5803_ENABLE > (0)
#include "ms5803function.h"
#endif

/*MS5837ѹ��������I2C�ӿ�*/
#if EXPD_MS5837_ENABLE > (0)
#include "ms5837function.h"
#endif

/* ����BMP280ѹ���¶ȴ����� */
#if EXPD_BMP280_ENABLE > (0)
#include "bmp280function.h"
#endif

/* ����BME280ѹ��ʪ���¶ȴ����� */
#if EXPD_BME280_ENABLE > (0)
#include "bme280function.h"
#endif

/* ����BME680���������� */
#if EXPD_BME680_ENABLE > (0)
#include "bme680function.h"
#endif

/*ADXL345�������ּ��ٶȼ�*/
#if EXPD_ADXL345_ENABLE
#include "adxl345function.h"
#endif

/*AT24Cxx�ⲿ�洢��*/
#if EXPD_AT24CXX_ENABLE > (0)
#include "at24cxxfunction.h"
#endif

/*AT25xxx�ⲿ�洢��*/
#if EXPD_AT25XXX_ENABLE > (0)
#include "at25xxxfunction.h"
#endif

/*FM24xxx�ⲿ�洢��*/
#if EXPD_FM24XXX_ENABLE > (0)
#include "fm24xxxfunction.h"
#endif

/*FM25xxx�ⲿ�洢��*/
#if EXPD_FM25XXX_ENABLE > (0)
#include "fm25xxxfunction.h"
#endif

/* ����nRF24L01����ͨѶ*/
#if EXPD_NRF24L01_ENABLE > (0)
#include "nrf24l01function.h"
#endif

/* ����ESP8266����ͨѶ*/
#if EXPD_ESP8266_ENABLE > (0)
#include "esp8266function.h"
#endif

/*W5500��̫��������*/
#if EXPD_W5500_ENABLE > (0)
#include "w5500function.h"
#endif

/*DS17887ʵʱʱ��*/
#if EXPD_DS17887_ENABLE > (0)
#include "ds17887function.h"
#endif

/*�������AI-BUSͨѶ*/
#if EXPD_AIBUS_ENABLE > (0)
#include "aibusfunction.h"
#endif

/*��ĺ������崫����*/
#if EXPD_NDIR_ENABLE > (0)
#include "ndirfunction.h"
#endif

/*HLPM025K3 PM25������*/
#if EXPD_HLPM_ENABLE > (0)
#include "hlpmfunction.h"
#endif

/*LCD1602Һ����ʾ��*/
#if EXPD_LCD1602_ENABLE > (0)
#include "lcd1602function.h"
#endif

/*OLED��ʾ��*/
#if EXPD_OLED_ENABLE > (0)
#include "oledfunction.h"
#endif

/*���Ĵ��ڴ�����*/
#if EXPD_DWLCD_ENABLE > (0)
#include "dwinlcdfunction.h"
#endif

/* ����NTC���¶�ϵ���ȵ������*/
#if EXPD_NTC_ENABLE > (0)
#include "ntcfunction.h"
#endif

/* ����S1336-5BQ������������Ϊ��ȼ�*/
#if EXPD_LUX_ENABLE > (0)
#include "luxfunction.h"
#endif

/* ����RTD���ȵ������*/
#if EXPD_RTD_ENABLE > (0)
#include "rtdfunction.h"
#endif

/* �������ð������������ĺ꣬1�����ã�0������*/
#if EXPD_KEY_ENABLE > (0)
#include "keysfunction.h"
#endif

#endif
/*********** (C) COPYRIGHT 1999-2019 Moonan Technology *********END OF FILE****/
