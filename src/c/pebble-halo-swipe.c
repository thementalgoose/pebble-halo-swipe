#include <pebble.h>
#include "constants.h"

static Window *s_window;
static Layer  *s_canvas_layer;

// ---------------------------------------------------------------------------
// Component 1: Center Circle
// ---------------------------------------------------------------------------
static void draw_center_circle(GContext *ctx, GPoint center) {
  graphics_context_set_fill_color(ctx, COLOR_CENTER_CIRCLE);
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

  graphics_context_set_stroke_color(ctx, COLOR_HOUR_HAND);
  graphics_context_set_stroke_width(ctx, HOUR_HAND_WIDTH);
  graphics_draw_line(ctx, center, hour_hand_tip);
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

  graphics_context_set_stroke_color(ctx, COLOR_MINUTE_HAND);
  graphics_context_set_stroke_width(ctx, MINUTE_HAND_WIDTH);
  graphics_draw_line(ctx, center, minute_hand_tip);
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

  graphics_context_set_fill_color(ctx, COLOR_BACKGROUND_HALO);
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

    graphics_context_set_fill_color(ctx, COLOR_HALO);
    graphics_fill_radial(ctx, halo_rect, GOvalScaleModeFitCircle, HALO_WIDTH, 0, minute_angle);
  }
}

// ---------------------------------------------------------------------------
// Canvas Update Procedure
// ---------------------------------------------------------------------------
static void canvas_update_proc(Layer *layer, GContext *ctx) {
  time_t now = time(NULL);
  struct tm *tick_time = localtime(&now);

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

  s_canvas_layer = layer_create(bounds);
  layer_set_update_proc(s_canvas_layer, canvas_update_proc);
  layer_add_child(window_layer, s_canvas_layer);
}

static void window_unload(Window *window) {
  layer_destroy(s_canvas_layer);
  s_canvas_layer = NULL;
}

// ---------------------------------------------------------------------------
// App Init / Deinit / Main
// ---------------------------------------------------------------------------
static void init(void) {
  s_window = window_create();
  window_set_background_color(s_window, COLOR_BACKGROUND);
  window_set_window_handlers(s_window, (WindowHandlers){
    .load = window_load,
    .unload = window_unload,
  });
  window_stack_push(s_window, true);

  tick_timer_service_subscribe(MINUTE_UNIT, tick_handler);
}

static void deinit(void) {
  tick_timer_service_unsubscribe();
  window_destroy(s_window);
}

int main(void) {
  init();
  app_event_loop();
  deinit();
}
