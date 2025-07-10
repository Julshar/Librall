#pragma once

#include <QWidget>
#include <QTextEdit>
#include <QString>

#include "MainAreaSection.h"

class QTextEdit;
class QLineEdit;

class ConsoleArea : public MainAreaSection
{
  Q_OBJECT

public:
  ConsoleArea(QWidget *parent = nullptr);
  void print(const QString &text);
  void print(const std::string &text);
  void flush();

private slots:
  void handleInput();

private:
  QTextEdit *outputArea;
  QLineEdit *inputField;
};

