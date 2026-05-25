# Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`class` [`Arduino_Video`](#class-arduino_video) | The main class for managing the video controller and the display.

# class [`Arduino_Video`](#class-arduino_video)
The main class for managing the video controller and the display.

## Summary

| Members                                                     | Descriptions                                |
|-------------------------------------------------------------|---------------------------------------------|
| `public ` [`Arduino_Video`](#public-arduino_videoint-width-int-height-displayshield-shield) | Construct a new Arduino_Video object with board-specific defaults. |
| `public ` [`~Arduino_Video`](#public-arduino_video) | Destructor for the Arduino_Video object. |
| `public int` [`begin`](#public-int-begin) | Initialize the video controller, backlight, and display. |
| `public void` [`end`](#public-void-end) | De-initialize the video controller and display. |
| `public bool` [`detect`](#public-bool-detect) | Checks if the display is connected. |
| `public int` [`width`](#public-int-width) | Get the width of the display. |
| `public int` [`height`](#public-int-height) | Get the height of the display. |
| `public bool` [`isRotated`](#public-bool-isrotated) | Check if the display is rotated. |
| `public int` [`drawBuffer`](#public-int-drawbufferuint16_t-x-uint16_t-y-const-void-buf) | Draw a raw pixel buffer to the display at specified coordinates. |
| `public void*` [`getFramebuffer`](#public-void-getframebuffer) | Get a direct pointer to the active hardware framebuffer. |
| `public void` [`setFrameDesc`](#public-void-setframedescuint16_t-w-uint16_t-h-uint16_t-pitch-uint32_t-buf_size) | *(Zephyr only)* Set the frame descriptor for the display layout. |
| `public void` [`clear`](#public-void-clear) | Clear the display buffer. |
| `public void` [`beginDraw`](#public-void-begindraw) | Begin drawing operations on the display. |
| `public void` [`endDraw`](#public-void-enddraw) | End drawing operations and commit updates to the panel. |
| `public void` [`set`](#public-void-setint-x-int-y-uint8_t-r-uint8_t-g-uint8_t-b) | Set the color of a specific pixel (handles automatic rotation/format mapping). |

> *Note: For all core drawing functions (such as `rect`, `circle`, `stroke`, `fill`), refer to the documentation of the underlying [`ArduinoGraphics`](https://reference.arduino.cc/reference/en/libraries/arduinographics/) library.*

## Members

### `public ` [`Arduino_Video`](#)`(int width, int height, DisplayShield &shield)`

Construct a new Arduino_Video object. If no parameters are provided, they are automatically configured via internal macros based on the target board selected in the IDE.

#### Default configurations:
- **Arduino Portenta H7:** `width = 1024`, `height = 768`, `shield = USBCVideo`
- **Arduino GIGA R1 WiFi:** `width = 800`, `height = 480`, `shield = GigaDisplayShield`

#### Parameters
- `width`: The custom width of the display.
- `height`: The custom height of the display.
- `shield`: The display shield object used (`GigaDisplayShield` or `USBCVideo`).

---

### `public ` [`~Arduino_Video`](#)`()`

Destructor. Cleans up video registers and tears down structural allocations safely.

---

### `public int` [`begin`](#)`()`

Initialize the video controller hardware bridge, turns on the display backlight panel, and automatically initializes the LVGL engine configuration if `lvgl.h` is detected in the compilation tree.

#### Returns
`int`: 
- `0`: Initialization successful.
- `1`: Unknown `ArduinoGraphics` initialization error.
- `2`: Insufficient RAM memory for LVGL display buffer allocation.
- `3`: Video Controller/Bridge hardware initialization failure or Zephyr Display driver not ready.

---

### `public void` [`end`](#)`()`

De-initialize the video controller, unloading drawing contexts and disabling active display layers.

---

### `public bool` [`detect`](#)`()`

Checks if the display shield hardware is physically connected to the board.

#### Returns
`bool`: True if the display is connected, False otherwise.

---

### `public int` [`width`](#)`()`

Get the current width of the display layout.

#### Returns
`int`: Width in pixels.

---

### `public int` [`height`](#)`()`

Get the current height of the display layout.

#### Returns
`int`: Height in pixels.

---

### `public bool` [`isRotated`](#)`()`

Check if the active display orientation is rotated or constrained by EDID video modes.

#### Returns
`bool`: `true` if rotated, `false` otherwise.

---

### `public int` [`drawBuffer`](#)`(uint16_t x, uint16_t y, const void *buf)`

Directly copies a block of raw pixel memory onto the display panel starting at the specified coordinates. *(Currently supported under Zephyr RTOS builds)*.

#### Parameters
- `x`: Top-left target X coordinate.
- `y`: Top-left target Y coordinate.
- `buf`: Pointer to the source pixel data buffer.

#### Returns
`int`: `0` on success, or a negative error code (e.g. `-ENODEV`) if the video device is not ready.

---

### `public void*` [`getFramebuffer`](#)`()`

Exposes direct low-level access to the active rendering video memory channel.

#### Returns
`void*`: A pointer pointing directly to the hardware VRAM allocation space, or `nullptr` if unavailable under the current backend target.

---

### `public void` [`setFrameDesc`](#)`(uint16_t w, uint16_t h, uint16_t pitch, uint32_t buf_size)`

*(Zephyr Architecture Only)* Configures the active row pitch, buffer byte constraints, and dimension boundaries for low-level screen writes.

#### Parameters
- `w`: Width of the frame in pixels.
- `h`: Height of the frame in pixels.
- `pitch`: Total number of pixels between consecutive rows in the data buffer.
- `buf_size`: Total allocation size of the data buffer in bytes.

---

### `public void` [`clear`](#)`()`

Clears the active display frame buffer instantly, filling it with the current background color setup or zeros.

---

### `public void` [`beginDraw`](#)`()`

Prepares the display pipeline for incoming sequential coordinate updates. 

---

### `public void` [`endDraw`](#)`()`

Ends the drawing sequence and instructs the DSI hardware peripheral to immediately flush and synchronize data changes onto the active screen.

---

### `public void` [`set`](#)`(int x, int y, uint8_t r, uint8_t g, uint8_t b)`

Plots a single pixel at the designated coordinates. This method automatically handles hardware format packing (e.g., RGB565 packaging matrix) and physical coordinate rotation tracking under the hood.

#### Parameters
- `x`: Target X coordinate of the pixel.
- `y`: Target Y coordinate of the pixel.
- `r`: Red color density component (0-255).
- `g`: Green color density component (0-255).
- `b`: Blue color density component (0-255).

---

> *Note: For comprehensive information on hardware acceleration methods, fonts, or shapes, please refer directly to the official documentation of the [`ArduinoGraphics`](https://reference.arduino.cc/reference/en/libraries/arduinographics/) repository.*