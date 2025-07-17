#pragma once

#include "ISubprogram.h"
#include "UIMode.h"
#include <QLineEdit>

class GameOfLifeLogic;
class GameOfLifeView;

class GameOfLifeProgram : public ISubprogram
{
public:
  explicit GameOfLifeProgram(QWidget* parent = nullptr);
  ~GameOfLifeProgram();

  QWidget* getMainWidget();
  QList<QWidget*> getSidePanelControls() override;

private:
  void handleBoardResize();
  
  GameOfLifeLogic* logic;
  GameOfLifeView* view;

  QLineEdit *colsInput;
  QLineEdit *rowsInput;
};
