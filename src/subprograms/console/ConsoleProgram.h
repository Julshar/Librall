#pragma once

#include <memory>
#include "SubprogramBase.h"

class ConsoleArea;

class ConsoleProgram : public SubprogramBase
{
  Q_OBJECT

public:
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