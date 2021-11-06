/*
 * marco_page.c
 *
 *  Created on: Nov 3, 2021
 *      Author: Steven
 */
#include "macro_page.h"
#include "math.h"


PAGE macro = {
		.title = "Macro",
		.update_page = macro_update,
		.on_click = macro_onclick
};

uint8_t init = 0;
MACRO_PAGE current_macro_page = MAIN;

int current_macro = 0;

char keybind = ' ';
Node *macro_head = NULL;
Node *macro_iter = NULL;

Macro combination[MAX_MACRO];

void macro_init(){
	uint32_t data[MAX_MACRO_TEMPLATE/4]={0};
	for(int i = 0; i < MAX_MACRO; i++){
		Flash_Read_Data(START_ADDR + MAX_MACRO_TEMPLATE*i, &data, MAX_MACRO_TEMPLATE/4);
		if(data[0] != 0XFFFFFFFF){

			uint8_t internal_i = 0;
			combination[i].keybind = (char)(data[0]);
			Node *head = NULL;
			Node *iter = NULL;

			while(1){
				int index = (1 + internal_i)/ 4;
				char value = (char)(data[index] >> (8 * ((1 + internal_i )%4)) );
				if(value == '/') break;

				if(head == NULL){
					head  = iter = create_node(value);
				}
				else{
					Node *new = create_node(value);
					//link it
					iter->next = new;
					new->prev = iter;
					iter = new;
				}
				internal_i++;

			}
			combination[i].macro = head;
		}
	}

}

void macro_update(){
	//update based on the current page
	if(!init){
		init = 1;
		macro_init();
	}

	char temp[30] = "";
	sprintf(temp, "Macro Num : %d", current_macro + 1);
	ssd1306_SetCursor(0, 20);
	ssd1306_WriteString(temp, Font_7x10, White);

	switch(current_macro_page){

	case MAIN:
		sprintf(temp,"Keybind : %c",combination[current_macro].keybind);
		ssd1306_SetCursor(0, 30);
		ssd1306_WriteString(temp, Font_7x10, White);


		if(combination[current_macro].macro == NULL){
			ssd1306_SetCursor(0, 40);
			ssd1306_WriteString("Not Set", Font_7x10, White);
		}
		else{ // baseline 40
			int index = 0;
			Node *temp = combination[current_macro].macro;
			while(temp != NULL){
				ssd1306_SetCursor(index * 7, 40);
				ssd1306_WriteChar(temp->data, Font_7x10, White);
				temp = temp->next;
				index++;
			}
		}
		break;
	case KEY:
		ssd1306_SetCursor(0, 30);
		ssd1306_WriteString("Set Keybind", Font_7x10, White);

		sprintf(temp,"Keybind : %c", keybind);
		ssd1306_SetCursor(0, 40);
		ssd1306_WriteString(temp, Font_7x10, White);
		break;
	case COMBINATION:
		ssd1306_SetCursor(0, 30);
		ssd1306_WriteString("Set Keybind", Font_7x10, White);

		if(macro_head == NULL){
			ssd1306_SetCursor(0, 40);
			ssd1306_WriteString("Input Macro", Font_7x10, White);
		}
		else{ // baseline 40
			int index = 0;
			Node *temp = combination[current_macro].macro;
			while(temp != NULL){
				ssd1306_SetCursor(index * 7, 40);
				ssd1306_WriteChar(temp->data, Font_7x10, White);
				temp = temp->next;
				index++;
			}
		}
		break;
	}
}

void macro_onclick(char *input, int charNum){
	if(charNum > 1) return;

	//deal with the possible combination
	//Ascii didnt lie between 128 - 255
	//Left arrow 129
	//right arrow 130
	//Up arrow 131
	//Down arrow 132
	switch(current_macro_page){
		case MAIN:
			//deal with macro display
			//for now deal enter
			if(input[0] == 13){
				current_macro_page = KEY;
				keybind = ' ';
			}
			else if(input[0] == 129){
				current_macro = (current_macro + 1) % MAX_MACRO;
			}
			else if(input[0] == 130){
				current_macro = (current_macro - 1) % MAX_MACRO;
			}
			break;
		case KEY:
			//handle with inputing the data
			if(input[0] == 13){
				current_macro_page = COMBINATION;
				macro_head = NULL;
				macro_iter = NULL;
			}
			else{
				keybind = input[0];
			}
			break;
		case COMBINATION:
			//handle with inputting the macro
			if(input[0] == 13){
				current_macro_page = MAIN;
				{
					if(combination[current_macro].macro != NULL){
						delete_all(combination[current_macro].macro);
					}
					combination[current_macro].macro = macro_head;
					combination[current_macro].keybind = keybind;
					//insert saving node to combination
				}
				{
					//insert flash handling
					char template[MAX_MACRO_TEMPLATE] = {0}; //hard cap
					uint32_t final_data[MAX_MACRO_TEMPLATE/4] = {0};
					//insert keybind
					template[0] = combination[current_macro].keybind;
					int index = 0;
					Node *temp = macro_head;
					while(temp != NULL){
						if(index >= (MAX_MACRO_TEMPLATE - 1)) break;
						template[1 + index] = temp->data;
						temp = temp->next;
						index++;
					}
					template[1 + index] = '/';
					Str_To_uint32(template, final_data);
					HAL_Delay(1000);
					Flash_Write_Data(START_ADDR + (MAX_MACRO_TEMPLATE * current_macro), final_data, MAX_MACRO_TEMPLATE/4);
					//
				}
			} //save macro
			else if(input[0] == 127){// backspace
				if(macro_iter != NULL){
					Node *temp = macro_iter->prev;
					delete_node(macro_iter);
					if(temp == NULL){
						macro_head = NULL;
					}
					macro_iter = temp;
				}
			}
			else{
				if(macro_head == NULL){
					macro_head  = macro_iter = create_node(input[0]);
				}
				else{
					Node *new = create_node(input[0]);
					//link it
					macro_iter->next = new;
					new->prev = macro_iter;
					macro_iter = new;
				}
			}
			break;
	}
	macro_update();
}

Node* get_macro(char value){
	for(int i = 0; i < MAX_MACRO; i++){
		if(combination[i].keybind == value){
			return combination[i].macro;
		}
	}
	return NULL;
}
