#pragma once

#include "ISubprogram.h"
#include "UIMode.h"

class GameOfLifeLogic;
class GameOfLifeView;

class GameOfLifeProgram : public ISubprogram
{
public:
  explicit GameOfLifeProgram(QWidget* parent = nullptr);
  ~GameOfLifeProgram();

  QWidget* getMainWidget();
  QList<QWidget*> getSidePanelControls() override;

private slots:
  void startSimulation();
  void stopSimulation();
  void randomizeCells();
  void clearCells();

private:
  GameOfLifeLogic* logic;
  GameOfLifeView* view;
};
