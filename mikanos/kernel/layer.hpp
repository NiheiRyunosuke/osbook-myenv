#pragma once

#include <memory>
#include <map>
#include <vector>

#include "graphics.hpp"
#include "window.hpp"

class Layer {
  public:
    /** @brief 指定されたIDを持つレイヤーを生成 */
    Layer(unsigned int id = 0);
    /** @brief このインスタンスのIDを返す */
    unsigned int ID() const;

    /** @brief ウィンドウを設定する。既存のウィンドウはこのレイヤーから外れる */
    Layer& SetWindow(const std::shared_ptr<Window>& window);
    /** @brief 設定されたウィンドウを返す */
    std::shared_ptr<Window> GetWindow() const;

    /** @brief レイヤーの位置情報を指定された絶対座標へと更新する。再描画はしない */
    Layer& Move(Vector2D<int> pos);
    /** @brief レイヤーの位置情報を指定された絶対座標へと更新する。再描画はしない */
    Layer& MoveRelative(Vector2D<int> pos_diff);

    /** @brief writerに現在設定されているウィンドウの内容を描画する */
    void DrawTo(PixelWriter& writer) const;

  private:
    unsigned int id_;
    Vector2D<int> pos_;
    std::shared_ptr<Window> window_;
}