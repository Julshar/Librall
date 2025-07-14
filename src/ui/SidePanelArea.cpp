#include "SidePanelArea.h"

SidePanelArea::SidePanelArea(QWidget *parent)
  : QWidget(parent)
{
  vLayout = new QVBoxLayout(this);
  setLayout(vLayout);
}

void SidePanelArea::setPanel(const QList<QWidget *> &widgets)
{
  // Clear previous panel content
  QLayoutItem *child;
  while ((child = layout()->takeAt(0)) != nullptr)
  {
    if (child->widget()) child->widget()->deleteLater();
    delete child;
  }

  for (QWidget *widget : widgets)
  {
    vLayout->addWidget(widget);
  }

  vLayout->addStretch();
}