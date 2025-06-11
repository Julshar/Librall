#include <iostream>

#include "VectorUtil.h"
#include "Random.h"
#include "Timer.h"
#include "SortAlgs.h"

#include <QApplication>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>

void sortingAlgsTest()
{
  Random::seedWithTime();

  std::vector<int> arr = VectorUtil::generateRandomVector(40, 0, 100);

  std::cout << "Unsorted array: ";
  VectorUtil::printVector(arr);

  std::vector<int> smallArrayCopy_1 = arr; // Copy for sorting
  std::vector<int> smallArrayCopy_2 = arr; // Copy for sorting
  std::vector<int> smallArrayCopy_3 = arr; // Copy for sorting
  std::vector<int> smallArrayCopy_4 = arr; // Copy for sorting

  SortAlgs::insertionSort(smallArrayCopy_1);
  std::cout << "TEST: Sorted small array (insertion): ";
  VectorUtil::printVector(smallArrayCopy_1);

  SortAlgs::mergeSort(smallArrayCopy_2);
  std::cout << "TEST: Sorted small array (merge):     ";
  VectorUtil::printVector(smallArrayCopy_2);

  SortAlgs::quickSort(smallArrayCopy_3);
  std::cout << "TEST: Sorted small array (quick):     ";
  VectorUtil::printVector(smallArrayCopy_3);

  SortAlgs::heapSort(smallArrayCopy_4);
  std::cout << "TEST: Sorted small array (heap):      ";
  VectorUtil::printVector(smallArrayCopy_4);
}

void sortingAlgsSpeedTest()
{
  Random::seedWithTime();

  std::vector<int> arr = VectorUtil::generateRandomVector(100000, 0, 100000);

  std::vector<int> largeArrayCopy_1 = arr; // Copy for sorting
  std::vector<int> largeArrayCopy_2 = arr; // Copy for sorting
  std::vector<int> largeArrayCopy_3 = arr; // Copy for sorting
  std::vector<int> largeArrayCopy_4 = arr; // Copy for sorting

  Timer timer;

  SortAlgs::insertionSort(largeArrayCopy_1);
  std::cout << "SPEED TEST: Insertion sort:\n";
  timer.printElapsedTimeSeconds();
  timer.reset();

  SortAlgs::mergeSort(largeArrayCopy_2);
  std::cout << "SPEED TEST: Merge sort:\n";
  timer.printElapsedTimeSeconds();
  timer.reset();

  SortAlgs::quickSort(largeArrayCopy_3);
  std::cout << "SPEED TEST: Quick sort:\n";
  timer.printElapsedTimeSeconds();
  timer.reset();

  SortAlgs::heapSort(largeArrayCopy_4);
  std::cout << "SPEED TEST: Heap sort:\n";
  timer.printElapsedTimeSeconds();
}

int main(int argc, char *argv[])
{
  QApplication app(argc, argv);
  QWidget window;
  window.setWindowTitle("Librall");

  auto* vbox = new QVBoxLayout(&window);

  auto* btnSortTest = new QPushButton("Sorting algorithms test", &window);
  vbox->addWidget(btnSortTest);
  QObject::connect(btnSortTest, &QPushButton::clicked, []()
  {
    sortingAlgsTest();
  });

  auto* btnSortSpeedTest = new QPushButton("Sorting algorithms speed test", &window);
  vbox->addWidget(btnSortSpeedTest);
  QObject::connect(btnSortSpeedTest, &QPushButton::clicked, []()
  {
    sortingAlgsSpeedTest();
  });

  window.setLayout(vbox);
  window.resize(400, 300);
  window.show();

  return app.exec();
}