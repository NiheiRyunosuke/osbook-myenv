#pragma once

#include <array>
#include <stdint.h>
#include "error.hpp"

class Error {
 public:
  enum Code {
    kSuccess,
    kFull,
  };

  Error(Code code) : code_{code} {
  }

  operator bool() const {
    return code_ != kSuccess;
  }

  const char* Name() const {
    switch (code_) {
      case kSuccess:
        return "Success";
      case kFull:
        return "Full";
    }
    return "Unknown";
  }

 private:
  Code code_;
};

namespace pci {

/** @brief CONFIG_ADDRESS register I/O port address */
const uint16_t kConfigAddress = 0x0cf8;
/** @brief CONFIG_DATA register I/O port address */
const uint16_t kConfigData = 0x0cfc;

struct Device {
  uint8_t bus, device, function, header_type;
};

/** @brief List of PCI devices found by ScanAllBus(). */
inline std::array<Device, 32> devices;
/** @brief Number of valid elements in devices. */
inline int num_device;

void WriteAddress(uint32_t address);
void WriteData(uint32_t value);
uint32_t ReadData();

uint16_t ReadVendorId(uint8_t bus, uint8_t device, uint8_t function);
uint16_t ReadDeviceId(uint8_t bus, uint8_t device, uint8_t function);
uint8_t ReadHeaderType(uint8_t bus, uint8_t device, uint8_t function);
uint32_t ReadClassCode(uint8_t bus, uint8_t device, uint8_t function);
uint32_t ReadBusNumbers(uint8_t bus, uint8_t device, uint8_t function);
bool IsSingleFunctionDevice(uint8_t header_type);

/** @brief Scan all PCI devices and store them in devices. */
Error ScanAllBus();

}
