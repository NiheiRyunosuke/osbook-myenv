#pragma once

#include <cstdint>

void InitializeLAPICTimer();
void StartLAPICTimer();
uint32_t LAPICTimerElapsed();
void StopLAPICTimer();

class TimerManager {
  public:
    void Tick();
    unsigned long CurrentTick() const { return tick_; }

  private:
    volatile unsigned long tick_{0};
};

extern TimerManager* timer_manager;

void LAPICTimerOnInterrupt();

class Timer {
  public:
    Timer(unsigned long timeout, int value);
    unsigned long Timeout() const { return timeout_; }
    int Value() const { return value_; }

  private:
    unsigned long timeout_;
    int value_;
};