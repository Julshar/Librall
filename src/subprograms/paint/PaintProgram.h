#pragma once

#include "SubprogramBase.h"

class PaintCanvas;
enum class DrawMode;

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
  QWidget* createToolSelectionWidget(QObject* parentObject);
  PaintCanvas* canvas = nullptr;
};