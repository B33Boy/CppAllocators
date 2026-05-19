add_executable(bench_small_allocs bench_small_allocs.cpp)
target_link_libraries(bench_small_allocs
    PRIVATE
    allocators_lib
    benchmark::benchmark
)