/*
  User overrides for LVGL configuration.

  Place this file in your sketch folder to customize LVGL settings.
  Any define here overrides the library defaults in lv_conf.h.
*/

/* Widgets used by this example */
#define LV_USE_IMAGE        1
#define LV_USE_CHECKBOX     1
#define LV_USE_BUTTON       1
#define LV_USE_LABEL        1
#define LV_USE_SLIDER       1   /* requires LV_USE_BAR */
#define LV_USE_BAR          1

/* Layouts used by this example */
#define LV_USE_FLEX         1
#define LV_USE_GRID         1

/* Theme used by this example */
#define LV_USE_THEME_DEFAULT 1

/* Color formats needed by this example */
#define LV_DRAW_SW_SUPPORT_RGB565       1   /* display pixel format */
#define LV_DRAW_SW_SUPPORT_RGB888       1   /* used internally for gradients */
#define LV_DRAW_SW_SUPPORT_ARGB8888     1   /* used internally for transparency */
