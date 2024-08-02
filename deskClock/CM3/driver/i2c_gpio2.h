#pragma once

#include "stdint.h"

void swi2c_init2(void);

int16_t start_i2c2(void);

int16_t write_i2c2(uint16_t data);

int16_t read_i2c2(uint16_t ack);

int16_t stop_i2c2(void);
