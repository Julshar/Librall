#include "MainWindow.h"
#include "SidePanelArea.h"
#include "ConsoleArea.h"
#include "Logger.h"
#include "ModeTabBar.h"

#include "SubprogramBase.h"
#include "SubprogramManager.h"
#include "GameOfLifeProgram.h"
#include "ConsoleProgram.h"

#include <QSplitter>
#include <QMenuBar>
#include <QVBoxLayout>

#include <QFileDialog>
#include <QFile>
#include <QByteArray>
#include <QTextStream>

MainWindow::MainWindow(QWidget *parent)
  : QMainWindow(parent)
{
  registerSubprogramFactories();
  setupMenuBar();
  setupLayout();
  setWindowTitle("Librall");
  resize(1000, 700);
}

void MainWindow::setupMenuBar()
{
  QMenuBar *menuBar = new QMenuBar(this);

  QMenu *fileMenu = menuBar->addMenu("File");
  QAction *openAction = fileMenu->addAction("Open...");
  connect(openAction, &QAction::triggered, this, &MainWindow::chooseFile);

  QMenu *toolsMenu = menuBar->addMenu("Tools");
  QAction *consoleMode = toolsMenu->addAction("Console Mode");
  connect(consoleMode, &QAction::triggered, [this]
  {
    enableMode(UIMode::Console);
    Logger::logDebug("Console mode activated.");
  });

  QAction *gameOfLife = toolsMenu->addAction("Game of Life");
  connect(gameOfLife, &QAction::triggered, [this]
  {
    Logger::logDebug("Initializing Game of Life...");
    enableMode(UIMode::GameOfLife);
  });

  QMenu *optionsMenu = menuBar->addMenu("Options");

  QMenu *viewModeMenu = new QMenu("File View Mode", this);
  QAction *textMode = viewModeMenu->addAction("Text");
  QAction *hexMode = viewModeMenu->addAction("Hex");
  QAction *binMode = viewModeMenu->addAction("Binary");

  optionsMenu->addMenu(viewModeMenu);

  connect(textMode, &QAction::triggered, [this]
  {
    currentDisplayMode = DisplayMode::Text;
    if (!currentFilePath.isEmpty()) reopenFile();
  });
  connect(hexMode, &QAction::triggered, [this]
  {
    currentDisplayMode = DisplayMode::Hex;
    if (!currentFilePath.isEmpty()) reopenFile();
  });
  connect(binMode, &QAction::triggered, [this]
  {
    currentDisplayMode = DisplayMode::Binary;
    if (!currentFilePath.isEmpty()) reopenFile();
  });

  QMenu *helpMenu = menuBar->addMenu("Help");

  setMenuBar(menuBar);
}

void MainWindow::setupLayout()
{
  mainSplitter = new QSplitter(Qt::Horizontal, this);
  sidePanel = new SidePanelArea;
  mainAreaStack = new QStackedWidget(this);

  sidePanel->setMinimumWidth(150);
  mainAreaStack->setMinimumWidth(400);

  mainSplitter->addWidget(sidePanel);
  mainSplitter->addWidget(mainAreaStack);
  mainSplitter->setSizes({150, 1000});
  mainSplitter->setStretchFactor(0, 0);
  mainSplitter->setStretchFactor(1, 1);

  modeTabBar = new ModeTabBar(this);
  // When user presses any tab (or closes tab) ModeTabBar emits proper signal
  // and MainWindow reacts with proper function thanks to below connect() calls.
  connect(modeTabBar, &ModeTabBar::modeSelected, this, &MainWindow::switchMode);
  connect(modeTabBar, &ModeTabBar::modeClosed, this, &MainWindow::closeMode);

  QWidget *central = new QWidget(this);
  QVBoxLayout *layout = new QVBoxLayout(central);
  layout->setContentsMargins(0, 0, 0, 0);

  layout->addWidget(modeTabBar);
  layout->addWidget(mainSplitter);
  central->setLayout(layout);
  setCentralWidget(central);
}

// Register lambdas for subprogram creation to use for later
void MainWindow::registerSubprogramFactories()
{
  auto& sm = SubprogramManager::instance();

  sm.registerFactory(UIMode::Console, [](QWidget* parent) {
    return std::make_unique<ConsoleProgram>(parent);
  });

  sm.registerFactory(UIMode::GameOfLife, [](QWidget* parent) {
    return std::make_unique<GameOfLifeProgram>(parent);
  });
}

// When clicked in Tools menu
void MainWindow::enableMode(UIMode mode)
{
  auto& sm = SubprogramManager::instance();

  if (sm.registerProgram(mode, this) == false)
  {
    Logger::logError(QString("ERROR! Failed to register subprogram for mode: %1").arg(static_cast<int>(mode)));
  }
  
  // Always activate the program
  sm.activateProgram(mode);

  SubprogramBase *prog = sm.getProgram(mode);
  if (prog)
  {
    // Set side panel widgets
    sidePanel->setPanel(prog->getSidePanelControls());

    // Get main widget and add it to stack if not in the stack (newly created)
    QWidget *mainWidget = prog->getMainWidget();
    if (mainAreaStack->indexOf(mainWidget) == -1)
    {
      mainAreaStack->addWidget(mainWidget);
    }

    // Set the main widget as current
    mainAreaStack->setCurrentWidget(mainWidget);
    currentMode = mode;

    modeTabBar->addMode(mode, modeName(mode));
    modeTabBar->setActive(mode);
  }
  else
  {
    Logger::logError(QString("ERROR! No subprogram found for mode: %1").arg(static_cast<int>(mode)));
  }
}

void MainWindow::closeMode(UIMode mode)
{
  modeTabBar->removeMode(mode);
  SubprogramManager::instance().closeProgram(mode);

  // TODO: This function is called when user clicks "x" on some tab.
  // When it is done, currently displayed mode should be closed and
  // erased from mainAreaStack. Furthermore, a neighboring mode on tab bar
  // should be activated automatically (if there is any).
  // Otherwise, current mode should be set to None and widgets cleared.

  if (currentMode == mode)
  {
    currentMode = UIMode::None;
    sidePanel->setPanel({});
  }
}

// When clicked on tab bar
void MainWindow::switchMode(UIMode mode)
{
  auto& sm = SubprogramManager::instance();
  sm.activateProgram(mode);

  SubprogramBase *prog = sm.getProgram(mode);
  if (prog)
  {
    sidePanel->setPanel(prog->getSidePanelControls());
    mainAreaStack->setCurrentWidget(prog->getMainWidget());
  }
  else
  {
    Logger::logError(QString("ERROR! No subprogram found for mode: %1").arg(static_cast<int>(mode)));
  }

  modeTabBar->setActive(mode);
  currentMode = mode;
}

// Console mode functions: chooseFile, reopenFile, formatData

void MainWindow::chooseFile()
{
  QString fileName = QFileDialog::getOpenFileName(this, "Open File");

  if (!fileName.isEmpty())
  {
    currentFilePath = fileName;
    reopenFile();
  }
  else
  {
    Logger::log("No file selected.");
  }
}

void MainWindow::reopenFile()
{
  if (!currentFilePath.isEmpty())
  {
    QFile file(currentFilePath);
    if (!file.open(QIODevice::ReadOnly))
    {
      Logger::log("Failed to open file.");
      return;
    }
    QByteArray data = file.readAll();
    file.close();

    QString formatted;
    formatData(data, formatted);

    Logger::log("#################################################\n"
                "File Loaded: " + currentFilePath + "\n"
                "#################################################\n");
    Logger::log(formatted + "\n");
  }
}

void MainWindow::formatData(const QByteArray &data, QString &formatted) const
{
  switch (currentDisplayMode)
  {
    case DisplayMode::Text:
      formatted = QString::fromUtf8(data);
      break;
    case DisplayMode::Hex:
    {
      QString hex;
      for (unsigned char byte : data)
      {
        hex += QString("%1 ").arg(byte, 2, 16, QChar('0'));
      }
      formatted = hex.toUpper();
      break;
    }
    case DisplayMode::Binary:
    {
      QString binary;
      for (unsigned char byte : data)
      {
        binary += QString("%1 ").arg(byte, 8, 2, QChar('0'));
      }
      formatted = binary;
      break;
    }
  }
}

// Helper function to get mode name

QString MainWindow::modeName(UIMode mode) const
{
  switch (mode)
  {
    case UIMode::Console: return "Console";
    case UIMode::GameOfLife: return "Game of Life";
    default: return "Unknown";
  }
}