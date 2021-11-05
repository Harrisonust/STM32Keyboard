/*
 * oled_manager.h
 *
 *  Created on: Oct 29, 2021
 *      Author: Steven
 */

#ifndef INC_OLED_MANAGER_H_
#define INC_OLED_MANAGER_H_

#include "ssd1306.h"
#include "page_template.h"

#define LINE_POSITION 12
#define LINE_THICKNESS 5
#define LINE_END (LINE_POSITION + LINE_THICKNESS)

extern PAGE status;

//int currentPage = 0;
//PAGE *page_array[1] = {&status};

void oled_ui_init();
void oled_clear_title();
void oled_clear_menu();
void oled_update_page();
void oled_next_page();
void oled_on_click_page(char *array, int arrayNum);
void oled_specfic_on_click(int page_num);


#endif /* INC_OLED_MANAGER_H_ */
