add_library(game_of_life STATIC
  GameOfLifeProgram.cpp
  GameOfLifeProgram.h
  GameOfLifeView.cpp
  GameOfLifeView.h
  GameOfLifeLogic.cpp
  GameOfLifeLogic.h
)

target_include_directories(game_of_life PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(game_of_life core Qt6::Widgets)