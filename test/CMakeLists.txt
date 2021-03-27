cmake_minimum_required(VERSION 3.4.1)

project(
  test
  VERSION 1.0
  LANGUAGES CXX)

set(CMAKE_C_STANDARD 11)
set(StrictWarningBuildFlags
    -Wall
    -Wextra
    -pedantic
    -Wshadow
    -Werror
    -Wno-c99-extensions
    -O0
    -g)
set(AsanFlags -fsanitize=address -fno-omit-frame-pointer)
find_package(GTest REQUIRED)
find_package(benchmark REQUIRED)

set(Tests hashtable linkedlist)
foreach(test_name ${Tests})
  add_executable(${test_name}
                 "${PROJECT_SOURCE_DIR}/${test_name}_test.cpp")
  target_compile_options(${test_name} PUBLIC ${StrictWarningBuildFlags}
                                                  ${AsanFlags})
  target_link_libraries(${test_name} lib_hashtable GTest::gtest
                        ${AsanFlags})
  add_test(${test_name}_test ${test_name})
endforeach()

set(Benchmarks hashtable linkedlist)
foreach(benchmark_name ${Benchmarks})
  add_executable(${benchmark_name}_benchmarks
                 "${PROJECT_SOURCE_DIR}/${benchmark_name}_benchmarks.cpp")
  target_compile_options(${benchmark_name}_benchmarks
                         PUBLIC ${StrictWarningBuildFlags} ${AsanFlags})
  target_link_libraries(${benchmark_name}_benchmarks lib_hashtable
                        benchmark::benchmark ${AsanFlags})
  add_test(${benchmark_name}_benchmarks ${benchmark_name}_benchmarks)
endforeach()
