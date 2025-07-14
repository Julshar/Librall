add_library(console STATIC
  ConsoleArea.cpp
  ConsoleArea.h
  SortAlgsComp.cpp
  SortAlgsComp.h
  ConsoleLoggerClient.cpp
  ConsoleLoggerClient.h
  ConsoleProgram.cpp
  ConsoleProgram.h
)

target_include_directories(console PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(console core util Qt6::Widgets)