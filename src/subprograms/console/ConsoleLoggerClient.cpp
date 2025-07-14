#include "ConsoleLoggerClient.h"
#include "ConsoleArea.h"
#include <QMetaObject>

ConsoleLoggerClient::ConsoleLoggerClient(ConsoleArea* console)
  : m_console(console) {}

void ConsoleLoggerClient::print(const QString& message)
{
  if (!m_console) return;

  QMetaObject::invokeMethod(m_console, [this, message]()
  {
    m_console->print(message);
  }, Qt::QueuedConnection);
}

void ConsoleLoggerClient::flush()
{
  if (!m_console) return;

  QMetaObject::invokeMethod(m_console, [this]()
  {
    m_console->flush();
  }, Qt::QueuedConnection);
}