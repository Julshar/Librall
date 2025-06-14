add_library (util
  Random.cpp
  SortAlgs.cpp
  ParallelSortAlgs.cpp
  Timer.cpp
  VectorUtil.cpp
)

# This causes any target that links to this (engine) target
# automatically include ${CMAKE_CURRENT_SOURCE_DIR} - dir where all engine files are
target_include_directories(util INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})