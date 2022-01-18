#include "battery.h"

#include "main.h"
#include "ssd1306.h"

extern ADC_HandleTypeDef hadc1;
uint32_t battery_level;
void battery_handler() {
    battery_level = HAL_ADC_GetValue(&hadc1);
    battery_level = ((battery_level - MIN_BATT) * 100) / (MAX_BATT - MIN_BATT);

    if (battery_level >= 87.5) {
        ssd1306_DrawPic(BATTERY_100_ICON, 0, 0);
    } else if (battery_level >= 67.5) {
        ssd1306_DrawPic(BATTERY_75_ICON, 0, 0);
    } else if (battery_level >= 37.5) {
        ssd1306_DrawPic(BATTERY_50_ICON, 0, 0);
    } else if (battery_level >= 10) {
        ssd1306_DrawPic(BATTERY_25_ICON, 0, 0);
    } else {
        ssd1306_DrawPic(BATTERY_EMPTY_ICON, 0, 0);
    }
}
