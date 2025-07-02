#pragma once

#include <QWidget>
#include <QMap>

#include "UIMode.h"

class QHBoxLayout;
class QPushButton;

class ModeTabBar : public QWidget
{
  Q_OBJECT

public:
  explicit ModeTabBar(QWidget *parent = nullptr);
  void addMode(UIMode mode, const QString &label);
  void removeMode(UIMode mode);
  void setActive(UIMode mode);

signals:
  void modeSelected(UIMode mode);
  void modeClosed(UIMode mode);

private:
  static constexpr int TAB_BAR_HEIGHT = 35;

  QHBoxLayout *layout;
  QMap<UIMode, QWidget*> modeWidgets;
};