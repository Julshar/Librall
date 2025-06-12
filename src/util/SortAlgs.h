#pragma once

#include <vector>

// Can make this a template class if needed for other types
// For now, it is specifically for sorting arrays of integers.

class SortAlgs
{
public:
  static void insertionSort(std::vector<int>& arr);
  static void insertionSort(int* arr, int size);

  static void mergeSort(std::vector<int>& arr);
  static void mergeSort(std::vector<int>& arr, int left, int right);
  static void mergeSort(int* arr, int size, int left, int right);
  static void mergeSort(int* arr, int size);

  static void quickSort(std::vector<int>& arr);
  static void quickSort(std::vector<int>& arr, int low, int high);
  static void quickSort(int* arr, int size);
  static void quickSort(int* arr, int size, int kiw, int high);

  static void heapSort(std::vector<int>& arr);
  static void heapSort(int* arr, int size);

private:
  static void merge(std::vector<int>& arr, int left, int mid, int right);
  static void merge(int* arr, int left, int mid, int right);
  static int partition(std::vector<int>& arr, int low, int high);
  static int partition(int* arr, int low, int high);
  static void heapify(std::vector<int>& arr, int n, int i);
  static void heapify(int* arr, int n, int i);
};