/*
 * led_mode_page.h
 *
 *  Created on: Nov 23, 2021
 *      Author: luoshiheng
 */

#ifndef INC_OLED_LED_MODE_PAGE_H_
#define INC_OLED_LED_MODE_PAGE_H_

#include "page_template.h"
#include "stm32f1xx_hal.h"
#include "RGB.h"

void led_mode_update();
void led_mode_onclick(char *combination, int charNum);


#endif /* INC_OLED_LED_MODE_PAGE_H_ */
