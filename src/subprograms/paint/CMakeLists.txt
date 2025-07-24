add_library(paint STATIC
  PaintProgram.cpp
  PaintProgram.h
  PaintCanvas.cpp
  PaintCanvas.h
)

target_include_directories(paint PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(paint core util Qt6::Widgets)