#pragma once

#include <QMainWindow>

class QSplitter;
class ButtonPanelArea;
class ConsoleArea;

class MainWindow : public QMainWindow {
  Q_OBJECT

public:
  MainWindow(QWidget *parent = nullptr);

private:
  void setupMenuBar();
  void setupLayout();

  QSplitter *mainSplitter;
  ButtonPanelArea *buttonPanel;
  ConsoleArea *console;
};