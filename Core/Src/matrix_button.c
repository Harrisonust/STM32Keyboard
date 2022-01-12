#include "matrix_button.h"

/**
 * @brief      Initialize the button on a GPIO pin
 *
 * @param      button  The button
 */
void button_init(Button *button, GPIO_TypeDef *Out_GPIOx, uint16_t Out_GPIO_Pin,
                 GPIO_TypeDef *In_GPIOx, uint16_t In_GPIO_Pin) {
    button->Button_Output_Port = Out_GPIOx;
    button->Button_Output_Pin = Out_GPIO_Pin;
    button->Button_Input_Port = In_GPIOx;
    button->Button_Input_Pin = In_GPIO_Pin;

    button->button_released_listener = NULL;
    button->button_clicked_listener = NULL;
    button->button_holding_listener = NULL;

    // button->debounce_threshold = 10;
}

/**
 * @brief      Returns whether the given button is pressed
 *
 * checks the Raw state, use button->pressed field for debounced state (checked in button_update)
 *
 * @param      button  The button
 *
 * @return     Logical Binary value of the state of the Button
 */
uint8_t button_read(Button *button) {
    HAL_GPIO_WritePin(button->Button_Output_Port, button->Button_Output_Pin, GPIO_PIN_SET);
    uint8_t status = HAL_GPIO_ReadPin(button->Button_Input_Port, button->Button_Input_Pin);
    HAL_GPIO_WritePin(button->Button_Output_Port, button->Button_Output_Pin, GPIO_PIN_RESET);
    return status;
}

/**
 * @brief      Update state (w/ debouncing) of this button and trigger any registered listeners
 *
 * @param      button The button to update
 */
void button_update(Button *button) {
    uint8_t state = button_read(button);
    uint8_t pressed = button->pressed;
    if (state != button->pressed) {
        if (++button->debouncer > button->debounce_threshold) {
            pressed = state;
        }
    } else {
        button->debouncer = 0;
    }

    if (pressed) {
        button->holding_cnt++;
        if (button->button_clicked_listener && !button->pressed) {
            button->button_clicked_listener(button, BUTTON_CLICKED);
        } else if (button->button_holding_listener && button->pressed && button->holding_cnt > HOLDING_COUNT_THRESHOLD) {
            button->button_holding_listener(button, BUTTON_HOLDING);
        }
    } else {
        button->holding_cnt = 0;
        if (button->button_released_listener && button->pressed) {
            button->button_released_listener(button, BUTTON_RELEASED);
        }
    }

    button->pressed = pressed;
}

void buttons_update(Button *button, uint16_t len) {
    for (int i = 0; i < len; i++) {
        button_update(&button[i]);
    }
}