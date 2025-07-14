#pragma once

#include "../../util/ILoggerClient.h"

class ConsoleArea;

class ConsoleLoggerClient : public ILoggerClient {
public:
  explicit ConsoleLoggerClient(ConsoleArea* console);
  void print(const QString& message) override;
  void flush() override;

private:
  ConsoleArea* m_console;
};