/*
 * macro_page.h
 *
 *  Created on: Nov 3, 2021
 *      Author: Steven
 */

#ifndef INC_OLED_MACRO_PAGE_H_
#define INC_OLED_MACRO_PAGE_H_

#define MAX_MACRO 2
#define START_ADDR 0x0807F800

#include "page_template.h"
#include "linked_list.h"
#include "flash.h"

typedef enum {MAIN, KEY, COMBINATION} MACRO_PAGE;

typedef struct{
	char keybind;
	Node *macro;
}Macro;

extern

void macro_update();
void macro_onclick(char *input, int charNum);
void macro_page_update();

#endif /* INC_OLED_MACRO_PAGE_H_ */
