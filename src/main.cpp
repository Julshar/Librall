#include <iostream>

#include "VectorUtil.h"
#include "Random.h"
#include "Timer.h"
#include "SortAlgs.h"

int main(int argc, char* argv[])
{
  Random::seedWithTime();

  std::vector<int> smallArray = VectorUtil::generateRandomVector(10, 0, 100);
  std::vector<int> largeArray = VectorUtil::generateRandomVector(100000, 0, 100000);

  std::cout << "Small array: ";
  VectorUtil::printVector(smallArray);

  std::vector<int> smallArrayCopy_1 = smallArray; // Copy for sorting
  std::vector<int> smallArrayCopy_2 = smallArray; // Copy for sorting
  std::vector<int> smallArrayCopy_3 = smallArray; // Copy for sorting
  std::vector<int> smallArrayCopy_4 = smallArray; // Copy for sorting

  SortAlgs::insertionSort(smallArrayCopy_1);
  std::cout << "TEST: Sorted small array (insertion): ";
  VectorUtil::printVector(smallArrayCopy_1);

  SortAlgs::mergeSort(smallArrayCopy_2);
  std::cout << "TEST: Sorted small array (merge): ";
  VectorUtil::printVector(smallArrayCopy_2);

  SortAlgs::quickSort(smallArrayCopy_3);
  std::cout << "TEST: Sorted small array (quick): ";
  VectorUtil::printVector(smallArrayCopy_3);

  SortAlgs::heapSort(smallArrayCopy_4);
  std::cout << "TEST: Sorted small array (heap): ";
  VectorUtil::printVector(smallArrayCopy_4);

  std::vector<int> largeArrayCopy_1 = largeArray; // Copy for sorting
  std::vector<int> largeArrayCopy_2 = largeArray; // Copy for sorting
  std::vector<int> largeArrayCopy_3 = largeArray; // Copy for sorting
  std::vector<int> largeArrayCopy_4 = largeArray; // Copy for sorting

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

  return 0;
}