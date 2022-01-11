#include "keyboard_system.h"

#include "cmsis_os.h"
#include "main.h"

OS_TYPE OS_type = OS_MAC;
static int cnt = 0;

void OS_handler(void) {
    if (read(BTN2))
        switch_OS(NULL, BUTTON_CLICKED);
}

void switch_OS(Button* b, ButtonEvent e) {
    cnt++;
    if (cnt % 2) {
        HAL_GPIO_WritePin(LED2_GPIO_Port, LED2_Pin, GPIO_PIN_SET);
        OS_type = OS_MAC;
    } else {
        HAL_GPIO_WritePin(LED2_GPIO_Port, LED2_Pin, GPIO_PIN_RESET);
        OS_type = OS_LINUX;
    }
    osDelay(50);
}