#pragma once

#include <vector>

class GameOfLifeLogic
{
public:
  GameOfLifeLogic(int rows = 20, int cols = 20);

  void toggleCell(int x, int y);
  void updateGeneration();

  bool cellState(int x, int y) const;
  int rowCount() const { return rows; }
  int colCount() const { return cols; }

private:
  int liveNeighborCount(int x, int y) const;

  int rows;
  int cols;
  std::vector<std::vector<bool>> currentState;
};