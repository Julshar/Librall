#include "GameOfLifeLogic.h"

GameOfLifeLogic::GameOfLifeLogic(int rows, int cols)
  : rows(rows), cols(cols), currentState(rows, std::vector<bool>(cols, false))
{}

void GameOfLifeLogic::toggleCell(int x, int y)
{
  if (x >= 0 && x < rows && y >= 0 && y < cols)
    currentState[x][y] = !currentState[x][y];
}

bool GameOfLifeLogic::cellState(int x, int y) const
{
  return currentState[x][y];
}

int GameOfLifeLogic::updateGeneration()
{
  int counter = 0;
  std::vector<std::vector<bool>> nextState = currentState; // optimize: NO NESTED VECTOR

  for (int x = 0; x < rows; ++x)
  {
    for (int y = 0; y < cols; ++y)
    {
      int neighbors = liveNeighborCount(x, y);
      if (currentState[x][y])
      {
        if (neighbors < 2 || neighbors > 3)
        {
          nextState[x][y] = false;
          ++counter; // count dead cells
        }
      }
      else
      {
        if (neighbors == 3)
        {
          nextState[x][y] = true;
          ++counter; // count born cells
        }
      }
    }
  }

  currentState = nextState;
  return counter; // return number of changes (born or dead cells)
}

int GameOfLifeLogic::liveNeighborCount(int x, int y) const
{
  int count = 0;
  for (int dx = -1; dx <= 1; ++dx)
  {
    for (int dy = -1; dy <= 1; ++dy)
    {
      if (dx == 0 && dy == 0) continue;
      int nx = x + dx;
      int ny = y + dy;
      if (nx >= 0 && nx < rows && ny >= 0 && ny < cols && currentState[nx][ny])
        ++count;
    }
  }
  return count;
}
