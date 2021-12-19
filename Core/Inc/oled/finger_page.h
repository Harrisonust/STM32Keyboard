/*
 * finger_page.h
 *
 *  Created on: Nov 19, 2021
 *      Author: Steven
 */

#ifndef INC_OLED_FINGER_PAGE_H_
#define INC_OLED_FINGER_PAGE_H_

#include "page_template.h"
#include "stm32f1xx_hal.h"
#include "fingerprint.h"

typedef enum state {DEFAULT,FINGER, MACRO} finger_page;

void finger_update();
void finger_onclick(char *combination, int charNum);

#endif /* INC_OLED_FINGER_PAGE_H_ */
