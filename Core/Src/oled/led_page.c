/*
 * led_page.c
 *
 *  Created on: Oct 29, 2021
 *      Author: Steven
 */
#include "../../Inc/oled/led_page.h"
#include "math.h"

int num_selection = 3;
int current_selection = 0;

PAGE led = {
		.title = "LED",
		.update_page = led_update,
		.on_click= led_onclick};

void led_update(){
	//try to init here
	led_page_update();
}

void led_onclick(char *combination, int charNum){
	// insert different keybinds combination here
	if(charNum > 1) return;

	switch(combination[0]){
		case 1:
			//left
			value[current_selection] = max(0, value[current_selection] - 1);
			break;
		case 2:
			//right
			value[current_selection] = min(255, value[current_selection] + 1);
		case 3:
			//up
			current_selection = (current_selection - 1) % current_selection;
			break;
		case 4:
			current_selection = (current_selection + 1) % current_selection;

	}
	led_page_update();
}

void led_page_update(){
	char temp[20];
	for(int i = 0; i < 3; i++){
		sprintf(temp,
				i == current_selection ? "%s	<-- %d" :"%s	    %d",
				color[i], value[i]);
		ssd1306_SetCursor(0, 20 + 15* (i));
		ssd1306_WriteString(temp, Font_7x10, White);
	}
}
