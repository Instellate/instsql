project(instsql_test)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(instsql_test main.cpp)
target_link_libraries(instsql_test PUBLIC instsql)
target_include_directories(instsql_test PUBLIC ${CMAKE_SOURCE_DIR}/lib/inc)