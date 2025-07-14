#pragma once

#include <QMainWindow>

#include <QStackedWidget>
#include <QMap>

#include "UIMode.h"

class QSplitter;
class SidePanelArea;
class ConsoleArea;
class ModeTabBar;
class MainAreaSection;

enum class DisplayMode { Text, Hex, Binary };

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  MainWindow(QWidget *parent = nullptr);

private:
  void setupMenuBar();
  void setupLayout();
  void registerSubprogramFactories();

  void enableMode(UIMode mode);
  void closeMode(UIMode mode);
  void switchMode(UIMode mode);

  void formatData(const QByteArray &data, QString &formatted) const;

  QSplitter *mainSplitter;
  SidePanelArea *sidePanel;
  ConsoleArea *console;

  QStackedWidget *mainAreaStack;
  ModeTabBar *modeTabBar;
  UIMode currentMode = UIMode::None;

  DisplayMode currentDisplayMode = DisplayMode::Text;
  QString currentFilePath;

private slots:
  void chooseFile();
  void reopenFile();

  QString modeName(UIMode mode) const;
};