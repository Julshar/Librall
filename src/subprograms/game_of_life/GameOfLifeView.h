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

public slots:
  void startSimulation();
  void stopSimulation();
  void randomizeCells();
  void clearCells();
  void toggleAutoRandomize();
  
private:
  void setupGrid();
  void refreshCell(int x, int y);

  bool autoRandomize = false;

  GameOfLifeLogic* logic;
  QVector<QVector<QPushButton*>> cells;

  QPushButton* startButton;
  QPushButton* stopButton;
  QTimer* timer;
};