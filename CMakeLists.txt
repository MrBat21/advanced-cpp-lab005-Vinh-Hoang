cmake_minimum_required(VERSION 3.16)
project(AlgorithmAnalysisLab LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include(CTest)

add_library(algorithms
    src/common.cpp
    src/duplicate.cpp
    src/frequency.cpp
)

target_include_directories(algorithms PUBLIC include)

add_executable(benchmark_app benchmark/benchmark.cpp)
target_link_libraries(benchmark_app PRIVATE algorithms)

add_executable(test_algorithms tests/test_algorithms.cpp)
target_link_libraries(test_algorithms PRIVATE algorithms)

if(BUILD_TESTING)
    add_test(NAME test_algorithms COMMAND test_algorithms)
endif()
