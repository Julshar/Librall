#include "ConsoleProgram.h"
#include "ConsoleArea.h"
#include "Logger.h"
#include "ConsoleLoggerClient.h"
#include "SortAlgsComp.h"

#include <QPushButton>
#include <QtConcurrent/QtConcurrent>
#include <QFutureWatcher>
#include <QWidget>
#include <QFuture>
#include <QObject>

ConsoleProgram::ConsoleProgram()
  : SubprogramBase(nullptr)
{
  m_consoleWidget = new ConsoleArea();
  Logger::setClient(std::make_shared<ConsoleLoggerClient>(m_consoleWidget));
}

ConsoleProgram::ConsoleProgram(QWidget* parent)
  : SubprogramBase(parent)
{
  m_consoleWidget = new ConsoleArea(parent);
  Logger::setClient(std::make_shared<ConsoleLoggerClient>(m_consoleWidget));
}

ConsoleProgram::~ConsoleProgram()
{
  Logger::setClient(nullptr);
  delete m_consoleWidget;
}

QWidget* ConsoleProgram::getMainWidget()
{
  return m_consoleWidget;
}

QList<QWidget *> ConsoleProgram::getSidePanelControls()
{
  QList<QWidget *> widgets;

  QPushButton *btnSortTest = new QPushButton("Test Sort");
  QPushButton *btnSortComp = new QPushButton("Compare Sort");
  QPushButton *btnFlushConsole = new QPushButton("Flush Console");

  QObject::connect(btnFlushConsole, &QPushButton::clicked, m_consoleWidget, &ConsoleArea::flushConsole);
  QObject::connect(btnSortTest, &QPushButton::clicked, [this]() { runSortTest(); });
  QObject::connect(btnSortComp, &QPushButton::clicked, [this]() { runSortComparison(); });

  widgets << btnSortTest << btnSortComp << btnFlushConsole;
  return widgets;
}

void ConsoleProgram::onActivated()
{
  Logger::log("[ConsoleProgram] Activated.");
}

void ConsoleProgram::onDeactivated()
{
  Logger::log("[ConsoleProgram] Deactivated.");
}

void ConsoleProgram::runSortTest()
{
  QFutureWatcher<void>* watcher = new QFutureWatcher<void>();
  QObject::connect(watcher, &QFutureWatcher<void>::finished, [watcher]()
  {
    Logger::log("[ConsoleProgram] Sorting test completed.\n");
    delete watcher;  // Manual cleanup required!
  });

  QFuture<void> future = QtConcurrent::run([]()
  {
    SortAlgsComp comp;
    comp.runFunctionalTest();
  });

  watcher->setFuture(future);
}

void ConsoleProgram::runSortComparison()
{
  QFutureWatcher<void>* watcher = new QFutureWatcher<void>();
  QObject::connect(watcher, &QFutureWatcher<void>::finished, [watcher]()
  {
    Logger::log("[ConsoleProgram] Sorting speed test completed.\n");
    delete watcher;  // Manual cleanup required!
  });

  QFuture<void> future = QtConcurrent::run([]()
  {
    SortAlgsComp comp;
    comp.runSpeedTest();
  });

  watcher->setFuture(future);
}

void ConsoleProgram::flushConsole()
{
  if (m_consoleWidget)
  {
    m_consoleWidget->flush();
  }
}

ConsoleArea* ConsoleProgram::consoleArea()
{
  return m_consoleWidget;
}
