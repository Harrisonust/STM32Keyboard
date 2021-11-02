#ifndef KEYINTERFACE_H
#define KEYINTERFACE_H
#include "main.h"

#define ROW_NUM 6
#define COL_NUM 14


typedef struct{
	uint8_t MODIFIER;
	uint8_t RESERVED;
	uint8_t KEYCODE1;
	uint8_t KEYCODE2;
	uint8_t KEYCODE3;
	uint8_t KEYCODE4;
	uint8_t KEYCODE5;
	uint8_t KEYCODE6;
} keyboardHID;

typedef struct{
	uint8_t LEFT_CTRL;
	uint8_t LEFT_SHIFT;
	uint8_t LEFT_ALT;
	uint8_t LEFT_GUI;
	uint8_t RIGHT_CTRL;
	uint8_t RIGHT_SHIFT;
	uint8_t RIGHT_ALT;
	uint8_t RIGHT_GUI;
}KeyModifier;

typedef struct{
	GPIO_TypeDef *keyboardEnablePort;
	uint16_t keyboardEnablePin;
	keyboardHID hid;
}keyboardStruct;


void keyThread(void);

void keyInterfaceInit(void);

GPIO_PinState readKey(uint8_t row, uint8_t col);

void sendKey(const uint8_t ch, const KeyModifier mod);

#endif
