#pragma once

#include "CM3DS_MPS2.h"
#include "stdint.h"

typedef struct
{
    __IO   uint32_t  mode; // 仅bit0有效
    __IO   uint16_t  TBPRD_shadow; // 参考TI
    __IO   uint16_t  CMPA_shadow; // 参考TI
    __IO   uint16_t  CMPB_shadow; // 参考TI
    __IO   uint16_t  CMPC_shadow; // 参考TI
}AHB_EPWM_TypeDef;

//base address
#define AHB_EPWM_BASE   (CM3DS_MPS2_TARGEXP1_BASE + 0x30000UL)

//mapping
#define AHB_EPWM        ((AHB_EPWM_TypeDef   *) AHB_EPWM_BASE)

