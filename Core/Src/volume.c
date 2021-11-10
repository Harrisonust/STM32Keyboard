/*
 * volume.c
 *
 *  Created on: Nov 10, 2021
 *      Author: luoshiheng
 */

#include "volume.h"
#define ENCODER_STEP 1

int32_t vol_counter = 0;

void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim){
	vol_counter = __HAL_TIM_GET_COUNTER(htim);
}

int32_t getVolume(){
	return vol_counter/ENCODER_STEP;
}
