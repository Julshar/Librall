#include "Timer.h"
#include <iostream>


Timer::Timer(/* args */)
{
  reset();
}

Timer::~Timer()
{
}

void Timer::reset()
{
  startTime_ = std::chrono::steady_clock::now();
}

long long Timer::elapsedTimeMili() const
{
  std::chrono::steady_clock::time_point currentTime = std::chrono::steady_clock::now();
  return std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - startTime_).count();
}

long long Timer::elapsedTimeMicro() const
{
  std::chrono::steady_clock::time_point currentTime = std::chrono::steady_clock::now();
  return std::chrono::duration_cast<std::chrono::microseconds>(currentTime - startTime_).count();
}

double Timer::elapsedTimeSeconds() const
{
  long long micro = elapsedTimeMicro();
  double seconds = static_cast<double>(micro) / 1'000'000.0;
  return seconds;
}

void Timer::printElapsedTimeMicro() const
{
  long long micro = elapsedTimeMicro();
  std::cout << "Execution time: " << micro << " microseconds.\n";
}

void Timer::printElapsedTimeSeconds() const
{
  double sec = elapsedTimeSeconds();
  std::cout << "Execution time: " << sec << " seconds.\n";
}