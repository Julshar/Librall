#include "ConsoleArea.h"

#include <QVBoxLayout>
#include <QTextEdit>
#include <QLineEdit>
#include <string>

ConsoleArea::ConsoleArea(QWidget *parent)
  : QWidget(parent)
{
  outputArea = new QTextEdit(this);
  inputField = new QLineEdit(this);

  auto *layout = new QVBoxLayout(this);
  layout->addWidget(outputArea);
  layout->addWidget(inputField);
  setLayout(layout);

  outputArea->setReadOnly(true);
  connect(inputField, &QLineEdit::returnPressed, this, &ConsoleArea::handleInput);
}

void ConsoleArea::print(const QString &text)
{
  outputArea->append(text);
}

void ConsoleArea::print(const std::string &text)
{
  outputArea->append(QString::fromStdString(text));
}

void ConsoleArea::handleInput()
{
  QString input = inputField->text();
  outputArea->append("> " + input);
  inputField->clear();
}

void ConsoleArea::flushConsole()
{
  flush();
}

void ConsoleArea::flush()
{
  outputArea->clear();
  inputField->clear();
}