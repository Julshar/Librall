cmake_minimum_required(VERSION 4.0.0)
project(librall VERSION 0.1.0
                DESCRIPTION "Basicly a learning project"
                LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)

# Link against Qt libraries
find_package(Qt6 REQUIRED COMPONENTS Widgets Concurrent Sql Core)

# enables AUTOMOC, AUTOUIC, AUTORCC
qt_standard_project_setup()

add_subdirectory(util)
add_subdirectory(core)
add_subdirectory(ui)
add_subdirectory(subprograms/game_of_life)
add_subdirectory(subprograms/console)
# add_subdirectory(subprograms/database_tool)

add_executable(${PROJECT_NAME} 
  main.cpp
)

target_link_libraries(${PROJECT_NAME} 
  PRIVATE
    util
    ui
    core
    game_of_life
    console
    # database_tool
    Qt6::Widgets
    Qt6::Sql
    Qt6::Concurrent
    Qt6::Core
)