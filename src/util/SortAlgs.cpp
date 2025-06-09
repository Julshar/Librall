#include "SortAlgs.h"

#include <vector>
#include <algorithm> // swap
#include <cstdlib>  // rand, srand

// Insertion Sort
void SortAlgs::insertionSort(std::vector<int>& arr)
{
  int n = arr.size();
  for (int i = 1; i < n; i++)
  {
    int key = arr[i];
    int j = i - 1;
    while (j >= 0 && arr[j] > key)
    {
      arr[j + 1] = arr[j];
      j--;
    }
    arr[j + 1] = key;
  }
}

void SortAlgs::insertionSort(int* arr, int size)
{
  // Implementation for array of integers
  for (int i = 1; i < size; i++)
  {
    int key = arr[i];
    int j = i - 1;
    while (j >= 0 && arr[j] > key)
    {
      arr[j + 1] = arr[j];
      j--;
    }
    arr[j + 1] = key;
  }
}

// Merge Sort
void SortAlgs::merge(std::vector<int>& arr, int left, int mid, int right)
{
  int n1 = mid - left + 1, n2 = right - mid;
  std::vector<int> L(arr.begin() + left, arr.begin() + mid + 1);
  std::vector<int> R(arr.begin() + mid + 1, arr.begin() + right + 1);
  int i = 0, j = 0, k = left;
  while (i < n1 && j < n2)
  {
    arr[k++] = (L[i] <= R[j]) ? L[i++] : R[j++];
  }
  while (i < n1)
  {
    arr[k++] = L[i++];
  }
  while (j < n2)
  {
    arr[k++] = R[j++];
  }
}

void SortAlgs::mergeSort(std::vector<int>& arr, int left, int right)
{
  if (left < right)
  {
    int mid = left + (right - left) / 2;
    mergeSort(arr, left, mid);
    mergeSort(arr, mid + 1, right);
    merge(arr, left, mid, right);
  }
}

void SortAlgs::mergeSort(std::vector<int>& arr)
{
  int left = 0;
  int right = arr.size() - 1;

  if (left < right)
  {
    int mid = left + (right - left) / 2;
    mergeSort(arr, left, mid);
    mergeSort(arr, mid + 1, right);
    merge(arr, left, mid, right);
  }
}

void SortAlgs::mergeSort(int* arr, int size)
{
  // Implementation for array of integers
}

// Quick Sort
int SortAlgs::partition(std::vector<int>& arr, int low, int high)
{
  int pivot = arr[high], i = low - 1;
  for (int j = low; j < high; j++)
  {
    if (arr[j] < pivot) std::swap(arr[++i], arr[j]);
  }
  std::swap(arr[i + 1], arr[high]);
  return i + 1;
}

void SortAlgs::quickSort(std::vector<int>& arr, int low, int high)
{
  if (low < high)
  {
    int pi = partition(arr, low, high);
    quickSort(arr, low, pi - 1);
    quickSort(arr, pi + 1, high);
  }
}

void SortAlgs::quickSort(std::vector<int>& arr)
{
  int low = 0;
  int high = arr.size() - 1;
  if (low < high)
  {
    int pi = partition(arr, low, high);
    quickSort(arr, low, pi - 1);
    quickSort(arr, pi + 1, high);
  }
}

void SortAlgs::quickSort(int* arr, int size)
{
  // Implementation for array of integers
}

// Heap Sort
void SortAlgs::heapify(std::vector<int>& arr, int n, int i)
{
  int largest = i, left = 2 * i + 1, right = 2 * i + 2;
  if (left < n && arr[left] > arr[largest]) largest = left;
  if (right < n && arr[right] > arr[largest]) largest = right;
  if (largest != i)
  {
    std::swap(arr[i], arr[largest]);
    heapify(arr, n, largest);
  }
}

void SortAlgs::heapSort(std::vector<int>& arr)
{
  int n = arr.size();
  for (int i = n / 2 - 1; i >= 0; i--) heapify(arr, n, i);
  for (int i = n - 1; i > 0; i--)
  {
    std::swap(arr[0], arr[i]);
    heapify(arr, i, 0);
  }
}

void SortAlgs::heapSort(int* arr, int size)
{
  // Implementation for array of integers
}