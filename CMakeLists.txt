cmake_minimum_required(VERSION 3.25)
project(instsql)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(INSTSQL_TEST ON)

if (INSTSQL_TEST)
    add_subdirectory(test)
endif ()

find_package(PostgreSQL REQUIRED)

add_library(${PROJECT_NAME} SHARED lib/src/Client.cpp lib/src/result/Result.cpp lib/inc/instsql/result/Result.h lib/src/result/Row.cpp lib/inc/instsql/result/Row.h)
target_include_directories(${PROJECT_NAME} PRIVATE ${PostgreSQL_INCLUDE_DIRS})
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/lib/inc)
target_link_libraries(${PROJECT_NAME} PUBLIC PostgreSQL::PostgreSQL)
target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wpedantic -Werror)