/*
 * layout_page.h
 *
 *  Created on: Nov 3, 2021
 *      Author: Steven
 */

#ifndef INC_OLED_LAYOUT_PAGE_H_
#define INC_OLED_LAYOUT_PAGE_H_

#include "page_template.h"

char *selection[20] = {
		"test1",
		"test2",
		"test3",
		"test4",
		"test5"
};

void layout_update();
void layout_onclick(char *combination, int charNum);

#endif /* INC_OLED_LAYOUT_PAGE_H_ */
