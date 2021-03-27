cmake_minimum_required(VERSION 3.4.1)

project(
  lib_hashtable_project
  VERSION 1.0
  LANGUAGES CXX)
option(BUILD_TESTS "" OFF)

set(CMAKE_CXX_STANDARD 17)
add_subdirectory("${PROJECT_SOURCE_DIR}/lib_hashtable")

if(BUILD_TESTS)
  enable_testing()
  add_definitions(-DTESTING)
  add_subdirectory("${PROJECT_SOURCE_DIR}/test")
endif()
