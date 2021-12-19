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

typedef enum{
    VOLUMENOACTION,
    VOLUMEUP,
    VOLUMEDOWN
}Volume_State;

Volume_State updateVolume();

#endif /* INC_VOLUME_H_ */
