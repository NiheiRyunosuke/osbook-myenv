#pragma once

struct Message {
  enum Type {
    kInterruptXHCI,
    kTimerTimeout,
    kKeyPush,
    kLayer,
    kLayerFinish,
  } type;

  uint64_t src_task;

  struct {
    LayerOperation op;
    unsigned int layer_id;
    int x, y;
  } layer;

  enum class LayerOperation {
    Move, MoveRelative, Draw
  };

  union {
    struct {
      unsigned long timeout;
      int value;
    } timer;

    struct {
      uint8_t modifier;
      uint8_t keycode;
      char ascii;
    } keyboard;
  } arg;
};