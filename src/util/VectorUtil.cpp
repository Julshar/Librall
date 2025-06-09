#include "VectorUtil.h"
#include "Random.h"

#include <iostream>

// Function to generate random array
std::vector<int> VectorUtil::generateRandomVector(int size, int minVal = 0, int maxVal = 100)
{
  std::vector<int> arr(size);
  for (int &num : arr)
  {
    num = Random::genValue(minVal, maxVal);
  }
  return arr;
}

// Utility function to print array
void VectorUtil::printVector(const std::vector<int>& arr)
{
  for (int num : arr)
  {
    std::cout << num << " ";
  }
  std::cout << std::endl;
}