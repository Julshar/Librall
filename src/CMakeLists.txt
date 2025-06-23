cmake_minimum_required(VERSION 4.0.0)
project(librall VERSION 0.1.0
                DESCRIPTION "Basicly a learning project"
                LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(util)
add_subdirectory(logic)

# Link against Qt (adjust version if needed)
find_package(Qt6 REQUIRED COMPONENTS Widgets Sql)
qt_standard_project_setup() # enables AUTOMOC, AUTOUIC, etc

add_executable(${PROJECT_NAME} 
                main.cpp
                MainWindow.cpp
                ButtonPanelArea.cpp
                ConsoleArea.cpp
                MainAreaSection.cpp
)

target_link_libraries(${PROJECT_NAME} 
                util
                logic
                Qt6::Widgets
                Qt6::Sql
)