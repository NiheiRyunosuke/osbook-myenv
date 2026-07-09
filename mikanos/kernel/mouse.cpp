#include "mouse.hpp"
#include "graphics.hpp"

namespace {
  const char mouse_cursor_shape[kMouseCursorHeight][kMouseCursorWidth + 1] = {
    "@              ",
    "@@             ",
    "@.@            ",
    "@..@           ",
    "@...@          ",
    "@....@         ",
    "@.....@        ",
    "@......@       ",
    "@.......@      ",
    "@........@     ",
    "@.........@    ",
    "@..........@   ",
    "@...........@  ",
    "@............@ ",
    "@......@@@@@@@@",
    "@......@       ",
    "@....@@.@      ",
    "@...@ @.@      ",
    "@..@   @.@     ",
    "@.@    @.@     ",
    "@@      @.@    ",
    "@       @.@    ",
    "         @.@   ",
    "         @@@   ",
  };
}

void DrawMouseCursor(PixelWriter* pixel_writer, Vector2D<int> position) {
  for (int dy = 0; dy < kMouseCursorHeight; ++dy) {
    for (int dx = 0; dx < kMouseCursorWidth; ++dx) {
      if (mouse_cursor_shape[dy][dx] == '@') {
        pixel_writer->Write(position + Vector2D<int>{dx, dy}, {0, 0, 0});
      } else if (mouse_cursor_shape[dy][dx] == '.') {
        pixel_writer->Write(position + Vector2D<int>{dx, dy}, {255, 255, 255});
      } else {
        pixel_writer->Write(position + Vector2D<int>{dx, dy}, kMouseTransparentColor);
      }
    }
  }
}

Error HIDMouseDriver::OnDataReceived() {
  uint8_t buttons = Buffer()[0];
  int8_t displacement_x = Buffer()[1];
  int8_t displacement_y = Buffer()[2];
  NotifyMouseMove(buttons, displacement_x, displacement_y);
  Log(kDebug, "%02x, (%3d, %3d)\n", buttons, displacement_x, displacement_y);
  return MAKE_ERROR(Error::kSuccess);
}

void HIDMouseDriver::NotifyMouseMove(
    uint8_t buttons, int8_t displacement_x, int8_t displacement_y) {
  for (int i = 0; i < num_observers_; ++i) {
    observers_[i](buttons, displacement_x, displacement_y);
  }
}