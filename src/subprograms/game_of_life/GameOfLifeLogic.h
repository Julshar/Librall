#pragma once

#include <vector>
#include <cstdint>

class GameOfLifeLogic
{
public:
  GameOfLifeLogic(int rows = 20, int cols = 20);

  void toggleCell(int x, int y);
  int updateGeneration();

  bool cellState(int x, int y) const;

  void resizeBoard(int newRows, int newCols);

  int rowCount() const { return rows; }
  int colCount() const { return cols; }

private:
  int index(int x, int y) const;
  int liveNeighborCount(int x, int y) const;

  int rows;
  int cols;
  std::vector<uint8_t> currentBoard;
};