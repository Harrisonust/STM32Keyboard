#include "host_OS.h"

#include "cmsis_os.h"
#include "main.h"
#include "ssd1306.h"
OS_TYPE OS_type = OS_MAC;

void OS_handler(void) {
    if (read(BTN2))
        switch_OS(NULL, BUTTON_CLICKED);
}

void switch_OS(Button* b, ButtonEvent e) {
    static uint16_t cnt = 0;
    cnt++;
    if (cnt % 2) {
        HAL_GPIO_WritePin(LED2_GPIO_Port, LED2_Pin, GPIO_PIN_SET);
        OS_type = OS_MAC;
    } else {
        HAL_GPIO_WritePin(LED2_GPIO_Port, LED2_Pin, GPIO_PIN_RESET);
        OS_type = OS_LINUX;
    }

    switch (OS_type) {
    case OS_MAC:
        ssd1306_DrawPic(APPLE_ICON, 30, 1);
        break;
    case OS_LINUX:
        ssd1306_DrawPic(LINUX_ICON, 30, 1);
        break;
    case OS_WINDOWS:
        ssd1306_DrawPic(WIN_ICON, 30, 1);
        break;
    default:
        break;
    }
    ssd1306_UpdateScreen();
}