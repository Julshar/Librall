#pragma once

#include <vector>

class VectorUtil
{
public:

  static std::vector<int> generateRandomVector(int size, int minVal, int maxVal);
  static void printVector(const std::vector<int>& vec);
  
};