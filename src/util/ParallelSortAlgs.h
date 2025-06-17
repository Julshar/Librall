#pragma once

#include <vector>
#include <thread>

class ParallelSortAlgs
{
public:

  static void init();

  static void mergeSort(std::vector<int>& arr);
  static void quickSort(std::vector<int>& arr);

private:

  static void mergeSortPrv(std::vector<int>& arr, int left, int right, int depth = 0);
  static void merge(std::vector<int>& arr, int left, int mid, int right);

  static void quickSortPrv(std::vector<int>& arr, int low, int high, int depth = 0);
  static int partition(std::vector<int>& arr, int low, int high);

  static int maxDepthMerge;
  static int maxDepthQuick;

  // Whenever a subarray size is smaller than this, no more threads will be created for sorting it.
  static constexpr int MIN_SUBARRAY_SIZE = 1000;
};