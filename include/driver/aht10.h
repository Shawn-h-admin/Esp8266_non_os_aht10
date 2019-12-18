
#ifndef __I2C_AHT10_H
#define	__I2C_AHT10_H

#include "c_types.h"
#include "ets_sys.h"
#include "osapi.h"

#define AHT10_ADDR_R 0x71 //connect GND
#define AHT10_ADDR_W 0x70 //connect GND
#define AHT10_CALIBRATION_CMD 0xE1 //calibration cmd for measuring
#define AHT10_GET_DATA 0xAC        //get data cmd


bool  AHT10_Init();
int32_t  AHT10_Data();

#endif
