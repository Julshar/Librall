#include "GameOfLifeProgram.h"
#include "GameOfLifeLogic.h"
#include "GameOfLifeView.h"
#include <QSlider>
#include <QLabel>
#include <QLineEdit>
#include <QIntValidator>
#include <QPushButton>
#include <QHBoxLayout>
#include "Logger.h"

GameOfLifeProgram::GameOfLifeProgram(QWidget* parent)
{
  logic = new GameOfLifeLogic();
  view = new GameOfLifeView(logic, parent);
}

GameOfLifeProgram::~GameOfLifeProgram()
{
  delete view;
  delete logic;
  if (rowsInput) delete rowsInput;
  if (colsInput) delete colsInput;
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

  QLabel *refreshSliderLabel = new QLabel(QString("Refresh rate"));
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

  colsInput = new QLineEdit(QString::number(logic->colCount()));
  colsInput->setPlaceholderText("Cols");
  colsInput->setFixedWidth(50);
  rowsInput = new QLineEdit(QString::number(logic->rowCount()));
  rowsInput->setPlaceholderText("Rows");
  rowsInput->setFixedWidth(50);
  QPushButton *resizeButton = new QPushButton("Resize");
  QLabel *rowsCountLabel = new QLabel("Rows:");
  QLabel *colsCountLabel = new QLabel("Cols:");
  

  /*
  * TODO: Not possible currently to display label and change it dynamically
  *       Need to find a way to create some box layout here for more flexibility
  *       or use a custom widget that can display label and slider together.
  * 
  *       Maybe widget creation should be moved to GameOfLifeView?
  *       This way we can have a single widget that contains all controls
  *       But then GameOfLifeProgram would have almost no functionality
  *       So maybe would be better to make ISubprogram derive from QWidget?
  */

  QObject::connect(btnStart, &QPushButton::clicked, view, &GameOfLifeView::startSimulation);
  QObject::connect(btnStop, &QPushButton::clicked, view, &GameOfLifeView::stopSimulation);
  QObject::connect(btnRandomize, &QPushButton::clicked, view, &GameOfLifeView::randomizeCells);
  QObject::connect(btnClear, &QPushButton::clicked, view, &GameOfLifeView::clearCells);
  QObject::connect(btnRandomizeOnFrozen, &QPushButton::clicked, view, &GameOfLifeView::toggleAutoRandomize);
  QObject::connect(refreshRateSlider, &QSlider::valueChanged, view, &GameOfLifeView::setRefreshInterval);
  QObject::connect(resizeButton, &QPushButton::clicked, [this]() {
    handleBoardResize();
  });

  widgets << btnStart << btnStop << btnRandomize << btnClear << btnRandomizeOnFrozen << refreshSliderLabel
          << refreshRateSlider << rowsCountLabel << rowsInput << colsCountLabel << colsInput << resizeButton;
  return widgets;
}

void GameOfLifeProgram::handleBoardResize()
{
  bool okRows, okCols;
  int rows = rowsInput->text().toInt(&okRows);
  int cols = colsInput->text().toInt(&okCols);

  if (okRows && okCols && rows < 100 && cols < 100)
  {
    view->resizeBoard(rows, cols);
  }
  else
  {
    Logger::logDebug("GameOfLifeProgram::handleBoardResize(): Failed to change board size. Invalid input size");
  }
}
