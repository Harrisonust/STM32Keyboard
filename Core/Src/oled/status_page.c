#include "../../Inc/oled/status_page.h"

PAGE status = {
		.title = "Status",
		.update_page = status_update,
		.on_click= status_onclick,
		.init = NULL

};


extern KEYBOARD_CONNECTION_MODE keyboard_connection_mode;

void status_update(){
	//Handle Bluetooth
	static char temp[30] = "";
	if(keyboard_connection_mode == KEYBOARD_CONNECTION_MODE_CABLE){
		snprintf(temp, 30, "MODE: CABLE");
	}else if(keyboard_connection_mode == KEYBOARD_CONNECTION_MODE_BLUETOOTH){
		snprintf(temp, 30, "MODE: BLUETOOTH");
	}
	ssd1306_SetCursor(0, 20);
	ssd1306_WriteString(temp, Font_7x10, White);

	//Handle Battery
	uint32_t battery_value = HAL_ADC_GetValue(&hadc1);
	battery_value = ((battery_value - MIN_BATT) * 100) / (MAX_BATT - MIN_BATT);


	snprintf(temp, 30, "Battery : %u %%", battery_value);
	ssd1306_SetCursor(0, 40);
	ssd1306_WriteString(temp, Font_7x10, White);
}

void status_onclick(char *combination, int charNum){

	if(combination[0] == 13){
		if(keyboard_connection_mode == KEYBOARD_CONNECTION_MODE_CABLE)
			keyboard_connection_mode = KEYBOARD_CONNECTION_MODE_BLUETOOTH;
		else if(keyboard_connection_mode == KEYBOARD_CONNECTION_MODE_BLUETOOTH)
			keyboard_connection_mode = KEYBOARD_CONNECTION_MODE_CABLE;
	}
	status_update();
}
