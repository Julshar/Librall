add_library(util STATIC
  Logger.cpp
  Logger.h
  ILoggerClient.h
  Random.cpp
  Random.h
  SortAlgs.cpp
  SortAlgs.h
  ParallelSortAlgs.cpp
  ParallelSortAlgs.h
  Timer.cpp
  Timer.h
  VectorUtil.cpp
  VectorUtil.h
)

target_include_directories(util PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(util
  PUBLIC Qt6::Core
  PRIVATE Qt6::Concurrent
)