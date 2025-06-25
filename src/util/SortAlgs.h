#pragma once

#include <vector>
#include <functional>
#include <algorithm> // std::make_heap, std::sort_heap

namespace SortAlgs
{
  namespace Helpers
  {
    template <typename T>
    void merge(std::vector<T>& arr, int left, int mid, int right, const std::function<bool(const T&, const T&)>& comp)
    {
      std::vector<T> leftVec(arr.begin() + left, arr.begin() + mid + 1);
      std::vector<T> rightVec(arr.begin() + mid + 1, arr.begin() + right + 1);

      int i = 0, j = 0, k = left;
      while (i < leftVec.size() && j < rightVec.size())
      {
        arr[k++] = comp(leftVec[i], rightVec[j]) ? leftVec[i++] : rightVec[j++];
      }
      while (i < leftVec.size())
      {
        arr[k++] = leftVec[i++];
      }
      while (j < rightVec.size())
      {
        arr[k++] = rightVec[j++];
      }
    }

    template <typename T>
    void mergeSortRec(std::vector<T>& arr, int left, int right, const std::function<bool(const T&, const T&)>& comp)
    {
      if (left < right)
      {
        int mid = left + (right - left) / 2;
        mergeSortRec(arr, left, mid, comp);
        mergeSortRec(arr, mid + 1, right, comp);
        merge(arr, left, mid, right, comp);
      }
    }

    template <typename T>
    int partition(std::vector<T>& arr, int low, int high, const std::function<bool(const T&, const T&)>& comp)
    {
      T pivot = arr[high];
      int i = low - 1;
      for (int j = low; j < high; ++j)
      {
        if (comp(arr[j], pivot))
        {
          std::swap(arr[++i], arr[j]);
        }
      }
      std::swap(arr[i + 1], arr[high]);
      return i + 1;
    }

    template <typename T>
    void quickSortRec(std::vector<T>& arr, int low, int high, const std::function<bool(const T&, const T&)>& comp)
    {
      if (low < high)
      {
        int pi = partition(arr, low, high, comp);
        quickSortRec(arr, low, pi - 1, comp);
        quickSortRec(arr, pi + 1, high, comp);
      }
    }

  } // Helpers

// ======================== INSERTION SORT ========================

  template <typename T>
  void insertionSort(std::vector<T>& arr, std::function<bool(const T&, const T&)> comp = std::less<T>())
  {
    for (size_t i = 1; i < arr.size(); ++i)
    {
      T key = arr[i];
      size_t j = i;
      while (j > 0 && comp(key, arr[j - 1]))
      {
        arr[j] = arr[j - 1];
        --j;
      }
      arr[j] = key;
    }
  }

  // ======================== MERGE SORT ============================

  template <typename T>
  void mergeSort(std::vector<T>& arr, std::function<bool(const T&, const T&)> comp = std::less<T>())
  {
    if (!arr.empty())
      Helpers::mergeSortRec(arr, 0, arr.size() - 1, comp);
  }

  // ======================== QUICK SORT ============================

  template <typename T>
  void quickSort(std::vector<T>& arr, std::function<bool(const T&, const T&)> comp = std::less<T>())
  {
    if (!arr.empty())
      Helpers::quickSortRec(arr, 0, arr.size() - 1, comp);
  }

  // ======================== HEAP SORT =============================
  
  template <typename T>
  void heapSort(std::vector<T>& arr, std::function<bool(const T&, const T&)> comp = std::less<T>())
  {
    auto compWrapper = [&](int i, int j) { return comp(arr[i], arr[j]); };
    std::make_heap(arr.begin(), arr.end(), [&](const T& a, const T& b) { return comp(b, a); }); // max heap if default
    std::sort_heap(arr.begin(), arr.end(), [&](const T& a, const T& b) { return comp(b, a); });
  }

} // namespace SortAlgs