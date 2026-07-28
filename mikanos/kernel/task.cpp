#include "task.hpp"

#include "asmfunc.h"
#include "timer.hpp"

void InitializeTask() {
  current_task = &task_a_ctx;

  __asm__("cli");
  timer_manager->AddTimer(
    Timer{timer_manager->CurrentTick() + kTaskTimerPeriod, kTaskTimerValue});
  __asm__("sti");
}