/*
 * led_page.c
 *
 *  Created on: Oct 29, 2021
 *      Author: Steven
 */
#include "../../Inc/oled/led_page.h"
#include "math.h"

char *oled_color[20] = {
		"bright",
		"green",
		"red",
		"blue"
};

char *led_aura[20] = {
		"WS2812DISABLE",
		"STATICMODE",
		"BREATHMODE",
		"LOOPMODE"
};

PAGE led = {
		.title = "LED",
		.update_page = led_update,
		.on_click= led_onclick,
		.init = led_init};

int current_led = 0;
int current_selection = 0;
uint8_t led_init_value = 0;

void led_init(){
	uint32_t data[MAX_LED] = {0};
	//get the data value
	// Flash_Read_Data (LED_START_ADDR, &data, MAX_LED);

	for(int i = 0; i < MAX_LED; i++){
		if(data[i] == 0xFFFFFFFF) continue;
		for(int j = 0; j < SELECTION; j++){
			ws2812.LED_Data[i][j] = (uint8_t)(data[i] >> (8 * j));
		}
	}

	uint32_t mode = 0;
	Flash_Read_Data(LED_MODE_ADDR, &mode, 1);
	if(data[0] != 0xFFFFFFFF){
		rgb_mode = mode >> 24; //check this
	}

}

void led_flash(){
	uint32_t temp[MAX_LED] = {0};
	for(int i = 0; i < MAX_LED; i++){
		for(int j = 3; j >= 0; j--){
			temp[i] = (temp[i] << 8) | ws2812.LED_Data[i][j];
		}
		// Flash_Write_Data(LED_START_ADDR, &temp, MAX_LED);
	}

	uint32_t mode = rgb_mode;
	Flash_Write_Data(LED_MODE_ADDR, &mode, 1);
}

void led_update(){
	if(!led_init_value){
		led_init_value = 1;
		led_init();
	};
	char temp[30] = " ";

	snprintf(temp, 30, "LED : %d", current_led + 1);
	ssd1306_SetCursor(80, 20);
	ssd1306_WriteString(temp, Font_6x8, White);

	for(int i = 0; i < 4; i++){
		snprintf(temp,30,
				(i + 1) == current_selection ? "%s:%u <-- " :"%s:%u ",
				oled_color[i], ws2812.LED_Data[current_led][i]);
		ssd1306_SetCursor(0, 20 + 10* (i));
		ssd1306_WriteString(temp, Font_6x8, White);
	}
//	else{
//		snprintf(temp, 30, "Mode : %s", led_aura[rgb_mode]);
//		ssd1306_SetCursor(80, 20);
//		ssd1306_WriteString(temp, Font_6x8, White);
//
//		for(int i = 0; i < 4; i++){
//			snprintf(temp,30,
//					(i + 1) == current_selection ? "%s <-- " :"%s ",
//					led_aura);
//			ssd1306_SetCursor(0, 20 + 10* (i));
//			ssd1306_WriteString(temp, Font_6x8, White);
//		}
//	}
}

void led_onclick(char *combination, int charNum){
	// insert different keybinds combination here
	if(charNum > 1) return;
	//Ascii didnt lie between 128 - 255
	//Left arrow 129
	//right arrow 130
	//Up arrow 131
	//Down arrow 132
	if(combination[0] == 13){//enter
		led_flash();
	}

	switch(combination[0]){
		case 130:
			//left
			if(current_selection == 0){
				//save the led data here
//				led_flash();
				current_led = (current_led + 1) % (MAX_LED);
				current_selection = 0;
			}
			else{//if value > 1
				ws2812.LED_Data[current_led][current_selection - 1] = max(0, ws2812.LED_Data[current_led][current_selection - 1] - 1);
			}
			break;
		case 129:
			//right
			if(current_selection == 0){
//				led_flash();
				current_led = (current_led - 1) < 0? MAX_LED - 1: (current_led - 1) % (MAX_LED);
				current_selection = 0;
			}
			else{//if value > 1
				ws2812.LED_Data[current_led][current_selection - 1] = min(255, ws2812.LED_Data[current_led][current_selection - 1] + 1);
			}
			break;
		case 131:
			//up
			current_selection = max(0, (current_selection - 1) % (SELECTION + 1));
			break;
		case 132:
			//down fix bug
			current_selection = (current_selection + 1) % (SELECTION + 1);
			break;

	}
//else{ //enter RGB mode
//	switch(combination[0]){
//		case 129:
//			//left
//			if(current_selection == 0){
//				//save the led data here
//				current_led = (current_led + 1) % (MAX_LED + 1);
//				current_selection = 0;
//			}
//			break;
//		case 130:
//			//right
//			if(current_selection == 0){
//				current_led = (current_led - 1) < 0? MAX_LED: (current_led - 1) % (MAX_LED + 1);
//				current_selection = 0;
//			}
//			else{
//				rgb_mode = current_selection - 1; //assuming enumeration
//			}
//			break;
//		case 131:
//			//up
//			current_selection = max(0, (current_selection - 1) % (SELECTION + 1));
//			break;
//		case 132:
//			//down fix bug
//			current_selection = (current_selection + 1) % (SELECTION + 1);
//			break;
//
//	}
//}
	led_update();
}

void led_page_update(){

}
