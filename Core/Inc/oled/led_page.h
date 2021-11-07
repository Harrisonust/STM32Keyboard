/*
 * led_page.h
 *
 *  Created on: Oct 29, 2021
 *      Author: Steven
 */

#ifndef INC_LED_PAGE_H_
#define INC_LED_PAGE_H_

#include "page_template.h"

#define min(a,b) (a > b) ? b : a
#define max(a,b) (a > b) ? a : b

char *color[20] = {
		"red",
		"green",
		"blue"
};

uint8_t value[3] = {0};
// insert init value handler in here

void led_update();
void led_onclick(char *combination, int charNum);
void led_page_update();

#endif /* INC_LED_PAGE_H_ */
