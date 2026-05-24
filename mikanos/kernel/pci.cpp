/**
 * @file pci.cpp
 *
 * PCIバス制御のプログラムを集めたファイル.
 */

#include "pci.hpp"

namespace {
  using namespace pci;

/** @brief CONFIG_ADDRESS 用の 32 ビット整数を生成する */
uint32_t MakeAddress(uint8_t bus, uint8_t device,
                    uint8_t function, uint8_t reg_addr){
  auto shl = [](uint32_t x, unsigned int bits) {
    return x << bits;
  };

  return shl(1, 31)  // enable bit
      | shl(bus, 16)
      | shl(device, 11)
      | shl(function, 8)
      | (reg_addr & 0xfcu);
    }

void WriteAddress(uint32_t address) {
  IoOut32(kConfigAddress, address);
}

void WriteData(uint32_t value) {
  IoOut32(kConfigData, value);
}

uint32_t ReadData() {
  return IoIn32(kConfigData);
}

uint16_t ReadVendorId(uint8_t bus, uint8_t device, uint8_t function) {
  WriteAddress(MakeAddress(bus, device, function, 0x00));
  return ReadData() & 0xffffu;
}

Error ScanAllBus() {
  num_device = 0;

  auto header_type = ReadHeaderType(0, 0, 0);
  if (IsSingleFunctionDevice(header_type)) {
    return ScanBus(0);
  }

  for (uint8_t function = 1; function < 8; ++function) {
    if (ReadVendorId(0, 0, function) == 0xffffu) {
      continue;
    }
    if (auto err = ScanBus(function)) {
      return err;
    }
  }
  return Error::kSuccess;
}



}