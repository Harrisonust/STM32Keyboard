/*
 * layout_page.c
 *
 *  Created on: Nov 3, 2021
 *      Author: Steven
 */
#include "layout_page.h"

int layout_selection = 5;
int curr_layout_selection = 0;

PAGE layout = {
		.title = "Layout",
		.update_page = layout_update,
		.on_click= layout_onclick,
		.init = NULL

};

void layout_update(){
	char temp[20];
		for(int i = 0; i < 3; i++){
			sprintf(temp,
					i == 0 ? "%s <--" :"%s",
					selection[(i + layout_selection) % curr_layout_selection]);
			ssd1306_SetCursor(0, 20 + 15* (i));
			ssd1306_WriteString(temp, Font_7x10, White);
		}
}

void layout_onclick(char *combination, int charNum){
	layout_selection = (layout_selection + 1)% curr_layout_selection;
	//insert function to handle it
	layout_update();
}

