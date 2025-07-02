#include "MainWindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
  QApplication app(argc, argv);

  app.setStyleSheet(R"(
    QToolTip {
      color: white;
      background-color: #333;
      border: 1px solid white;
      padding: 2px;
      border-radius: 3px;
    }
  )");
  
  MainWindow window;
  window.show();
  return app.exec();
}