#pragma once

#include <QMainWindow>

#include <QStackedWidget>
#include <QMap>

#include "UIMode.h"

class QSplitter;
class ButtonPanelArea;
class ConsoleArea;
class ModeTabBar;
class MainAreaSection;

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  MainWindow(QWidget *parent = nullptr);

private:
  void setupMenuBar();
  void setupLayout();

  void enableMode(UIMode mode);
  void closeMode(UIMode mode);
  void switchMode(UIMode mode);

  void formatData(const QByteArray &data, QString &formatted) const;

  QSplitter *mainSplitter;
  ButtonPanelArea *buttonPanel;
  ConsoleArea *console;

  QStackedWidget *mainAreaStack;
  ModeTabBar *modeTabBar;
  QMap<UIMode, MainAreaSection*> activeModes;
  UIMode currentMode = UIMode::None;

private slots:
  void chooseFile();
  void reopenFile();

  QString modeName(UIMode mode) const;
};