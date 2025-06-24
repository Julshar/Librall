#pragma once

#include <QString>
#include <string>
#include "ConsoleArea.h"

class Logger
{
public:
  static void attachConsole(ConsoleArea* console);

  static void log(const QString& msg);
  static void logDebug(const QString& msg);
  static void logError(const QString& msg);

  static void log(const std::string& msg);
  static void logDebug(const std::string& msg);
  static void logError(const std::string& msg);

  static void log(const char* msg);
  static void logDebug(const char* msg);
  static void logError(const char* msg);

private:
  static inline ConsoleArea* s_console = nullptr;
};