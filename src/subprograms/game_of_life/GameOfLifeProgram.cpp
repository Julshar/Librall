#include "GameOfLifeProgram.h"
#include "GameOfLifeLogic.h"
#include "GameOfLifeView.h"
#include <QSlider>
#include <QLabel>

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
  QSlider *refreshRateSlider = new QSlider(Qt::Horizontal);
  refreshRateSlider->setRange(25, 500);
  refreshRateSlider->setValue(view->getRefreshInterval());
  refreshRateSlider->setStyleSheet(R"(
  QSlider::handle:horizontal
  {
      background: #6eb800;
      width: 20px;
      border-radius: 12px;
  }
  QSlider::groove:horizontal
  {
      height: 12px;
      background: #444;
  }
)");
  QLabel *refreshSliderLabel = new QLabel(QString("Refresh rate"));

  /*
  * TODO: Not possible currently to display label and change it dynamically
  *       Need to find a way to create some box layout here for more flexibility
  *       or use a custom widget that can display label and slider together.
  * 
  *       Maybe passing a layout instead of List of QWidgets? Or both?
  */

  QObject::connect(btnStart, &QPushButton::clicked, view, &GameOfLifeView::startSimulation);
  QObject::connect(btnStop, &QPushButton::clicked, view, &GameOfLifeView::stopSimulation);
  QObject::connect(btnRandomize, &QPushButton::clicked, view, &GameOfLifeView::randomizeCells);
  QObject::connect(btnClear, &QPushButton::clicked, view, &GameOfLifeView::clearCells);
  QObject::connect(btnRandomizeOnFrozen, &QPushButton::clicked, view, &GameOfLifeView::toggleAutoRandomize);
  QObject::connect(refreshRateSlider, &QSlider::valueChanged, view, &GameOfLifeView::setRefreshInterval);

  widgets << btnStart << btnStop << btnRandomize << btnClear << btnRandomizeOnFrozen << refreshSliderLabel
          << refreshRateSlider;
  return widgets;
}