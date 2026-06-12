/*
    This file is part of the Arduino_Video library.

    Copyright (C) Arduino s.r.l. and/or its affiliated companies

    This Source Code Form is subject to the terms of the Mozilla Public
    License, v. 2.0. If a copy of the MPL was not distributed with this
    file, You can obtain one at http://mozilla.org/MPL/2.0/.

*/

#pragma once
#include "Arduino.h"

/**
 * @class DisplayShield
 * @brief Abstract base class representing a display shield interface.
 */
class DisplayShield {
public:
  /**
   * @brief Initialize the display shield.
   *
   * @param edidmode The EDID video mode to configure.
   * @return int 0 on success, otherwise an error code.
   */
  virtual int init(int edidmode) = 0;

  /**
   * @brief Get the EDID mode matching the requested resolution.
   *
   * @param h The requested horizontal resolution.
   * @param v The requested vertical resolution.
   * @return int The selected EDID mode.
   */
  virtual int getEdidMode(int h, int v);

  /**
   * @brief Get the connection status of the display.
   *
   * @return int Greater than 0 if the display is connected, otherwise 0.
   */
  virtual int getStatus();
};

/**
 * @class GigaDisplayShieldClass
 * @brief Display shield implementation for the Arduino Giga Display Shield.
 */
class GigaDisplayShieldClass : public DisplayShield {
public:
  int init(int edidmode);
  int getEdidMode(int h, int v);
  int getStatus();
};

extern GigaDisplayShieldClass GigaDisplayShield;

/**
 * @class USBCVideoClass
 * @brief Display shield implementation for a display attached to the USB-C port.
 */
class USBCVideoClass : public DisplayShield {
public:
  int init(int edidmode);
  int getEdidMode(int h, int v);
  int getStatus();
};

extern USBCVideoClass USBCVideo;
