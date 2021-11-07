/*
 * led_page.c
 *
 *  Created on: Oct 29, 2021
 *      Author: Steven
 */
#include "../../Inc/oled/led_page.h"
#include "math.h"


PAGE led = {
		.title = "LED",
		.update_page = led_update,
		.on_click= led_onclick};

int current_led = 0;
int current_selection = 0;

void led_update(){
	char temp[20] = " ";

	sprintf(temp, "LED : %d", current_led + 1);
	ssd1306_WriteString(temp, Font_6x8, White);

	for(int i = 0; i < 4; i++){
		sprintf(temp,
				i == current_selection ? "%s	<-- %d" :"%s	    %d",
				color[i], ws2812.LED_Data[current_led][i]);
		ssd1306_SetCursor(0, 20 + 15* (i));
		ssd1306_WriteString(temp, Font_6x8, White);
	}
}

void led_onclick(char *combination, int charNum){
	// insert different keybinds combination here
	if(charNum > 1) return;
	//Ascii didnt lie between 128 - 255
	//Left arrow 129
	//right arrow 130
	//Up arrow 131
	//Down arrow 132
	switch(combination[0]){
		case 129:
			//left
			if(current_selection == 0){
				current_led = (current_led + 1) % (MAX_LED);
				current_selection = 0;
			}
			else{//if value > 1
				ws2812.LED_Data[current_led][current_selection - 1] = max(0, ws2812.LED_Data[current_led][current_selection - 1] - 1);
			}
			break;
		case 130:
			//right
			if(current_selection == 0){
				current_led = (current_led - 1) % (MAX_LED);
				current_selection = 0;
			}
			else{//if value > 1
				ws2812.LED_Data[current_led][current_selection - 1] = min(255, ws2812.LED_Data[current_led][current_selection - 1] + 1);
			}
			break;
		case 131:
			//up
			current_selection = (current_selection - 1) % (SELECTION + 1);
			break;
		case 132:
			current_selection = (current_selection + 1) % (SELECTION + 1);

	}
	led_page_update();
}

void led_page_update(){

}
