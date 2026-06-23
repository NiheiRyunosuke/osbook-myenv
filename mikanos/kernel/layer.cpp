#include "layer.hpp"
#include <algorithm>

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

Layer* LayerManager::FindLayer(unsigned int id) {
  auto pred = [id](const std::unique_ptr<Layer>& elem) {
    return elem->ID() == id;
  };
  auto it = std::find_if(layers_.begin(), layers_.end(), pred);
  if (it == layers_.end()) {
    return nullptr;
  }
  return it->get();
}

void LayerManager::Move(unsigned int id, Vector2D<int> new_position) {
  FindLayer(id)->Move(new_position);
}

void LayerManager::MoveRelative(unsigned int id, Vector2D<int> pos_diff) {
  FindLayer(id)->MoveRelative(pos_diff);
}