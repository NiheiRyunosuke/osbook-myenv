BPB* boot_volume_image;

void initialize(void* volume_image) {
  boot_volume_image = reinterpret_cast<fat::BPB*>(volume_image);
}