#include "SortAlgsComp.h"
#include "VectorUtil.h"
#include "Random.h"
#include "Timer.h"
#include "SortAlgs.h"
#include "ParallelSortAlgs.h"
#include "Logger.h"

#include <iostream>
#include <vector>

#include <string>
#include <QString>

void SortAlgsComp::runFunctionalTest()
{
  Random::seedWithTime();
  std::vector<int> arr = VectorUtil::generateRandomVector(40, 0, 100);
  Logger::log("Unsorted array: ");
  VectorUtil::printVector(arr);

  std::vector<int> c1 = arr, c2 = arr, c3 = arr, c4 = arr;
  SortAlgs::insertionSort(c1); Logger::log("Insertion: "); VectorUtil::printVector(c1);
  SortAlgs::mergeSort(c2);     Logger::log("Merge:     "); VectorUtil::printVector(c2);
  SortAlgs::quickSort(c3);     Logger::log("Quick:     "); VectorUtil::printVector(c3);
  SortAlgs::heapSort(c4);      Logger::log("Heap:      "); VectorUtil::printVector(c4);
}

void SortAlgsComp::runSpeedTest()
{
  Random::seedWithTime();
  std::vector<int> arr = VectorUtil::generateRandomVector(100000, 0, 100000);
  std::vector<int> c1 = arr, c2 = arr, c3 = arr, c4 = arr, c5 = arr, c6 = arr;
  Timer timer;

  SortAlgs::insertionSort(c1); Logger::log("Insertion: "); Logger::log(std::to_string(timer.elapsedTimeMicro()) + " microseconds"); timer.reset();
  SortAlgs::mergeSort(c2);     Logger::log("Merge:     "); Logger::log(std::to_string(timer.elapsedTimeMicro()) + " microseconds"); timer.reset();
  SortAlgs::quickSort(c3);     Logger::log("Quick:     "); Logger::log(std::to_string(timer.elapsedTimeMicro()) + " microseconds"); timer.reset();
  SortAlgs::heapSort(c4);      Logger::log("Heap:      "); Logger::log(std::to_string(timer.elapsedTimeMicro()) + " microseconds"); timer.reset();
  ParallelSortAlgs::mergeSort(c5); Logger::log("Parallel Merge: "); Logger::log(std::to_string(timer.elapsedTimeMicro()) + " microseconds"); timer.reset();
  ParallelSortAlgs::quickSort(c6); Logger::log("Parallel Quick: "); Logger::log(std::to_string(timer.elapsedTimeMicro()) + " microseconds");
}