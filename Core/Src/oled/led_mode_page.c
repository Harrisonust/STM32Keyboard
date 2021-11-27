/*
 * led_mode_page.c
 *
 *  Created on: Nov 23, 2021
 *      Author: luoshiheng
 */

#include "led_mode_page.h"

extern WS2812Mode rgb_mode;

PAGE rgb_pattern = {
		.title = "RGB Mode",
		.update_page = led_mode_update,
		.on_click= led_mode_onclick,
		.init = NULL

};

void led_mode_update(){
    static char temp[30] = "";
	switch(rgb_mode){
        case STATICMODE:
            sprintf(temp, "STATICMODE");
            break;
        case BREATHMODE:
            sprintf(temp, "BREATHMODE");
            break;
        case LOOPMODE:
            sprintf(temp, "LOOPMODE");
            break;
        case WS2812DISABLE:
            sprintf(temp, "WS2812DISABLE");
            break;
        default:
        	sprintf(temp, "ERROR");
        	break;
    }
	ssd1306_SetCursor(0, 20);
	ssd1306_WriteString(temp, Font_7x10, White);
}

void led_mode_onclick(char *combination, int charNum){
	if(combination[0] == 13){
		rgb_mode = (++rgb_mode) % NUM_OF_RGB_MODE;
		led_mode_update();
	}
}
