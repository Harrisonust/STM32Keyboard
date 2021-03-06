/*
 * led_page.h
 *
 *  Created on: Oct 29, 2021
 *      Author: Steven
 */

#ifndef INC_LED_PAGE_H_
#define INC_LED_PAGE_H_

#include "page_template.h"
#include "RGB.h"
#include "flash.h"

#define min(a,b) (a > b) ? b : a
#define max(a,b) (a > b) ? a : b

#define LED_START_ADDR 0x0807D800
#define LED_MODE_ADDR 0x0807E800

#define SELECTION 4

extern WS2812 ws2812;
extern WS2812Mode rgb_mode;

//uint8_t value[3] = {0};
//// insert init value handler in here

void led_update();
void led_init();
void led_onclick(char *combination, int charNum);
void led_page_update();

#endif /* INC_LED_PAGE_H_ */
