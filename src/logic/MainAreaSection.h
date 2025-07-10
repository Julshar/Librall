#pragma once

#include <QWidget>

// This is a parent class for MainArea widgets
// However it does not create layout to give children more flexibility
// Creating layout is responsibility of every MainAreaSection child class

class MainAreaSection : public QWidget
{
  Q_OBJECT

public:
  MainAreaSection(QWidget *parent = nullptr);
  virtual ~MainAreaSection();
};