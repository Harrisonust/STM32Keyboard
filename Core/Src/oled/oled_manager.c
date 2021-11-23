/*
 * oled_manager.c
 *
 *  Created on: Oct 29, 2021
 *      Author: Steven
 */

#include "../../Inc/oled/oled_manager.h"

extern PAGE status;
extern PAGE led;
extern PAGE macro;
extern PAGE finger;
extern PAGE rgb_pattern;

int currentPage = 0;
PAGE *page_array[] = {&status, &rgb_pattern, &led, &macro, &finger};

void oled_ui_init(){
	ssd1306_Init();
	//set up the line division
	for(int i = LINE_POSITION; i < LINE_END; i++){
		ssd1306_Line(0, i, SSD1306_WIDTH, i, White);
	}
	oled_update_page();
}

void oled_clear_title(){

	for(int i = 0; i <  LINE_POSITION; i++){
		ssd1306_Line(0, i, SSD1306_WIDTH, i, Black);
	}

}

void oled_clear_menu(){
	for(int i = LINE_END; i < SSD1306_HEIGHT; i++){
		ssd1306_Line(0, i, SSD1306_WIDTH, i, Black);
	}
}

void oled_update_page(){
	oled_clear_title();
	oled_clear_menu();
	ssd1306_SetCursor(0, 1);
	ssd1306_WriteString((page_array[currentPage])->title, Font_7x10, White);
	(page_array[currentPage]->update_page)();
	ssd1306_UpdateScreen();
}

void oled_next_page(){
	currentPage = (currentPage + 1) % (sizeof(page_array)/sizeof(*page_array));
	oled_update_page();
}

void oled_on_click_page(char *array, int arrayNum){
	oled_clear_menu();
	(page_array[currentPage]->on_click)(array, arrayNum);
	ssd1306_UpdateScreen();
}




