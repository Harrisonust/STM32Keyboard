#ifndef KEY_HANDLER_H
#define KEY_HANDLER_H

#include "main.h"
#include "matrix_button.h"

#define KEYBOARD_LAYOUT_84

#if defined(KEYBOARD_LAYOUT_84)
#define ROW_NUM 6
#define COL_NUM 14
#elif defined(KEYBOARD_LAYOUT_16)
#define ROW_NUM 4
#define COL_NUM 4
#endif

// clang-format off
#define NUM_OF_KEYS ROW_NUM * COL_NUM - 4
// clang-format on

typedef enum {
    KEY16,
    KEY84
} KeyboardLayout;

typedef struct {
    uint8_t MODIFIER;
    uint8_t RESERVED;
    uint8_t KEYCODE1;
    uint8_t KEYCODE2;
    uint8_t KEYCODE3;
    uint8_t KEYCODE4;
    uint8_t KEYCODE5;
    uint8_t KEYCODE6;
} keyboardHID;

typedef struct {
    uint8_t LEFT_CTRL;
    uint8_t LEFT_SHIFT;
    uint8_t LEFT_ALT;
    uint8_t LEFT_META;
    uint8_t RIGHT_CTRL;
    uint8_t RIGHT_SHIFT;
    uint8_t RIGHT_ALT;
    uint8_t RIGHT_META;
} KeyModifier;

typedef struct {
    keyboardHID hid;
} keyboardStruct;

typedef enum {
    KEYBOARD_CONNECTION_MODE_CABLE,
    KEYBOARD_CONNECTION_MODE_BLUETOOTH
} KEYBOARD_CONNECTION_MODE;

typedef enum {
    KEYBOARD_OPERATION_MODE_NORMAL,
    KEYBOARD_OPERATION_MODE_CONFIG
} KEYBOARD_OPERATION_MODE;

typedef enum {
    DISPLAY_OS_PAGE,
    DISPLAY_CONNECTION_PAGE,
    DISPLAY_OPERATION_PAGE,
    DISPLAY_RGB_PAGE,
    DISPLAY_NUM_PAGE
} Display_selected_page;

void key_thread(void);

void send_key(const uint8_t ch, const KeyModifier mod);

void send_password();

void keyboard_mode_display_update();
#endif