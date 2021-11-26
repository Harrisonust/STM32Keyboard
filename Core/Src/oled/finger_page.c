/*
 * finger_page.c
 *
 *  Created on: Nov 19, 2021
 *      Author: Steven
 */
#include "finger_page.h"

uint8_t current_page = 0;

PAGE finger = {
		.title = "Fingerprint",
		.update_page = finger_update,
		.on_click = finger_onclick,
		.init = NULL
};

finger_page page_mode = DEFAULT;

uint8_t fingerprint_mode = 0;
uint8_t macro_mode = 0;
//the function of the fingerprint is just to set macro and
//fingerprint.

void finger_update(){
	char temp[30];
	snprintf(temp, 30, "Set Fingerprint");
	ssd1306_SetCursor(0, 20);
	ssd1306_WriteString(temp, Font_6x8, White);

	snprintf(temp, 30, "Enter to Start");
	ssd1306_SetCursor(0, 30);
	ssd1306_WriteString(temp, Font_6x8, White);

	if(fingerprint_mode >= 0){
		snprintf(temp, 30, "Finger %s", fingerprint_mode == 0? "Recorded" : "Error");
		ssd1306_SetCursor(0, 40);
		ssd1306_WriteString(temp, Font_6x8, White);
	}

	uint16_t template_num = get_template_number();
	snprintf(temp, 30, template_num == 0 ? "No Finger Saved" : "Finger Saved");
	ssd1306_SetCursor(0, 50);
	ssd1306_WriteString(temp, Font_6x8, White);
}

void finger_onclick(char *combination, int charNum){

	if(page_mode == DEFAULT && current_page == 0){
		if(combination[0] == 13){
			//start scanning the shit
			fingerprint_mode = save_fingerprint(0);
		}

		else if(combination[0] == 129){
			//start scanning the shit
			reset_database();
			fingerprint_mode = -1;

		}
		else if(combination[0] == 130){
			check_fingerprint();

		}
	}
	finger_update();
}
