add_executable(bench_small_allocs bench_small_allocs.cpp)
target_link_libraries(bench_small_allocs
    PRIVATE
    allocators_lib
    benchmark::benchmark
)

add_executable(bench_large_allocs bench_large_allocs.cpp)
target_link_libraries(bench_large_allocs
    PRIVATE
    allocators_lib
    benchmark::benchmark
)

add_executable(bench_stack_allocs bench_stack_allocs.cpp)
target_link_libraries(bench_stack_allocs
    PRIVATE
    allocators_lib
    benchmark::benchmark
)