#pragma once

#include <memory>
#include "ISubprogram.h"

class ConsoleArea;

class ConsoleProgram : public ISubprogram
{
public:
  ConsoleProgram();
  explicit ConsoleProgram(QWidget* parent);
  ~ConsoleProgram();

  QList<QWidget*> getSidePanelControls() override;
  QWidget* getMainWidget();

  void onActivated() override;
  void onDeactivated() override;

  void runSortTest();
  void runSortComparison();
  void flushConsole();

  ConsoleArea* consoleArea();

private:
  ConsoleArea* m_consoleWidget;
};