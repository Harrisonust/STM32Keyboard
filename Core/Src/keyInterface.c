// clang-format off
#include "keyInterface.h"

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
#include "KeyID.h"
#include "keyboard_system.h"
// clang-format on

extern OS_TYPE OS_type;
extern USBD_HandleTypeDef hUsbDeviceFS;
keyboardStruct keyboardStct;
extern UART_HandleTypeDef huart4;
extern TIM_HandleTypeDef htim2;
KEYBOARD_CONNECTION_MODE keyboard_connection_mode = KEYBOARD_CONNECTION_MODE_CABLE;
KEYBOARD_OPERATION_MODE keyboard_operation_mode = KEYBOARD_OPERATION_MODE_NORMAL;

void keyInterfaceInit(void) {
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
}

void sendPassword() {
    KeyModifier m = {0};
    char pw[] = "helloElec3300";
    for (uint8_t i = 0; i < strlen(pw); i++) {
        sendKey(getKeyIDByChar(pw[i]), m);
        osDelay(20);
    }
}

void buttonSendKey(Button* b, ButtonEvent e);
void buttonFreeKey(Button* b, ButtonEvent e);
void buttonDebug(Button* b, ButtonEvent e);

void buttons_init(Button* buttons, const int len) {
    button_init(&buttons[0], Pin(COL0), Pin(ROW0));
    buttons[0].keycode = KEY_ESC;
    button_init(&buttons[1], Pin(COL1), Pin(ROW0));
    buttons[1].keycode = KEY_F1;
    button_init(&buttons[2], Pin(COL2), Pin(ROW0));
    buttons[2].keycode = KEY_F2;
    button_init(&buttons[3], Pin(COL3), Pin(ROW0));
    buttons[3].keycode = KEY_F3;
    button_init(&buttons[4], Pin(COL4), Pin(ROW0));
    buttons[4].keycode = KEY_F4;
    button_init(&buttons[5], Pin(COL5), Pin(ROW0));
    buttons[5].keycode = KEY_F5;
    button_init(&buttons[6], Pin(COL6), Pin(ROW0));
    buttons[6].keycode = KEY_F6;
    button_init(&buttons[7], Pin(COL7), Pin(ROW0));
    buttons[7].keycode = KEY_F7;
    button_init(&buttons[8], Pin(COL8), Pin(ROW0));
    buttons[8].keycode = KEY_F8;
    button_init(&buttons[9], Pin(COL9), Pin(ROW0));
    buttons[9].keycode = KEY_F9;
    button_init(&buttons[10], Pin(COL10), Pin(ROW0));
    buttons[10].keycode = KEY_F10;
    button_init(&buttons[11], Pin(COL11), Pin(ROW0));
    buttons[11].keycode = KEY_F11;
    button_init(&buttons[12], Pin(COL12), Pin(ROW0));
    buttons[12].keycode = KEY_F12;
    button_init(&buttons[13], Pin(COL13), Pin(ROW0));
    buttons[13].keycode = KEY_DELETE;

    button_init(&buttons[14], Pin(COL0), Pin(ROW1));
    buttons[14].keycode = KEY_GRAVE;
    button_init(&buttons[15], Pin(COL1), Pin(ROW1));
    buttons[15].keycode = KEY_1;
    button_init(&buttons[16], Pin(COL2), Pin(ROW1));
    buttons[16].keycode = KEY_2;
    button_init(&buttons[17], Pin(COL3), Pin(ROW1));
    buttons[17].keycode = KEY_3;
    button_init(&buttons[18], Pin(COL4), Pin(ROW1));
    buttons[18].keycode = KEY_4;
    button_init(&buttons[19], Pin(COL5), Pin(ROW1));
    buttons[19].keycode = KEY_5;
    button_init(&buttons[20], Pin(COL6), Pin(ROW1));
    buttons[20].keycode = KEY_6;
    button_init(&buttons[21], Pin(COL7), Pin(ROW1));
    buttons[21].keycode = KEY_7;
    button_init(&buttons[22], Pin(COL8), Pin(ROW1));
    buttons[22].keycode = KEY_8;
    button_init(&buttons[23], Pin(COL9), Pin(ROW1));
    buttons[23].keycode = KEY_9;
    button_init(&buttons[24], Pin(COL10), Pin(ROW1));
    buttons[24].keycode = KEY_0;
    button_init(&buttons[25], Pin(COL11), Pin(ROW1));
    buttons[25].keycode = KEY_KPMINUS;
    button_init(&buttons[26], Pin(COL12), Pin(ROW1));
    buttons[26].keycode = KEY_KPPLUS;
    button_init(&buttons[27], Pin(COL13), Pin(ROW1));
    buttons[27].keycode = KEY_BACKSPACE;

    button_init(&buttons[28], Pin(COL0), Pin(ROW2));
    buttons[28].keycode = KEY_TAB;
    button_init(&buttons[29], Pin(COL1), Pin(ROW2));
    buttons[29].keycode = KEY_Q;
    button_init(&buttons[30], Pin(COL2), Pin(ROW2));
    buttons[30].keycode = KEY_W;
    button_init(&buttons[31], Pin(COL3), Pin(ROW2));
    buttons[31].keycode = KEY_E;
    button_init(&buttons[32], Pin(COL4), Pin(ROW2));
    buttons[32].keycode = KEY_R;
    button_init(&buttons[33], Pin(COL5), Pin(ROW2));
    buttons[33].keycode = KEY_T;
    button_init(&buttons[34], Pin(COL6), Pin(ROW2));
    buttons[34].keycode = KEY_Y;
    button_init(&buttons[35], Pin(COL7), Pin(ROW2));
    buttons[35].keycode = KEY_U;
    button_init(&buttons[36], Pin(COL8), Pin(ROW2));
    buttons[36].keycode = KEY_I;
    button_init(&buttons[37], Pin(COL9), Pin(ROW2));
    buttons[37].keycode = KEY_O;
    button_init(&buttons[38], Pin(COL10), Pin(ROW2));
    buttons[38].keycode = KEY_P;
    button_init(&buttons[39], Pin(COL11), Pin(ROW2));
    buttons[39].keycode = KEY_LEFTBRACE;
    button_init(&buttons[40], Pin(COL12), Pin(ROW2));
    buttons[40].keycode = KEY_RIGHTBRACE;
    button_init(&buttons[41], Pin(COL13), Pin(ROW2));
    buttons[41].keycode = KEY_BACKSLASH;

    button_init(&buttons[42], Pin(COL0), Pin(ROW3));
    buttons[42].keycode = KEY_CAPSLOCK;
    button_init(&buttons[43], Pin(COL1), Pin(ROW3));
    buttons[43].keycode = KEY_A;
    button_init(&buttons[44], Pin(COL2), Pin(ROW3));
    buttons[44].keycode = KEY_S;
    button_init(&buttons[45], Pin(COL3), Pin(ROW3));
    buttons[45].keycode = KEY_D;
    button_init(&buttons[46], Pin(COL4), Pin(ROW3));
    buttons[46].keycode = KEY_F;
    button_init(&buttons[47], Pin(COL5), Pin(ROW3));
    buttons[47].keycode = KEY_G;
    button_init(&buttons[48], Pin(COL6), Pin(ROW3));
    buttons[48].keycode = KEY_H;
    button_init(&buttons[49], Pin(COL7), Pin(ROW3));
    buttons[49].keycode = KEY_J;
    button_init(&buttons[50], Pin(COL8), Pin(ROW3));
    buttons[50].keycode = KEY_K;
    button_init(&buttons[51], Pin(COL9), Pin(ROW3));
    buttons[51].keycode = KEY_L;
    button_init(&buttons[52], Pin(COL10), Pin(ROW3));
    buttons[52].keycode = KEY_SEMICOLON;
    button_init(&buttons[53], Pin(COL11), Pin(ROW3));
    buttons[53].keycode = KEY_APOSTROPHE;
    button_init(&buttons[54], Pin(COL12), Pin(ROW3));
    buttons[54].keycode = KEY_ENTER;

    button_init(&buttons[55], Pin(COL0), Pin(ROW4));
    buttons[55].keycode = KEY_LEFTSHIFT;
    button_init(&buttons[56], Pin(COL1), Pin(ROW4));
    buttons[56].keycode = KEY_Z;
    button_init(&buttons[57], Pin(COL2), Pin(ROW4));
    buttons[57].keycode = KEY_X;
    button_init(&buttons[58], Pin(COL3), Pin(ROW4));
    buttons[58].keycode = KEY_C;
    button_init(&buttons[59], Pin(COL4), Pin(ROW4));
    buttons[59].keycode = KEY_V;
    button_init(&buttons[60], Pin(COL5), Pin(ROW4));
    buttons[60].keycode = KEY_B;
    button_init(&buttons[61], Pin(COL6), Pin(ROW4));
    buttons[61].keycode = KEY_N;
    button_init(&buttons[62], Pin(COL7), Pin(ROW4));
    buttons[62].keycode = KEY_M;
    button_init(&buttons[63], Pin(COL8), Pin(ROW4));
    buttons[63].keycode = KEY_COMMA;
    button_init(&buttons[64], Pin(COL9), Pin(ROW4));
    buttons[64].keycode = KEY_DOT;
    button_init(&buttons[65], Pin(COL10), Pin(ROW4));
    buttons[65].keycode = KEY_SLASH;
    button_init(&buttons[66], Pin(COL11), Pin(ROW4));
    buttons[66].keycode = KEY_RIGHTSHIFT;
    button_init(&buttons[67], Pin(COL12), Pin(ROW4));
    buttons[67].keycode = KEY_UP;

    button_init(&buttons[68], Pin(COL0), Pin(ROW5));
    buttons[68].keycode = KEY_LEFTCTRL;
    button_init(&buttons[69], Pin(COL1), Pin(ROW5));
    buttons[69].keycode = KEY_LEFTMETA;
    button_init(&buttons[70], Pin(COL2), Pin(ROW5));
    buttons[70].keycode = KEY_LEFTALT;
    button_init(&buttons[71], Pin(COL3), Pin(ROW5));
    buttons[71].keycode = KEY_SPACE;
    button_init(&buttons[72], Pin(COL4), Pin(ROW5));
    buttons[72].keycode = KEY_RIGHTALT;
    button_init(&buttons[73], Pin(COL5), Pin(ROW5));
    buttons[73].keycode = KEY_NONE;  //fn
    button_init(&buttons[74], Pin(COL6), Pin(ROW5));
    buttons[74].keycode = KEY_RIGHTCTRL;
    button_init(&buttons[75], Pin(COL7), Pin(ROW5));
    buttons[75].keycode = KEY_LEFT;
    button_init(&buttons[76], Pin(COL8), Pin(ROW5));
    buttons[76].keycode = KEY_DOWN;
    button_init(&buttons[77], Pin(COL9), Pin(ROW5));
    buttons[77].keycode = KEY_RIGHT;
    button_init(&buttons[78], Pin(COL10), Pin(ROW5));
    buttons[78].keycode = KEY_HOME;
    button_init(&buttons[79], Pin(COL11), Pin(ROW5));
    buttons[79].keycode = KEY_END;

    for (int i = 0; i < len; i++) {
        buttons[i].button_clicked_listener = buttonSendKey;
        buttons[i].button_released_listener = buttonFreeKey;
    }
}

void buttonDebug(Button* b, ButtonEvent e) {
    HAL_GPIO_TogglePin(LED3_GPIO_Port, LED3_Pin);
    osDelay(100);
}

Button buttons[NUM_OF_KEYS];
KeyModifier keyModifier;

void buttonSendKey(Button* b, ButtonEvent e) {
    switch (b->keycode) {
    case KEY_LEFTCTRL:
        keyModifier.LEFT_CTRL = 1;
        HAL_GPIO_WritePin(LED2_GPIO_Port, LED2_Pin, GPIO_PIN_SET);
        break;
    case KEY_LEFTSHIFT:
        keyModifier.LEFT_SHIFT = 1;
        HAL_GPIO_WritePin(LED2_GPIO_Port, LED2_Pin, GPIO_PIN_SET);
        break;
    case KEY_LEFTALT:
        keyModifier.LEFT_ALT = 1;
        HAL_GPIO_WritePin(LED2_GPIO_Port, LED2_Pin, GPIO_PIN_SET);
        break;
    case KEY_LEFTMETA:
        keyModifier.LEFT_META = 1;
        HAL_GPIO_WritePin(LED2_GPIO_Port, LED2_Pin, GPIO_PIN_SET);
        break;
    case KEY_RIGHTCTRL:
        keyModifier.RIGHT_CTRL = 1;
        HAL_GPIO_WritePin(LED2_GPIO_Port, LED2_Pin, GPIO_PIN_SET);
        break;
    case KEY_RIGHTSHIFT:
        keyModifier.RIGHT_SHIFT = 1;
        HAL_GPIO_WritePin(LED2_GPIO_Port, LED2_Pin, GPIO_PIN_SET);
        break;
    case KEY_RIGHTALT:
        keyModifier.RIGHT_ALT = 1;
        HAL_GPIO_WritePin(LED2_GPIO_Port, LED2_Pin, GPIO_PIN_SET);
        break;
    case KEY_RIGHTMETA:
        keyModifier.RIGHT_META = 1;
        HAL_GPIO_WritePin(LED2_GPIO_Port, LED2_Pin, GPIO_PIN_SET);
        break;
    default:
        sendKey(b->keycode, keyModifier);
        break;
    }
}

void buttonFreeKey(Button* b, ButtonEvent e) {
    switch (b->keycode) {
    case KEY_LEFTCTRL:
        keyModifier.LEFT_CTRL = 0;
        HAL_GPIO_WritePin(LED2_GPIO_Port, LED2_Pin, GPIO_PIN_RESET);
        break;
    case KEY_LEFTSHIFT:
        keyModifier.LEFT_SHIFT = 0;
        HAL_GPIO_WritePin(LED2_GPIO_Port, LED2_Pin, GPIO_PIN_RESET);
        break;
    case KEY_LEFTALT:
        keyModifier.LEFT_ALT = 0;
        HAL_GPIO_WritePin(LED2_GPIO_Port, LED2_Pin, GPIO_PIN_RESET);
        break;
    case KEY_LEFTMETA:
        keyModifier.LEFT_META = 0;
        HAL_GPIO_WritePin(LED2_GPIO_Port, LED2_Pin, GPIO_PIN_RESET);
        break;
    case KEY_RIGHTCTRL:
        keyModifier.RIGHT_CTRL = 0;
        HAL_GPIO_WritePin(LED2_GPIO_Port, LED2_Pin, GPIO_PIN_RESET);
        break;
    case KEY_RIGHTSHIFT:
        keyModifier.RIGHT_SHIFT = 0;
        HAL_GPIO_WritePin(LED2_GPIO_Port, LED2_Pin, GPIO_PIN_RESET);
        break;
    case KEY_RIGHTALT:
        keyModifier.RIGHT_ALT = 0;
        HAL_GPIO_WritePin(LED2_GPIO_Port, LED2_Pin, GPIO_PIN_RESET);
        break;
    case KEY_RIGHTMETA:
        keyModifier.RIGHT_META = 0;
        HAL_GPIO_WritePin(LED2_GPIO_Port, LED2_Pin, GPIO_PIN_RESET);
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
}

void keyThread(void) {
    keyInterfaceInit();
    buttons_init(buttons, NUM_OF_KEYS);
    for (;;) {
        KeyboardModeHandler();

        if (keyboard_operation_mode == KEYBOARD_OPERATION_MODE_CONFIG) {
        } else if (keyboard_operation_mode == KEYBOARD_OPERATION_MODE_NORMAL) {
            buttons_update(buttons, NUM_OF_KEYS);
            VolumeHandler();
            OS_handler();
        }
        osDelay(1);
    }
}
