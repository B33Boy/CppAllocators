cmake_minimum_required(VERSION 3.19)
project(allocator_benchmarks VERSION 0.1 LANGUAGES CXX)

add_compile_options(-Wall -Wextra)

# ============ Allocators Lib ============
add_library(allocators_lib INTERFACE)

target_include_directories(allocators_lib INTERFACE
    ${PROJECT_SOURCE_DIR}/include
)
target_compile_features(allocators_lib INTERFACE cxx_std_23)

# ============ Testing ============
enable_testing()

include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
)
FetchContent_MakeAvailable(googletest)

# ============ Subdirs ============
add_subdirectory(examples)
add_subdirectory(tests)
add_subdirectory(benchmarks)

