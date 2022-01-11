#ifndef _OS_H
#define _OS_H

#include "matrix_button.h"

typedef enum {
    OS_UNKNOWN,
    OS_WINDOWS,
    OS_LINUX,
    OS_MAC,
    OS_ANDROID,
    OS_IOS,
} OS_TYPE;

void OS_handler(void);

void switch_OS(Button* b, ButtonEvent e);

#endif