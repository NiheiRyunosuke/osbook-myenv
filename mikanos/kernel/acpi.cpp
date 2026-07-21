#include "acpi.hpp"

#include <cstring>
#include <cstdlib>
#include "logger.hpp"


bool RSDP::IsValid() const {
  if (strncmp(this->signature, "RSD PTR ", 8) != 0) {
    Log(kDebug, "invalid signature: %.8s\n", this->signature);
    return false;
  }
  if (this->revision != 2) {
    Log(kDebug, "ACPI revision must be 2: %d\n", this->revision);
    return false;
  }
  if (auto sum = SumBytes(this, 20); sum != 0) {
    Log(kDebug, "sum of 20 bytes must be 0: %d\n", sum);
    return false;
  }
  if (auto sum = SumBytes(this, 36); sum != 0) {
    Log(kDebug, "sum of 36 bytes must be 0: %d\n", sum);
    return false;
  }
  return true;
}

void Initialize(const RSDP& rsdp) {
  if (!rsdp.IsValid()) {
    Log(kError, "RSDP is not valid\n");
    exit(1);
  }
}