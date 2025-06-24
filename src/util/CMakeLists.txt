add_library (util
  Random.cpp
  SortAlgs.cpp
  ParallelSortAlgs.cpp
  Timer.cpp
  VectorUtil.cpp
)

target_include_directories(util INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})