#include "ButtonPanelArea.h"

#include <iostream>
#include <QVBoxLayout>
#include <QPushButton>

#include "SortAlgsComp.h"
#include "DatabaseTest.h"

ButtonPanelArea::ButtonPanelArea(QWidget *parent)
  : QWidget(parent)
{
  auto *layout = new QVBoxLayout(this);

  QPushButton *btnSortTest = new QPushButton("Test Sort");
  QPushButton *btnSortComp = new QPushButton("Compare Sort");
  QPushButton *btnDBTest = new QPushButton("Test DB");

  connect(btnSortTest, &QPushButton::clicked, []() {
  SortAlgsComp::runFunctionalTest();
});

connect(btnSortComp, &QPushButton::clicked, []() {
  SortAlgsComp::runSpeedTest();
});

connect(btnDBTest, &QPushButton::clicked, []() {
  int res = DatabaseTest::runTest();
  std::cout << "Database test returned: " << res << "\n";
});

  layout->addWidget(btnSortTest);
  layout->addWidget(btnSortComp);
  layout->addWidget(btnDBTest);
  layout->addStretch();
  setLayout(layout);
}