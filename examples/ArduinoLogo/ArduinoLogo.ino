/*
  ArduinoLogo

  created 17 Apr 2023
  by Leonardo Cavagnis
*/

#include "Arduino_Video.h"
#include "ArduinoGraphics.h"

#include "img_arduinologo.h"
// Alternatively, any raw RGB565 image can be included on demand using this macro
// Online image converter: https://lvgl.io/tools/imageconverter (Output format: Binary RGB565)
/*
#define INCBIN_PREFIX
#include "incbin.h"
INCBIN(test, "/home/user/Downloads/test.bin");
*/

Arduino_Video Display;

Image img_arduinologo(ENCODING_RGB16, (uint8_t *) texture_raw, 300, 300);

void error() {
    while (true) {
        digitalWrite(LED_BUILTIN, LOW);
        delay(500);
        digitalWrite(LED_BUILTIN, HIGH);
        delay(500);
    }
}

void setup() {
  if (Display.begin()) {
      error();
  }

  Display.beginDraw();
  Display.image(img_arduinologo, (Display.width() - img_arduinologo.width())/2, (Display.height() - img_arduinologo.height())/2);
  Display.endDraw();
}

void loop() { }
