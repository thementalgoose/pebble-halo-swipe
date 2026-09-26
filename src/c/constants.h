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
#define HOUR_HAND_WIDTH         8
#define MINUTE_HAND_LENGTH      85
#define MINUTE_HAND_WIDTH       2
#define HALO_RADIUS             MINUTE_HAND_LENGTH
#define HALO_WIDTH              12

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
#define COLOR_BACKGROUND        GColorBlack
#define COLOR_BACKGROUND_HALO   GColorDarkGray
#define COLOR_CENTER_CIRCLE     GColorWhite
#define COLOR_HOUR_HAND         GColorWhite
#define COLOR_MINUTE_HAND       GColorWhite
#define COLOR_MINUTE_HALO       GColorWhite
#define COLOR_HALO              COLOR_MINUTE_HALO