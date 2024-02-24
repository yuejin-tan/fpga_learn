#pragma once

#include "CM3DS_MPS2.h"
#include "stdint.h"

typedef struct
{
    __IO   uint32_t  A;
    __I    uint32_t  B;
}DMA_AHB_TypeDef;

//base address
#define DMA_AHB_BASE   (CM3DS_MPS2_TARGEXP0_BASE + 0x0000)

//mapping
#define DMA_AHB        ((DMA_AHB_TypeDef   *) DMA_AHB_BASE)

