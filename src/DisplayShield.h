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
