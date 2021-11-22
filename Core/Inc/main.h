/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f1xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

void HAL_TIM_MspPostInit(TIM_HandleTypeDef *htim);

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define BAT_ADC_Pin GPIO_PIN_0
#define BAT_ADC_GPIO_Port GPIOC
#define VOL_CH1_Pin GPIO_PIN_0
#define VOL_CH1_GPIO_Port GPIOA
#define VOL_CH2_Pin GPIO_PIN_1
#define VOL_CH2_GPIO_Port GPIOA
#define LED1_Pin GPIO_PIN_1
#define LED1_GPIO_Port GPIOB
#define LED2_Pin GPIO_PIN_2
#define LED2_GPIO_Port GPIOB
#define RGB_Pin GPIO_PIN_9
#define RGB_GPIO_Port GPIOE
#define BTN1_Pin GPIO_PIN_14
#define BTN1_GPIO_Port GPIOE
#define BTN2_Pin GPIO_PIN_15
#define BTN2_GPIO_Port GPIOE
#define FINGERPRINT_INT_Pin GPIO_PIN_15
#define FINGERPRINT_INT_GPIO_Port GPIOB
#define FINGERPRINT_INT_EXTI_IRQn EXTI15_10_IRQn
#define COL3_Pin GPIO_PIN_13
#define COL3_GPIO_Port GPIOD
#define COL2_Pin GPIO_PIN_14
#define COL2_GPIO_Port GPIOD
#define COL1_Pin GPIO_PIN_15
#define COL1_GPIO_Port GPIOD
#define COL0_Pin GPIO_PIN_6
#define COL0_GPIO_Port GPIOC
#define FINGER_TXD_Pin GPIO_PIN_9
#define FINGER_TXD_GPIO_Port GPIOA
#define FINGER_RXD_Pin GPIO_PIN_10
#define FINGER_RXD_GPIO_Port GPIOA
#define BT_TXD_Pin GPIO_PIN_10
#define BT_TXD_GPIO_Port GPIOC
#define BT_RXD_Pin GPIO_PIN_11
#define BT_RXD_GPIO_Port GPIOC
#define ROW0_Pin GPIO_PIN_0
#define ROW0_GPIO_Port GPIOD
#define ROW0_EXTI_IRQn EXTI0_IRQn
#define ROW1_Pin GPIO_PIN_1
#define ROW1_GPIO_Port GPIOD
#define ROW1_EXTI_IRQn EXTI1_IRQn
#define ROW2_Pin GPIO_PIN_2
#define ROW2_GPIO_Port GPIOD
#define ROW2_EXTI_IRQn EXTI2_IRQn
#define ROW3_Pin GPIO_PIN_3
#define ROW3_GPIO_Port GPIOD
#define ROW3_EXTI_IRQn EXTI3_IRQn
#define USB_EN_Pin GPIO_PIN_6
#define USB_EN_GPIO_Port GPIOD
#define LED3_Pin GPIO_PIN_3
#define LED3_GPIO_Port GPIOB
#define OLED_SCL_Pin GPIO_PIN_6
#define OLED_SCL_GPIO_Port GPIOB
#define OLED_SDA_Pin GPIO_PIN_7
#define OLED_SDA_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */
#define Pin(name) name##_GPIO_Port, name##_Pin
#define set(pin) HAL_GPIO_WritePin(Pin(pin), GPIO_PIN_SET)
#define reset(pin) HAL_GPIO_WritePin(Pin(pin), GPIO_PIN_RESET)
#define read(pin) HAL_GPIO_ReadPin(Pin(pin))
/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
