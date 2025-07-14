add_library(database_tool STATIC
  DatabaseTest.cpp
  DatabaseTest.h
)

target_include_directories(database_tool PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(database_tool Qt6::Widgets Qt6::Sql)