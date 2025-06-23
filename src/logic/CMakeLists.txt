add_library (logic
  DatabaseTest.cpp
  SortAlgsComp.cpp
)

target_include_directories(logic INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(logic util)
# target_link_libraries(logic Qt6::Widgets Qt6::Sql)

find_package(Qt6 REQUIRED COMPONENTS Widgets Sql)
target_link_libraries(logic Qt6::Widgets Qt6::Sql)