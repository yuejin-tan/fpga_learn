#include "thp_bme280_drv.h"
#include "i2c_gpio2.h"
#include "stdio.h"

/*****************底层控制函数*****************/
/**
  * @brief 设备写
  * @param BME280：写目标设备
  * @param ADDR：写入地址
  * @param DATA：写入数据
  * @retval 写操作反馈
  */
static int BME280_Write(Sensor_BME280* BME280, uint8_t ADDR, uint8_t DATA)
{
    int16_t ans;

    ans = start_i2c2();
    if (ans < 0)
    {
        stop_i2c2();
        return -__LINE__ - 1000;
    }

    ans = write_i2c2(BME280->IIC_ADDR | (uint8_t)0u);
    if (ans < 0 || ans == 1)
    {
        stop_i2c2();
        return -__LINE__ - 1000;
    }

    ans = write_i2c2(ADDR);
    if (ans < 0 || ans == 1)
    {
        stop_i2c2();
        return -__LINE__ - 1000;
    }

    ans = write_i2c2(DATA);
    if (ans < 0 || ans == 1)
    {
        stop_i2c2();
        return -__LINE__ - 1000;
    }

    stop_i2c2();
    return 0;
}

/**
  * @brief 设备读
  * @param BME280：读目标设备
  * @param ADDR：读取的开始地址
  * @param DATA：读入的数据
  * @param DATA_NUM：读入数据的数量
  * @retval 读操作反馈
  */
static int BME280_Read(Sensor_BME280* BME280, uint8_t ADDR, uint8_t* DATA, uint16_t DATA_NUM)
{
    int16_t ans;

    ans = start_i2c2();
    if (ans < 0)
    {
        stop_i2c2();
        return -__LINE__ - 1000;
    }

    ans = write_i2c2(BME280->IIC_ADDR | (uint8_t)0u);
    if (ans < 0 || ans == 1)
    {
        stop_i2c2();
        return -__LINE__ - 1000;
    }

    ans = write_i2c2(ADDR);
    if (ans < 0 || ans == 1)
    {
        stop_i2c2();
        return -__LINE__ - 1000;
    }

    ans = stop_i2c2();
    if (ans < 0)
    {
        stop_i2c2();
        return -__LINE__ - 1000;
    }

    ans = start_i2c2();
    if (ans < 0)
    {
        stop_i2c2();
        return -__LINE__ - 1000;
    }

    ans = write_i2c2(BME280->IIC_ADDR | (uint8_t)1u);
    if (ans < 0 || ans == 1)
    {
        stop_i2c2();
        return -__LINE__ - 1000;
    }

    for (uint16_t i = 0; i < DATA_NUM; i++)
    {
        if (i == (DATA_NUM - 1))
        {
            ans = read_i2c2(1);
            if (ans < 0)
            {
                stop_i2c2();
                return -__LINE__ - 1000;
            }
            DATA[i] = (uint8_t)ans;
        }
        else
        {
            ans = read_i2c2(0);
            if (ans < 0)
            {
                stop_i2c2();
                return -__LINE__ - 1000;
            }
            DATA[i] = (uint8_t)ans;
        }
    }

    stop_i2c2();
    return 0;
}

/**
  * @brief 位操作
  * @param Reg:被修改的值
  * @param Bit_Start:开始修改的位置
  * @param Bit_Stop:结束修改的位置
  * @param Value:需要修改成的值(二进制表示)
  * @retval 返回修改完成后的变量
  */
static inline uint8_t Bit_Modification(uint8_t Reg, uint8_t Bit_Start, uint8_t Bit_Stop, uint8_t Value)
{
    uint8_t X = 0xFFu;
    for (uint8_t i = Bit_Start; i < Bit_Stop + 1; i++)
    {
        X &= ~(1 << i);
    }
    Reg &= X;
    Reg |= Value << Bit_Start;
    return Reg;
}

/*****************功能函数*****************/
/**
  * @brief 获取当前温度、湿度、压力
  * @param BME280：目标设备
  * @param Temp：温度
  * @param Hum：湿度
  * @param Press：压力
  * @retval 操作反馈
  */
int BME280_Get_ALL(Sensor_BME280* BME280, float* Temp, float* Hum, float* Press)
{
    uint8_t DATA_IN[8] = { 0 };
    if (BME280_Read(BME280, R_Press_MSB, DATA_IN, 8) != BME280_OK)
    {
        return BME280_Error;
    }
    int32_t adc_P = { 0 };
    int32_t adc_T = { 0 };
    int32_t adc_H = { 0 };

    adc_P = ((int32_t)DATA_IN[0] << 12) | ((int32_t)DATA_IN[1] << 4) | ((int32_t)DATA_IN[2] >> 4);
    adc_T = ((int32_t)DATA_IN[3] << 12) | ((int32_t)DATA_IN[4] << 4) | ((int32_t)DATA_IN[5] >> 4);
    adc_H = ((int32_t)DATA_IN[6] << 8) | ((int32_t)DATA_IN[7]);

    //压力计算
    int32_t var1, var2, p;
    var1 = (((int32_t)BME280->t_fine) >> 1) - (int32_t)64000;
    var2 = (((var1 >> 2) * (var1 >> 2)) >> 11) * ((int32_t)BME280->DIG.dig_P6);
    var2 = var2 + ((var1 * ((int32_t)BME280->DIG.dig_P5)) << 1);
    var2 = (var2 >> 2) + (((int32_t)BME280->DIG.dig_P4) << 16);
    var1 = (((BME280->DIG.dig_P3 * (((var1 >> 2) * (var1 >> 2)) >> 13)) >> 3) + ((((int32_t)BME280->DIG.dig_P2) * var1) >> 1)) >> 18;
    var1 = ((((32768 + var1)) * ((int32_t)BME280->DIG.dig_P1)) >> 15);
    if (var1 == 0) {
        return 0;
        // avoid exception caused by division by zero  
    }
    p = (((uint32_t)(((int32_t)1048576) - adc_P) - (var2 >> 12))) * 3125;
    if (p < 0x80000000)
    {
        p = (p << 1) / ((uint32_t)var1);
    }
    else
    {
        p = (p / (uint32_t)var1) * 2;
    }
    var1 = (((int32_t)BME280->DIG.dig_P9) * ((int32_t)(((p >> 3) * (p >> 3)) >> 13))) >> 12;
    var2 = (((int32_t)(p >> 2)) * ((int32_t)BME280->DIG.dig_P8)) >> 13;
    p = (uint32_t)((int32_t)p + ((var1 + var2 + BME280->DIG.dig_P7) >> 4));
    *Press = p;

    //温度计算
    var1 = ((((adc_T >> 3) - ((int32_t)BME280->DIG.dig_T1 << 1))) * ((int32_t)BME280->DIG.dig_T2)) >> 11;
    var2 = (((((adc_T >> 4) - ((int32_t)BME280->DIG.dig_T1)) * ((adc_T >> 4) - ((int32_t)BME280->DIG.dig_T1))) >> 12) * ((int32_t)BME280->DIG.dig_T3)) >> 14;
    BME280->t_fine = var1 + var2;
    *Temp = ((BME280->t_fine * 5 + 128) >> 8) * 0.01f;

    //湿度计算
    var1 = (BME280->t_fine - ((int32_t)76800));
    var1 = (((((adc_H << 14) - (((int32_t)BME280->DIG.dig_H4) << 20) - (((int32_t)BME280->DIG.dig_H5) * var1)) +
        ((int32_t)16384)) >> 15) * (((((((var1 * ((int32_t)BME280->DIG.dig_H6)) >> 10) *
            (((var1 * ((int32_t)BME280->DIG.dig_H3)) >> 11) + ((int32_t)32768))) >> 10) +
            ((int32_t)2097152)) * ((int32_t)BME280->DIG.dig_H2) + 8192) >> 14));
    var1 = (var1 - (((((var1 >> 15) * (var1 >> 15)) >> 7) * ((int32_t)BME280->DIG.dig_H1)) >> 4));
    var1 = (var1 < 0 ? 0 : var1);   var1 = (var1 > 419430400 ? 419430400 : var1);

    *Hum = (uint32_t)(var1 >> 12) * (1.0f / 1024.0f);

    return BME280_OK;
}

/**
  * @brief 读取补偿值
  * @param BME280：目标设备
  * @retval 操作反馈
  */
int BME280_Get_DIG(Sensor_BME280* BME280)
{
    // 依赖于小端的内存布局
    //温度 & 压力
    if (BME280_Read(BME280, R_DIG_T1_MSB, &BME280->DIG.dig_T1, 24) != BME280_OK)
    {
        return BME280_Error;
    }

    //湿度
    if (BME280_Read(BME280, R_DIG_H1, &BME280->DIG.dig_H1, 1) != BME280_OK)
    {
        return BME280_Error;
    }
    if (BME280_Read(BME280, R_DIG_H2_LSB, &BME280->DIG.dig_H2, 2) != BME280_OK)
    {
        return BME280_Error;
    }
    if (BME280_Read(BME280, R_DIG_H3, &BME280->DIG.dig_H3, 1) != BME280_OK)
    {
        return BME280_Error;
    }
    uint8_t DATA_H_buff[3] = { 0 };
    if (BME280_Read(BME280, R_DIG_H4_MSB, DATA_H_buff, 3) != BME280_OK)
    {
        return BME280_Error;
    }
    BME280->DIG.dig_H4 = ((uint16_t)DATA_H_buff[0] << 4) | ((uint16_t)DATA_H_buff[1] & 0xfu);
    BME280->DIG.dig_H5 = ((uint16_t)DATA_H_buff[1] >> 4) | ((uint16_t)DATA_H_buff[2] << 8);
    if (BME280_Read(BME280, R_DIG_H6, &BME280->DIG.dig_H6, 1) != BME280_OK)
    {
        return BME280_Error;
    }
    return BME280_OK;
}

/**
  * @brief 通过结构体参数配置传感器
  * @param BME280：目标设备
  * @retval 操作反馈
  */
int BME280_Configuration(Sensor_BME280* BME280)
{
    uint8_t DATA_Config = { 0 };
    uint8_t DATA_Ctrl_Hum = { 0 };
    uint8_t DATA_Ctrl_Meas = { 0 };
    //三个配置寄存器写入顺序：Config、Ctrl_Hum、Ctrl_Meas
    //Config
    //Tstandby位
    DATA_Config = Bit_Modification(DATA_Config, 5, 7, BME280->BME280_Tstandby);
    //Filter位
    DATA_Config = Bit_Modification(DATA_Config, 2, 4, BME280->BME280_IIR_Time);

    //Ctrl_Hum
    DATA_Ctrl_Hum = Bit_Modification(DATA_Ctrl_Hum, 0, 2, BME280->HUM_overSamp);

    //Ctrl_Meas
    //温度过采样
    DATA_Ctrl_Meas = Bit_Modification(DATA_Ctrl_Meas, 5, 7, BME280->TEMP_overSamp);
    //压力过采样
    DATA_Ctrl_Meas = Bit_Modification(DATA_Ctrl_Meas, 2, 4, BME280->PRESS_overSamp);
    //设备模式
    DATA_Ctrl_Meas = Bit_Modification(DATA_Ctrl_Meas, 0, 1, BME280->BME280_Mode);

    //依次写入设备
    if (BME280_Write(BME280, R_Config, DATA_Config) != BME280_OK)
    {
        return BME280_Error;
    }
    if (BME280_Write(BME280, R_Ctrl_Hum, DATA_Ctrl_Hum) != BME280_OK)
    {
        return BME280_Error;
    }
    if (BME280_Write(BME280, R_Ctrl_Meas, DATA_Ctrl_Meas) != BME280_OK)
    {
        return BME280_Error;
    }
    return BME280_OK;
}

/**
  * @brief 复位设备
  * @param BME280：目标设备
  * @retval 操作反馈
  */
int BME280_Reset(Sensor_BME280* BME280)
{
    if (BME280_Write(BME280, R_Reset, 0xB6) != BME280_OK)
    {
        return BME280_Error;
    }
    return BME280_OK;
}

/**
  * @brief 读取设备ID
  * @param BME280：目标设备
  * @param ID：读取的ID
  * @retval 操作反馈
  */
int BME280_ID(Sensor_BME280* BME280, uint8_t* ID)
{
    if (BME280_Read(BME280, R_ID, ID, 1) != BME280_OK)
    {
        return BME280_Error;
    }
    return BME280_OK;
}
