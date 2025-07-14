#include "ConsoleProgram.h"
#include "ConsoleArea.h"
#include "Logger.h"
#include "ConsoleLoggerClient.h"
#include "SortAlgsComp.h"

#include <QPushButton>
#include <QtConcurrent/QtConcurrent>
#include <QWidget>


ConsoleProgram::ConsoleProgram()
{
  m_consoleWidget = new ConsoleArea();

  // Attach logging to this subprogram's console
  Logger::setClient(std::make_shared<ConsoleLoggerClient>(m_consoleWidget));
}

ConsoleProgram::ConsoleProgram(QWidget* parent)
{
  m_consoleWidget = new ConsoleArea(parent);

  // Attach logging to this subprogram's console
  Logger::setClient(std::make_shared<ConsoleLoggerClient>(m_consoleWidget));
}

ConsoleProgram::~ConsoleProgram()
{
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
  QtConcurrent::run([]()
  {
    SortAlgsComp comp;
    comp.runFunctionalTest();
  });
}

void ConsoleProgram::runSortComparison()
{
  QtConcurrent::run([]()
  {
    SortAlgsComp comp;
    comp.runSpeedTest();
  });
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
