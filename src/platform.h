/*
    This file is part of the Arduino_Video library.

    Copyright (C) Arduino s.r.l. and/or its affiliated companies

    This Source Code Form is subject to the terms of the Mozilla Public
    License, v. 2.0. If a copy of the MPL was not distributed with this
    file, You can obtain one at http://mozilla.org/MPL/2.0/.

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

int platformInit(void);
void platformGpioSet(PlatformGpio gpio, bool state);
bool platformGpioGet(PlatformGpio gpio);
void platformGpioSetDirection(PlatformGpio gpio, bool output);
int platformI2cWrite(uint8_t saddr, uint8_t offset, uint8_t val);
int platformI2cRead(uint8_t saddr, uint8_t offset, uint8_t *buf, size_t len);
void platformDelayMs(uint32_t ms);
void platformLvglStartTick(void);

#endif /* _PLATFORM_H */
