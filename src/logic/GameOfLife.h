#pragma once

#include "MainAreaSection.h"
#include <QGridLayout>
#include <QTimer>
#include <QPushButton>
#include <vector>

class GameOfLife : public MainAreaSection
{
  Q_OBJECT

public:
  explicit GameOfLife(QWidget *parent = nullptr);

private slots:
  void toggleCell();
  void updateGeneration();
  void startSimulation();
  void stopSimulation();

private:
  static constexpr int rows = 20;
  static constexpr int cols = 20;

  QGridLayout *gridLayout;
  std::vector<std::vector<QPushButton*>> cells;
  std::vector<std::vector<bool>> currentState;

  QTimer *timer;
  QPushButton *startButton;
  QPushButton *stopButton;

  int liveNeighborCount(int row, int col) const;
};
