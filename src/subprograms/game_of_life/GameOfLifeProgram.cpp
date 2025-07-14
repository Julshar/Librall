#include "GameOfLifeProgram.h"
#include "GameOfLifeLogic.h"
#include "GameOfLifeView.h"

GameOfLifeProgram::GameOfLifeProgram(QWidget* parent)
{
  logic = new GameOfLifeLogic();
  view = new GameOfLifeView(logic, parent);
}

GameOfLifeProgram::~GameOfLifeProgram()
{
  delete view;
  delete logic;
}

QWidget* GameOfLifeProgram::getMainWidget()
{
  return view;
}

QList<QWidget*> GameOfLifeProgram::getSidePanelControls()
{
  QList<QWidget *> widgets;

  QPushButton *btnStart = new QPushButton("Start");
  QPushButton *btnStop = new QPushButton("Stop");
  QPushButton *btnRandomize = new QPushButton("Randomize");
  QPushButton *btnClear = new QPushButton("Clear");
  QPushButton *btnRandomizeOnFrozen = new QPushButton("Auto Randomize");
  btnRandomizeOnFrozen->setCheckable(true);

  QObject::connect(btnStart, &QPushButton::clicked, view, &GameOfLifeView::startSimulation);
  QObject::connect(btnStop, &QPushButton::clicked, view, &GameOfLifeView::stopSimulation);
  QObject::connect(btnRandomize, &QPushButton::clicked, view, &GameOfLifeView::randomizeCells);
  QObject::connect(btnClear, &QPushButton::clicked, view, &GameOfLifeView::clearCells);
  QObject::connect(btnRandomizeOnFrozen, &QPushButton::clicked, view, &GameOfLifeView::toggleAutoRandomize);

  widgets << btnStart << btnStop << btnRandomize << btnClear << btnRandomizeOnFrozen;
  return widgets;
}