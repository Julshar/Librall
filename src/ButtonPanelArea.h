#pragma once

#include <QWidget>
#include <QVBoxLayout>

#include "UIMode.h"

class ButtonPanelArea : public QWidget
{
  Q_OBJECT

private:
  QVBoxLayout *vLayout = nullptr;

public:
  ButtonPanelArea(QWidget *parent = nullptr);

  void setMode(UIMode mode);
};