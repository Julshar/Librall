#include "Logger.h"
#include <iostream>

#undef DEBUG

void Logger::setClient(std::shared_ptr<ILoggerClient> client)
{
  s_client = client;
}

void Logger::log(const QString& msg)
{
  if (s_client)
  {
    s_client->print(msg);
  }

  #ifdef DEBUG
  std::cout << msg.toStdString() << std::endl;
  #endif
}

void Logger::logDebug(const QString& msg)
{
  QString formatted = "[DEBUG] " + msg;
  if (s_client)
  {
    s_client->print(formatted);
  }

  std::cout << formatted.toStdString() << std::endl;
}

void Logger::logError(const QString& msg)
{
  QString formatted = "ERROR! " + msg;
  if (s_client)
  {
    s_client->print(formatted);
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

void Logger::flush()
{
  if (s_client)
  {
    s_client->flush();
  }
}
