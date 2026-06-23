#include "layer.hpp"

Layer& Layer::Move(Vector2D<int> pos) {
  pos_ = pos;
  return *this;
}

Layer& Layer::MoveRelative(Vector2D<int> pos_diff) {
  pos_ += pos_diff;
  return *this;
}

void Layer::DrawTo(PixelWriter& writer) const {
  if (window_) {
    window_->DrawTo(writer, pos_);
  }
}

Layer& LayerManager::NewLayer() {
  ++latest_id_;
  return *layers_.emplace_back(new Layer{latest_id_});
}