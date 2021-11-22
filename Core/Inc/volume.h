/*
 * volume.h
 *
 *  Created on: Nov 10, 2021
 *      Author: luoshiheng
 */

#ifndef INC_VOLUME_H_
#define INC_VOLUME_H_
#include "main.h"
typedef enum{
    VOLUMENOACTION,
    VOLUMEUP,
    VOLUMEDOWN
}Volume_State;

int32_t getVolume();
Volume_State getVolume2();
#endif /* INC_VOLUME_H_ */
