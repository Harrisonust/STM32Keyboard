#include "display_manager.h"

#include "battery.h"
#include "host_OS.h"
#include "key_handler.h"
#include "ssd1306.h"

/** 
 * display_manager_init()
 * @brief 
 */

void display_manager_init() {
    OS_display_init();
}

/** 
 * display_manager_update()
 * @brief every ssd_draw functoin should only be called in this function 
 *        after that, ssd_update function will be called once, all the previous
 *        draw should be then updated.
 */

void display_manager_update() {
    keyboard_mode_display_update();
    OS_display_update();
    battery_display_update();
    ssd1306_UpdateScreen();
}