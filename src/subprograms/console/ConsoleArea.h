#pragma once

#include <QWidget>
#include <QTextEdit>
#include <QString>

class QTextEdit;
class QLineEdit;

class ConsoleArea : public QWidget
{
  Q_OBJECT

public:
  ConsoleArea(QWidget *parent = nullptr);
  void print(const QString &text);
  void print(const std::string &text);
  void flush();

public slots:
  void flushConsole();

private slots:
  void handleInput();

private:
  QTextEdit *outputArea;
  QLineEdit *inputField;
};

