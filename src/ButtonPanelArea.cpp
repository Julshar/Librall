#include "ButtonPanelArea.h"

#include <iostream>
#include <QPushButton>
#include <QtConcurrent/QtConcurrent>

#include "SortAlgsComp.h"
#include "DatabaseTest.h"
#include "Logger.h"

ButtonPanelArea::ButtonPanelArea(QWidget *parent)
  : QWidget(parent)
{
  vLayout = new QVBoxLayout(this);
  setLayout(vLayout);
}

void ButtonPanelArea::setMode(UIMode mode)
{
  QLayoutItem *child;
  while ((child = layout()->takeAt(0)) != nullptr)
  {
    /*
    * deleteLater() is used to safely schedule the widget for deletion
    * after it finishes any pending events, avoiding potential crashes
    * or undefined behavior from immediate deletion.
    */
    if (child->widget()) child->widget()->deleteLater();
    delete child;
  }

  switch (mode)
  {
    case UIMode::Console:
    {
      QPushButton *btnSortTest = new QPushButton("Test Sort");
      QPushButton *btnSortComp = new QPushButton("Compare Sort");
      QPushButton *btnDBTest = new QPushButton("Test DB");
      QPushButton *btnFlushConsole = new QPushButton("Flush Console");

      connect(btnFlushConsole, &QPushButton::clicked, []()
      {
        Logger::flush();
      });

      connect(btnSortTest, &QPushButton::clicked, []()
      {
        // QtConcurrent::run produces warnings if result is not used
        // we don't need result here but save it to avoid warnings
        QFuture<void> result = QtConcurrent::run([]()
        {
          SortAlgsComp comp;
          comp.runFunctionalTest();
        });
      });

      connect(btnSortComp, &QPushButton::clicked, []()
      {
        QFuture<void> result = QtConcurrent::run([]() 
        {
          SortAlgsComp comp;
          comp.runSpeedTest();
        });
      });

      connect(btnDBTest, &QPushButton::clicked, []()
      {
        int res = DatabaseTest::runTest();
        std::cout << "Database test returned: " << res << "\n";
      });
      vLayout->addWidget(btnSortTest);
      vLayout->addWidget(btnSortComp);
      vLayout->addWidget(btnDBTest);
      vLayout->addWidget(btnFlushConsole);
      break;
    }
    case UIMode::GameOfLife:
    {
      QPushButton *btnStart = new QPushButton("Start");
      QPushButton *btnStop = new QPushButton("Stop");
      QPushButton *btnRandomize = new QPushButton("Randomize");

      vLayout->addWidget(btnStart);
      vLayout->addWidget(btnStop);
      vLayout->addWidget(btnRandomize);
      break;
    }
    case UIMode::None:
    {
      break;
    }
  }
  vLayout->addStretch(); // Always end with stretch for spacing
}