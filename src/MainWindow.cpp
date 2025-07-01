#include "MainWindow.h"
#include "ButtonPanelArea.h"
#include "ConsoleArea.h"
#include "MainAreaSection.h"
#include "Logger.h"

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
    Logger::logDebug("Console mode activated.");
  });

  QAction *gameOfLife = toolsMenu->addAction("Game of Life");
  connect(gameOfLife, &QAction::triggered, [this]
  {
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