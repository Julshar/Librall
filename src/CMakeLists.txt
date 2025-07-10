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
add_subdirectory(logic)

add_executable(${PROJECT_NAME} 
  main.cpp
  MainWindow.cpp
  ButtonPanelArea.cpp
  Logger.cpp
  ModeTabBar.cpp
)

target_link_libraries(${PROJECT_NAME} 
  util
  logic
  Qt6::Widgets
  Qt6::Sql
  Qt6::Concurrent
  Qt6::Core
)