#include "task.hpp"

#include "asmfunc.h"
#include "timer.hpp"

alignas(16) TaskContext task_b_ctx, task_a_ctx;

namespace {
  TaskContext* current_task;
}

void SwitchTask() {
  TaskContext* old_current_task = current_task;
  if (current_task == &task_a_ctx) {
    current_task = &task_b_ctx;
  } else {
    current_task = &task_a_ctx;
  }
  SwitchContext(current_task, old_current_task);
}

void InitializeTask() {
  current_task = &task_a_ctx;

  __asm__("cli");
  timer_manager->AddTimer(
    Timer{timer_manager->CurrentTick() + kTaskTimerPeriod, kTaskTimerValue});
  __asm__("sti");
}

Task::Task(uint64_t id) : id_{id} {
}

Task& Task::InitContext(TaskFunc* f, int64_t data) {
  const size_t stack_size = kDefaultStackBytes / sizeof(stack_[0]);
  stack_.resize(stack_size);
  uint64_t stack_end = reinterpret_cast<uint64_t>(&stack_[stack_size]);

  memset(&context_, 0, sizeof(context_));
  context_.cr3 = GetCR3();
  context_.rflags = 0x202;
  context_.cs = kKernelCS;
  context_.ss = kKernelSS;
  context_.rsp = (stack_end & ~0xflu) - 8;
  context_.rip = reinterpret_cast<uint64_t>(f);
  context_.rdi = id_;
  context_.rsi = data;

  // MXCSR のすべての例外をマスクする
  *reinterpret_cast<uint32_t*>(&context_.fxsave_area[24]) = 0x1f80;

  return *this;
}