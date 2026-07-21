#include "acpi.hpp"

#include <cstring>
#include <cstdlib>
#include "logger.hpp"


void Initialize(const RSDP& rsdp) {
  if (!rsdp.IsVAlid()) {
    Log(kError, "RSDP is not valid\n");
    exit(1);
  }
}