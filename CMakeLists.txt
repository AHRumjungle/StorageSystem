cmake_minimum_required(VERSION 3.0.0)
project(storageSystem VERSION 0.1.0 LANGUAGES C CXX)

include(CTest)
enable_testing()

add_executable(storageSystem main.cpp 
sqlite/sqlite3.h 
sqlite/sqlite3.c
utilFunctions.h)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
