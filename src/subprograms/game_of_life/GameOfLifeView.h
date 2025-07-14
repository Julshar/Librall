#pragma once

#include <QWidget>
#include <QVector>
#include <QPushButton>
#include <QTimer>

class GameOfLifeLogic;

class GameOfLifeView : public QWidget
{
  Q_OBJECT

public:
  explicit GameOfLifeView(GameOfLifeLogic* logic, QWidget* parent = nullptr);

  void updateUI();

  int getRefreshInterval() { return refreshInterval; }

public slots:
  void startSimulation();
  void stopSimulation();
  void randomizeCells();
  void clearCells();
  void toggleAutoRandomize();
  void setRefreshInterval(int interval);
  
private:
  void setupGrid();
  void refreshCell(int x, int y);

  bool autoRandomize = false;
  int refreshInterval = 200; // milliseconds
  int refreshIntervalStep = 25;

  GameOfLifeLogic* logic;
  QVector<QVector<QPushButton*>> cells;

  QPushButton* startButton;
  QPushButton* stopButton;
  QTimer* timer;
};