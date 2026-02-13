/*
 * Copyright 2023 Arduino SA
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

/**
 * @file Arduino_Video.h
 * @author Leonardo Cavagnis
 * @brief Header file for the Arduino Video library.
 *
 * This library allows to manage the video output on Arduino boards,
 * providing functions to draw graphics on the screen.
 */

#ifndef _ARDUINO_VIDEO_H
#define _ARDUINO_VIDEO_H

/* Includes ------------------------------------------------------------------*/
#include "platform.h"
#include "DisplayShield.h"

/* Class ----------------------------------------------------------------------*/

/**
 * @class Arduino_Video
 * @brief The main class for managing the video controller and the display.
 */
class Arduino_Video
#ifdef ARDUINO_VIDEO_HAS_GRAPHICS
 : public ArduinoGraphics
#endif
{
public:
/**
 * @brief Constructs a new Arduino_Video object with the specified width, height, and display shield.
 * 
 * @param width The width of the display.
 * @param height The height of the display.
 * @param shield The display shield used.
 *               - GigaDisplayShield: Giga Display Shield
 *               - USBCVideo: Display attach to the USB-C port
 */
#if defined(ARDUINO_PORTENTA_H7_M7)
  Arduino_Video(int width = 1024, int height = 768, DisplayShield &shield = USBCVideo);
#elif defined(ARDUINO_GIGA) && defined(ARDUINO_ARCH_MBED)
  Arduino_Video(int width = 800, int height = 480, DisplayShield &shield = GigaDisplayShield);
#else
  #error "Arduino_Video: unsupported board or core configuration"
#endif

  /**
   * @brief Destructor for the Arduino_Video object.
   */
  ~Arduino_Video();

  /**
   * @brief Initialize the video controller and display.
   * 
   * @return int 0 if initialization is successful, otherwise an error code.
   */
  int begin();

  /**
   * @brief De-initialize the video controller and display.
   */  
  void end();

  /**
   * @brief Get the width of the display.
   * 
   * @return int The width of the display.
   */
  int width();

  /**
   * @brief Get the height of the display.
   * 
   * @return int The height of the display.
   */
  int height();

  /**
   * @brief Check if the display is rotated.
   * 
   * @return bool True if the display is rotated, false otherwise.
   */
  bool isRotated();

  /**
   * @brief Checks if the display is connected.  
   * 
   * @return true if the display is connected, false otherwise. 
   */
   bool detect();

#ifdef ARDUINO_VIDEO_HAS_GRAPHICS
  /**
   * @brief Clear the display.
   */
  void clear();

  /**
   * @brief Begin drawing operations on the display.
   */
  virtual void beginDraw();

  /**
   * @brief End drawing operations on the display.
   */
  virtual void endDraw();

  /**
   * @brief Set the color of the pixel at the specified coordinates.
   * 
   * @param x The x-coordinate of the pixel.
   * @param y The y-coordinate of the pixel.
   * @param r The red component of the color.
   * @param g The green component of the color.
   * @param b The blue component of the color.
   */
  virtual void set(int x, int y, uint8_t r, uint8_t g, uint8_t b);
#endif
private:
    DisplayShield*    _shield;
    bool                _rotated;
    int                 _edidMode;
    uint32_t            _width;
    uint32_t            _height;
};

#endif /* _ARDUINO_VIDEO_H */
