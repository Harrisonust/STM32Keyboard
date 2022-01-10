#include "keyboard_system.h"

#include "cmsis_os.h"
#include "main.h"

OS_TYPE OS_type = OS_MAC;

void OS_handler(void) {
    static int cnt = 0;
    if (read(BTN2)) {
        cnt++;
        if (cnt % 2)
            OS_type = OS_LINUX;
        else
            OS_type = OS_MAC;
        osDelay(50);  // use better method like falling edge
    }
}