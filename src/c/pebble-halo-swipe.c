#include <pebble.h>
#include "constants.h"

typedef enum {
  DATA_MODE_NONE = 0,
  DATA_MODE_HEART_RATE = 1,
  DATA_MODE_DATE = 2
} DataMode;

typedef enum {
  DATE_FORMAT_DD_MMM = 0,
  DATE_FORMAT_MMM_DD = 1
} DateFormatMode;

static Window *s_window;
static Layer  *s_canvas_layer;
static GPath  *s_heart_path = NULL;

static const GPathInfo HEART_PATH_INFO = {
  .num_points = 8,
  .points = (GPoint []) {
    {0, -4},
    {-6, -10},
    {-11, -4},
    {-11, 2},
    {0, 11},
    {11, 2},
    {11, -4},
    {6, -10}
  }
};

// ---------------------------------------------------------------------------
// Settings (persisted via AppMessage from Clay)
// ---------------------------------------------------------------------------

#define PERSIST_KEY_HOUR_HAND       1
#define PERSIST_KEY_MINUTE_HAND     2
#define PERSIST_KEY_MINUTE_HALO     3
#define PERSIST_KEY_HALO_BACKGROUND 4
#define PERSIST_KEY_HEART_RATE      5
#define PERSIST_KEY_DATA            6
#define PERSIST_KEY_DATE_FORMAT     7
#define PERSIST_KEY_BACKGROUND      8
#define PERSIST_KEY_CENTER_CIRCLE   9
#define PERSIST_KEY_HAND_TAIL_LENGTH 10
#define PERSIST_KEY_CACHED_HEART_RATE 11

static GColor s_color_hour_hand;
static GColor s_color_minute_hand;
static GColor s_color_minute_halo;
static GColor s_color_halo_background;
static GColor s_color_heart_rate;
static GColor s_color_background;
static GColor s_color_center_circle;

static DataMode s_data_mode = DATA_MODE_DATE;
static DateFormatMode s_date_format_mode = DATE_FORMAT_DD_MMM;
static int s_hand_tail_length = 8;

static int s_heart_rate = 0;

static void load_settings(void) {
  s_color_hour_hand       = persist_exists(PERSIST_KEY_HOUR_HAND)
    ? GColorFromHEX(persist_read_int(PERSIST_KEY_HOUR_HAND))
    : COLOR_HOUR_HAND;
  s_color_minute_hand     = persist_exists(PERSIST_KEY_MINUTE_HAND)
    ? GColorFromHEX(persist_read_int(PERSIST_KEY_MINUTE_HAND))
    : COLOR_MINUTE_HAND;
  s_color_minute_halo     = persist_exists(PERSIST_KEY_MINUTE_HALO)
    ? GColorFromHEX(persist_read_int(PERSIST_KEY_MINUTE_HALO))
    : COLOR_MINUTE_HALO;
  s_color_halo_background = persist_exists(PERSIST_KEY_HALO_BACKGROUND)
    ? GColorFromHEX(persist_read_int(PERSIST_KEY_HALO_BACKGROUND))
    : COLOR_BACKGROUND_HALO;
  s_color_heart_rate      = persist_exists(PERSIST_KEY_HEART_RATE)
    ? GColorFromHEX(persist_read_int(PERSIST_KEY_HEART_RATE))
    : COLOR_HEART_RATE;
  s_color_background      = persist_exists(PERSIST_KEY_BACKGROUND)
    ? GColorFromHEX(persist_read_int(PERSIST_KEY_BACKGROUND))
    : COLOR_BACKGROUND;
  s_color_center_circle   = persist_exists(PERSIST_KEY_CENTER_CIRCLE)
    ? GColorFromHEX(persist_read_int(PERSIST_KEY_CENTER_CIRCLE))
    : COLOR_CENTER_CIRCLE;
  s_data_mode             = persist_exists(PERSIST_KEY_DATA)
    ? (DataMode)persist_read_int(PERSIST_KEY_DATA)
    : DATA_MODE_DATE;
  s_date_format_mode      = persist_exists(PERSIST_KEY_DATE_FORMAT)
    ? (DateFormatMode)persist_read_int(PERSIST_KEY_DATE_FORMAT)
    : DATE_FORMAT_DD_MMM;
  s_hand_tail_length      = persist_exists(PERSIST_KEY_HAND_TAIL_LENGTH)
    ? persist_read_int(PERSIST_KEY_HAND_TAIL_LENGTH)
    : 8;
  if (persist_exists(PERSIST_KEY_CACHED_HEART_RATE)) {
    s_heart_rate          = persist_read_int(PERSIST_KEY_CACHED_HEART_RATE);
  }
}

static void inbox_received_handler(DictionaryIterator *iter, void *context) {
  Tuple *t;

  t = dict_find(iter, MESSAGE_KEY_ColorHourHand);
  if (t) {
    persist_write_int(PERSIST_KEY_HOUR_HAND, t->value->int32);
  }

  t = dict_find(iter, MESSAGE_KEY_ColorMinuteHand);
  if (t) {
    persist_write_int(PERSIST_KEY_MINUTE_HAND, t->value->int32);
  }

  t = dict_find(iter, MESSAGE_KEY_ColorMinuteHalo);
  if (t) {
    persist_write_int(PERSIST_KEY_MINUTE_HALO, t->value->int32);
  }

  t = dict_find(iter, MESSAGE_KEY_ColorHaloBackground);
  if (t) {
    persist_write_int(PERSIST_KEY_HALO_BACKGROUND, t->value->int32);
  }

  t = dict_find(iter, MESSAGE_KEY_ColorHeartRate);
  if (t) {
    persist_write_int(PERSIST_KEY_HEART_RATE, t->value->int32);
  }

  t = dict_find(iter, MESSAGE_KEY_ColorBackground);
  if (t) {
    persist_write_int(PERSIST_KEY_BACKGROUND, t->value->int32);
  }

  t = dict_find(iter, MESSAGE_KEY_ColorCenterCircle);
  if (t) {
    persist_write_int(PERSIST_KEY_CENTER_CIRCLE, t->value->int32);
  }

  t = dict_find(iter, MESSAGE_KEY_HandTailLength);
  if (t) {
    persist_write_int(PERSIST_KEY_HAND_TAIL_LENGTH, t->value->int32);
  }

  t = dict_find(iter, MESSAGE_KEY_Data);
  if (t) {
    if (t->type == TUPLE_CSTRING) {
      if (strcmp(t->value->cstring, "none") == 0) {
        persist_write_int(PERSIST_KEY_DATA, DATA_MODE_NONE);
      } else if (strcmp(t->value->cstring, "date") == 0) {
        persist_write_int(PERSIST_KEY_DATA, DATA_MODE_DATE);
      } else {
        persist_write_int(PERSIST_KEY_DATA, DATA_MODE_HEART_RATE);
      }
    } else if (t->type == TUPLE_INT || t->type == TUPLE_UINT) {
      persist_write_int(PERSIST_KEY_DATA, t->value->int32);
    }
  }

  t = dict_find(iter, MESSAGE_KEY_DateFormat);
  if (t) {
    if (t->type == TUPLE_CSTRING) {
      if (strcmp(t->value->cstring, "MMM dd") == 0) {
        persist_write_int(PERSIST_KEY_DATE_FORMAT, DATE_FORMAT_MMM_DD);
      } else {
        persist_write_int(PERSIST_KEY_DATE_FORMAT, DATE_FORMAT_DD_MMM);
      }
    } else if (t->type == TUPLE_INT || t->type == TUPLE_UINT) {
      persist_write_int(PERSIST_KEY_DATE_FORMAT, t->value->int32);
    }
  }

  load_settings();

  if (s_window) {
    window_set_background_color(s_window, s_color_background);
  }

  if (s_canvas_layer) {
    layer_mark_dirty(s_canvas_layer);
  }
}

// ---------------------------------------------------------------------------
// Pebble Health Handler
// ---------------------------------------------------------------------------
static void health_handler(HealthEventType event, void *context) {
  if (event == HealthEventHeartRateUpdate || event == HealthEventSignificantUpdate) {
    HealthValue val = health_service_peek_current_value(HealthMetricHeartRateBPM);
    if (val > 0) {
      s_heart_rate = (int)val;
      persist_write_int(PERSIST_KEY_CACHED_HEART_RATE, s_heart_rate);
      if (s_canvas_layer) {
        layer_mark_dirty(s_canvas_layer);
      }
    }
  }
}

// ---------------------------------------------------------------------------
// Component 1: Center Circle
// ---------------------------------------------------------------------------
static void draw_center_circle(GContext *ctx, GPoint center) {
  graphics_context_set_fill_color(ctx, s_color_center_circle);
  graphics_fill_circle(ctx, center, CENTER_CIRCLE_RADIUS);
}

// ---------------------------------------------------------------------------
// Component 2: Hour Hand (small and wide)
// ---------------------------------------------------------------------------
static void draw_hour_hand(GContext *ctx, GPoint center, struct tm *tick_time) {
  // Calculate hour angle including minute progression
  int32_t hour_angle = (TRIG_MAX_ANGLE * (((tick_time->tm_hour % 12) * 60) + tick_time->tm_min)) / (12 * 60);

  GPoint hour_hand_tip = {
    .x = center.x + (int16_t)(sin_lookup(hour_angle) * (int32_t)HOUR_HAND_LENGTH / TRIG_MAX_RATIO),
    .y = center.y - (int16_t)(cos_lookup(hour_angle) * (int32_t)HOUR_HAND_LENGTH / TRIG_MAX_RATIO),
  };

  GPoint hour_hand_tail = {
    .x = center.x - (int16_t)(sin_lookup(hour_angle) * (int32_t)s_hand_tail_length / TRIG_MAX_RATIO),
    .y = center.y + (int16_t)(cos_lookup(hour_angle) * (int32_t)s_hand_tail_length / TRIG_MAX_RATIO),
  };

  graphics_context_set_stroke_color(ctx, s_color_hour_hand);
  graphics_context_set_stroke_width(ctx, HOUR_HAND_WIDTH);
  graphics_draw_line(ctx, hour_hand_tail, hour_hand_tip);
}

// ---------------------------------------------------------------------------
// Component 3: Minute Hand (long and narrow)
// ---------------------------------------------------------------------------
static void draw_minute_hand(GContext *ctx, GPoint center, struct tm *tick_time) {
  int32_t minute_angle = TRIG_MAX_ANGLE * tick_time->tm_min / 60;

  GPoint minute_hand_tip = {
    .x = center.x + (int16_t)(sin_lookup(minute_angle) * (int32_t)MINUTE_HAND_LENGTH / TRIG_MAX_RATIO),
    .y = center.y - (int16_t)(cos_lookup(minute_angle) * (int32_t)MINUTE_HAND_LENGTH / TRIG_MAX_RATIO),
  };

  GPoint minute_hand_tail = {
    .x = center.x - (int16_t)(sin_lookup(minute_angle) * (int32_t)s_hand_tail_length / TRIG_MAX_RATIO),
    .y = center.y + (int16_t)(cos_lookup(minute_angle) * (int32_t)s_hand_tail_length / TRIG_MAX_RATIO),
  };

  graphics_context_set_stroke_color(ctx, s_color_minute_hand);
  graphics_context_set_stroke_width(ctx, MINUTE_HAND_WIDTH);
  graphics_draw_line(ctx, minute_hand_tail, minute_hand_tip);
}

// ---------------------------------------------------------------------------
// Background Halo (full 360 around watchface beneath all other layers)
// ---------------------------------------------------------------------------
static void draw_background_halo(GContext *ctx, GPoint center) {
  GRect halo_rect = GRect(
    center.x - HALO_RADIUS,
    center.y - HALO_RADIUS,
    HALO_RADIUS * 2,
    HALO_RADIUS * 2
  );

  graphics_context_set_fill_color(ctx, s_color_halo_background);
  graphics_fill_radial(ctx, halo_rect, GOvalScaleModeFitCircle, HALO_WIDTH, 0, TRIG_MAX_ANGLE);
}

// ---------------------------------------------------------------------------
// Minute Halo (around watchface, clipped to the end of the minute hand)
// ---------------------------------------------------------------------------

static void draw_halo(GContext *ctx, GPoint center, struct tm *tick_time) {
  int32_t minute_angle = TRIG_MAX_ANGLE * tick_time->tm_min / 60;

  if (minute_angle > 0) {
    GRect halo_rect = GRect(
      center.x - HALO_RADIUS,
      center.y - HALO_RADIUS,
      HALO_RADIUS * 2,
      HALO_RADIUS * 2
    );

    graphics_context_set_fill_color(ctx, s_color_minute_halo);
    graphics_fill_radial(ctx, halo_rect, GOvalScaleModeFitCircle, HALO_WIDTH, 0, minute_angle);
  }
}

// ---------------------------------------------------------------------------
// Heart Rate Display (printed underneath middle of clock and within halo)
// ---------------------------------------------------------------------------
static void draw_heart_rate(GContext *ctx, GPoint center) {
  if (!s_heart_path) {
    return;
  }

  char hr_text[16];
  if (s_heart_rate > 0) {
    snprintf(hr_text, sizeof(hr_text), "%d", s_heart_rate);
  } else {
    snprintf(hr_text, sizeof(hr_text), "--");
  }

  GFont font = fonts_get_system_font(FONT_KEY_DATA);
  GSize text_size = graphics_text_layout_get_content_size(
    hr_text, font, GRect(0, 0, 100, 30), GTextOverflowModeFill, GTextAlignmentLeft
  );

  int heart_width = 20;
  int gap = 8;
  int total_width = heart_width + gap + text_size.w;

  int start_x = center.x - (total_width / 2);
  int heart_y = center.y + (HALO_RADIUS * 4 / 9);

  // Position heart path
  gpath_move_to(s_heart_path, GPoint(start_x + (heart_width / 2), heart_y));

  // Draw heart icon
  graphics_context_set_fill_color(ctx, s_color_heart_rate);
  gpath_draw_filled(ctx, s_heart_path);

  // Draw text
  graphics_context_set_text_color(ctx, s_color_heart_rate);
  GRect text_rect = GRect(
    start_x + heart_width + gap,
    heart_y - (text_size.h / 2) - 1,
    text_size.w + 4,
    text_size.h
  );
  graphics_draw_text(ctx, hr_text, font, text_rect, GTextOverflowModeFill, GTextAlignmentLeft, NULL);
}

// ---------------------------------------------------------------------------
// Date Display (printed underneath middle of clock and within halo)
// ---------------------------------------------------------------------------
static void draw_date(GContext *ctx, GPoint center, struct tm *tick_time) {
  char date_text[16];
  if (s_date_format_mode == DATE_FORMAT_MMM_DD) {
    strftime(date_text, sizeof(date_text), "%b %d", tick_time);
  } else {
    strftime(date_text, sizeof(date_text), "%d %b", tick_time);
  }

  GFont font = fonts_get_system_font(FONT_KEY_DATA);
  GSize text_size = graphics_text_layout_get_content_size(
    date_text, font, GRect(0, 0, 100, 30), GTextOverflowModeFill, GTextAlignmentCenter
  );

  int date_y = center.y + (HALO_RADIUS * 4 / 9);

  GRect text_rect = GRect(
    center.x - (text_size.w / 2) - 2,
    date_y - (text_size.h / 2) - 1,
    text_size.w + 4,
    text_size.h
  );

  graphics_context_set_text_color(ctx, s_color_heart_rate);
  graphics_draw_text(ctx, date_text, font, text_rect, GTextOverflowModeFill, GTextAlignmentCenter, NULL);
}

// ---------------------------------------------------------------------------
// Bottom Data Router
// ---------------------------------------------------------------------------
static void draw_bottom_data(GContext *ctx, GPoint center, struct tm *tick_time) {
  if (s_data_mode == DATA_MODE_HEART_RATE) {
    draw_heart_rate(ctx, center);
  } else if (s_data_mode == DATA_MODE_DATE) {
    draw_date(ctx, center, tick_time);
  }
}

// ---------------------------------------------------------------------------
// Canvas Update Procedure
// ---------------------------------------------------------------------------
static void canvas_update_proc(Layer *layer, GContext *ctx) {
  time_t now = time(NULL);
  struct tm *tick_time = DEBUG_TIME;
  if (!tick_time) {
    tick_time = localtime(&now);
  }

  GRect bounds = layer_get_bounds(layer);
  GPoint center = grect_center_point(&bounds);

  // Background
  graphics_context_set_fill_color(ctx, COLOR_BACKGROUND);
  graphics_fill_rect(ctx, bounds, 0, GCornerNone);

  graphics_context_set_antialiased(ctx, true);

  // Draw Background Halo (full 360) beneath all other layers
  draw_background_halo(ctx, center);

  // Draw Minute Halo around watchface, clipped to the end of the minute hand
  draw_halo(ctx, center, tick_time);

  // Draw Bottom Data (none, heart_rate, or date)
  draw_bottom_data(ctx, center, tick_time);

  // Draw Component 2: Hour Hand (small and wide)
  draw_hour_hand(ctx, center, tick_time);
  
  // Draw Component 3: Minute Hand (long and narrow)
  draw_minute_hand(ctx, center, tick_time);

  // Draw Component 1: Center Circle (drawn over hands for clean pivot point)
  draw_center_circle(ctx, center);
}

// ---------------------------------------------------------------------------
// Tick Handler
// ---------------------------------------------------------------------------
static void tick_handler(struct tm *tick_time, TimeUnits units_changed) {
  if (s_canvas_layer) {
    layer_mark_dirty(s_canvas_layer);
  }
}

// ---------------------------------------------------------------------------
// Window Lifecycle
// ---------------------------------------------------------------------------
static void window_load(Window *window) {
  Layer *window_layer = window_get_root_layer(window);
  GRect bounds = layer_get_bounds(window_layer);

  s_heart_path = gpath_create(&HEART_PATH_INFO);

  s_canvas_layer = layer_create(bounds);
  layer_set_update_proc(s_canvas_layer, canvas_update_proc);
  layer_add_child(window_layer, s_canvas_layer);
}

static void window_unload(Window *window) {
  if (s_heart_path) {
    gpath_destroy(s_heart_path);
    s_heart_path = NULL;
  }
  layer_destroy(s_canvas_layer);
  s_canvas_layer = NULL;
}

// ---------------------------------------------------------------------------
// App Init / Deinit / Main
// ---------------------------------------------------------------------------
static void init(void) {
  load_settings();

  app_message_register_inbox_received(inbox_received_handler);
  app_message_open(app_message_inbox_size_maximum(), app_message_outbox_size_maximum());

  s_window = window_create();
  window_set_background_color(s_window, COLOR_BACKGROUND);
  window_set_window_handlers(s_window, (WindowHandlers){
    .load = window_load,
    .unload = window_unload,
  });
  window_stack_push(s_window, true);

  health_service_events_subscribe(health_handler, NULL);
  HealthValue live_hr = health_service_peek_current_value(HealthMetricHeartRateBPM);
  if (live_hr > 0) {
    s_heart_rate = (int)live_hr;
    persist_write_int(PERSIST_KEY_CACHED_HEART_RATE, s_heart_rate);
  }

  tick_timer_service_subscribe(MINUTE_UNIT, tick_handler);
}

static void deinit(void) {
  health_service_events_unsubscribe();
  tick_timer_service_unsubscribe();
  window_destroy(s_window);
}

int main(void) {
  init();
  app_event_loop();
  deinit();
}
