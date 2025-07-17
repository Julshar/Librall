#include "GameOfLifeView.h"
#include "GameOfLifeLogic.h"
#include "Logger.h"
#include "Random.h"
#include <QGridLayout>
#include <QLineEdit>

GameOfLifeView::GameOfLifeView(GameOfLifeLogic* logic, QWidget* parent)
  : QWidget(parent), logic(logic)
{
  mainLayout = new QVBoxLayout(this);

  setupGrid();

  setLayout(mainLayout);

  timer = new QTimer(this);
  connect(timer, &QTimer::timeout, this, &GameOfLifeView::updateUI);
}

void GameOfLifeView::setupGrid()
{
  // Create new layout and grid
  gridLayout = new QGridLayout();

  int rows = logic->rowCount();
  int cols = logic->colCount();

  cells.resize(rows);
  for (int y = 0; y < rows; ++y)
  {
    cells[y].resize(cols);
    for (int x = 0; x < cols; ++x)
    {
      QPushButton* cell = new QPushButton();
      cell->setFixedSize(20, 20);
      cell->setStyleSheet("background-color: black; border: 1px solid gray;");
      gridLayout->addWidget(cell, y, x);
      cells[y][x] = cell;
      refreshCell(x, y);

      connect(cell, &QPushButton::clicked, this, [this, x, y]()
      {
        this->logic->toggleCell(x, y);
        refreshCell(x, y);
      });
    }
  }

  mainLayout->addLayout(gridLayout);
}

void GameOfLifeView::clearGrid()
{
  if (gridLayout)
  {
    for (auto& row : cells)
    {
      for (auto& cell : row)
      {
        cell->setParent(nullptr);
        delete cell; // Clean up old buttons
      }
    }
    mainLayout->removeItem(gridLayout);
    delete gridLayout;
    gridLayout = nullptr;
    cells.clear();
  }
  else
  {
    Logger::logDebug("GameOfLifeView::clearGrid(): Grid layout already cleared or not initialized");
  }
}

void GameOfLifeView::resizeBoard(int rows, int cols)
{
  logic->resizeBoard(rows, cols);
  clearGrid();
  setupGrid();
  Logger::logDebug("Game of Life: Board resized to " + std::to_string(rows) + "x" + std::to_string(cols));
}

void GameOfLifeView::refreshCell(int x, int y)
{
  bool alive = logic->cellState(x, y);
  cells[y][x]->setStyleSheet(alive
    ? "background-color: white;"
    : "background-color: black;");
}

void GameOfLifeView::updateUI()
{
  int changed = logic->updateGeneration();
  if (changed == 0 && autoRandomize)
  {
    randomizeCells();
    return; // Skip cell refresh - done in randomizeCells
  }

  int rows = logic->rowCount();
  int cols = logic->colCount();
  for (int y = 0; y < rows; ++y)
  {
    for (int x = 0; x < cols; ++x)
    {
      refreshCell(x, y);
    }
  }
}

void GameOfLifeView::startSimulation()
{
  timer->start(refreshInterval);
  Logger::logDebug("Game of Life: Simulation started");
}

void GameOfLifeView::stopSimulation()
{
  timer->stop();
  Logger::logDebug("Game of Life: Simulation stopped");
}
void GameOfLifeView::setRefreshInterval(int interval)
{
  interval = interval % refreshIntervalStep > refreshIntervalStep / 2
    ? (interval / refreshIntervalStep + 1) * refreshIntervalStep
    : (interval / refreshIntervalStep) * refreshIntervalStep;
  
  if (interval != refreshInterval)
  {
    refreshInterval = interval;
    if (timer->isActive())
    {
      timer->setInterval(refreshInterval);
    }
    Logger::logDebug("Game of Life: Refresh interval set to " + std::to_string(refreshInterval) + " ms");
  }
}

void GameOfLifeView::randomizeCells()
{
  int rows = logic->rowCount();
  int cols = logic->colCount();
  for (int y = 0; y < rows; ++y)
  {
    for (int x = 0; x < cols; ++x)
    {
      if (Random::genBool() == true)
      {
        logic->toggleCell(x, y);
      }
      refreshCell(x, y);
    }
  }
  Logger::logDebug("Game of Life: Cells randomized");
}

void GameOfLifeView::clearCells()
{
  int rows = logic->rowCount();
  int cols = logic->colCount();
  for (int y = 0; y < rows; ++y)
  {
    for (int x = 0; x < cols; ++x)
    {
      if (logic->cellState(x, y))
      {
        logic->toggleCell(x, y);
      }
      refreshCell(x, y);
    }
  }

  Logger::logDebug("Game of Life: Cells cleared");
}

void GameOfLifeView::toggleAutoRandomize()
{
  autoRandomize = !autoRandomize;
}