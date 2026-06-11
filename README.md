# 📺 Arduino Video Library

The Arduino Video Library manages the video output on Arduino boards, providing functions to draw on the screen and integrate third-party video libraries such as [LVGL](https://lvgl.io/).

It acts as a hardware abstraction layer, allowing you to draw basic shapes via [ArduinoGraphics](https://github.com/arduino-libraries/ArduinoGraphics) or build advanced graphical user interfaces (GUIs) by seamlessly integrating [LVGL (v9.x or higher)](https://lvgl.io/).

> ⚠️ **Core Compatibility:** This library functions strictly under the **[ArduinoCore-zephyr](https://github.com/arduino/ArduinoCore-zephyr)** core environment. Standard Mbed or non-RTOS Arduino cores are not supported.

---

## Supported Hardware

| Board | Video Output / Shield Supported | Default Resolution |
| :--- | :--- | :--- |
| **Arduino GIGA R1 WiFi** | Giga Display Shield | 800 x 480 |
| **Arduino Portenta H7** (M7 Core) | USB Type-C Video Output / Giga Display Shield | 1024 x 768 |

---

## License

Except where noted in the file headers, most of the files in this library are licensed under the terms of the GNU General Public License, version 2, so that is the license that applies to the library as a whole.

---

📚 For more information about this library, please refer to the documentation [here](./docs/).
