/*
 * volume.h
 *
 *  Created on: Nov 10, 2021
 *      Author: luoshiheng
 */

#ifndef INC_VOLUME_H_
#define INC_VOLUME_H_
#include "main.h"

#define ENCODER_STEP 4

typedef enum {
    VOLUME_NO_ACTION,
    VOLUME_UP,
    VOLUME_DOWN
} Volume_State;

void encoder_init(void);

Volume_State update_volume(void);

void volume_handler(void);

#endif /* INC_VOLUME_H_ */
