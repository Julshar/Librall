#include "ParallelSortAlgs.h"

void ParallelSortAlgs::merge(std::vector<int>& arr, int left, int mid, int right)
{
  int n1 = mid - left + 1, n2 = right - mid;
  std::vector<int> L(arr.begin() + left, arr.begin() + mid + 1);
  std::vector<int> R(arr.begin() + mid + 1, arr.begin() + right + 1);
  int i = 0, j = 0, k = left;
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

    if (depth < MAX_DEPTH)
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
  mergeSortPrv(arr, 0, arr.size() - 1);
}