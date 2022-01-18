#include "display_manager.h"

#include "battery.h"
#include "host_OS.h"
#include "key_handler.h"
#include "ssd1306.h"

void display_manager_init() {
    OS_handler_init();
}

void display_manager_update() {
    KeyboardModeHandler();
    OS_display_update();
    battery_handler();
    ssd1306_UpdateScreen();
}