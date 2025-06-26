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

// Wrapper aliases - avoid using lambda functions but move logic to separate namespace
namespace SortWrappers
{
  inline void insertionIntAsc(std::vector<int>& v) { SortAlgs::insertionSort<int>(v); }
  inline void mergeIntAsc(std::vector<int>& v) { SortAlgs::mergeSort<int>(v); }
  inline void quickIntAsc(std::vector<int>& v) { SortAlgs::quickSort<int>(v); }
  inline void heapIntAsc(std::vector<int>& v) { SortAlgs::heapSort<int>(v); }
}

// anonymous namespace for file-local functions
namespace 
{
  template <typename SortFunc>
  void runAndLogSort(const std::string& name, SortFunc sorter, const std::vector<int>& original)
  {
    std::vector<int> arr = original;
    Timer timer;
    sorter(arr);
    auto time = timer.elapsedTimeMicro();
    Logger::log(name + ": ");
    Logger::log(std::to_string(time) + " microseconds");
  }

  template <typename SortFunc>
  void runAndPrintSorted(const std::string& name, SortFunc sorter, const std::vector<int>& original)
  {
    std::vector<int> arr = original;
    sorter(arr);
    Logger::log(name + ": ");
    Logger::log(arr);
  }
}

void SortAlgsComp::runFunctionalTest()
{
  Random::seedWithTime();
  Logger::log("#################################################\n"
              "Running functional test for sorting algorithms...\n"
              "#################################################\n");
  std::vector<int> arr = VectorUtil::generateRandomVector(40, 0, 100);
  Logger::log("Unsorted array: ");
  Logger::log(arr);
  Logger::log("-------------------------------------------------");

  // Both wrappers and lambdas can be used to perform the same task here.
  // Lambdas are more flexible, but wrappers can be more readable and reusable.

  // Using wrappers for ascending order
  Logger::log("Ascending order: ");
  runAndPrintSorted("Insertion Sort", SortWrappers::insertionIntAsc, arr);
  runAndPrintSorted("Merge Sort", SortWrappers::mergeIntAsc, arr);
  runAndPrintSorted("Quick Sort", SortWrappers::quickIntAsc, arr);
  runAndPrintSorted("Heap Sort", SortWrappers::heapIntAsc, arr);

  Logger::log("-------------------------------------------------");

  // Using lambdas for descending order
  Logger::log("Descending order: ");
  runAndPrintSorted("Insertion Sort", [](std::vector<int>& v) { SortAlgs::insertionSort<int, std::greater<int>>(v); }, arr);
  runAndPrintSorted("Merge Sort", [](std::vector<int>& v) { SortAlgs::mergeSort<int, std::greater<int>>(v); }, arr);
  runAndPrintSorted("Quick Sort", [](std::vector<int>& v) { SortAlgs::quickSort<int, std::greater<int>>(v); }, arr);
  runAndPrintSorted("Heap Sort", [](std::vector<int>& v) { SortAlgs::heapSort<int, std::greater<int>>(v); }, arr);

  Logger::log(" ");
}

void SortAlgsComp::runSpeedTest()
{
  Random::seedWithTime();
  Logger::log("#################################################\n"
              "Running speed test for sorting algorithms...\n"
              "#################################################\n");
  std::vector<int> arr = VectorUtil::generateRandomVector(100000, 0, 100000);

  runAndLogSort("Insertion Sort", SortWrappers::insertionIntAsc, arr);
  runAndLogSort("Merge Sort", SortWrappers::mergeIntAsc, arr);
  runAndLogSort("Quick Sort: ", SortWrappers::quickIntAsc, arr);
  runAndLogSort("Heap Sort", SortWrappers::heapIntAsc, arr);
  runAndLogSort("Parallel Merge", ParallelSortAlgs::mergeSort,  arr);
  runAndLogSort("Parallel Quick", ParallelSortAlgs::quickSort,  arr);

  Logger::log(" ");
}