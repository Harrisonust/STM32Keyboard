#include "host_OS.h"

#include "cmsis_os.h"
#include "main.h"
#include "ssd1306.h"
OS_TYPE OS_type = OS_LINUX;

void OS_handler_init() {
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
}

void switch_OS(Button* b, ButtonEvent e) {
    OS_type++;
    OS_type %= OS_NUM;
}

void OS_display_update() {
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
        ssd1306_DrawPic(PACMAN_ICON0, 30, 1);
        break;
    }
}