/**
 * This Library was originally written by Olivier Van den Eede (4ilo) in 2016.
 * Some refactoring was done and SPI support was added by Aleksander Alekseev (afiskon) in 2018.
 *
 * https://github.com/afiskon/stm32-ssd1306
 */

#ifndef __SSD1306_H__
#define __SSD1306_H__

#include <_ansi.h>
#include <stddef.h>

_BEGIN_STD_C

#include "ssd1306_conf.h"

#if defined(STM32F0)
#include "stm32f0xx_hal.h"
#elif defined(STM32F1)
#include "stm32f1xx_hal.h"
#elif defined(STM32F4)
#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_gpio.h"
#elif defined(STM32L0)
#include "stm32l0xx_hal.h"
#elif defined(STM32L1)
#include "stm32l1xx_hal.h"
#elif defined(STM32L4)
#include "stm32l4xx_hal.h"
#elif defined(STM32F3)
#include "stm32f3xx_hal.h"
#elif defined(STM32H7)
#include "stm32h7xx_hal.h"
#elif defined(STM32F7)
#include "stm32f7xx_hal.h"
#elif defined(STM32G0)
#include "stm32g0xx_hal.h"
#else
#error "SSD1306 library was tested only on STM32F0, STM32F1, STM32F3, STM32F4, STM32F7, STM32L0, STM32L1, STM32L4, STM32H7, STM32G0 MCU families. Please modify ssd1306.h if you know what you are doing. Also please send a pull request if it turns out the library works on other MCU's as well!"
#endif

#include "ssd1306_fonts.h"

/* vvv I2C config vvv */

#ifndef SSD1306_I2C_PORT
#define SSD1306_I2C_PORT hi2c1
#endif

#ifndef SSD1306_I2C_ADDR
#define SSD1306_I2C_ADDR (0x3C << 1)
#endif

/* ^^^ I2C config ^^^ */

/* vvv SPI config vvv */

#ifndef SSD1306_SPI_PORT
#define SSD1306_SPI_PORT hspi1
#endif

#ifndef SSD1306_CS_Port
#define SSD1306_CS_Port GPIOB
#endif
#ifndef SSD1306_CS_Pin
#define SSD1306_CS_Pin GPIO_PIN_0
#endif

#ifndef SSD1306_DC_Port
#define SSD1306_DC_Port GPIOC
#endif
#ifndef SSD1306_DC_Pin
#define SSD1306_DC_Pin GPIO_PIN_5
#endif

#ifndef SSD1306_Reset_Port
#define SSD1306_Reset_Port GPIOC
#endif
#ifndef SSD1306_Reset_Pin
#define SSD1306_Reset_Pin GPIO_PIN_4
#endif

/* ^^^ SPI config ^^^ */

#if defined(SSD1306_USE_I2C)
extern I2C_HandleTypeDef SSD1306_I2C_PORT;
#elif defined(SSD1306_USE_SPI)
extern SPI_HandleTypeDef SSD1306_SPI_PORT;
#else
#error "You should define SSD1306_USE_SPI or SSD1306_USE_I2C macro!"
#endif

// SSD1306 OLED height in pixels
#ifndef SSD1306_HEIGHT
#define SSD1306_HEIGHT 64
#endif

// SSD1306 width in pixels
#ifndef SSD1306_WIDTH
#define SSD1306_WIDTH 128
#endif

#ifndef SSD1306_BUFFER_SIZE
#define SSD1306_BUFFER_SIZE SSD1306_WIDTH* SSD1306_HEIGHT / 8
#endif

// Enumeration for screen colors
typedef enum {
    Black = 0x00,  // Black color, no pixel
    White = 0x01   // Pixel is set. Color depends on OLED
} SSD1306_COLOR;

typedef enum {
    SSD1306_OK = 0x00,
    SSD1306_ERR = 0x01  // Generic error.
} SSD1306_Error_t;

// Struct to store transformations
typedef struct {
    uint16_t CurrentX;
    uint16_t CurrentY;
    uint8_t Initialized;
    uint8_t DisplayOn;
} SSD1306_t;

typedef struct {
    uint8_t x;
    uint8_t y;
} SSD1306_VERTEX;

// Procedure definitions
void ssd1306_Init(void);
void ssd1306_Fill(SSD1306_COLOR color);
void ssd1306_UpdateScreen(void);
void ssd1306_DrawPixel(uint8_t x, uint8_t y, SSD1306_COLOR color);
char ssd1306_WriteChar(char ch, FontDef Font, SSD1306_COLOR color);
char ssd1306_WriteString(char* str, FontDef Font, SSD1306_COLOR color);
void ssd1306_SetCursor(uint8_t x, uint8_t y);
void ssd1306_Line(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, SSD1306_COLOR color);
void ssd1306_DrawArc(uint8_t x, uint8_t y, uint8_t radius, uint16_t start_angle, uint16_t sweep, SSD1306_COLOR color);
void ssd1306_DrawCircle(uint8_t par_x, uint8_t par_y, uint8_t par_r, SSD1306_COLOR color);
void ssd1306_Polyline(const SSD1306_VERTEX* par_vertex, uint16_t par_size, SSD1306_COLOR color);
void ssd1306_DrawRectangle(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, SSD1306_COLOR color);
void ssd1306_DrawPic(const uint16_t* pic, uint8_t x, uint8_t y);
/**
 * @brief Sets the contrast of the display.
 * @param[in] value contrast to set.
 * @note Contrast increases as the value increases.
 * @note RESET = 7Fh.
 */
void ssd1306_SetContrast(const uint8_t value);
/**
 * @brief Set Display ON/OFF.
 * @param[in] on 0 for OFF, any for ON.
 */
void ssd1306_SetDisplayOn(const uint8_t on);
/**
 * @brief Reads DisplayOn state.
 * @return  0: OFF.
 *          1: ON.
 */
uint8_t ssd1306_GetDisplayOn();

// Low-level procedures
void ssd1306_Reset(void);
void ssd1306_WriteCommand(uint8_t byte);
void ssd1306_WriteData(uint8_t* buffer, size_t buff_size);
SSD1306_Error_t ssd1306_FillBuffer(uint8_t* buf, uint32_t len);

#define PIC_ROW_LEN 16
#define PIC_COL_LEN 16

static const uint16_t BLE_ICON[] = {
    0x0200,
    0x0300,
    0x0280,
    0x0240,
    0x1220,
    0x0a40,
    0x0680,
    0x0300,
    0x0300,
    0x0680,
    0x0a40,
    0x1220,
    0x0240,
    0x0280,
    0x0300,
    0x0200};

static const uint16_t CABLE_ICON[] = {
    0x0000,
    0x2800,
    0x3840,
    0x38a0,
    0x1110,
    0x1110,
    0x1110,
    0x1110,
    0x1110,
    0x1110,
    0x1110,
    0x1110,
    0x0a38,
    0x0438,
    0x0028,
    0x0000};

static const uint16_t BATTERY_EMPTY_ICON[] = {
    0x03c0,
    0x0240,
    0x0e70,
    0x0810,
    0x0810,
    0x0810,
    0x0810,
    0x0810,
    0x0810,
    0x0810,
    0x0810,
    0x0810,
    0x0810,
    0x0810,
    0x0810,
    0x0ff0};

static const uint16_t BATTERY_25_ICON[] = {
    0x03c0,
    0x0240,
    0x0e70,
    0x0810,
    0x0810,
    0x0810,
    0x0810,
    0x0810,
    0x0810,
    0x0810,
    0x0810,
    0x0ff0,
    0x0ff0,
    0x0ff0,
    0x0ff0,
    0x0ff0};

static const uint16_t BATTERY_50_ICON[] = {
    0x03c0,
    0x0240,
    0x0e70,
    0x0810,
    0x0810,
    0x0810,
    0x0810,
    0x0810,
    0x0ff0,
    0x0ff0,
    0x0ff0,
    0x0ff0,
    0x0ff0,
    0x0ff0,
    0x0ff0,
    0x0ff0};

static const uint16_t BATTERY_75_ICON[] = {
    0x03c0,
    0x0240,
    0x0e70,
    0x0810,
    0x0810,
    0x0ff0,
    0x0ff0,
    0x0ff0,
    0x0ff0,
    0x0ff0,
    0x0ff0,
    0x0ff0,
    0x0ff0,
    0x0ff0,
    0x0ff0,
    0x0ff0};

static const uint16_t BATTERY_100_ICON[] = {
    0x03c0,
    0x03c0,
    0x0ff0,
    0x0ff0,
    0x0ff0,
    0x0ff0,
    0x0ff0,
    0x0ff0,
    0x0ff0,
    0x0ff0,
    0x0ff0,
    0x0ff0,
    0x0ff0,
    0x0ff0,
    0x0ff0,
    0x0ff0};

static const uint16_t WIN_ICON[] = {
    0x0000,
    0x000f,
    0x0f7f,
    0x7f7f,
    0x7f7f,
    0x7f7f,
    0x7f7f,
    0x7f7f,
    0x0000,
    0x7f7f,
    0x7f7f,
    0x7f7f,
    0x7f7f,
    0x7f7f,
    0x0f0f,
    0x0000};

static const uint16_t APPLE_ICON[] = {
    0x00c0,
    0x01c0,
    0x0180,
    0x3938,
    0x7c7c,
    0xfffe,
    0xfff8,
    0xfff0,
    0xfff0,
    0xfff0,
    0xfff8,
    0xfffe,
    0x7ffc,
    0x7ffc,
    0x3ff8,
    0x1c70};

static const uint16_t LINUX_ICON[] = {
    0x0180,
    0x03c0,
    0x0370,
    0x03e0,
    0x03e0,
    0x07f0,
    0x1ff0,
    0x3e38,
    0x061c,
    0x0610,
    0x0610,
    0x0610,
    0x0630,
    0x0660,
    0x07e0,
    0x0770};

static const uint16_t PACMAN_ICON0[] = {
    0x0ff0,
    0x1ff8,
    0x3ffc,
    0x7ffe,
    0x3fff,
    0x0fff,
    0x03ff,
    0x00ff,
    0x00ff,
    0x03ff,
    0x0fff,
    0x3fff,
    0x7ffe,
    0x3ffc,
    0x1ff8,
    0x0ff0};

static const uint16_t PACMAN_ICON1[] = {
    0x0ff0,
    0x3ffc,
    0x7ffe,
    0x7ffe,
    0xc78f,
    0x8307,
    0x8307,
    0xe3c7,
    0xe3c7,
    0xc78f,
    0xffff,
    0xffff,
    0xffff,
    0xffff,
    0xcf7f,
    0xc633};

static const uint16_t PACMAN_ICON2[] = {
    0x1ff8,
    0x3ffc,
    0x7ffe,
    0xffff,
    0xffff,
    0xe7cf,
    0xcf9f,
    0xcd9b,
    0xc183,
    0xc183,
    0xffff,
    0xffff,
    0xffff,
    0xffff,
    0xfe7f,
    0xcc33};

_END_STD_C

#endif  // __SSD1306_H__
