// clang-format off
#include "key_handler.h"

#include "main.h"
#include "cmsis_os.h"
#include "stm32f1xx_hal_uart.h"
#include "usbd_hid.h"
#include "usb_device.h"

#include "RGB.h"
#include "macro_page.h"
#include "oled_manager.h"
#include "volume.h"
#include "matrix_button.h"
#include "HID_code.h"
#include "host_OS.h"
// clang-format on

extern USBD_HandleTypeDef hUsbDeviceFS;
keyboardStruct keyboardStct;
extern UART_HandleTypeDef huart4;
extern TIM_HandleTypeDef htim2;

KEYBOARD_CONNECTION_MODE keyboard_connection_mode = KEYBOARD_CONNECTION_MODE_CABLE;
KEYBOARD_OPERATION_MODE keyboard_operation_mode = KEYBOARD_OPERATION_MODE_NORMAL;
extern OS_TYPE OS_type;
Button buttons[NUM_OF_KEYS];
KeyModifier keyModifier;

void keyboardStructInit(void) {
    keyboardStct.hid.KEYCODE1 = 0x00;
    keyboardStct.hid.KEYCODE2 = 0x00;
    keyboardStct.hid.KEYCODE3 = 0x00;
    keyboardStct.hid.KEYCODE4 = 0x00;
    keyboardStct.hid.KEYCODE5 = 0x00;
    keyboardStct.hid.KEYCODE6 = 0x00;
    htim2.Instance->CNT = 0xffff / 2;
}

// add device as a parameter. e.g. cable, bluetooth
void sendKey(const uint8_t ch, const KeyModifier mod) {
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

void sendPassword() {
    // KeyModifier m = {0};
    // char pw[] = "helloElec3300";
    // for (uint8_t i = 0; i < strlen(pw); i++) {
    //     sendKey(getKeyIDByChar(pw[i]), m);
    //     osDelay(20);
    // }
}

void buttonSendKey(Button* b, ButtonEvent e);
void buttonFreeKey(Button* b, ButtonEvent e);
void buttonDebug(Button* b, ButtonEvent e);

void buttons_init(Button* btns, const int len) {
    button_init(&btns[0], Pin(COL0), Pin(ROW0));
    btns[0].keycode = KEY_ESC;
    button_init(&btns[1], Pin(COL1), Pin(ROW0));
    btns[1].keycode = KEY_F1;
    button_init(&btns[2], Pin(COL2), Pin(ROW0));
    btns[2].keycode = KEY_F2;
    button_init(&btns[3], Pin(COL3), Pin(ROW0));
    btns[3].keycode = KEY_F3;
    button_init(&btns[4], Pin(COL4), Pin(ROW0));
    btns[4].keycode = KEY_F4;
    button_init(&btns[5], Pin(COL5), Pin(ROW0));
    btns[5].keycode = KEY_F5;
    button_init(&btns[6], Pin(COL6), Pin(ROW0));
    btns[6].keycode = KEY_F6;
    button_init(&btns[7], Pin(COL7), Pin(ROW0));
    btns[7].keycode = KEY_F7;
    button_init(&btns[8], Pin(COL8), Pin(ROW0));
    btns[8].keycode = KEY_F8;
    button_init(&btns[9], Pin(COL9), Pin(ROW0));
    btns[9].keycode = KEY_F9;
    button_init(&btns[10], Pin(COL10), Pin(ROW0));
    btns[10].keycode = KEY_F10;
    button_init(&btns[11], Pin(COL11), Pin(ROW0));
    btns[11].keycode = KEY_F11;
    button_init(&btns[12], Pin(COL12), Pin(ROW0));
    btns[12].keycode = KEY_F12;
    button_init(&btns[13], Pin(COL13), Pin(ROW0));
    btns[13].keycode = KEY_DELETE;

    button_init(&btns[14], Pin(COL0), Pin(ROW1));
    btns[14].keycode = KEY_GRAVE;
    button_init(&btns[15], Pin(COL1), Pin(ROW1));
    btns[15].keycode = KEY_1;
    button_init(&btns[16], Pin(COL2), Pin(ROW1));
    btns[16].keycode = KEY_2;
    button_init(&btns[17], Pin(COL3), Pin(ROW1));
    btns[17].keycode = KEY_3;
    button_init(&btns[18], Pin(COL4), Pin(ROW1));
    btns[18].keycode = KEY_4;
    button_init(&btns[19], Pin(COL5), Pin(ROW1));
    btns[19].keycode = KEY_5;
    button_init(&btns[20], Pin(COL6), Pin(ROW1));
    btns[20].keycode = KEY_6;
    button_init(&btns[21], Pin(COL7), Pin(ROW1));
    btns[21].keycode = KEY_7;
    button_init(&btns[22], Pin(COL8), Pin(ROW1));
    btns[22].keycode = KEY_8;
    button_init(&btns[23], Pin(COL9), Pin(ROW1));
    btns[23].keycode = KEY_9;
    button_init(&btns[24], Pin(COL10), Pin(ROW1));
    btns[24].keycode = KEY_0;
    button_init(&btns[25], Pin(COL11), Pin(ROW1));
    btns[25].keycode = KEY_MINUS;
    button_init(&btns[26], Pin(COL12), Pin(ROW1));
    btns[26].keycode = KEY_EQUAL;
    button_init(&btns[27], Pin(COL13), Pin(ROW1));
    btns[27].keycode = KEY_BACKSPACE;

    button_init(&btns[28], Pin(COL0), Pin(ROW2));
    btns[28].keycode = KEY_TAB;
    button_init(&btns[29], Pin(COL1), Pin(ROW2));
    btns[29].keycode = KEY_Q;
    button_init(&btns[30], Pin(COL2), Pin(ROW2));
    btns[30].keycode = KEY_W;
    button_init(&btns[31], Pin(COL3), Pin(ROW2));
    btns[31].keycode = KEY_E;
    button_init(&btns[32], Pin(COL4), Pin(ROW2));
    btns[32].keycode = KEY_R;
    button_init(&btns[33], Pin(COL5), Pin(ROW2));
    btns[33].keycode = KEY_T;
    button_init(&btns[34], Pin(COL6), Pin(ROW2));
    btns[34].keycode = KEY_Y;
    button_init(&btns[35], Pin(COL7), Pin(ROW2));
    btns[35].keycode = KEY_U;
    button_init(&btns[36], Pin(COL8), Pin(ROW2));
    btns[36].keycode = KEY_I;
    button_init(&btns[37], Pin(COL9), Pin(ROW2));
    btns[37].keycode = KEY_O;
    button_init(&btns[38], Pin(COL10), Pin(ROW2));
    btns[38].keycode = KEY_P;
    button_init(&btns[39], Pin(COL11), Pin(ROW2));
    btns[39].keycode = KEY_LEFTBRACE;
    button_init(&btns[40], Pin(COL12), Pin(ROW2));
    btns[40].keycode = KEY_RIGHTBRACE;
    button_init(&btns[41], Pin(COL13), Pin(ROW2));
    btns[41].keycode = KEY_BACKSLASH;

    button_init(&btns[42], Pin(COL0), Pin(ROW3));
    btns[42].keycode = KEY_CAPSLOCK;
    button_init(&btns[43], Pin(COL1), Pin(ROW3));
    btns[43].keycode = KEY_A;
    button_init(&btns[44], Pin(COL2), Pin(ROW3));
    btns[44].keycode = KEY_S;
    button_init(&btns[45], Pin(COL3), Pin(ROW3));
    btns[45].keycode = KEY_D;
    button_init(&btns[46], Pin(COL4), Pin(ROW3));
    btns[46].keycode = KEY_F;
    button_init(&btns[47], Pin(COL5), Pin(ROW3));
    btns[47].keycode = KEY_G;
    button_init(&btns[48], Pin(COL6), Pin(ROW3));
    btns[48].keycode = KEY_H;
    button_init(&btns[49], Pin(COL7), Pin(ROW3));
    btns[49].keycode = KEY_J;
    button_init(&btns[50], Pin(COL8), Pin(ROW3));
    btns[50].keycode = KEY_K;
    button_init(&btns[51], Pin(COL9), Pin(ROW3));
    btns[51].keycode = KEY_L;
    button_init(&btns[52], Pin(COL10), Pin(ROW3));
    btns[52].keycode = KEY_SEMICOLON;
    button_init(&btns[53], Pin(COL11), Pin(ROW3));
    btns[53].keycode = KEY_APOSTROPHE;
    button_init(&btns[54], Pin(COL12), Pin(ROW3));
    btns[54].keycode = KEY_ENTER;

    button_init(&btns[55], Pin(COL0), Pin(ROW4));
    btns[55].keycode = KEY_LEFTSHIFT;
    button_init(&btns[56], Pin(COL1), Pin(ROW4));
    btns[56].keycode = KEY_Z;
    button_init(&btns[57], Pin(COL2), Pin(ROW4));
    btns[57].keycode = KEY_X;
    button_init(&btns[58], Pin(COL3), Pin(ROW4));
    btns[58].keycode = KEY_C;
    button_init(&btns[59], Pin(COL4), Pin(ROW4));
    btns[59].keycode = KEY_V;
    button_init(&btns[60], Pin(COL5), Pin(ROW4));
    btns[60].keycode = KEY_B;
    button_init(&btns[61], Pin(COL6), Pin(ROW4));
    btns[61].keycode = KEY_N;
    button_init(&btns[62], Pin(COL7), Pin(ROW4));
    btns[62].keycode = KEY_M;
    button_init(&btns[63], Pin(COL8), Pin(ROW4));
    btns[63].keycode = KEY_COMMA;
    button_init(&btns[64], Pin(COL9), Pin(ROW4));
    btns[64].keycode = KEY_DOT;
    button_init(&btns[65], Pin(COL10), Pin(ROW4));
    btns[65].keycode = KEY_SLASH;
    button_init(&btns[66], Pin(COL11), Pin(ROW4));
    btns[66].keycode = KEY_RIGHTSHIFT;
    button_init(&btns[67], Pin(COL12), Pin(ROW4));
    btns[67].keycode = KEY_UP;

    button_init(&btns[68], Pin(COL0), Pin(ROW5));
    btns[68].keycode = KEY_LEFTCTRL;
    button_init(&btns[69], Pin(COL1), Pin(ROW5));
    btns[69].keycode = KEY_LEFTMETA;
    button_init(&btns[70], Pin(COL2), Pin(ROW5));
    btns[70].keycode = KEY_LEFTALT;
    button_init(&btns[71], Pin(COL3), Pin(ROW5));
    btns[71].keycode = KEY_SPACE;
    button_init(&btns[72], Pin(COL4), Pin(ROW5));
    btns[72].keycode = KEY_RIGHTALT;
    button_init(&btns[73], Pin(COL5), Pin(ROW5));
    btns[73].keycode = KEY_FN;  //fn
    button_init(&btns[74], Pin(COL6), Pin(ROW5));
    btns[74].keycode = KEY_RIGHTCTRL;
    button_init(&btns[75], Pin(COL7), Pin(ROW5));
    btns[75].keycode = KEY_LEFT;
    button_init(&btns[76], Pin(COL8), Pin(ROW5));
    btns[76].keycode = KEY_DOWN;
    button_init(&btns[77], Pin(COL9), Pin(ROW5));
    btns[77].keycode = KEY_RIGHT;
    button_init(&btns[78], Pin(COL10), Pin(ROW5));
    btns[78].keycode = KEY_HOME;
    button_init(&btns[79], Pin(COL11), Pin(ROW5));
    btns[79].keycode = KEY_END;

    for (int i = 0; i < len; i++) {
        btns[i].button_clicked_listener = buttonSendKey;
        btns[i].button_holding_listener = buttonSendKey;
        btns[i].button_released_listener = buttonFreeKey;
    }
    btns[73].button_clicked_listener = switch_OS;
    btns[73].button_released_listener = NULL;
    btns[73].button_holding_listener = NULL;
}

void buttonDebug(Button* b, ButtonEvent e) {
    HAL_GPIO_TogglePin(LED2_GPIO_Port, LED2_Pin);
    sendKey(b->keycode, keyModifier);
}

void buttonSendKey(Button* b, ButtonEvent e) {
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
    sendKey(b->keycode, keyModifier);
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

void VolumeHandler() {
    Volume_State vol_state = updateVolume();
    KeyModifier m = {0};
    if (vol_state == VOLUMEDOWN) {
        if (OS_type == OS_MAC)
            sendKey(0x80, m);
        if (OS_type == OS_LINUX)
            sendKey(KEY_F12, m);  //volume up
    } else if (vol_state == VOLUMEUP) {
        if (OS_type == OS_MAC)
            sendKey(0x81, m);
        if (OS_type == OS_LINUX)
            sendKey(KEY_F11, m);  //volume down
    } else if (vol_state == VOLUMENOACTION) {
    }
}

void KeyboardModeHandler() {
    // if (readKey(0, 0)) {
    //     keyboard_operation_mode++;
    //     keyboard_operation_mode %= 2;
    // }
    // if (readKey(0, 1)) {
    //     Node* n = get_macro('x');
    //     for (Node* ptr = n; ptr != NULL; ptr = ptr->next) {
    //         sendKey(KEY_t>data), m);
    //         osDelay(20);
    //     }
    // }
    if (keyboard_connection_mode == KEYBOARD_CONNECTION_MODE_CABLE)
        ssd1306_DrawPic(CABLE_ICON, 60, 1);
    else if (keyboard_connection_mode == KEYBOARD_CONNECTION_MODE_BLUETOOTH)
        ssd1306_DrawPic(BLE_ICON, 60, 1);
}

void keyThread(void) {
    keyboardStructInit();
    buttons_init(buttons, NUM_OF_KEYS);
    for (;;) {
        if (keyboard_operation_mode == KEYBOARD_OPERATION_MODE_CONFIG) {
        } else if (keyboard_operation_mode == KEYBOARD_OPERATION_MODE_NORMAL) {
            buttons_update(buttons, NUM_OF_KEYS);
            VolumeHandler();
        }
        osDelay(1);
    }
}
