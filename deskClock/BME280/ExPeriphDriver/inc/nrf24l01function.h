/******************************************************************************/
/** 模块名称：扩展外设驱动                                                   **/
/** 文件名称：nrf24l01function.h                                             **/
/** 版    本：V1.0.0                                                         **/
/** 简    介：用于实现nRF24L01无线通讯模块的操作                             **/
/**           nRF24L01的命令格式：指令+数据                                  **/
/**           指令为高位在前，数据是低字节在前，具体指令如下：               **/
/**           +------------+--------+---------------------------+            **/
/**           |  指令名称  |指令格式|          实现操作         |            **/
/**           +------------+--------+---------------------------+            **/
/**           | R_REGISTER |000AAAAA|读寄存器，AAAAA为寄存器地址|            **/
/**           +------------+--------+---------------------------+            **/
/**           | W_REGISTER |001AAAAA|写寄存器，AAAAA为寄存器地址|            **/
/**           +------------+--------+---------------------------+            **/
/**           |R_RX_PAYLOAD|01100001|读RX有效数据，在RX模式有效 |            **/
/**           +------------+--------+---------------------------+            **/
/**           |W_TX_PAYLOAD|10100000|写TX有效数据，在TX模式有效 |            **/
/**           +------------+--------+---------------------------+            **/
/**           |  FLUSH_TX  |11100001|清除TX_FIFO寄存器          |            **/
/**           +------------+--------+---------------------------+            **/
/**           |  FLUSH_RX  |11100010|清楚RX_FIFO寄存器          |            **/
/**           +------------+--------+---------------------------+            **/
/**           | REUSE_TX_PL|11100011|重新使用上一包有效数据     |            **/
/**           +------------+--------+---------------------------+            **/
/**           |    NOP     |11111111|空操作，可用来读状态寄存器 |            **/
/**           +------------+--------+---------------------------+            **/
/**           寄存器及对象地址如下：                                         **/
/**           +---------+-----------+----+---------------------------+       **/
/**           |地址(Hex)|   名称    |属性|    说明                   |       **/
/**           +---------+-----------+----+---------------------------+       **/
/**           |  00     |  CONFIG   |读写| 配置寄存器                |       **/
/**           +---------+-----------+----+---------------------------+       **/
/**           |  01     |   EN_AA   |读写| 使能 自动应答 功能        |       **/
/**           +---------+-----------+----+---------------------------+       **/
/**           |  02     | EN_RXADDR |读写| 接收地址允许              |       **/
/**           +---------+-----------+----+---------------------------+       **/
/**           |  03     |  SETUP_AW |读写|设置地址宽度,所有数据通道  |       **/
/**           +---------+-----------+----+---------------------------+       **/
/**           |  04     | SETUP_RETR|读写|建立自动重发               |       **/
/**           +---------+-----------+----+---------------------------+       **/
/**           |  05     |  RF_CH    |读写|射频通道                   |       **/
/**           +---------+-----------+----+---------------------------+       **/
/**           |  06     |  RF_SETUP |读写|射频寄存器                 |       **/
/**           +---------+-----------+----+---------------------------+       **/
/**           |  07     |  STATUS   |读写|状态寄存器                 |       **/
/**           +---------+-----------+----+---------------------------+       **/
/**           |  08     | OBSERVE_TX|只读|发送检测寄存器             |       **/
/**           +---------+-----------+----+---------------------------+       **/
/**           |  09     |     CD    |只读|载波检测                   |       **/
/**           +---------+-----------+----+---------------------------+       **/
/**           |  0A     | RX_ADDR_P0|读写|数据通道 0 接收地址        |       **/
/**           +---------+-----------+----+---------------------------+       **/
/**           |  0B     | RX_ADDR_P1|读写|数据通道 1 接收地址        |       **/
/**           +---------+-----------+----+---------------------------+       **/
/**           |  0C     | RX_ADDR_P2|读写|数据通道 2 接收地址        |       **/
/**           +---------+-----------+----+---------------------------+       **/
/**           |  0D     | RX_ADDR_P3|读写|数据通道 3 接收地址        |       **/
/**           +---------+-----------+----+---------------------------+       **/
/**           |  0E     | RX_ADDR_P4|读写|数据通道 4 接收地址        |       **/
/**           +---------+-----------+----+---------------------------+       **/
/**           |  0F     | RX_ADDR_P5|读写|数据通道 5 接收地址        |       **/
/**           +---------+-----------+----+---------------------------+       **/
/**           |  10     |  TX_ADDR  |读写|发送地址                   |       **/
/**           +---------+-----------+----+---------------------------+       **/
/**           |  11     |  RX_PW_P0 |读写|接收数据通道 0 有效数据宽度|       **/
/**           +---------+-----------+----+---------------------------+       **/
/**           |  12     |  RX_PW_P1 |读写|接收数据通道 1 有效数据宽度|       **/
/**           +---------+-----------+----+---------------------------+       **/
/**           |  13     |  RX_PW_P2 |读写|接收数据通道 2 有效数据宽度|       **/
/**           +---------+-----------+----+---------------------------+       **/
/**           |  14     |  RX_PW_P3 |读写|接收数据通道 3 有效数据宽度|       **/
/**           +---------+-----------+----+---------------------------+       **/
/**           |  15     |  RX_PW_P4 |读写|接收数据通道 4 有效数据宽度|       **/
/**           +---------+-----------+----+---------------------------+       **/
/**           |  16     |  RX_PW_P5 |读写|接收数据通道 5 有效数据宽度|       **/
/**           +---------+-----------+----+---------------------------+       **/
/**           |  17     |FIFO_STATUS|只读|FIFO 状态寄存器            |       **/
/**           +---------+-----------+----+---------------------------+       **/
/**           |  N/A    |   TX_PLD  |只写|TXdata payload register    |       **/
/**           +---------+-----------+----+---------------------------+       **/
/**           |  N/A    |   RX_PLD  |只读|RX data payload register   |       **/
/**           +---------+-----------+----+---------------------------+       **/
/**--------------------------------------------------------------------------**/
/** 修改记录：                                                               **/
/**     版本      日期              作者              说明                   **/
/**     V1.0.0  2018-01-15          木南              创建文件               **/
/**     V1.0.1  2019-12-17          木南              修改为基于对象的操作   **/
/**                                                                          **/
/******************************************************************************/ 

#ifndef __NRF24L01FUNCTION_H
#define __NRF24L01FUNCTION_H

#include <stdint.h>

/*定义NRF24L01错误枚举*/
typedef enum NRF24L01Error {
  NRF24L01_NoError,
  NRF24L01_InitError,
  NRF24L01_Absent
}NRF24L01ErrorType;

/* 定义片选信号枚举 */
typedef enum NRF24L01CS {
  NRF24L01CS_Enable,
  NRF24L01CS_Disable
}NRF24L01CSType;

/* 定义使能信号枚举 */
typedef enum NRF24L01CE {
  NRF24L01CE_Enable,
  NRF24L01CE_Disable
}NRF24L01CEType;

/*定义模式枚举*/
typedef enum NRF24L01Mode {
  NRF24L01TxMode=0,
  NRF24L01RxMode=1
}NRF24L01ModeType;

/* 定义NRF24L01对象类型 */
typedef struct NRF24L01Object {
  uint8_t reg[8];//记录前8个配置寄存器
  uint8_t (*ReadWriteByte)(uint8_t TxData);//声明向nRF24L01读写一个字节的函数
  void (*ChipSelect)(NRF24L01CSType cs);//声明片选操作函数
  void (*ChipEnable)(NRF24L01CEType en);//声明使能及模式操作函数
  uint8_t (*GetIRQ)(void);//声明中断获取函数
  void (*Delayms)(volatile uint32_t nTime);       //毫秒延时操作指针
}NRF24L01ObjectType;

typedef uint8_t (*NRF24L01ReadWriteByte)(uint8_t TxData);//声明向nRF24L01读写一个字节的函数
typedef void (*NRF24L01ChipSelect)(NRF24L01CSType cs);//声明片选操作函数
typedef void (*NRF24L01ChipEnable)(NRF24L01CEType en);//声明使能及模式操作函数
typedef uint8_t (*NRF24L01GetIRQ)(void);//声明中断获取函数
typedef void (*NRF24L01Delayms)(volatile uint32_t nTime);       //毫秒延时操作指针

/*启动NRF24L01发送一次数据包*/
uint8_t NRF24L01TransmitPacket(NRF24L01ObjectType *nrf,uint8_t *txbuf);

/*启动NRF24L01接收一次数据包*/
uint8_t NRF24L01ReceivePacket(NRF24L01ObjectType *nrf,uint8_t *rxbuf);

/*nRF24L01对象初始化函数*/
NRF24L01ErrorType NRF24L01Initialization(NRF24L01ObjectType *nrf,       //nRF24L01对象
                                         NRF24L01ReadWriteByte spiReadWrite,    //SPI读写函数指针
                                         NRF24L01ChipSelect cs, //片选信号操作函数指针
                                         NRF24L01ChipEnable ce, //使能信号操作函数指针
                                         NRF24L01GetIRQ irq,    //中断信号获取函数指针
                                         NRF24L01Delayms delayms        //毫秒延时
                                        );

#endif

/*********** (C) COPYRIGHT 1999-2018 Moonan Technology *********END OF FILE****/
