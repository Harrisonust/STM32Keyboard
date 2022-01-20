#include "display_manager.h"

#include "RGB.h"
#include "battery.h"
#include "host_OS.h"
#include "key_handler.h"
#include "ssd1306.h"

void display_manager_init() {
    OS_display_update();
}

void display_manager_update() {
    keyboard_mode_display_update();
    RGB_display_update();
    OS_display_update();
    battery_display_update();
    ssd1306_UpdateScreen();
}