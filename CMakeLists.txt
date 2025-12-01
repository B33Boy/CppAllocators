cmake_minimum_required(VERSION 3.19)
project(crappy_allocators VERSION 0.1 LANGUAGES CXX)

add_compile_options(-Wall -Wextra -Wpedantic)

# ============ Allocators Lib ============
add_library(allocators_lib INTERFACE)

target_include_directories(allocators_lib INTERFACE
    ${PROJECT_SOURCE_DIR}/include
)
target_compile_features(allocators_lib INTERFACE cxx_std_23)


# ============ Subdirs ============
add_subdirectory(examples)
add_subdirectory(benchmarks)
