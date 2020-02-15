cmake_minimum_required(VERSION 2.8.3)
project(testSQLITE)

add_definitions(-std=c++11 -ofast)

#find_package(SQLite3)
#if(NOT SQLITE3_FOUND)
#    message(FATAL_ERROR "SQLite3 not found")
#endif()

set(SQLITE3_INCLUDE_DIRS "/usr/local/Cellar/sqlite/3.23.1/include")
set(SQLITE3_LIB_DIRS "/usr/local/Cellar/sqlite/3.23.1/lib")
set(SQLITE_LIBRARIES "sqlite3")

include_directories(${SQLITE3_INCLUDE_DIRS})
link_directories(${SQLITE3_LIB_DIRS})

file(GLOB SRC_FILES "*.cpp")

add_executable(testSQLITE ${SRC_FILES})

target_link_libraries(testSQLITE ${SQLITE_LIBRARIES})
