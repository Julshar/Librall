cmake_minimum_required(VERSION 4.0.0)
project(librall VERSION 0.1.0
                DESCRIPTION "Basicly a learning project"
                LANGUAGES C CXX)

# needed?
include(CTest)
enable_testing()

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(util)

add_executable(librall main.cpp)

target_link_libraries(librall util)

# needed?
set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)