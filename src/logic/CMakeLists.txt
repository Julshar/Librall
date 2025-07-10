add_library (logic
  DatabaseTest.cpp
  SortAlgsComp.cpp
  GameOfLife.cpp
  ConsoleArea.cpp
  MainAreaSection.cpp
)

target_include_directories(logic PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
# target_include_directories(util INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(logic PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/..)

target_link_libraries(logic util)

target_link_libraries(logic
  Qt6::Widgets
  Qt6::Sql
  Qt6::Concurrent
  Qt6::Core)