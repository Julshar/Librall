#include "SortAlgsComp.h"
#include "VectorUtil.h"
#include "Random.h"
#include "Timer.h"
#include "SortAlgs.h"
#include "ParallelSortAlgs.h"

#include <iostream>
#include <vector>

void SortAlgsComp::runFunctionalTest()
{
  Random::seedWithTime();
  std::vector<int> arr = VectorUtil::generateRandomVector(40, 0, 100);
  std::cout << "Unsorted array: ";
  VectorUtil::printVector(arr);

  std::vector<int> c1 = arr, c2 = arr, c3 = arr, c4 = arr;
  SortAlgs::insertionSort(c1); std::cout << "Insertion: "; VectorUtil::printVector(c1);
  SortAlgs::mergeSort(c2);     std::cout << "Merge:     "; VectorUtil::printVector(c2);
  SortAlgs::quickSort(c3);     std::cout << "Quick:     "; VectorUtil::printVector(c3);
  SortAlgs::heapSort(c4);      std::cout << "Heap:      "; VectorUtil::printVector(c4);
}

void SortAlgsComp::runSpeedTest()
{
  Random::seedWithTime();
  std::vector<int> arr = VectorUtil::generateRandomVector(100000, 0, 100000);
  std::vector<int> c1 = arr, c2 = arr, c3 = arr, c4 = arr, c5 = arr, c6 = arr;
  Timer timer;

  SortAlgs::insertionSort(c1); std::cout << "Insertion: "; timer.printElapsedTimeSeconds(); timer.reset();
  SortAlgs::mergeSort(c2);     std::cout << "Merge:     "; timer.printElapsedTimeSeconds(); timer.reset();
  SortAlgs::quickSort(c3);     std::cout << "Quick:     "; timer.printElapsedTimeSeconds(); timer.reset();
  SortAlgs::heapSort(c4);      std::cout << "Heap:      "; timer.printElapsedTimeSeconds(); timer.reset();
  ParallelSortAlgs::mergeSort(c5); std::cout << "Parallel Merge: "; timer.printElapsedTimeSeconds(); timer.reset();
  ParallelSortAlgs::quickSort(c6); std::cout << "Parallel Quick: "; timer.printElapsedTimeSeconds();
}