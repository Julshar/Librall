#include <QMainWindow>

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  MainWindow(QWidget *parent = nullptr);

  static void sortingAlgsTest();
  static void sortingAlgsSpeedTest();
  static int databaseTest();
};