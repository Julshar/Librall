#include "GameOfLifeArea.h"
#include <QVBoxLayout>

GameOfLifeArea::GameOfLifeArea(QWidget *parent)
  : MainAreaSection(parent), currentState(rows, std::vector<bool>(cols, false))
{
  auto *mainLayout = new QVBoxLayout(this);
  gridLayout = new QGridLayout();

  for (int x = 0; x < rows; ++x)
  {
    std::vector<QPushButton*> row;
    for (int y = 0; y < cols; ++y)
    {
      QPushButton *cell = new QPushButton();
      cell->setFixedSize(20, 20);
      cell->setStyleSheet("background-color: white; border: 1px solid gray;");
      gridLayout->addWidget(cell, x, y);
      row.push_back(cell);

      connect(cell, &QPushButton::clicked, [this, x, y, cell]()
      {
        currentState[x][y] = !currentState[x][y];
        cell->setStyleSheet(currentState[x][y]
          ? "background-color: black;"
          : "background-color: white;");
      });
    }
    cells.push_back(row);
  }

  mainLayout->addLayout(gridLayout);

  startButton = new QPushButton("Start");
  stopButton = new QPushButton("Stop");
  mainLayout->addWidget(startButton);
  mainLayout->addWidget(stopButton);

  timer = new QTimer(this);
  timer->setInterval(300); // ms

  connect(startButton, &QPushButton::clicked, this, &GameOfLifeArea::startSimulation);
  connect(stopButton, &QPushButton::clicked, this, &GameOfLifeArea::stopSimulation);
  connect(timer, &QTimer::timeout, this, &GameOfLifeArea::updateGeneration);

  setLayout(mainLayout);
}

void GameOfLifeArea::startSimulation()
{
  timer->start();
}

void GameOfLifeArea::stopSimulation()
{
  timer->stop();
}

void GameOfLifeArea::toggleCell()
{
}

void GameOfLifeArea::updateGeneration()
{
  std::vector<std::vector<bool>> nextState = currentState;

  for (int x = 0; x < rows; ++x)
  {
    for (int y = 0; y < cols; ++y)
    {
      int neighbors = liveNeighborCount(x, y);
      if (currentState[x][y])
      {
        nextState[x][y] = (neighbors == 2 || neighbors == 3);
      }
      else
      {
        nextState[x][y] = (neighbors == 3);
      }
    }
  }

  currentState = nextState;

  for (int x = 0; x < rows; ++x)
  {
    for (int y = 0; y < cols; ++y)
    {
      cells[x][y]->setStyleSheet(currentState[x][y]
        ? "background-color: black;"
        : "background-color: white;");
    }
  }
}

int GameOfLifeArea::liveNeighborCount(int row, int col) const
{
  int count = 0;
  for (int dx = -1; dx <= 1; ++dx)
  {
    for (int dy = -1; dy <= 1; ++dy)
    {
      if (dx == 0 && dy == 0) continue;
      int nx = row + dx;
      int ny = col + dy;
      if (nx >= 0 && nx < rows && ny >= 0 && ny < cols && currentState[nx][ny])
      {
        ++count;
      }
    }
  }
  return count;
}