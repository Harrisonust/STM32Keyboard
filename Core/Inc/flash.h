/*
 * flash.h
 *
 *  Created on: Nov 5, 2021
 *      Author: Steven
 */

#ifndef INC_FLASH_H_
#define INC_FLASH_H_


#include "stm32f1xx_hal.h"
#include "math.h"


uint32_t Flash_Write_Data (uint32_t StartPageAddress, uint32_t *Data, uint16_t numberofwords);

void Flash_Read_Data (uint32_t StartPageAddress, uint32_t *RxBuf, uint16_t numberofwords);

void Convert_To_Str (uint32_t *Data, char *Buf);

void Str_To_uint32(char *Buf, uint32_t *Holder);

void Flash_Write_NUM (uint32_t StartSectorAddress, float Num);

float Flash_Read_NUM (uint32_t StartSectorAddress);

#endif /* INC_FLASH_H_ */
