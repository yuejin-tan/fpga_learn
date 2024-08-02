#pragma once
#include "stdint.h"

#define BME280_OK 0
#define BME280_Error 1
//寄存器地址
#define R_ID 0xD0
#define R_Reset 0xE0
#define R_Ctrl_Hum 0xF2
#define R_Status 0xF3
#define R_Ctrl_Meas 0xF4
#define R_Config 0xF5
#define R_Press_MSB 0xF7
#define R_Press_LSB 0xF8
#define R_Press_XLSB 0xF9
#define R_Temp_MSB 0xFA
#define R_Temp_LSB 0xFB
#define R_Temp_XLSB 0xFC
#define R_Hum_MSB 0xFD
#define R_Hum_LSB 0xFE
//补偿参数寄存器
#define R_DIG_T1_MSB 0x88
#define R_DIG_T1_LSB 0x89
#define R_DIG_T2_MSB 0x8A
#define R_DIG_T2_LSB 0x8B
#define R_DIG_T3_MSB 0x8C
#define R_DIG_T3_LSB 0x8D

#define R_DIG_P1_MSB 0x8E
#define R_DIG_P1_LSB 0x8F
#define R_DIG_P2_MSB 0x90
#define R_DIG_P2_LSB 0x91
#define R_DIG_P3_MSB 0x92
#define R_DIG_P3_LSB 0x93
#define R_DIG_P4_MSB 0x94
#define R_DIG_P4_LSB 0x95
#define R_DIG_P5_MSB 0x96
#define R_DIG_P5_LSB 0x97
#define R_DIG_P6_MSB 0x98
#define R_DIG_P6_LSB 0x99
#define R_DIG_P7_MSB 0x9a
#define R_DIG_P7_LSB 0x9b
#define R_DIG_P8_MSB 0x9c
#define R_DIG_P8_LSB 0x9d
#define R_DIG_P9_MSB 0x9e
#define R_DIG_P9_LSB 0x9f

#define R_DIG_H1 0xA1
#define R_DIG_H2_LSB 0xE1
#define R_DIG_H2_MSB 0xE2
#define R_DIG_H3 0xE3
#define R_DIG_H4_MSB 0xE4
#define R_DIG_H4_LSB 0xE5
#define R_DIG_H5_MSB 0xE5
#define R_DIG_H5_LSB 0xE6
#define R_DIG_H6 0xE7
/*****************结构体*****************/
//过采样
#define BME280_Over_OFF 0x0
#define BME280_Over_1 0x1
#define BME280_Over_2 0x2
#define BME280_Over_4 0x3
#define BME280_Over_8 0x4
#define BME280_Over_16 0x5
//设备模式
#define BME280_Mode_Sleep 0x0  //睡眠模式
#define BME280_Mode_Forced 0x1 //强制模式
#define BME280_Mode_Normal 0x3 //正常模式
//正常模式下非活动持续时间(ms)
#define BME280_Tstandby_0_5 0x0
#define BME280_Tstandby_62_5 0x1
#define BME280_Tstandby_125 0x2
#define BME280_Tstandby_250 0x3
#define BME280_Tstandby_500 0x4
#define BME280_Tstandby_1000 0x5
#define BME280_Tstandby_10 0x6
#define BME280_Tstandby_20 0x7
//IIR滤波器的时间常数
#define BME280_Filter_OFF 0x0 //关闭
#define BME280_Filter_2 0x1
#define BME280_Filter_4 0x2
#define BME280_Filter_8 0x3
#define BME280_Filter_16 0x4

struct BME280_Compensation
{
    uint16_t dig_T1;
    int16_t dig_T2;
    int16_t dig_T3;
    uint16_t dig_P1;
    int16_t dig_P2;
    int16_t dig_P3;
    int16_t dig_P4;
    int16_t dig_P5;
    int16_t dig_P6;
    int16_t dig_P7;
    int16_t dig_P8;
    int16_t dig_P9;
    int16_t dig_H2;
    int16_t dig_H4;
    int16_t dig_H5;
    // 手动调整布局
    uint8_t dig_H1;
    uint8_t dig_H3;
    int8_t dig_H6;
};
/*****************总结构体*****************/

  //结构体
typedef struct __BME280
{
    int32_t t_fine;     //全局温度值
    struct BME280_Compensation DIG;
    uint8_t IIC_ADDR; //地址
    uint8_t BME280_Mode;     //设备模式
    uint8_t BME280_Tstandby; //正常模式下非活动持续时间(ms)
    uint8_t BME280_IIR_Time; //IIR滤波器的时间常数
    uint8_t PRESS_overSamp;//压力过采样
    uint8_t TEMP_overSamp;//温度过采样
    uint8_t HUM_overSamp; //湿度过采样
} Sensor_BME280;

int BME280_Reset(Sensor_BME280* BME280);
int BME280_ID(Sensor_BME280* BME280, uint8_t* ID);
int BME280_Get_DIG(Sensor_BME280* BME280);
int BME280_Configuration(Sensor_BME280* BME280);
int BME280_Get_ALL(Sensor_BME280* BME280, float* Temp, float* Hum, float* Press);
