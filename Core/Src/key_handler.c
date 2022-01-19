// clang-format off
#include "key_handler.h"

#include "main.h"
#include "cmsis_os.h"
#include "stm32f1xx_hal_uart.h"
#include "usbd_hid.h"
#include "usb_device.h"

#include "ssd1306.h"
#include "volume.h"
#include "matrix_button.h"
#include "HID_code.h"
#include "host_OS.h"
#include "display_icon.h"
#include "RGB.h"

// clang-format on

extern USBD_HandleTypeDef hUsbDeviceFS;
extern UART_HandleTypeDef huart4;

KEYBOARD_CONNECTION_MODE keyboard_connection_mode = KEYBOARD_CONNECTION_MODE_CABLE;
KEYBOARD_OPERATION_MODE keyboard_operation_mode = KEYBOARD_OPERATION_MODE_NORMAL;
Button buttons[NUM_OF_KEYS];
keyboardStruct keyboardStct;
KeyModifier keyModifier;
extern OS_TYPE OS_type;

void keyboardStructInit(void) {
    keyboardStct.hid.KEYCODE1 = 0x00;
    keyboardStct.hid.KEYCODE2 = 0x00;
    keyboardStct.hid.KEYCODE3 = 0x00;
    keyboardStct.hid.KEYCODE4 = 0x00;
    keyboardStct.hid.KEYCODE5 = 0x00;
    keyboardStct.hid.KEYCODE6 = 0x00;
}

/**
 * TODO: add device as a parameter. e.g. cable, bluetooth
 */
void send_key(const uint8_t ch, const KeyModifier mod) {
    // if (keyboard_connection_mode == KEYBOARD_CONNECTION_MODE_BLUETOOTH) {
    //     uint8_t data[1] = {'a'};
    //     HAL_UART_Transmit(&huart4, data, 1, 2000);
    // }

    keyboardStct.hid.MODIFIER = (mod.LEFT_CTRL << 0) | (mod.LEFT_SHIFT << 1) | (mod.LEFT_ALT << 2) | (mod.LEFT_META << 3) | (mod.RIGHT_CTRL << 4) | (mod.RIGHT_SHIFT << 5) | (mod.RIGHT_ALT << 6) | (mod.RIGHT_META << 7);
    keyboardStct.hid.KEYCODE1 = ch;

    USBD_HID_SendReport(&hUsbDeviceFS, (uint8_t*)&keyboardStct.hid, sizeof(keyboardStct.hid));
    osDelay(20);

    keyboardStct.hid.MODIFIER = 0x00;
    keyboardStct.hid.KEYCODE1 = 0x00;
    USBD_HID_SendReport(&hUsbDeviceFS, (uint8_t*)&keyboardStct.hid, sizeof(keyboardStct.hid));
    osDelay(20);
}

void send_password() {
    // KeyModifier m = {0};
    // char pw[] = "helloElec3300";
    // for (uint8_t i = 0; i < strlen(pw); i++) {
    //     send_key(getKeyIDByChar(pw[i]), m);
    //     osDelay(20);
    // }
}

void buttonsend_key(Button* b, ButtonEvent e);
void buttonFreeKey(Button* b, ButtonEvent e);
void buttonDebug(Button* b, ButtonEvent e);
void switch_selected_target(Button* b, ButtonEvent e);

void buttons_init(Button* btns, const int len) {
    button_init(&btns[0], Pin(COL0), Pin(ROW0), KEY_ESC);
    button_init(&btns[1], Pin(COL1), Pin(ROW0), KEY_F1);
    button_init(&btns[2], Pin(COL2), Pin(ROW0), KEY_F2);
    button_init(&btns[3], Pin(COL3), Pin(ROW0), KEY_F3);
    button_init(&btns[4], Pin(COL4), Pin(ROW0), KEY_F4);
    button_init(&btns[5], Pin(COL5), Pin(ROW0), KEY_F5);
    button_init(&btns[6], Pin(COL6), Pin(ROW0), KEY_F6);
    button_init(&btns[7], Pin(COL7), Pin(ROW0), KEY_F7);
    button_init(&btns[8], Pin(COL8), Pin(ROW0), KEY_F8);
    button_init(&btns[9], Pin(COL9), Pin(ROW0), KEY_F9);
    button_init(&btns[10], Pin(COL10), Pin(ROW0), KEY_F10);
    button_init(&btns[11], Pin(COL11), Pin(ROW0), KEY_F11);
    button_init(&btns[12], Pin(COL12), Pin(ROW0), KEY_F12);
    button_init(&btns[13], Pin(COL13), Pin(ROW0), KEY_DELETE);

    button_init(&btns[14], Pin(COL0), Pin(ROW1), KEY_GRAVE);
    button_init(&btns[15], Pin(COL1), Pin(ROW1), KEY_1);
    button_init(&btns[16], Pin(COL2), Pin(ROW1), KEY_2);
    button_init(&btns[17], Pin(COL3), Pin(ROW1), KEY_3);
    button_init(&btns[18], Pin(COL4), Pin(ROW1), KEY_4);
    button_init(&btns[19], Pin(COL5), Pin(ROW1), KEY_5);
    button_init(&btns[20], Pin(COL6), Pin(ROW1), KEY_6);
    button_init(&btns[21], Pin(COL7), Pin(ROW1), KEY_7);
    button_init(&btns[22], Pin(COL8), Pin(ROW1), KEY_8);
    button_init(&btns[23], Pin(COL9), Pin(ROW1), KEY_9);
    button_init(&btns[24], Pin(COL10), Pin(ROW1), KEY_0);
    button_init(&btns[25], Pin(COL11), Pin(ROW1), KEY_MINUS);
    button_init(&btns[26], Pin(COL12), Pin(ROW1), KEY_EQUAL);
    button_init(&btns[27], Pin(COL13), Pin(ROW1), KEY_BACKSPACE);

    button_init(&btns[28], Pin(COL0), Pin(ROW2), KEY_TAB);
    button_init(&btns[29], Pin(COL1), Pin(ROW2), KEY_Q);
    button_init(&btns[30], Pin(COL2), Pin(ROW2), KEY_W);
    button_init(&btns[31], Pin(COL3), Pin(ROW2), KEY_E);
    button_init(&btns[32], Pin(COL4), Pin(ROW2), KEY_R);
    button_init(&btns[33], Pin(COL5), Pin(ROW2), KEY_T);
    button_init(&btns[34], Pin(COL6), Pin(ROW2), KEY_Y);
    button_init(&btns[35], Pin(COL7), Pin(ROW2), KEY_U);
    button_init(&btns[36], Pin(COL8), Pin(ROW2), KEY_I);
    button_init(&btns[37], Pin(COL9), Pin(ROW2), KEY_O);
    button_init(&btns[38], Pin(COL10), Pin(ROW2), KEY_P);
    button_init(&btns[39], Pin(COL11), Pin(ROW2), KEY_LEFTBRACE);
    button_init(&btns[40], Pin(COL12), Pin(ROW2), KEY_RIGHTBRACE);
    button_init(&btns[41], Pin(COL13), Pin(ROW2), KEY_BACKSLASH);

    button_init(&btns[42], Pin(COL0), Pin(ROW3), KEY_CAPSLOCK);
    button_init(&btns[43], Pin(COL1), Pin(ROW3), KEY_A);
    button_init(&btns[44], Pin(COL2), Pin(ROW3), KEY_S);
    button_init(&btns[45], Pin(COL3), Pin(ROW3), KEY_D);
    button_init(&btns[46], Pin(COL4), Pin(ROW3), KEY_F);
    button_init(&btns[47], Pin(COL5), Pin(ROW3), KEY_G);
    button_init(&btns[48], Pin(COL6), Pin(ROW3), KEY_H);
    button_init(&btns[49], Pin(COL7), Pin(ROW3), KEY_J);
    button_init(&btns[50], Pin(COL8), Pin(ROW3), KEY_K);
    button_init(&btns[51], Pin(COL9), Pin(ROW3), KEY_L);
    button_init(&btns[52], Pin(COL10), Pin(ROW3), KEY_SEMICOLON);
    button_init(&btns[53], Pin(COL11), Pin(ROW3), KEY_APOSTROPHE);
    button_init(&btns[54], Pin(COL12), Pin(ROW3), KEY_ENTER);

    button_init(&btns[55], Pin(COL0), Pin(ROW4), KEY_LEFTSHIFT);
    button_init(&btns[56], Pin(COL1), Pin(ROW4), KEY_Z);
    button_init(&btns[57], Pin(COL2), Pin(ROW4), KEY_X);
    button_init(&btns[58], Pin(COL3), Pin(ROW4), KEY_C);
    button_init(&btns[59], Pin(COL4), Pin(ROW4), KEY_V);
    button_init(&btns[60], Pin(COL5), Pin(ROW4), KEY_B);
    button_init(&btns[61], Pin(COL6), Pin(ROW4), KEY_N);
    button_init(&btns[62], Pin(COL7), Pin(ROW4), KEY_M);
    button_init(&btns[63], Pin(COL8), Pin(ROW4), KEY_COMMA);
    button_init(&btns[64], Pin(COL9), Pin(ROW4), KEY_DOT);
    button_init(&btns[65], Pin(COL10), Pin(ROW4), KEY_SLASH);
    button_init(&btns[66], Pin(COL11), Pin(ROW4), KEY_RIGHTSHIFT);
    button_init(&btns[67], Pin(COL12), Pin(ROW4), KEY_UP);

    button_init(&btns[68], Pin(COL0), Pin(ROW5), KEY_LEFTCTRL);
    button_init(&btns[69], Pin(COL1), Pin(ROW5), KEY_LEFTMETA);
    button_init(&btns[70], Pin(COL2), Pin(ROW5), KEY_LEFTALT);
    button_init(&btns[71], Pin(COL3), Pin(ROW5), KEY_SPACE);
    button_init(&btns[72], Pin(COL4), Pin(ROW5), KEY_RIGHTALT);
    button_init(&btns[73], Pin(COL5), Pin(ROW5), KEY_FN);  //fn
    button_init(&btns[74], Pin(COL6), Pin(ROW5), KEY_RIGHTCTRL);
    button_init(&btns[75], Pin(COL7), Pin(ROW5), KEY_LEFT);
    button_init(&btns[76], Pin(COL8), Pin(ROW5), KEY_DOWN);
    button_init(&btns[77], Pin(COL9), Pin(ROW5), KEY_RIGHT);
    button_init(&btns[78], Pin(COL10), Pin(ROW5), KEY_HOME);
    button_init(&btns[79], Pin(COL11), Pin(ROW5), KEY_END);

    for (int i = 0; i < len; i++) {
        btns[i].button_clicked_listener = buttonsend_key;
        btns[i].button_holding_listener = buttonsend_key;
        btns[i].button_released_listener = buttonFreeKey;
    }
    btns[73].button_clicked_listener = switch_RGB_backlight;
    btns[73].button_released_listener = NULL;
    btns[73].button_holding_listener = switch_selected_target;
}

void switch_selected_target(Button* b, ButtonEvent e) {
    static uint8_t cnt = 0;
    if (cnt % 2 == 0) {
        buttons[73].button_clicked_listener = switch_RGB_backlight;
        // ssd1306_DrawInvertedPic()
    }
    if (cnt % 2 == 1) {
        buttons[73].button_clicked_listener = OS_switch;
        // ssd1306_DrawInvertedPic();
    }
    cnt++;
}

void buttonDebug(Button* b, ButtonEvent e) {
    HAL_GPIO_TogglePin(LED2_GPIO_Port, LED2_Pin);
    send_key(b->keycode, keyModifier);
}

void buttonsend_key(Button* b, ButtonEvent e) {
    switch (b->keycode) {
    case KEY_LEFTCTRL:
        keyModifier.LEFT_CTRL = 1;
        break;
    case KEY_LEFTSHIFT:
        keyModifier.LEFT_SHIFT = 1;
        break;
    case KEY_LEFTALT:
        keyModifier.LEFT_ALT = 1;
        break;
    case KEY_LEFTMETA:
        keyModifier.LEFT_META = 1;
        break;
    case KEY_RIGHTCTRL:
        keyModifier.RIGHT_CTRL = 1;
        break;
    case KEY_RIGHTSHIFT:
        keyModifier.RIGHT_SHIFT = 1;
        break;
    case KEY_RIGHTALT:
        keyModifier.RIGHT_ALT = 1;
        break;
    case KEY_RIGHTMETA:
        keyModifier.RIGHT_META = 1;
        break;
    case KEY_FN:
        return;
    default:
        break;
    }
    send_key(b->keycode, keyModifier);
}

void buttonFreeKey(Button* b, ButtonEvent e) {
    switch (b->keycode) {
    case KEY_LEFTCTRL:
        keyModifier.LEFT_CTRL = 0;
        break;
    case KEY_LEFTSHIFT:
        keyModifier.LEFT_SHIFT = 0;
        break;
    case KEY_LEFTALT:
        keyModifier.LEFT_ALT = 0;
        break;
    case KEY_LEFTMETA:
        keyModifier.LEFT_META = 0;
        break;
    case KEY_RIGHTCTRL:
        keyModifier.RIGHT_CTRL = 0;
        break;
    case KEY_RIGHTSHIFT:
        keyModifier.RIGHT_SHIFT = 0;
        break;
    case KEY_RIGHTALT:
        keyModifier.RIGHT_ALT = 0;
        break;
    case KEY_RIGHTMETA:
        keyModifier.RIGHT_META = 0;
        break;
    default:
        break;
    }
}

void keyboard_mode_handler() {
    // if (readKey(0, 0)) {
    //     keyboard_operation_mode++;
    //     keyboard_operation_mode %= 2;
    // }
}

void keyboard_mode_display_update() {
    if (keyboard_connection_mode == KEYBOARD_CONNECTION_MODE_CABLE)
        ssd1306_DrawPic(CABLE_ICON, 60, 1);
    else if (keyboard_connection_mode == KEYBOARD_CONNECTION_MODE_BLUETOOTH)
        ssd1306_DrawPic(BLE_ICON, 60, 1);
    if (keyboard_operation_mode == KEYBOARD_OPERATION_MODE_CONFIG)
        ssd1306_DrawPic(SETTING_ICON, 90, 1);
    else if (keyboard_operation_mode == KEYBOARD_OPERATION_MODE_NORMAL)
        ssd1306_DrawPic(NORMAL_ICON, 90, 1);
}

void key_thread(void) {
    keyboardStructInit();
    buttons_init(buttons, NUM_OF_KEYS);
    encoder_init();
    for (;;) {
        if (keyboard_operation_mode == KEYBOARD_OPERATION_MODE_CONFIG) {
        } else if (keyboard_operation_mode == KEYBOARD_OPERATION_MODE_NORMAL) {
            buttons_update(buttons, NUM_OF_KEYS);
            volume_handler();
        }
        osDelay(1);
    }
}
