/*
    This file is part of the Arduino_Video library.

    Copyright (C) Arduino s.r.l. and/or its affiliated companies

    This Source Code Form is subject to the terms of the Mozilla Public
    License, v. 2.0. If a copy of the MPL was not distributed with this
    file, You can obtain one at http://mozilla.org/MPL/2.0/.

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
#define DMA2D_INPUT_RGB565 0x00000002U /* RGB565 color mode */
#endif

/**
 * @brief Initialize the DSI host and display backend.
 *
 * @param bus The DSI bus index.
 * @param edid Pointer to the parsed EDID information.
 * @param dt Pointer to the display timing configuration.
 * @return int 0 on success, otherwise an error code.
 */
int dsi_init(uint8_t bus, struct edid *edid, struct display_timing *dt);

/**
 * @brief Clear the framebuffer with a solid color.
 *
 * @param color The fill color in RGB888 format.
 */
void dsi_lcdClear(uint32_t color);

/**
 * @brief Draw an image buffer to a destination buffer.
 *
 * @param pSrc Pointer to the source image buffer.
 * @param pDst Pointer to the destination buffer, or NULL for the current framebuffer.
 * @param xSize The width of the image in pixels.
 * @param ySize The height of the image in pixels.
 * @param ColorMode The color mode of the image data.
 */
void dsi_lcdDrawImage(void *pSrc, void *pDst, uint32_t xSize, uint32_t ySize, uint32_t ColorMode);

/**
 * @brief Fill a rectangular area with a solid color.
 *
 * @param pDst Pointer to the destination buffer.
 * @param xSize The width of the area in pixels.
 * @param ySize The height of the area in pixels.
 * @param ColorMode The fill color in RGB888 format.
 */
void dsi_lcdFillArea(void *pDst, uint32_t xSize, uint32_t ySize, uint32_t ColorMode);

/**
 * @brief Configure the color lookup table (CLUT).
 *
 * @param clut Pointer to the color lookup table.
 */
void dsi_configueCLUT(uint32_t *clut);

/**
 * @brief Commit the current framebuffer to the display.
 *
 * @param reload True to reload the framebuffer, false to skip the update.
 */
void dsi_drawCurrentFrameBuffer(bool reload = true);

/**
 * @brief Get the address of the current (back) framebuffer.
 *
 * @return uint32_t The framebuffer address.
 */
uint32_t dsi_getCurrentFrameBuffer(void);

/**
 * @brief Get the address of the active (front) framebuffer.
 *
 * @return uint32_t The framebuffer address.
 */
uint32_t dsi_getActiveFrameBuffer(void);

/**
 * @brief Get the end address of the framebuffer region.
 *
 * @return uint32_t The end address of the framebuffer region.
 */
uint32_t dsi_getFramebufferEnd(void);

/**
 * @brief Get the horizontal size of the display.
 *
 * @return uint32_t The display width in pixels.
 */
uint32_t dsi_getDisplayXSize(void);

/**
 * @brief Get the vertical size of the display.
 *
 * @return uint32_t The display height in pixels.
 */
uint32_t dsi_getDisplayYSize(void);
#endif /* _DSI_H */
