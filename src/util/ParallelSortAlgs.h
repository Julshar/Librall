#pragma once

#include <vector>
#include <thread>

class ParallelSortAlgs
{
public:

  static void mergeSort(std::vector<int>& arr);

private:

  static void mergeSortPrv(std::vector<int>& arr, int left, int right, int depth = 0);
  static void merge(std::vector<int>& arr, int left, int mid, int right);

  static const int MAX_DEPTH = 3; // Not used currently. Const is preffered for clarity, but this value can differ based on implementation
  static int maxDepth;
};