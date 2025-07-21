#pragma once

#include "SubprogramBase.h"
#include "UIMode.h"
#include <QLineEdit>

class GameOfLifeLogic;
class GameOfLifeView;

class GameOfLifeProgram : public SubprogramBase
{
  Q_OBJECT
  
public:
  explicit GameOfLifeProgram(QWidget* parent = nullptr);
  ~GameOfLifeProgram();

  QWidget* getMainWidget();
  QList<QWidget*> getSidePanelControls() override;

private:
  void handleBoardResize();
  
  GameOfLifeLogic* m_logic;
  GameOfLifeView* m_view;

  QLineEdit* m_colsInput;
  QLineEdit* m_rowsInput;
};
