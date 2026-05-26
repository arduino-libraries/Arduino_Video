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

 #include "DisplayShield.h"

#include "Arduino.h"
#include "anx7625.h"
extern "C" {
#include "video_modes.h"
}

#if defined(ARDUINO_GIGA) && defined(__ZEPHYR__)
int GigaDisplayShieldClass::init(int edidmode) {
    return 0;
}

int GigaDisplayShieldClass::getEdidMode(int h, int v) {
    return EDID_MODE_480x800_60Hz;
}

int GigaDisplayShieldClass::getStatus() {
    return 1; // TODO: Not implemented;
}

GigaDisplayShieldClass GigaDisplayShield;
#endif /* ARDUINO_GIGA && __ZEPHYR__ */

int USBCVideoClass::init(int edidmode) {
    struct edid recognized_edid;
    int err_code = 0;

    memset(&recognized_edid, 0, sizeof(recognized_edid));

    //Initialization of ANX7625
    err_code = anx7625_init(0);
    if(err_code < 0) {
        return err_code;
    }

    //Checking HDMI plug event
    err_code = anx7625_wait_hpd_event(0);
    if(err_code < 0) {
        return err_code;
    }

    //Read EDID
    anx7625_dp_get_edid(0, &recognized_edid);

    //DSI Configuration
    err_code = anx7625_dp_start(0, &recognized_edid, (enum edid_modes) edidmode);
    if(err_code < 0) {
        return err_code;
    }

    return 0;
}

int USBCVideoClass::getEdidMode(int h, int v) {
    int edidmode = video_modes_get_edid(h, v);

    return edidmode;
}

int USBCVideoClass::getStatus() {
    int detected = anx7625_get_hpd_event(0);

    return detected;
}

USBCVideoClass USBCVideo;
