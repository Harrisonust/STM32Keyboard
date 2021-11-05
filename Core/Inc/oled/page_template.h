/*
 * page_template.h
 *
 *  Created on: Oct 29, 2021
 *      Author: Steven
 */

#ifndef INC_PAGE_TEMPLATE_H_
#define INC_PAGE_TEMPLATE_H_

#include "ssd1306.h"

typedef struct{
	char title[30];
	void (*update_page)();
	void (*on_click)(char*, int);

}PAGE;

#endif /* INC_PAGE_TEMPLATE_H_ */
