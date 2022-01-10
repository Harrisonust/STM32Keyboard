/*
 * matrix_button.h
 *
 *  Created on: Dec 25, 2021
 *      Author: Harrison
 */

#ifndef INC_MATRIX_BUTTON_H_
#define INC_MATRIX_BUTTON_H_

#include "stm32f1xx_hal.h"
//
#include "keyInterface.h"

#define HOLDING_COUNT_THRESHOLD 1000
typedef enum {
    BUTTON_CLICKED,
    BUTTON_RELEASED,
    BUTTON_HOLDING,
} ButtonEvent;

typedef struct BUTTON_DEF Button;

typedef void (*ButtonListener)(Button *, ButtonEvent);

typedef struct BUTTON_DEF {
    GPIO_TypeDef *Button_Output_Port;
    uint16_t Button_Output_Pin;

    GPIO_TypeDef *Button_Input_Port;
    uint16_t Button_Input_Pin;

    uint16_t debouncer;
    // Public state
    uint8_t pressed;
    uint32_t holding_cnt;

    // Public Writable configuration
    uint16_t debounce_threshold;
    ButtonListener button_released_listener;
    ButtonListener button_clicked_listener;
    ButtonListener button_holding_listener;

    uint8_t keycode;

} Button;

/**
 * @brief      Initialize the button on a GPIO pin
 *
 * @param      button  The button
 */
void button_init(Button *button, GPIO_TypeDef *Out_GPIOx, uint16_t Out_GPIO_Pin,
                 GPIO_TypeDef *In_GPIOx, uint16_t In_GPIO_Pin);

/**
 * @brief      Returns whether the given button is pressed
 *
 * checks the Raw state, use button->pressed field for debounced state (checked in button_update)
 *
 * @param      button  The button
 *
 * @return     Logical Binary value of the state of the Button
 */
uint8_t button_read(Button *button);

/**
 * @brief      Update state (w/ debouncing) of this button and trigger any registered listeners
 *
 * @param      button The button to update
 */
void button_update(Button *button);

void buttons_update(Button *button, uint16_t len);

#endif /* INC_MATRIX_BUTTON_H_ */