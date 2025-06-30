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

  void formatData(const QByteArray &data, QString &formatted) const;

  QSplitter *mainSplitter;
  ButtonPanelArea *buttonPanel;
  ConsoleArea *console;

private slots:
  void chooseFile();
  void reopenFile();
};