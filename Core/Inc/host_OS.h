#ifndef _OS_H
#define _OS_H

#include "matrix_button.h"

typedef enum {
    OS_WINDOWS,
    OS_LINUX,
    OS_MAC,
    OS_NUM
} OS_TYPE;

void OS_handler_init();

void OS_handler(void);

void switch_OS(Button* b, ButtonEvent e);

void OS_display_update(void);
#endif