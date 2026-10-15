/*
    This file is part of the Arduino_Video library.

    Copyright (C) Arduino s.r.l. and/or its affiliated companies

    This Source Code Form is subject to the terms of the Mozilla Public
    License, v. 2.0. If a copy of the MPL was not distributed with this
    file, You can obtain one at http://mozilla.org/MPL/2.0/.

*/

#ifndef _ARDUINO_VIDEO_BACKEND_H
#define _ARDUINO_VIDEO_BACKEND_H

/*
 * ARDUINO_VIDEO_DIRECT_FB selects the display backend at build time:
 *
 *  - defined   -> the panel is fully managed by a Zephyr display driver
 *                 (ST7701 on the Giga Display Shield, either on the Giga R1 or
 *                 on a Portenta H7 + midcarrier built with the Giga Display
 *                 core configuration). The library draws straight into the
 *                 LTDC framebuffer; the Zephyr driver performs the DSI panel
 *                 bring-up at boot.
 *  - undefined -> the library drives the MIPI-DSI bridge itself (anx7625 over
 *                 USB-C on the Portenta H7).
 */
#if defined(__ZEPHYR__)
#include <zephyr/devicetree.h>
#if DT_HAS_COMPAT_STATUS_OKAY(sitronix_st7701)
#define ARDUINO_VIDEO_DIRECT_FB 1
#endif
#endif

#endif /* _ARDUINO_VIDEO_BACKEND_H */
