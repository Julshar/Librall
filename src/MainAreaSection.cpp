#include "MainAreaSection.h"
#include <QLabel>
#include <QVBoxLayout>

MainAreaSection::MainAreaSection(QWidget *parent)
  : QWidget(parent)
{
  auto *layout = new QVBoxLayout(this);
  layout->addWidget(new QLabel("Dynamic Section"));
  setLayout(layout);
}