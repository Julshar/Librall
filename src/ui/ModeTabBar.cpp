#include "ModeTabBar.h"

#include <QHBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QToolButton>

ModeTabBar::ModeTabBar(QWidget *parent)
  : QWidget(parent)
{
  setStyleSheet("background-color:rgb(38, 38, 38);"); // Darker gray, for contrast
  
  layout = new QHBoxLayout(this);
  layout->setSpacing(4);
  layout->setContentsMargins(8, 4, 8, 4);
  setLayout(layout);

  // Prevent bar from growing vertiaclly
  setFixedHeight(TAB_BAR_HEIGHT);
}

void ModeTabBar::addMode(UIMode mode, const QString &label)
{
  if (modeWidgets.contains(mode)) return;

  QWidget *container = new QWidget(this);
  QHBoxLayout *containerLayout = new QHBoxLayout(container);
  containerLayout->setContentsMargins(2, 2, 2, 2);

  QPushButton *tabButton = new QPushButton(label, container);
  tabButton->setFlat(true);
  tabButton->setCheckable(true); // allows toggling
  tabButton->setAutoExclusive(true); // ensures only one is "checked"
  tabButton->setStyleSheet(R"(
    QPushButton {
        background-color: #444;
        color: white;
        border-radius: 5px;
        padding: 6px 12px;
    }
    QPushButton:checked {
        background-color:rgb(110, 184, 0);
        color: white;
    }
    QPushButton:!checked:hover {
        background-color: #555;
    }
  )");

  QToolButton *closeButton = new QToolButton(container);
  closeButton->setText("x");
  closeButton->setFixedSize(16, 16);
  closeButton->setToolTip("Close Tab");
  closeButton->setStyleSheet(R"(
    QToolButton {
        background-color: #444;
        border: none;
        color: white;
    }
    QToolButton:hover {
        background-color: #666;
        border-radius: 8px;
    }
  )");

  connect(tabButton, &QPushButton::clicked, [this, mode]()
  {
    emit modeSelected(mode);
  });

  connect(closeButton, &QToolButton::clicked, [this, mode]()
  {
    emit modeClosed(mode);
  });

  containerLayout->addWidget(tabButton);
  containerLayout->addWidget(closeButton);
  container->setLayout(containerLayout);

  layout->addWidget(container);
  modeWidgets[mode] = container;
}

void ModeTabBar::removeMode(UIMode mode)
{
  if (!modeWidgets.contains(mode)) return;

  QWidget *w = modeWidgets.take(mode);
  layout->removeWidget(w);
  delete w;
}

void ModeTabBar::setActive(UIMode mode)
{
  for (auto it = modeWidgets.begin(); it != modeWidgets.end(); ++it)
  {
    QWidget *container = it.value();
    QPushButton *button = container->findChild<QPushButton *>();
    if (button)
    {
      button->setChecked(it.key() == mode);
    }
  }
}