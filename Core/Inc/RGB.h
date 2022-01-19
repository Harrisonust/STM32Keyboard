/*
 * RGB.h
 *
 *  Created on: Nov 2, 2021
 *      Author: luoshiheng
 */

#ifndef INC_WS2812_H_
#define INC_WS2812_H_
#include <stdlib.h>

#include "main.h"
#include "matrix_button.h"

#define RESET_TIMEOUT 50
#define MAX_LED 80

typedef struct {
    uint32_t LED_num;
    TIM_HandleTypeDef* tim;
    uint32_t channel;
    uint32_t pwmData[(24 * MAX_LED) + RESET_TIMEOUT];
    uint8_t LED_Data[MAX_LED][4];  // make it dynamic later
    uint8_t brightness;            // smaller means lighter
} WS2812;

typedef struct {
    uint32_t LED_num;
    TIM_HandleTypeDef* tim;
    uint32_t channel;
} WS2812_InitStruct;

typedef struct {
    uint8_t R;
    uint8_t G;
    uint8_t B;
} RGB;

typedef enum {
    WS2812DISABLE,
    STATICMODE,
    BREATHMODE,
    LOOPMODE,
    STATICBREATHMODE,
    LAYEREDMODE,
    NUM_OF_RGB_MODE
} WS2812Mode;

#define rgb(r, g, b) \
    { .R = r, .G = g, .B = b }

#define WS2812_WHITE \
    { .R = 255, .G = 255, .B = 255 }
#define WS2812_BLUE \
    { .R = 0, .G = 0, .B = 255 }
#define WS2812_RED \
    { .R = 255, .G = 0, .B = 0 }
#define WS2812_GREEN \
    { .R = 0, .G = 255, .B = 0 }
#define WS2812_PURPLE \
    { .R = 255, .G = 0, .B = 255 }
#define WS2812_YELLOW \
    { .R = 255, .G = 255, .B = 0 }
#define WS2812_CYAN \
    { .R = 0, .G = 255, .B = 255 }
#define WS2812_ORANGE \
    { .R = 255, .G = 30, .B = 0 }
#define WS2812_GOLD \
    { .R = 255, .G = 215, .B = 0 }
#define WS2812_OLIVE \
    { .R = 128, .G = 128, .B = 0 }
#define WS2812_BROWN \
    { .R = 139, .G = 69, .B = 19 }
#define WS2812_PINK \
    { .R = 255, .G = 20, .B = 147 }
#define WS2812_NONE \
    { .R = 0, .G = 0, .B = 0 }

#define WS2812_ONECODE 32
#define WS2812_ZEROCODE 16

// specify timer and timer channel here
void WS2812_init(WS2812* instance, WS2812_InitStruct* stuc);

void WS2812_Deinit(WS2812* ws);

// set led color by three uint8_t value corresponding to rgb
void WS2812_LED_Set(WS2812* ws, const uint32_t LED_index, const uint8_t R, const uint8_t G, const uint8_t B);

// set brightness lower the brighter
void WS2812_LED_SetBrightness(WS2812* ws, const uint8_t brightness);

// set led color by a RGB value
void WS2812_LED_SetRGB(WS2812* ws, const uint32_t LED_index, const RGB rgb);

//
void WS2812_LED_ClearRGB(WS2812* ws, const uint32_t LED_index);

// three different patterns of led which is called inside WS2812_LED_Task
void WS2812_Loop_Pattern(WS2812* ws);
void WS2812_Breath_Pattern(WS2812* ws);
void WS2812_Static_Pattern(WS2812* ws);
void WS2812_sendData(WS2812* ws);

// an infinite loop
void WS2812_LED_Task(const void* par);

void switch_RGB_backlight(Button* b, ButtonEvent e);
#endif /* INC_WS2812_H_ */
