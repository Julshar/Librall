#include "MainWindow.h"
#include "ButtonPanelArea.h"
#include "ConsoleArea.h"
#include "MainAreaSection.h"
#include "Logger.h"

#include <QSplitter>
#include <QMenuBar>
#include <QVBoxLayout>

MainWindow::MainWindow(QWidget *parent)
  : QMainWindow(parent)
{
  setupMenuBar();
  setupLayout();
  setWindowTitle("Librall - Advanced GUI");
  resize(1000, 700);
}

void MainWindow::setupMenuBar()
{
  QMenuBar *menuBar = new QMenuBar(this);

  QMenu *fileMenu = menuBar->addMenu("File");
  QMenu *optionsMenu = menuBar->addMenu("Options");
  QMenu *helpMenu = menuBar->addMenu("Help");

  setMenuBar(menuBar);
}

void MainWindow::setupLayout()
{
  mainSplitter = new QSplitter(Qt::Horizontal, this);
  buttonPanel = new ButtonPanelArea;
  console = new ConsoleArea;

  Logger::attachConsole(console);

  buttonPanel->setMinimumWidth(150);
  console->setMinimumWidth(400);

  mainSplitter->addWidget(buttonPanel);
  mainSplitter->addWidget(console);

  mainSplitter->setStretchFactor(0, 1);
  mainSplitter->setStretchFactor(1, 3);

  QWidget *central = new QWidget(this);
  QVBoxLayout *layout = new QVBoxLayout(central);
  layout->addWidget(mainSplitter);
  central->setLayout(layout);
  setCentralWidget(central);
}