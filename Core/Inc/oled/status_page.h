/*
 * status_page.h
 *
 *  Created on: Oct 29, 2021
 *      Author: Steven
 */

#ifndef INC_STATUS_PAGE_H_
#define INC_STATUS_PAGE_H_

#define MAX_BATT 2048
#define MIN_BATT 1639

#include "page_template.h"
#include "stm32f1xx_hal.h"

enum connection {NONE, BLUETOOTH};

extern ADC_HandleTypeDef hadc1;

void status_update();
void status_onclick(char *combination, int charNum);

#endif /* INC_STATUS_PAGE_H_ */
