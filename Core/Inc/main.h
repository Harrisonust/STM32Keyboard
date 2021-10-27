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
#define TFT_SCL_Pin GPIO_PIN_5
#define TFT_SCL_GPIO_Port GPIOA
#define TFT_SDA_Pin GPIO_PIN_7
#define TFT_SDA_GPIO_Port GPIOA
#define TFT_DC_Pin GPIO_PIN_4
#define TFT_DC_GPIO_Port GPIOC
#define TFT_RES_Pin GPIO_PIN_5
#define TFT_RES_GPIO_Port GPIOC
#define TFT_CS_Pin GPIO_PIN_0
#define TFT_CS_GPIO_Port GPIOB
#define COL13_Pin GPIO_PIN_11
#define COL13_GPIO_Port GPIOB
#define COL12_Pin GPIO_PIN_12
#define COL12_GPIO_Port GPIOB
#define COL11_Pin GPIO_PIN_13
#define COL11_GPIO_Port GPIOB
#define COL10_Pin GPIO_PIN_14
#define COL10_GPIO_Port GPIOB
#define COL9_Pin GPIO_PIN_15
#define COL9_GPIO_Port GPIOB
#define COL8_Pin GPIO_PIN_8
#define COL8_GPIO_Port GPIOD
#define COL7_Pin GPIO_PIN_9
#define COL7_GPIO_Port GPIOD
#define COL6_Pin GPIO_PIN_10
#define COL6_GPIO_Port GPIOD
#define COL5_Pin GPIO_PIN_11
#define COL5_GPIO_Port GPIOD
#define COL4_Pin GPIO_PIN_12
#define COL4_GPIO_Port GPIOD
#define COL3_Pin GPIO_PIN_13
#define COL3_GPIO_Port GPIOD
#define COL2_Pin GPIO_PIN_14
#define COL2_GPIO_Port GPIOD
#define COL1_Pin GPIO_PIN_15
#define COL1_GPIO_Port GPIOD
#define COL0_Pin GPIO_PIN_6
#define COL0_GPIO_Port GPIOC
#define ROW5_Pin GPIO_PIN_7
#define ROW5_GPIO_Port GPIOC
#define ROW4_Pin GPIO_PIN_8
#define ROW4_GPIO_Port GPIOC
#define ROW3_Pin GPIO_PIN_9
#define ROW3_GPIO_Port GPIOC
#define ROW2_Pin GPIO_PIN_8
#define ROW2_GPIO_Port GPIOA
#define ROW1_Pin GPIO_PIN_9
#define ROW1_GPIO_Port GPIOA
#define ROW0_Pin GPIO_PIN_10
#define ROW0_GPIO_Port GPIOA
#define USB_EN_Pin GPIO_PIN_6
#define USB_EN_GPIO_Port GPIOD
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
