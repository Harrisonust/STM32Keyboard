#include "../../Inc/oled/status_page.h"

PAGE status = {
		.title = "Status",
		.update_page = status_update,
		.on_click= status_onclick};



void status_update(){
	//Handle Bluetooth
	char temp[30] = "";
	{
		//insert helper to gain current status
	}
	sprintf(temp, "Bluetooth : %s", "yes");
	ssd1306_SetCursor(0, 20);
	ssd1306_WriteString(temp, Font_7x10, White);

	//Handle Battery
	HAL_ADC_Start(&hadc1);
	HAL_ADC_PollForConversion(&hadc1, 1000);
	uint32_t battery_value = HAL_ADC_GetValue(&hadc1);

	sprintf(temp, "Battery : %u %%", battery_value);
	ssd1306_SetCursor(0, 40);
	ssd1306_WriteString(temp, Font_7x10, White);
}

void status_onclick(char *combination, int charNum){
	status_update();
}
