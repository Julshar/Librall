#pragma once

#include <QString>
#include <string>
#include <vector>
#include <sstream>

#include "ILoggerClient.h"

class ConsoleArea;

class Logger
{
public:
  static void setClient(std::shared_ptr<ILoggerClient> client);

  static void log(const QString& msg);
  static void logDebug(const QString& msg);
  static void logError(const QString& msg);
  
  static void log(const std::string& msg);
  static void logDebug(const std::string& msg);
  static void logError(const std::string& msg);
  
  static void log(const char* msg);
  static void logDebug(const char* msg);
  static void logError(const char* msg);
  
  template <typename T>
  static void log(const std::vector<T>& vec)
  {
    std::ostringstream oss;
    for (const auto& item : vec)
    {
      oss << item << ' ';
    }
    log(QString::fromStdString(oss.str()));
  }

  static void flush();

private:
  static inline std::shared_ptr<ILoggerClient> s_client = nullptr;
};