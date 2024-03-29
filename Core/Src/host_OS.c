#include "host_OS.h"

#include "display_icon.h"
#include "key_handler.h"
#include "main.h"
#include "ssd1306.h"

OS_TYPE OS_type = OS_LINUX;

void OS_switch(Button* b, ButtonEvent e) {
    OS_type++;
    OS_type %= OS_NUM;
    if(e == BUTTON_CLICKED)
        HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, 1);
    else
        HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, 0);
}

void switch_debug(Button* b, ButtonEvent e) {
    if(e == BUTTON_CLICKED)
        HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, 1);
    else
        HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, 0);
}

extern Display_selected_page s_page;
void OS_display_update() {
    switch (OS_type) {
    case OS_MAC:
        ssd1306_DrawPic(APPLE_ICON, 24 * 1, 1);
        break;
    case OS_LINUX:
        ssd1306_DrawPic(LINUX_ICON, 24 * 1, 1);
        break;
    case OS_WINDOWS:
        ssd1306_DrawPic(WIN_ICON, 24 * 1, 1);
        break;
    default:
        ssd1306_DrawPic(PACMAN_ICON0, 24 * 1, 1);
        break;
    }
    ssd1306_DrawRectangle(24 * 1 - 1, 0, 24 * 1 + 16, 16, s_page == DISPLAY_OS_PAGE);
}