add_library(core STATIC
  SubprogramManager.cpp
  SubprogramManager.h
  SubprogramBase.h
  UIMode.h
)

target_include_directories(core PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(core
  PRIVATE Qt6::Core
  PUBLIC Qt6::Widgets
  PUBLIC util
)