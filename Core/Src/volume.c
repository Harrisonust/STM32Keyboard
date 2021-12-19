/*
 * volume.c
 *
 *  Created on: Nov 10, 2021
 *      Author: luoshiheng
 */

#include "volume.h"

int32_t vol_counter = 0;
int32_t prev_vol_counter = 0;
void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim){
	prev_vol_counter = vol_counter;
	vol_counter = __HAL_TIM_GET_COUNTER(htim)/ENCODER_STEP;
}

Volume_State updateVolume(){
	if(vol_counter > prev_vol_counter)
		return VOLUMEUP;
	else if(vol_counter < prev_vol_counter)
		return VOLUMEDOWN;
	else return VOLUMENOACTION;
}
