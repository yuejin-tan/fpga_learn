#pragma once

#include "CM3DS_MPS2.h"
#include "stdint.h"

struct  CMD_BITS {
    uint8_t EN : 1;
    uint8_t ERR : 1;
    uint8_t RX : 3;
    uint8_t TX : 3;
};

union CMD_DEF {
    uint8_t all;
    struct CMD_BITS bit;
};

typedef struct
{
    __IO   union CMD_DEF cmd;
    __IO   uint8_t  data;
    // 至少是8
    __IO   uint16_t  buad_div_2;
}AHB_UART_TypeDef;

//base address
#define AHB_UART_BASE   (CM3DS_MPS2_TARGEXP0_BASE + 0x0000)

//mapping
#define AHB_UART        ((AHB_UART_TypeDef   *) AHB_UART_BASE)
