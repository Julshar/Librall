#pragma once

#include "SubprogramBase.h"

class PaintCanvas;

class PaintProgram : public SubprogramBase
{
  Q_OBJECT

public:
  explicit PaintProgram(QWidget* parent = nullptr);
  ~PaintProgram() override;
  
  QWidget* getMainWidget() override;
  QList<QWidget*> getSidePanelControls() override;
  void onActivated() override;
  void onDeactivated() override;

private:
  PaintCanvas* canvas = nullptr;
};