#pragma once

#include <chrono>

class Timer
{
private:
  std::chrono::steady_clock::time_point startTime_;
  
public:
  Timer();
  ~Timer();

  void reset();
  long long elapsedTimeMili() const;
  long long elapsedTimeMicro() const;
  double elapsedTimeSeconds() const;
  void printElapsedTimeMicro() const;
  void printElapsedTimeSeconds() const;
};
