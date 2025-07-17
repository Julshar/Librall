#include "GameOfLifeLogic.h"

GameOfLifeLogic::GameOfLifeLogic(int rows, int cols)
  : rows(rows), cols(cols), currentBoard(rows * cols, 0)
{}

// x = column, y = row
int GameOfLifeLogic::index(int x, int y) const
{
  return y * cols + x;
}

void GameOfLifeLogic::toggleCell(int x, int y)
{
  if (x >= 0 && x < cols && y >= 0 && y < rows)
  {
    int idx = index(x, y);
    currentBoard[idx] = !currentBoard[idx];
  }
}

bool GameOfLifeLogic::cellState(int x, int y) const
{
  if (x >= 0 && x < cols && y >= 0 && y < rows)
    return currentBoard[index(x, y)] != 0;
  return false;
}

int GameOfLifeLogic::updateGeneration()
{
  int counter = 0;
  std::vector<uint8_t> nextState(rows * cols, 0);

  for (int y = 0; y < rows; ++y)
  {
    for (int x = 0; x < cols; ++x)
    {
      int neighbors = liveNeighborCount(x, y);
      int idx = index(x, y);

      if (currentBoard[idx])
      {
        if (neighbors == 2 || neighbors == 3)
        {
          nextState[idx] = 1; // survives
        }
        else
        {
          nextState[idx] = 0; // dies
          ++counter;
        }
      }
      else
      {
        if (neighbors == 3)
        {
          nextState[idx] = 1; // born
          ++counter;
        }
      }
    }
  }

  currentBoard = std::move(nextState);
  return counter;
}

int GameOfLifeLogic::liveNeighborCount(int x, int y) const
{
  int count = 0;

  for (int dy = -1; dy <= 1; ++dy)
  {
    for (int dx = -1; dx <= 1; ++dx)
    {
      if (dx == 0 && dy == 0) continue;

      int nx = x + dx;
      int ny = y + dy;

      if (nx >= 0 && nx < cols && ny >= 0 && ny < rows)
      {
        if (currentBoard[index(nx, ny)])
          ++count;
      }
    }
  }

  return count;
}

void GameOfLifeLogic::resizeBoard(int newRows, int newCols)
{
  std::vector<uint8_t> newState(newRows * newCols, 0);

  int minRows = std::min(rows, newRows);
  int minCols = std::min(cols, newCols);

  for (int y = 0; y < minRows; ++y)
  {
    for (int x = 0; x < minCols; ++x)
    {
      newState[y * newCols + x] = currentBoard[index(x, y)];
    }
  }

  rows = newRows;
  cols = newCols;
  currentBoard = std::move(newState);
}
