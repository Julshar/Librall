#include "ParallelSortAlgs.h"

#include <cmath> // for std::log2
#include <iostream> // std::cout

#undef DEBUG

int ParallelSortAlgs::maxDepthMerge = 0;
int ParallelSortAlgs::maxDepthQuick = 0;

void ParallelSortAlgs::init()
{
  ParallelSortAlgs::maxDepthMerge = std::thread::hardware_concurrency() ? std::log2(std::thread::hardware_concurrency()) : 2;
  ParallelSortAlgs::maxDepthQuick = ParallelSortAlgs::maxDepthMerge;
  #ifdef DEBUG
  std::cout << "ParallelSortAlgs::init: Using max depth (merge): " << ParallelSortAlgs::maxDepthMerge << "\n";
  std::cout << "ParallelSortAlgs::init: Using max depth (quick): " << ParallelSortAlgs::maxDepthQuick << "\n";
  std::cout << "ParallelSortAlgs::init: std::thread::hardware_concurrency(): " << std::thread::hardware_concurrency() << "\n";
  #endif
}

/*
*  MERGE SORT
*/

void ParallelSortAlgs::merge(std::vector<int>& arr, int left, int mid, int right)
{
  int n1 = mid - left + 1;
  int n2 = right - mid;
  std::vector<int> L(arr.begin() + left, arr.begin() + mid + 1);
  std::vector<int> R(arr.begin() + mid + 1, arr.begin() + right + 1);
  int i = 0;
  int j = 0;
  int k = left;
  while (i < n1 && j < n2)
  {
    arr[k++] = (L[i] <= R[j]) ? L[i++] : R[j++];
  }
  while (i < n1) arr[k++] = L[i++];
  while (j < n2) arr[k++] = R[j++];
}

void ParallelSortAlgs::mergeSortPrv(std::vector<int>& arr, int left, int right, int depth)
{
  if (left < right)
  {
    int mid = left + (right - left) / 2;

    if (depth < maxDepthMerge && (right - left) > MIN_SUBARRAY_SIZE)
    {
      std::thread t1(&ParallelSortAlgs::mergeSortPrv, std::ref(arr), left, mid, depth + 1);
      std::thread t2(&ParallelSortAlgs::mergeSortPrv, std::ref(arr), mid + 1, right, depth + 1);
      t1.join();
      t2.join();
    } 
    else
    {
      mergeSortPrv(arr, left, mid, depth + 1);
      mergeSortPrv(arr, mid + 1, right, depth + 1);
    }

  merge(arr, left, mid, right);
  }
}

void ParallelSortAlgs::mergeSort(std::vector<int>& arr)
{
  // This has to be done only once per device. Maybe move it to some global init later.
  init();
  mergeSortPrv(arr, 0, arr.size() - 1);
}

/*
*  QUICK SORT
*/

void ParallelSortAlgs::quickSortPrv(std::vector<int>& arr, int low, int high, int depth)
{
  if (low < high)
  {
    int pi = partition(arr, low, high);

    if (depth < maxDepthQuick && (high - low) > MIN_SUBARRAY_SIZE)
    {
      std::thread t1(&ParallelSortAlgs::quickSortPrv, std::ref(arr), low, pi - 1, depth + 1);
      std::thread t2(&ParallelSortAlgs::quickSortPrv, std::ref(arr), pi + 1, high, depth + 1);
      // quickSortPrv(arr, pi + 1, high, depth + 1); // faster to reuse thread?
      t1.join();
      t2.join();
    } 
    else
    {
      quickSortPrv(arr, low, pi - 1, depth + 1);
      quickSortPrv(arr, pi + 1, high, depth + 1);
    }
  }
}

void ParallelSortAlgs::quickSort(std::vector<int>& arr)
{
  // This has to be done only once per device. Maybe move it to some global init later.
  init();
  quickSortPrv(arr, 0, arr.size() - 1);
}

int ParallelSortAlgs::partition(std::vector<int>& arr, int low, int high)
{
  int pivot = arr[high];
  int i = low - 1;
  for (int j = low; j < high; j++)
  {
    if (arr[j] < pivot) std::swap(arr[++i], arr[j]);
  }
  std::swap(arr[i + 1], arr[high]);
  return i + 1;
}