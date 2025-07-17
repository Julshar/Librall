#pragma once

#include <QWidget>
#include <QVector>
#include <QPushButton>
#include <QTimer>
#include <QVBoxLayout>

class GameOfLifeLogic;

class GameOfLifeView : public QWidget
{
  Q_OBJECT

public:
  explicit GameOfLifeView(GameOfLifeLogic* logic, QWidget* parent = nullptr);

  void updateUI();

  int getRefreshInterval() { return refreshInterval; }
  
  void resizeBoard(int rows, int cols);

public slots:
  void startSimulation();
  void stopSimulation();
  void randomizeCells();
  void clearCells();
  void toggleAutoRandomize();
  void setRefreshInterval(int interval);
  
private:
  void refreshCell(int x, int y);
  void setupGrid();
  void clearGrid();

  bool autoRandomize = false;
  int refreshInterval = 200; // milliseconds
  int refreshIntervalStep = 25;

  GameOfLifeLogic* logic;
  QVector<QVector<QPushButton*>> cells;

  QVBoxLayout* mainLayout = nullptr;
  QGridLayout* gridLayout = nullptr;

  QTimer* timer;
};