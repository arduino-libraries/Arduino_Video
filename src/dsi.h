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
#ifndef _DSI_H
#define _DSI_H

#include <stdint.h>

struct edid;

struct display_timing {
	unsigned int pixelclock;
	unsigned int hactive;
	unsigned int hfront_porch;
	unsigned int hback_porch;
	unsigned int hsync_len;
	unsigned int vactive;
	unsigned int vfront_porch;
	unsigned int vback_porch;
	unsigned int vsync_len;
	unsigned int hpol : 1;
	unsigned int vpol : 1;
};

/* Color mode constants for dsi_lcdDrawImage */
#ifndef DMA2D_INPUT_RGB565
#define DMA2D_INPUT_RGB565  0x00000002U  /* RGB565 color mode */
#endif

#ifdef ARDUINO_ARCH_MBED
/* DSI handle is only available on mbed platform */
extern DSI_HandleTypeDef dsi;
#endif

int			dsi_init(uint8_t bus, struct edid *edid, struct display_timing *dt);
void		dsi_lcdClear(uint32_t color);
void		dsi_lcdDrawImage(void *pSrc, void *pDst, uint32_t xSize, uint32_t ySize, uint32_t ColorMode);
void		dsi_lcdFillArea(void *pDst, uint32_t xSize, uint32_t ySize, uint32_t ColorMode);
void		dsi_configueCLUT(uint32_t* clut);
void		dsi_drawCurrentFrameBuffer(bool reload = true);
uint32_t	dsi_getCurrentFrameBuffer(void);
uint32_t 	dsi_getActiveFrameBuffer(void);
uint32_t	dsi_getFramebufferEnd(void);
uint32_t 	dsi_getDisplayXSize(void);
uint32_t 	dsi_getDisplayYSize(void);
#endif /* _DSI_H */
