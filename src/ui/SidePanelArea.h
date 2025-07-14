#pragma once

#include <QWidget>
#include <QVBoxLayout>
#include <QList>

class SidePanelArea : public QWidget
{
  Q_OBJECT

private:
  QVBoxLayout *vLayout = nullptr;

public:
  explicit SidePanelArea(QWidget *parent = nullptr);

  void setPanel(const QList<QWidget *> &widgets);
};