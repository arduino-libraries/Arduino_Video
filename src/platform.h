/*
 * Copyright (C) Arduino s.r.l. and/or its affiliated companies
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */
#ifndef _PLATFORM_H
#define _PLATFORM_H

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

/* Board capability macros */
#ifndef LED_BUILTIN
#define LED_BUILTIN LEDR
#endif

#if __has_include("HasIncludeArduinoGraphics.h")
#include "ArduinoGraphics.h"
#define ARDUINO_VIDEO_HAS_GRAPHICS
#endif

#if defined(__ZEPHYR__) && defined(CONFIG_INPUT_GT911)
#define ARDUINO_VIDEO_HAS_TOUCH
#endif

enum PlatformGpio {
    PLATFORM_GPIO_VIDEO_ON,
    PLATFORM_GPIO_VIDEO_RST,
    PLATFORM_GPIO_OTG_ON,
};

int  platformInit(void);
void platformGpioSet(PlatformGpio gpio, bool state);
bool platformGpioGet(PlatformGpio gpio);
void platformGpioSetDirection(PlatformGpio gpio, bool output);
int  platformI2cWrite(uint8_t saddr, uint8_t offset, uint8_t val);
int  platformI2cRead(uint8_t saddr, uint8_t offset, uint8_t *buf, size_t len);
void platformDelayMs(uint32_t ms);
void platformLvglStartTick(void);

#endif /* _PLATFORM_H */
