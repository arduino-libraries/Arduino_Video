/*
    This file is part of the Arduino_Video library.

    Copyright (C) Arduino s.r.l. and/or its affiliated companies

    This Source Code Form is subject to the terms of the Mozilla Public
    License, v. 2.0. If a copy of the MPL was not distributed with this
    file, You can obtain one at http://mozilla.org/MPL/2.0/.

*/

#pragma once
#include "Arduino.h"

class DisplayShield {
public:
  virtual int init(int edidmode) = 0;
  virtual int getEdidMode(int h, int v);
  virtual int getStatus();
};

class GigaDisplayShieldClass : public DisplayShield {
public:
  int init(int edidmode);
  int getEdidMode(int h, int v);
  int getStatus();
};

extern GigaDisplayShieldClass GigaDisplayShield;

class USBCVideoClass : public DisplayShield {
public:
  int init(int edidmode);
  int getEdidMode(int h, int v);
  int getStatus();
};

extern USBCVideoClass USBCVideo;
