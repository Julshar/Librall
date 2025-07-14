#pragma once

#include <QWidget>

class ISubprogram
{
public:
  virtual ~ISubprogram() = default;

  // Returns the QWidget that should appear in the main area
  virtual QWidget* getMainWidget() = 0;

  // Returns QWidgets representing side panel controls like buttons, etc.
  // This can be empty if no side panel is needed
  virtual QList<QWidget *> getSidePanelControls() { return {}; }

  // Optional
  virtual void onActivated() {}
  virtual void onDeactivated() {}
};