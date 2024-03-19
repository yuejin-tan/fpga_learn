#pragma once

#include "CMSDK_CM0.h"
#include "stdint.h"

typedef struct
{
    __IO   uint8_t  seg0;
    __IO   uint8_t  seg1;
    __IO   uint8_t  seg2;
    __IO   uint8_t  seg3;
    __IO   uint8_t  seg4;
    __IO   uint8_t  seg5;
    __IO   uint8_t  seg6;
    __IO   uint8_t  seg7;
}AHB_LED_TypeDef;

//base address
//base address
#define CM0_AHB3_BASE   (0x40010000UL)
#define AHB_LED_BASE   (CM0_AHB3_BASE + 0x0000)

//mapping
#define AHB_LED        ((AHB_LED_TypeDef   *) AHB_LED_BASE)

