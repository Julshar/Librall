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
  : SubprogramBase(parent)
{
  m_logic = new GameOfLifeLogic();
  m_view = new GameOfLifeView(m_logic, parent);
}

GameOfLifeProgram::~GameOfLifeProgram()
{
  // TODO: Crash on application close
  //
  // m_view should only be deleted here when this program is closed from tab bar
  // When the whole appliaction is closed, MainWindow will delete m_view
  // Now m_view is deleted here always hence the crash when closing application with Game of Life open
  delete m_view;
  delete m_logic;
}

QWidget* GameOfLifeProgram::getMainWidget()
{
  return m_view;
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
  refreshRateSlider->setValue(m_view->getRefreshInterval());
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

  m_colsInput = new QLineEdit(QString::number(m_logic->colCount()));
  m_colsInput->setPlaceholderText("Cols");
  m_colsInput->setFixedWidth(50);
  m_rowsInput = new QLineEdit(QString::number(m_logic->rowCount()));
  m_rowsInput->setPlaceholderText("Rows");
  m_rowsInput->setFixedWidth(50);
  QPushButton *resizeButton = new QPushButton("Resize");
  QLabel *rowsCountLabel = new QLabel("Rows:");
  QLabel *colsCountLabel = new QLabel("Cols:");

  QObject::connect(btnStart, &QPushButton::clicked, m_view, &GameOfLifeView::startSimulation);
  QObject::connect(btnStop, &QPushButton::clicked, m_view, &GameOfLifeView::stopSimulation);
  QObject::connect(btnRandomize, &QPushButton::clicked, m_view, &GameOfLifeView::randomizeCells);
  QObject::connect(btnClear, &QPushButton::clicked, m_view, &GameOfLifeView::clearCells);
  QObject::connect(btnRandomizeOnFrozen, &QPushButton::clicked, m_view, &GameOfLifeView::toggleAutoRandomize);
  QObject::connect(refreshRateSlider, &QSlider::valueChanged, m_view, &GameOfLifeView::setRefreshInterval);
  QObject::connect(resizeButton, &QPushButton::clicked, [this]() {
    handleBoardResize();
  });

  widgets << btnStart << btnStop << btnRandomize << btnClear << btnRandomizeOnFrozen << refreshSliderLabel
          << refreshRateSlider << rowsCountLabel << m_rowsInput << colsCountLabel << m_colsInput << resizeButton;
  return widgets;
}

void GameOfLifeProgram::handleBoardResize()
{
  bool okRows, okCols;
  int rows = m_rowsInput->text().toInt(&okRows);
  int cols = m_colsInput->text().toInt(&okCols);

  if (okRows && okCols && rows < 100 && cols < 100)
  {
    m_view->resizeBoard(rows, cols);
  }
  else
  {
    Logger::logDebug("GameOfLifeProgram::handleBoardResize(): Failed to change board size. Invalid input size");
  }
}
