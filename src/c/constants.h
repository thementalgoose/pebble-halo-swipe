#pragma once
#include <pebble.h>

// ===========================================================================
// Configurable Sizes for Watchface Components
// ===========================================================================
// Component 1: Center circle
// Component 2: Hour hand (small and wide)
// Component 3: Minute hand (long and narrow)
// Halo: Around the watchface, clipped to the end of the minute hand
// ===========================================================================

#if defined(PBL_PLATFORM_EMERY) || defined(PBL_PLATFORM_GABBRO)
// Large displays (Emery: 200x228, Gabbro: 228x228)
#define CENTER_CIRCLE_RADIUS    7
#define HOUR_HAND_LENGTH        52
#define HOUR_HAND_WIDTH         6
#define MINUTE_HAND_LENGTH      100
#define MINUTE_HAND_WIDTH       2
#define HALO_RADIUS             96
#define HALO_WIDTH              16

#elif defined(PBL_PLATFORM_CHALK)
// Round display (Chalk: 180x180)
#define CENTER_CIRCLE_RADIUS    6
#define HOUR_HAND_LENGTH        45
#define HOUR_HAND_WIDTH         7
#define MINUTE_HAND_LENGTH      75
#define MINUTE_HAND_WIDTH       2
#define HALO_RADIUS             MINUTE_HAND_LENGTH
#define HALO_WIDTH              10

#else
// Standard displays (144x168: Aplite, Basalt, Diorite, Flint)
#define CENTER_CIRCLE_RADIUS    5
#define HOUR_HAND_LENGTH        38
#define HOUR_HAND_WIDTH         6
#define MINUTE_HAND_LENGTH      64
#define MINUTE_HAND_WIDTH       2
#define HALO_RADIUS             MINUTE_HAND_LENGTH
#define HALO_WIDTH              8

#endif

// ===========================================================================
// Configurable Colors
// ===========================================================================
#if defined(PBL_COLOR)
#define COLOR_BACKGROUND        GColorBlack
#define COLOR_BACKGROUND_HALO   GColorPictonBlue
#define COLOR_CENTER_CIRCLE     GColorWhite
#define COLOR_HOUR_HAND         GColorLightGray
#define COLOR_MINUTE_HAND       GColorWhite
#define COLOR_MINUTE_HALO       GColorWhite
#define COLOR_HEART_RATE        GColorWhite
#define COLOR_HALO              COLOR_MINUTE_HALO
#else
#define COLOR_BACKGROUND        GColorBlack
#define COLOR_BACKGROUND_HALO   GColorDarkGray
#define COLOR_CENTER_CIRCLE     GColorWhite
#define COLOR_HOUR_HAND         GColorWhite
#define COLOR_MINUTE_HAND       GColorWhite
#define COLOR_MINUTE_HALO       GColorWhite
#define COLOR_HEART_RATE        GColorWhite
#define COLOR_HALO              COLOR_MINUTE_HALO
#endif

// ===========================================================================
// Configurable Fonts
// ===========================================================================
#if defined(PBL_PLATFORM_EMERY) || defined(PBL_PLATFORM_GABBRO)
  #define FONT_KEY_DATA           FONT_KEY_LECO_20_BOLD_NUMBERS
#else
  #define FONT_KEY_DATA           FONT_KEY_GOTHIC_24_BOLD
#endif

// ===========================================================================
// Debug Time Configuration
// Set to NULL by default. When set (e.g. &(struct tm){ .tm_hour = 10, .tm_min = 10 }),
// this fixed time will be used for time rendering instead of system time.
// ===========================================================================
#ifdef IS_EMULATOR_BUILD
  // Emulator-only test data
  #define DEBUG_TIME              &(struct tm){ .tm_hour = 10, .tm_min = 10, .tm_year = 2026, .tm_mon = 6, or .tm_mday = 20 }
#else
  // Production code
  #define DEBUG_TIME              NULL
#endif