#pragma once

#ifdef __cplusplus
extern "C" {
#endif

struct AppEvent {
  enum Type {
    kQuit,
    kMouseMove,
    kMouseButton,
  } type;

  union {
    struct {
      int x, y;
      int dx, dy;
      uint8_t buttons;
    } mouse_move;
  } arg;
};

#ifdef __cplusplus
} // extern "C"
#endif