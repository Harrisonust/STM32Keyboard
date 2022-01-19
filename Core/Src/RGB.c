/*
 * RGB.c
 *
 *  Created on: Nov 2, 2021
 *      Author: luoshiheng
 */
#include "RGB.h"

#include "cmsis_os.h"
#include "key_handler.h"
#include "led_page.h"
#include "ssd1306.h"
#include "stdio.h"

uint8_t datasentflag = 0;
WS2812 ws2812;
RGB defaultColorList[] = {WS2812_WHITE, WS2812_BLUE, WS2812_RED, WS2812_GREEN, WS2812_YELLOW, WS2812_CYAN, WS2812_PURPLE, WS2812_ORANGE, WS2812_PINK, WS2812_BROWN};
extern TIM_HandleTypeDef htim1;
// extern uint32_t last_keyinterrupt_tick;

int16_t constrain(const int16_t val, const int16_t lower, const int16_t upper) {
    if (val < lower)
        return lower;
    if (val > upper)
        return upper;
    return val;
}

void WS2812_init(WS2812* ws, WS2812_InitStruct* stuc) {
    ws->tim = stuc->tim;
    ws->channel = stuc->channel;
    ws->LED_num = stuc->LED_num;
    ws->brightness = 1;
}

void WS2812_Deinit(WS2812* ws) {
    // Dont think we actually need this
}

void WS2812_LED_SetBrightness(WS2812* ws, const uint8_t brightness) {
    ws->brightness = brightness;
}

void WS2812_LED_Set(WS2812* ws, const uint32_t index, const uint8_t R, const uint8_t G, const uint8_t B) {
    if (index < 0 || index >= ws->LED_num)
        return;
    ws->LED_Data[index][0] = index;  // make index 0 stores brightness
    ws->LED_Data[index][1] = constrain(G * (ws->brightness / 99.0), 0, 255);
    ws->LED_Data[index][2] = constrain(R * (ws->brightness / 99.0), 0, 255);
    ws->LED_Data[index][3] = constrain(B * (ws->brightness / 99.0), 0, 255);
}

void WS2812_LED_SetRGB(WS2812* ws, const uint32_t LED_index, const RGB rgb) {
    WS2812_LED_Set(ws, LED_index, rgb.R, rgb.G, rgb.B);
}

void WS2812_LED_ClearRGB(WS2812* ws, const uint32_t LED_index) {
    RGB color = rgb(0, 0, 0);
    WS2812_LED_SetRGB(ws, LED_index, color);
}

void HAL_TIM_PWM_PulseFinishedCallback(TIM_HandleTypeDef* htim) {
    HAL_TIM_PWM_Stop_DMA(&htim1, TIM_CHANNEL_1);
    datasentflag = 1;
}

void WS2812_sendData(WS2812* ws) {
    uint32_t index = 0;

    for (uint8_t i = 0; i < MAX_LED; i++) {
        uint32_t color = ((ws->LED_Data[i][1] << 16) | (ws->LED_Data[i][2] << 8) | (ws->LED_Data[i][3]));

        for (int8_t offset = 23; offset >= 0; offset--, index++) {
            if (color & (1 << offset))
                ws->pwmData[index] = WS2812_ONECODE;
            else
                ws->pwmData[index] = WS2812_ZEROCODE;
        }
    }

    for (uint8_t i = 0; i < RESET_TIMEOUT; index++, i++)
        ws->pwmData[index] = 0;

    HAL_TIM_PWM_Start_DMA(&htim1, TIM_CHANNEL_1, ws->pwmData, index);
    while (!datasentflag) {
    };
    datasentflag = 0;
}

static uint32_t color_index = 0;
static int32_t led_index = 0;
void WS2812_LoopTask(WS2812* ws) {
    static uint32_t counter = 0;
    led_index = counter++;
    if (led_index == ws2812.LED_num) {
        color_index++;
        led_index = 0;
        counter = 0;
    }
    if (color_index == sizeof(defaultColorList) / sizeof(RGB))
        color_index = 0;
    WS2812_LED_SetRGB(&ws2812, led_index, defaultColorList[color_index]);
}

void WS2812_BreathTask(WS2812* ws) {
    static int8_t step = 1;
    if (step == 1) {
        WS2812_LED_SetRGB(&ws2812, led_index, defaultColorList[color_index]);
        if (led_index > ws2812.LED_num - 1)
            step = -1;
    }
    if (step == -1) {
        WS2812_LED_ClearRGB(&ws2812, led_index);
        if (led_index < 0) {
            step = 1;
            color_index++;
            color_index %= 10;
        }
    }
    led_index += step;
}

void WS2812_StaticTask(WS2812* ws) {
    for (int i = 0; i < MAX_LED; i++)
        WS2812_LED_SetRGB(&ws2812, i, defaultColorList[color_index]);
}

uint8_t speed;
void WS2812_StaticBreathTask(WS2812* ws) {
    speed = 15;
    const int16_t lower_limit = -3, upper_limit = 13;
    static int8_t step = 1;
    static int16_t curr_brightness = upper_limit;
    if (step == 1 && curr_brightness >= upper_limit)
        step = -1;
    else if (step == -1 && curr_brightness <= lower_limit)
        step = 1;

    curr_brightness += step;
    int constrained_brightness = constrain(curr_brightness, 0, 10);

    WS2812_LED_SetBrightness(&ws2812, constrained_brightness);
    for (int i = 0; i < MAX_LED; i++)
        WS2812_LED_SetRGB(&ws2812, i, defaultColorList[color_index]);
}

// uint8_t speed;
// void WS2812_TheMatrixTask(WS2812* ws) {
//     speed = 15;

//     WS2812_LED_SetRGB(&ws2812, 0, (RGB)WS2812_GREEN);
// }

void WS2812_Disable(WS2812* ws) {
    for (int i = 0; i < MAX_LED; i++) {
        WS2812_LED_ClearRGB(ws, i);
    }
}

void switch_RGB_backlight(Button* b, ButtonEvent e) {
    color_index++;
    color_index %= sizeof(defaultColorList) / sizeof(RGB);
}

uint32_t brightness = 1;  // range from 0(nolight) to 99(full)
uint8_t speed = 1;        // range from 0(slowest) to 99(fastest)
WS2812Mode rgb_mode = STATICMODE;
// WS2812Mode last_rgb_mode = LOOPMODE; // TODO: keep the same mode after reboot
// extern uint8_t sleep_mode; // TODO: implement sleep mode

void WS2812_LED_Task(void const* par) {
    WS2812_InitStruct ws2812_initStruct = {.LED_num = MAX_LED, .tim = &htim1, .channel = TIM_CHANNEL_1};
    WS2812_init(&ws2812, &ws2812_initStruct);

    for (;;) {
        // if (sleep_mode) {
        //     rgb_mode = WS2812DISABLE;
        // }
        WS2812_LED_SetBrightness(&ws2812, brightness);
        switch (rgb_mode) {
        case LOOPMODE:
            WS2812_LoopTask(&ws2812);
            break;
        case BREATHMODE:
            WS2812_BreathTask(&ws2812);
            break;
        case STATICMODE:
            WS2812_StaticTask(&ws2812);
            break;
        case STATICBREATHMODE:
            WS2812_StaticBreathTask(&ws2812);
            break;
        case WS2812DISABLE:
        default:
            WS2812_Disable(&ws2812);
            break;
        }
        WS2812_sendData(&ws2812);
        speed = constrain(speed, 0, 99);
        osDelay(200 * (1 - speed / 100.0));
    }
    WS2812_Deinit(&ws2812);
}
