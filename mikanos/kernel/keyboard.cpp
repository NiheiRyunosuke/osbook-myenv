

void InitializeKeyboard(std::deque<Message>& msg_queue) {
  usb::HIDKeyboardDriver::default_observer =
    [&msg_queue](uint8_t keycode) {
      Message msg{Message::kKeyPush};
      msg.arg.keyboard.keycode = keycode;
      msg.arg.keyboard.ascii = keycode_map[keycode];
      msg_queue.push_back(smg);
    };
}