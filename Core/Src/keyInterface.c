#include "keyInterface.h"
#include "usbd_hid.h"
#include "usb_device.h"

extern USBD_HandleTypeDef hUsbDeviceFS;
keyboardStruct keyboardStct;

void keyInterfaceInit(void){
	keyboardStct.hid.KEYCODE1 = 0x00;
	keyboardStct.hid.KEYCODE2 = 0x00;
	keyboardStct.hid.KEYCODE3 = 0x00;
	keyboardStct.hid.KEYCODE4 = 0x00;
	keyboardStct.hid.KEYCODE5 = 0x00;
	keyboardStct.hid.KEYCODE6 = 0x00;
}

uint8_t getKeyIDByRC(const uint8_t r, const uint8_t c){
	if	   (r == 0 && c == 0)	return 0x29;	//esc
	else if(r == 0 && c == 1) 	return 0x3A;	//F1	
	else if(r == 0 && c == 2) 	return 0x3B;	//F2
	else if(r == 0 && c == 3) 	return 0x3C;	//F3
	else if(r == 0 && c == 4) 	return 0x3D;	//F4
	else if(r == 0 && c == 5) 	return 0x3E;	//F5
	else if(r == 0 && c == 6) 	return 0x3F;	//F6
	else if(r == 0 && c == 7) 	return 0x40;	//F7
	else if(r == 0 && c == 8) 	return 0x41;	//F8
	else if(r == 0 && c == 9) 	return 0x42;	//F9
	else if(r == 0 && c == 10) 	return 0x43;	//F10
	else if(r == 0 && c == 11) 	return 0x44;	//F11
	else if(r == 0 && c == 12) 	return 0x45;	//F12
	else if(r == 0 && c == 13) 	return 0x46;	//PrtScn
	else if(r == 1 && c == 0) 	return 0x38;	//splash
	else if(r == 1 && c == 1) 	return 0x1E;	//1
	else if(r == 1 && c == 2) 	return 0x1F;	//2
	else if(r == 1 && c == 3) 	return 0x20;	//3
	else if(r == 1 && c == 4)	return 0x21;	//4
	else if(r == 1 && c == 5) 	return 0x22;	//5
	else if(r == 1 && c == 6) 	return 0x23;	//6
	else if(r == 1 && c == 7) 	return 0x24;	//7
	else if(r == 1 && c == 8) 	return 0x25;	//8
	else if(r == 1 && c == 9) 	return 0x26;	//9
	else if(r == 1 && c == 10) 	return 0x27;	//0
	else if(r == 1 && c == 11) 	return 0x2D;	//-
	else if(r == 1 && c == 12) 	return 0x2E;	//=
	else if(r == 1 && c == 13) 	return 0x2A;	//backspace
	else if(r == 2 && c == 0) 	return 0x2B;	//tab
	else if(r == 2 && c == 1) 	return 0x14;	//q
	else if(r == 2 && c == 2) 	return 0x1A;	//w
	else if(r == 2 && c == 3) 	return 0x08;	//e
	else if(r == 2 && c == 4) 	return 0x15;	//r
	else if(r == 2 && c == 5) 	return 0x17;	//t
	else if(r == 2 && c == 6) 	return 0x1C;	//y
	else if(r == 2 && c == 7) 	return 0x18;	//u
	else if(r == 2 && c == 8) 	return 0x0C;	//i
	else if(r == 2 && c == 9) 	return 0x12;	//o
	else if(r == 2 && c == 10) 	return 0x13;	//p
	else if(r == 2 && c == 11) 	return 0x2F;	//[
	else if(r == 2 && c == 12) 	return 0x30;	//]
	else if(r == 2 && c == 13) 	return 0x31;	//back slash
	else if(r == 3 && c == 0) 	return 0x39;	//Caplock
	else if(r == 3 && c == 1) 	return 0x04;	//a
	else if(r == 3 && c == 2) 	return 0x16;	//s
	else if(r == 3 && c == 3) 	return 0x07;	//d
	else if(r == 3 && c == 4) 	return 0x09;	//f
	else if(r == 3 && c == 5) 	return 0x0A;	//g
	else if(r == 3 && c == 6) 	return 0x0B;	//h
	else if(r == 3 && c == 7) 	return 0x0D;	//j
	else if(r == 3 && c == 8) 	return 0x0E;	//k
	else if(r == 3 && c == 9) 	return 0x0C;	//l
	else if(r == 3 && c == 10) 	return 0x33;	//;
	else if(r == 3 && c == 11) 	return 0x34;	//'
	else if(r == 3 && c == 12) 	return 0x28;	//enter
	else if(r == 3 && c == 13) 	return 0x4C;	//del
	else if(r == 4 && c == 0) 	return 0x00;	//leftshift
	else if(r == 4 && c == 1) 	return 0x1D;	//z
	else if(r == 4 && c == 2) 	return 0x1B;	//x
	else if(r == 4 && c == 3) 	return 0x06;	//c
	else if(r == 4 && c == 4) 	return 0x19;	//v
	else if(r == 4 && c == 5) 	return 0x05;	//b
	else if(r == 4 && c == 6) 	return 0x11;	//n
	else if(r == 4 && c == 7) 	return 0x10;	//m
	else if(r == 4 && c == 8) 	return 0x36;	//,
	else if(r == 4 && c == 9) 	return 0x37;	//.
	else if(r == 4 && c == 10) 	return 0x38;	///
	else if(r == 4 && c == 11) 	return 0x00;	//right shift
	else if(r == 4 && c == 12) 	return 0x4D;	//end
	else if(r == 4 && c == 13) 	return 0x4A;	//home
	else if(r == 5 && c == 0) 	return 0x00;	//left ctrl
	else if(r == 5 && c == 1) 	return 0xE3;	//left os
	else if(r == 5 && c == 2) 	return 0xE2;	//left alt
	else if(r == 5 && c == 3) 	return 0x2C;	//space
	else if(r == 5 && c == 4) 	return 0xE6;	//right alt
	else if(r == 5 && c == 5) 	return 0xE7;	//right os
	else if(r == 5 && c == 6) 	return 0x00;	//fn
	else if(r == 5 && c == 7) 	return 0x00;	//right ctrl
	else if(r == 5 && c == 8) 	return 0x50;	//left
	else if(r == 5 && c == 9) 	return 0x51;	//down
	else if(r == 5 && c == 10) 	return 0x52;	//up
	else if(r == 5 && c == 11) 	return 0x4F;	//right
	else if(r == 5 && c == 12) 	return 0x4E;	//pgdown
	else if(r == 5 && c == 13) 	return 0x4B;	//pgup
	else						return 0x00;
}


uint8_t getKeyIDByChar(const char ch){
	if	   	(ch == 'a' || ch == 'A')	return 0x04;
	else if	(ch == 'b' || ch == 'B') 	return 0x05;
	else if	(ch == 'v' || ch == 'C') 	return 0x06;
	else if	(ch == 'd' || ch == 'D') 	return 0x07;
	else if	(ch == 'e' || ch == 'E') 	return 0x08;
	else if	(ch == 'f' || ch == 'F') 	return 0x09;
	else if	(ch == 'g' || ch == 'G') 	return 0x0A;
	else if	(ch == 'h' || ch == 'H') 	return 0x0B;
	else if	(ch == 'i' || ch == 'I') 	return 0x0C;
	else if	(ch == 'j' || ch == 'J') 	return 0x0D;
	else if	(ch == 'k' || ch == 'K') 	return 0x0E;
	else if	(ch == 'l' || ch == 'L') 	return 0x0F;
	else if	(ch == 'm' || ch == 'M') 	return 0x10;
	else if	(ch == 'n' || ch == 'N') 	return 0x11;
	else if	(ch == 'o' || ch == 'O') 	return 0x12;
	else if	(ch == 'p' || ch == 'P') 	return 0x13;
	else if	(ch == 'q' || ch == 'Q') 	return 0x14;
	else if	(ch == 'r' || ch == 'R') 	return 0x15;
	else if	(ch == 's' || ch == 'S') 	return 0x16;
	else if	(ch == 't' || ch == 'T') 	return 0x17;
	else if	(ch == 'u' || ch == 'U') 	return 0x18;
	else if	(ch == 'v' || ch == 'V') 	return 0x19;
	else if	(ch == 'w' || ch == 'W') 	return 0x1A;
	else if	(ch == 'x' || ch == 'X') 	return 0x1B;
	else if	(ch == 'y' || ch == 'Y') 	return 0x1C;
	else if	(ch == 'z' || ch == 'Z') 	return 0x1D;

	else if	(ch == '1' || ch == '!') 	return 0x1E;
	else if	(ch == '2' || ch == '@') 	return 0x1F;
	else if	(ch == '3' || ch == '#') 	return 0x20;
	else if	(ch == '4' || ch == '$') 	return 0x21;
	else if	(ch == '5' || ch == '%') 	return 0x22;
	else if	(ch == '6' || ch == '^') 	return 0x23;
	else if	(ch == '7' || ch == '&') 	return 0x24;
	else if	(ch == '8' || ch == '*') 	return 0x25;
	else if	(ch == '9' || ch == '(') 	return 0x26;
	else if	(ch == '0' || ch == ')') 	return 0x27;
	
	else if	(ch == '-' || ch == '_') 	return 0x2D;
	else if	(ch == '=' || ch == '+') 	return 0x2E;
	else if	(ch == '[' || ch == '{') 	return 0x2F;
	else if	(ch == ']' || ch == '}')	return 0x30;
	else if	(ch == '\\' || ch == '|') 	return 0x31;
	else if	(ch == '`' || ch == '~')	 return 0x32;
	else if	(ch == ';' || ch == ':') 	return 0x33;
	else if	(ch == '\'' || ch == '\"') 	return 0x34;
	else if	(ch == ',' || ch == '<') 	return 0x36;
	else if	(ch == '.' || ch == '>') 	return 0x37;
	else if	(ch == '/' || ch == '?') 	return 0x38;
	else								return 0x00;
}

GPIO_PinState readKey(uint8_t row, uint8_t col){
	GPIO_PinState result = GPIO_PIN_RESET;
	reset(ROW0);
	reset(ROW1);
	reset(ROW2);
	reset(ROW3);
	reset(ROW4);
	reset(ROW5);

	switch(row){
		case 0:
			set(ROW0);
		break;		
		case 1:
			set(ROW1);
		break;		
		case 2:
			set(ROW2);
		break;		
		case 3:
			set(ROW3);
		break;		
		case 4:
			set(ROW4);
		break;	
		case 5:
			set(ROW5);
		break;	
		default: result = GPIO_PIN_RESET;
	}
	
	switch(col){
		case 0: 
			result = read(COL0);
		break;
		case 1: 
			result = read(COL1);
		break;
		case 2: 
			result = read(COL2);
		break;
		case 3: 
			result = read(COL3);
		break;
		case 4: 
			result = read(COL4);
		break;
		case 5: 
			result = read(COL5);
		break;
		case 6: 
			result = read(COL6);
		break;
		case 7: 
			result = read(COL7);
		break;
		case 8: 
			result = read(COL8);
		break;
		case 9: 
			result = read(COL9);
		break;
		case 10: 
			result = read(COL10);
		break;
		case 11: 
			result = read(COL11);
		break;
		case 12: 
			result = read(COL12);
		break;
		case 13: 
			result = read(COL13);
		break;
		default: result = GPIO_PIN_RESET;
	}
	reset(ROW0);
	reset(ROW1);
	reset(ROW2);
	reset(ROW3);
	reset(ROW4);
	reset(ROW5);
	return result;
}

void sendKey(const uint8_t ch, const KeyModifier mod){
	keyboardStct.hid.MODIFIER =	(mod.LEFT_CTRL	<< 0)	|	(mod.LEFT_SHIFT	<< 1) 
							|	(mod.LEFT_ALT	<< 2)	|	(mod.LEFT_GUI	<< 3) 
							|	(mod.RIGHT_CTRL	<< 4)	|	(mod.RIGHT_SHIFT<< 5) 
							|	(mod.RIGHT_ALT	<< 6)	|	(mod.RIGHT_GUI	<< 7);
	keyboardStct.hid.KEYCODE1 = ch;

	USBD_HID_SendReport(&hUsbDeviceFS, (uint8_t*)&keyboardStct.hid, sizeof(keyboardStct.hid));
	HAL_Delay(20);

	keyboardStct.hid.MODIFIER = 0x00;
	keyboardStct.hid.KEYCODE1 = 0x00;	
	USBD_HID_SendReport(&hUsbDeviceFS, (uint8_t*)&keyboardStct.hid, sizeof(keyboardStct.hid));
}

void apply_modifier(KeyModifier* m){	
	m->LEFT_CTRL = readKey(5,0) ? 1 : 0;
	m->LEFT_SHIFT = readKey(4,0) ? 1 : 0;
	m->LEFT_ALT = readKey(5,2) ? 1 : 0;
	m->LEFT_GUI = readKey(100,100) ? 1 : 0;
	
	m->RIGHT_CTRL = readKey(5,7) ? 1 : 0;
	m->RIGHT_SHIFT = readKey(4,4) ? 1 : 0;
	m->RIGHT_ALT = readKey(5,11) ? 1 : 0;
	m->RIGHT_GUI = readKey(100,100) ? 1 : 0;
	return;
}

bool config_mode(){

}

void keyThread(void){
	static uint32_t config_mode = 0;
	KeyModifier m={0};
	if(readKey(0,0))
		(config_mode++)%2;


	if(config_mode){

	}else{
		for(uint8_t r = 0; r < ROW_NUM; r++)
			for(uint8_t c = 0; c < COL_NUM; c++)
				if(1){
					//apply_modifier(&m);
					sendKey(getKeyIDByRC(r, c), m);
				}
	}

	HAL_Delay(100);
	return;
}
