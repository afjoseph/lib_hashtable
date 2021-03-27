cmake_minimum_required(VERSION 3.4.1)

project(lib_hashtable VERSION 1.0)
add_library(${PROJECT_NAME} INTERFACE)
set_target_properties(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE CXX)
target_include_directories(${PROJECT_NAME} INTERFACE "${PROJECT_SOURCE_DIR}/")
