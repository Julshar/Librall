#include "MainWindow.h"
#include "ButtonPanelArea.h"
#include "ConsoleArea.h"
#include "MainAreaSection.h"
#include "Logger.h"
#include "ModeTabBar.h"
#include "GameOfLifeArea.h"

#include <QSplitter>
#include <QMenuBar>
#include <QVBoxLayout>

#include <QFileDialog>
#include <QFile>
#include <QByteArray>
#include <QTextStream>

enum class DisplayMode { Text, Hex, Binary };
DisplayMode currentDisplayMode = DisplayMode::Text;
QString currentFilePath;

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
    enableMode(UIMode::GameOfLife);
    Logger::logDebug("Initializing Game of Life...");
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
  buttonPanel = new ButtonPanelArea;
  mainAreaStack = new QStackedWidget(this);

  buttonPanel->setMinimumWidth(150);
  mainAreaStack->setMinimumWidth(400);

  mainSplitter->addWidget(buttonPanel);
  mainSplitter->addWidget(mainAreaStack);
  mainSplitter->setStretchFactor(0, 1);
  mainSplitter->setStretchFactor(1, 3);

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

void MainWindow::enableMode(UIMode mode)
{
  if (activeModes.contains(mode))
  {
    // Tab (mode) already open, just activate
    mainAreaStack->setCurrentWidget(activeModes[mode]);
    buttonPanel->setMode(mode);
    modeTabBar->setActive(mode);
    currentMode = mode;
    return;
  }

  MainAreaSection *section = nullptr;
  switch (mode)
  {
    case UIMode::Console:
    {
      ConsoleArea *c = new ConsoleArea(this);
      Logger::attachConsole(c);
      section = c;
      break;
    }
    case UIMode::GameOfLife:
    {
      section = new GameOfLifeArea(this);
      break;
    }
  }

  if (section)
  {
    mainAreaStack->addWidget(section);
    activeModes[mode] = section;
    mainAreaStack->setCurrentWidget(section);
    buttonPanel->setMode(mode);
    modeTabBar->addMode(mode, modeName(mode));
    currentMode = mode;
  }
}

void MainWindow::closeMode(UIMode mode)
{
  if (!activeModes.contains(mode)) return;

  QWidget *widget = activeModes[mode];
  mainAreaStack->removeWidget(widget);
  delete widget;
  activeModes.remove(mode);
  modeTabBar->removeMode(mode);

  if (currentMode == mode)
  {
    currentMode = UIMode::None;
    buttonPanel->setMode(UIMode::None);
  }
}

void MainWindow::switchMode(UIMode mode)
{
  if (!activeModes.contains(mode)) return;
  mainAreaStack->setCurrentWidget(activeModes[mode]);
  buttonPanel->setMode(mode);
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