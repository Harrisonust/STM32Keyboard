#include "../../Inc/oled/status_page.h"

PAGE status = {
		.title = "Status",
		.update_page = status_update,
		.on_click= status_onclick};



void status_update(){
	//Handle Bluetooth
	static char temp[30] = "";
	snprintf(temp, 30, "Bluetooth : %s","yes");
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
	status_update();
}
