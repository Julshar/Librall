#pragma once

#include <QString>

class ILoggerClient
{
public:
  virtual ~ILoggerClient() = default;
  virtual void print(const QString& message) = 0;
  virtual void flush() = 0;
};