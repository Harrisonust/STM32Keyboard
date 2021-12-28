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

// uint8_t curr_btn_state[4][4] = {0};
// uint8_t prev_btn_state[4][4] = {0};
// uint32_t pressed_startTick[4][4] = {0};
GPIO_PinState readKey(uint8_t row, uint8_t col) {
    //     prev_btn_state[row][col] = curr_btn_state[row][col];

    //     reset(COL0);
    //     reset(COL1);
    //     reset(COL2);
    //     reset(COL3);
    //     //	reset(COL4);
    //     //	reset(COL5);

    //     switch (col) {
    //     case 0:
    //         set(COL0);
    //         break;
    //     case 1:
    //         set(COL1);
    //         break;
    //     case 2:
    //         set(COL2);
    //         break;
    //     case 3:
    //         set(COL3);
    //         break;
    //         //		case 4:	set(COL4);	break;
    //         //		case 5:	set(COL5);	break;
    //     default:
    //         break;
    //     }

    //     switch (row) {
    //     case 0:
    //         curr_btn_state[0][col] = read(ROW0);
    //         break;
    //     case 1:
    //         curr_btn_state[1][col] = read(ROW1);
    //         break;
    //     case 2:
    //         curr_btn_state[2][col] = read(ROW2);
    //         break;
    //     case 3:
    //         curr_btn_state[3][col] = read(ROW3);
    //         break;
    //         //		case 4:		curr_btn_state[4][col] = read(ROW4);		break;
    //         //		case 5:		curr_btn_state[5][col] = read(ROW5);		break;
    //         //		case 6:		curr_btn_state[6][col] = read(ROW6);		break;
    //         //		case 7:		curr_btn_state[7][col] = read(ROW7);		break;
    //         //		case 8:		curr_btn_state[8][col] = read(ROW8);		break;
    //         //		case 9:		curr_btn_state[9][col] = read(ROW9);		break;
    //         //		case 10:	curr_btn_state[10][col] = read(ROW10);		break;
    //         //		case 11:	curr_btn_state[11][col] = read(ROW11);		break;
    //         //		case 12:	curr_btn_state[12][col] = read(ROW12);		break;
    //         //		case 13:	curr_btn_state[13][col] = read(ROW13);		break;
    //     default:
    //         break;
    //     }

    //     reset(COL0);
    //     reset(COL1);
    //     reset(COL2);
    //     reset(COL3);
    //     //	reset(COL4);
    //     //	reset(COL5);

    // #define LONG_PRESS_TIMEOUT 1000

    //     if (curr_btn_state[row][col] == 1 && prev_btn_state[row][col] == 0) {
    //         pressed_startTick[row][col] = HAL_GetTick();
    //     }
    //     if ((curr_btn_state[row][col] == 1) && (HAL_GetTick() - pressed_startTick[row][col] > LONG_PRESS_TIMEOUT)) {
    //         return GPIO_PIN_SET;
    //     }

    //     if (curr_btn_state[row][col] == 1 && prev_btn_state[row][col] == 0)
    //         return GPIO_PIN_SET;
    //     else
    //         return GPIO_PIN_RESET;
    return GPIO_PIN_RESET;
}

void apply_modifier(KeyModifier* m) {
    // m->LEFT_CTRL = readKey(5, 0) ? 1 : 0;
    // m->LEFT_SHIFT = readKey(4, 0) ? 1 : 0;
    // m->LEFT_ALT = readKey(5, 2) ? 1 : 0;
    // m->LEFT_GUI = readKey(100, 100) ? 1 : 0;

    // m->RIGHT_CTRL = readKey(5, 7) ? 1 : 0;
    // m->RIGHT_SHIFT = readKey(4, 4) ? 1 : 0;
    // m->RIGHT_ALT = readKey(5, 11) ? 1 : 0;
    // m->RIGHT_GUI = readKey(100, 100) ? 1 : 0;
    return;
}

// add device as a parameter. e.g. cable, bluetooth
void sendKey(const uint8_t ch, const KeyModifier mod) {
    // if (keyboard_connection_mode == KEYBOARD_CONNECTION_MODE_BLUETOOTH) {
    //     uint8_t data[1] = {'a'};
    //     HAL_UART_Transmit(&huart4, data, 1, 2000);
    // }

    keyboardStct.hid.MODIFIER = (mod.LEFT_CTRL << 0) | (mod.LEFT_SHIFT << 1) | (mod.LEFT_ALT << 2) | (mod.LEFT_GUI << 3) | (mod.RIGHT_CTRL << 4) | (mod.RIGHT_SHIFT << 5) | (mod.RIGHT_ALT << 6) | (mod.RIGHT_GUI << 7);
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
void buttons_init(Button* buttons, int len) {
    button_init(&buttons[0], Pin(COL0), Pin(ROW0));
    button_init(&buttons[1], Pin(COL0), Pin(ROW1));
    button_init(&buttons[2], Pin(COL0), Pin(ROW2));
    button_init(&buttons[3], Pin(COL0), Pin(ROW3));
    button_init(&buttons[4], Pin(COL1), Pin(ROW0));
    button_init(&buttons[5], Pin(COL1), Pin(ROW1));
    button_init(&buttons[6], Pin(COL1), Pin(ROW2));
    button_init(&buttons[7], Pin(COL1), Pin(ROW3));
    button_init(&buttons[8], Pin(COL2), Pin(ROW0));
    button_init(&buttons[9], Pin(COL2), Pin(ROW1));
    button_init(&buttons[10], Pin(COL2), Pin(ROW2));
    button_init(&buttons[11], Pin(COL2), Pin(ROW3));
    button_init(&buttons[12], Pin(COL3), Pin(ROW0));
    button_init(&buttons[13], Pin(COL3), Pin(ROW1));
    button_init(&buttons[14], Pin(COL3), Pin(ROW2));
    button_init(&buttons[15], Pin(COL3), Pin(ROW3));

    buttons[0].data = 'a';
    buttons[1].data = 'b';
    buttons[2].data = 'c';
    buttons[3].data = 'd';

    for (int i = 0; i < len; i++) {
        buttons[i].button_clicked_listener = buttonSendKey;
    }
}

void buttonSendKey(Button* b, ButtonEvent e) {
    sendKey(getKeyIDByChar(b->data), b->modifier);
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
    //         sendKey(getKeyIDByChar(ptr->data), m);
    //         osDelay(20);
    //     }
    // }
}

void keyThread(void) {
    keyInterfaceInit();
    Button buttons[NUM_OF_KEYS];
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
