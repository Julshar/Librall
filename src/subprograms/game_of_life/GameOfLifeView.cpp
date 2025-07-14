#include "GameOfLifeView.h"
#include "GameOfLifeLogic.h"
#include "Logger.h"
#include <QGridLayout>
#include <QVBoxLayout>

GameOfLifeView::GameOfLifeView(GameOfLifeLogic* logic, QWidget* parent)
  : QWidget(parent), logic(logic)
{
  QVBoxLayout* mainLayout = new QVBoxLayout(this);
  QGridLayout* gridLayout = new QGridLayout();

  int rows = logic->rowCount();
  int cols = logic->colCount();

  cells.resize(rows);
  for (int x = 0; x < rows; ++x)
  {
    cells[x].resize(cols);
    for (int y = 0; y < cols; ++y)
    {
      QPushButton* cell = new QPushButton();
      cell->setFixedSize(20, 20);
      cell->setStyleSheet("background-color: white; border: 1px solid gray;");
      gridLayout->addWidget(cell, x, y);
      cells[x][y] = cell;

      connect(cell, &QPushButton::clicked, this, [this, x, y]()
      {
        this->logic->toggleCell(x, y);
        refreshCell(x, y);
      });
    }
  }

  mainLayout->addLayout(gridLayout);

  startButton = new QPushButton("Start");
  stopButton = new QPushButton("Stop");
  mainLayout->addWidget(startButton);
  mainLayout->addWidget(stopButton);

  connect(startButton, &QPushButton::clicked, this, &GameOfLifeView::startSimulation);
  connect(stopButton, &QPushButton::clicked, this, &GameOfLifeView::stopSimulation);

  timer = new QTimer(this);
  connect(timer, &QTimer::timeout, this, &GameOfLifeView::updateUI);

  setLayout(mainLayout);
}

void GameOfLifeView::refreshCell(int x, int y)
{
  bool alive = logic->cellState(x, y);
  cells[x][y]->setStyleSheet(alive
    ? "background-color: black;"
    : "background-color: white;");
}

void GameOfLifeView::updateUI()
{
  logic->updateGeneration();
  int rows = logic->rowCount();
  int cols = logic->colCount();
  for (int x = 0; x < rows; ++x)
  {
    for (int y = 0; y < cols; ++y)
    {
      refreshCell(x, y);
    }
  }
}

void GameOfLifeView::startSimulation()
{
  timer->start(300);
  Logger::logDebug("Game of Life: Simulation started.");
}

void GameOfLifeView::stopSimulation()
{
  timer->stop();
  Logger::logDebug("Game of Life: Simulation stopped.");
}

void GameOfLifeView::randomizeCells()
{
  Logger::logDebug("Game of Life: Randomizing cells.");
}

void GameOfLifeView::clearCells()
{
  Logger::logDebug("Game of Life: Clearing cells.");
}