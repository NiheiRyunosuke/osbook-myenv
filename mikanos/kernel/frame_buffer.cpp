Error FrameBuffer::Initialize(const FrameBufferConfig& config) {
  config_ = config;

  const auto bits_per_pixel = BitsPerPixel(config_.pixel_format);
  if (bits_per_pixel <= 0) {
    return MAKE_ERROR(Error::kUnknownPixelFormat);
  }

  if (config_.frame_buffer) {
    buffer_.resize(0);
  } else {
    buffer_.resize(
        ((bits_per_pixel + 7) / 8)
        * config_.horizontal_resolution * config_.vertical_resolution);
    config_.frame_buffer = buffer_.data();
    config_.pixels_per_scan_line = config_.horizontal_resolution;
  }

  switch (config_.pixel_format) {
    case kPixelRGBResv8BitPerColor:
      writer_ = std::make_unique<RGBResv8BitPerColorPixelWriter>(config_);
      break;
    case kPixelBGRResv8BitPerColor:
      writer_ = std::make_unique<BGRResv8BitPerColorPixelWriter>(config_);
      break;
    default:
      return MAKE_ERROR(Error::kUnknownPixelFormat);
  }

  return MAKE_ERROR(Error::kSuccess);
}