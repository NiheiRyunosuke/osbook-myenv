#pragma once

#include <vector>
#include <optional>
#include <string>
#include "graphics.hpp"
#include "frame_buffer.hpp"

class Window {
  public:
    /** @brief WindowWriter は Window と関連付けられた PixelWriter を提供する */
    class WindowWriter : public PixelWriter {
      public:
        WindowWriter(Window& window) : window_{window} {}
        /** @brief 指定された位置に指定された色を描く */
        virtual void Write(Vector2D<int> pos, const PixelColor& c) override {
          window_.Write(pos, c);
        }
        /** @brief Width は関連付けられた Window の横幅をピクセル単位で返す。 */
        virtual int Width() const override { return window_.Width(); }
        /** @brief Height は関連付けられた Window の高さをピクセル単位で返す。 */
        virtual int Height() const override { return window_.Height(); }

      private:
        Window& window_;
    };

    /** @brief 指定されたピクセル数の平面描画領域を作成する.  */
    Window(int width, int height, PixelFormat shadow_format);
    virtual ~Window() = default;
    Window(const Window& rhs) = delete;
    Window& operator=(const Window& rhs) = delete;

    /** @brief 与えられた FrameBuffer にこのウィンドウの表示領域を描画する。
     * 
     * @param dst 描画先
     * @param position writer の左上を基準とした描画位置
     */
    void DrawTo(FrameBuffer& dst, Vector2D<int> pos, const Rectangle<int>& area);
    /** @brief 透過色を設定する.  */
    void SetTransparentColor(std::optional<PixelColor> c);
    /** @brief このインスタンスに紐づいた WindowWriter を取得する */
    WindowWriter* Writer();

    /** @brief 指定した位置のピクセルを返す。 */
    const PixelColor& At(Vector2D<int> pos) const;
    /** @brief 指定した位置にピクセルを書き込む。 */
    void Write(Vector2D<int> pos, PixelColor c);

    /** @brief 平面描画領域の横幅をピクセル単位で返す。 */
    int Width() const;
    /** @brief 平面描画領域の高さをピクセル単位で返す。 */
    int Height() const;
    /** @brief 平面描画領域のサイズをピクセル単位で返す。 */
    Vector2D<int> Size() const;

    void Move(Vector2D<int> dst_pos, const Rectangle<int>& src);

    virtual void Activate() {}
    virtual void Deactivate() {}

  private:
    int width_, height_;
    std::vector<std::vector<PixelColor>> data_{};
    WindowWriter writer_{*this};
    std::optional<PixelColor> transparent_color_{std::nullopt};

    FrameBuffer shadow_buffer_{};
};

class ToplevelWindow : public Window {
  public: 
    static constexpr Vector2D<int> kTopLeftMargin{4, 24};
    static constexpr Vector2D<int> kBottomRightMargin{4, 4};

    class InnerAreaWriter : public PixelWriter {
      public:
        InnerAreaWriter(ToplevelWindow& window) : window_{window} {}
        virtual void Write(Vector2D<int> pos, const PixelColor& c) override {
          window_.Write(pos + kTopLeftMargin, c);
        }
        virtual int Width() const override {
          return window_.Width() - kTopLeftMargin.x - kBottomRightMargin.x; }
        virtual int Height() const override {
          return window_.Height() - kTopLeftMargin.y - kBottomRightMargin.y; }
      
      private:
        ToplevelWindow& window_;
    };

    ToplevelWindow(int width, int height, PixelFormat shadow_format,
                  const std::string& title);

    virtual void Activate() override;
    virtual void Deactivate() override;

    InnerAreaWriter* InnerWriter() { return &inner_writer_; }
    Vector2D<int> InnerSize() const;

  private:
    std::string title;
    InnerAreaWriter inner_writer_{*this};
};

void DrawWindow(PixelWriter& writer, const char* title);
void DrawTextbox(PixelWriter& writer, Vector2D<int> pos, Vector2D<int> size);