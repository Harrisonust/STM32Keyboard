/*
 * volume.c
 *
 *  Created on: Nov 10, 2021
 *      Author: luoshiheng
 */

#include "volume.h"
#define ENCODER_STEP 5

int32_t vol_counter = 0;
int32_t prev_vol_counter = 0;

void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim){
	prev_vol_counter = vol_counter;
	vol_counter = __HAL_TIM_GET_COUNTER(htim)/ENCODER_STEP;
}

int32_t getVolume(){
	return vol_counter/ENCODER_STEP;
}


Volume_State getVolume2(){
	if(vol_counter > prev_vol_counter)
		return VOLUMEUP;
	else if(vol_counter < prev_vol_counter)
		return VOLUMEDOWN;
	else return VOLUMENOACTION;
}
