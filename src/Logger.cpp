#include "Logger.h"
#include <iostream>

void Logger::attachConsole(ConsoleArea* console)
{
  s_console = console;
}

void Logger::log(const QString& msg)
{
  if (s_console)
  {
    s_console->print(msg);
  }
  std::cout << msg.toStdString() << std::endl;
}

void Logger::logDebug(const QString& msg)
{
  QString formatted = "[DEBUG] " + msg;
  if (s_console)
  {
    s_console->print(formatted);
  }
  std::cout << formatted.toStdString() << std::endl;
}

void Logger::logError(const QString& msg)
{
  QString formatted = "ERROR! " + msg;
  if (s_console)
  {
    s_console->print(formatted);
  }
  std::cerr << formatted.toStdString() << std::endl;
}

void Logger::log(const std::string& msg)
{
  log(QString::fromStdString(msg));
}

void Logger::logDebug(const std::string& msg)
{
  logDebug(QString::fromStdString(msg));
}

void Logger::logError(const std::string& msg)
{
  logError(QString::fromStdString(msg));
}

void Logger::log(const char* msg)
{
  log(QString::fromUtf8(msg));
}

void Logger::logDebug(const char* msg)
{
  logDebug(QString::fromUtf8(msg));
}

void Logger::logError(const char* msg)
{
  logError(QString::fromUtf8(msg));
}