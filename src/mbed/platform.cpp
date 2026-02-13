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
#ifdef ARDUINO_ARCH_MBED

#include <Arduino.h>
#include <drivers/DigitalOut.h>
#include <drivers/DigitalInOut.h>
#include <drivers/I2C.h>
#include "mbed.h"

#include "../platform.h"

#if __has_include("lvgl.h")
#include "lvgl.h"
#endif

static mbed::DigitalOut video_on_pin(PK_2, 0);
static mbed::DigitalOut video_rst_pin(PJ_3, 0);
static mbed::DigitalInOut otg_on_pin(PJ_6, PIN_INPUT, PullUp, 0);
#if defined(ARDUINO_PORTENTA_H7_M7)
static mbed::I2C i2c(I2C_SDA_INTERNAL, I2C_SCL_INTERNAL);
#endif

int platformInit(void) {
    /* GPIOs are already initialized by mbed constructors */
    return 0;
}

void platformGpioSet(PlatformGpio gpio, bool state) {
    switch (gpio) {
    case PLATFORM_GPIO_VIDEO_ON:
        video_on_pin = state ? 1 : 0;
        break;
    case PLATFORM_GPIO_VIDEO_RST:
        video_rst_pin = state ? 1 : 0;
        break;
    case PLATFORM_GPIO_OTG_ON:
        otg_on_pin = state ? 1 : 0;
        break;
    }
}

bool platformGpioGet(PlatformGpio gpio) {
    switch (gpio) {
    case PLATFORM_GPIO_OTG_ON:
        return otg_on_pin.read() != 0;
    default:
        return false;
    }
}

void platformGpioSetDirection(PlatformGpio gpio, bool output) {
    switch (gpio) {
    case PLATFORM_GPIO_OTG_ON:
        if (output) {
            otg_on_pin.output();
        } else {
            otg_on_pin.input();
        }
        break;
    default:
        break;
    }
}

int platformI2cWrite(uint8_t saddr, uint8_t offset, uint8_t val) {
#if defined(ARDUINO_PORTENTA_H7_M7)
    char buf[2] = {(char)offset, (char)val};
    return i2c.write(saddr, buf, 2);
#else
    return -1;
#endif
}

int platformI2cRead(uint8_t saddr, uint8_t offset, uint8_t *buf, size_t len) {
#if defined(ARDUINO_PORTENTA_H7_M7)
    char off = (char)offset;
    i2c.write(saddr, &off, 1, true);
    return i2c.read(saddr, (char*)buf, len);
#else
    return -1;
#endif
}

void platformDelayMs(uint32_t ms) {
    delay(ms);
}

void platformLvglStartTick(void) {
#if __has_include("lvgl.h")
    static rtos::Thread lvgl_inc_thd;
    static bool started = false;
    if (!started) {
        lvgl_inc_thd.start([] {
            while (1) {
                lv_tick_inc(16);
                delay(16);
            }
        });
        started = true;
    }
#endif
}

#endif /* ARDUINO_ARCH_MBED */
