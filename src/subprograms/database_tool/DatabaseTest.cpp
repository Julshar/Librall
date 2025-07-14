#include "DatabaseTest.h"

#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlTableModel>
#include <QTableView>
#include <QDebug>
#include <iostream>

int DatabaseTest::runTest()
{
  std::cout << "Hello database!\n";
  QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
  db.setDatabaseName("data/world-db/world.sql");

  if (!db.open())
  {
    qDebug() << "Error: " << db.lastError().text();
    return -1;
  }

  QSqlTableModel *model = new QSqlTableModel;
  model->setTable("table_name");
  model->select();

  QTableView *view = new QTableView;
  view->setModel(model);
  view->resize(800, 600);
  view->show();

  return 0;
}