cmake_minimum_required(VERSION 3.19)
project(allocator_benchmarks VERSION 0.1 LANGUAGES CXX)

# ============ Allocators Lib ============
add_library(allocators_lib INTERFACE)

target_include_directories(allocators_lib INTERFACE
    ${PROJECT_SOURCE_DIR}/include
)
target_compile_features(allocators_lib INTERFACE cxx_std_23)
target_compile_options(allocators_lib INTERFACE -Wall -Wextra)
# ============ Testing ============
enable_testing()

include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
)
FetchContent_MakeAvailable(googletest)

# ============ Benchmarking ============
FetchContent_Declare(
    googlebenchmark
    URL https://github.com/google/benchmark/archive/refs/tags/v1.8.4.zip
)
# Disable benchmark's own tests so they don't clutter the test suite
set(BENCHMARK_ENABLE_TESTING OFF CACHE BOOL "" FORCE)
set(BENCHMARK_ENABLE_GTEST_TESTS OFF CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googlebenchmark)

# Suppress warnings on third party targets we don't control
target_compile_options(benchmark PRIVATE -w)
target_compile_options(benchmark_main PRIVATE -w)

# ============ Subdirs ============
add_subdirectory(examples)
add_subdirectory(tests)
add_subdirectory(benchmarks)

