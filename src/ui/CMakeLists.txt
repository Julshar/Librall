add_library(ui STATIC
  MainWindow.cpp
  MainWindow.h
  ModeTabBar.cpp
  ModeTabBar.h
  SidePanelArea.cpp
  SidePanelArea.h
)

target_include_directories(ui PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(ui
  PUBLIC core
  PUBLIC console
  PUBLIC util
  PUBLIC game_of_life
  PUBLIC paint
  PRIVATE Qt6::Widgets
)

