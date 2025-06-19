cmake_minimum_required(VERSION 4.0.0)
project(librall VERSION 0.1.0
                DESCRIPTION "Basicly a learning project"
                LANGUAGES C CXX)

# needed?
include(CTest)
enable_testing()

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(util)

# Find Qt (adjust version if needed)
find_package(Qt6 REQUIRED COMPONENTS Widgets Sql)
qt_standard_project_setup() # enables AUTOMOC, AUTOUIC, etc

add_executable(${PROJECT_NAME} main.cpp)

target_link_libraries(librall util)
target_link_libraries(${PROJECT_NAME} Qt6::Widgets Qt6::Sql)

# needed?
set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)