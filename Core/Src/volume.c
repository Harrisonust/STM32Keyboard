/*
 * volume.c
 *
 *  Created on: Nov 10, 2021
 *      Author: luoshiheng
 */

#include "volume.h"

#include "HID_code.h"
#include "host_OS.h"
#include "key_handler.h"

int32_t vol_counter = 0;
int32_t prev_vol_counter = 0;
void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim) {
    prev_vol_counter = vol_counter;
    vol_counter = __HAL_TIM_GET_COUNTER(htim) / ENCODER_STEP;
}

/**
 * TODO: having some bugs in encoder it is too sensitive
 */

Volume_State update_volume() {
    if (vol_counter > prev_vol_counter)
        return VOLUME_UP;
    else if (vol_counter < prev_vol_counter)
        return VOLUME_DOWN;
    else
        return VOLUME_NO_ACTION;
}

extern OS_TYPE OS_type;
void volume_handler() {
    Volume_State vol_state = update_volume();
    KeyModifier m = {0};
    if (vol_state == VOLUME_DOWN) {
        if (OS_type == OS_MAC)
            send_key(0x80, m);
        if (OS_type == OS_LINUX)
            send_key(KEY_F12, m);  //volume up
    } else if (vol_state == VOLUME_UP) {
        if (OS_type == OS_MAC)
            send_key(0x81, m);
        if (OS_type == OS_LINUX)
            send_key(KEY_F11, m);  //volume down
    } else if (vol_state == VOLUME_NO_ACTION) {
    }
}