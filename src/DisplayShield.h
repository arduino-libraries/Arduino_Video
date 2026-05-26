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
 *
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
