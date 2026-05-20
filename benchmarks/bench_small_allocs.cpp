#include "linear_allocator.hpp"
#include "stack_allocator.hpp"
#include "system_allocator.hpp"

#include <benchmark/benchmark.h>

static void BM_SystemAllocator_SmallAllocs(benchmark::State& state)
{
    SystemAllocator a;
    for ( auto _ : state )
    {
        auto* p = a.allocate<int>();
        benchmark::DoNotOptimize(p); // prevents the compiler from eliding the call
        a.deallocate(p);
    }
}

static void BM_LinearAllocator_SmallAllocs(benchmark::State& state)
{
    LinearAllocator<1024 * 1024> a; // 1MB backing buffer
    for ( auto _ : state )
    {
        auto* p = a.allocate<int>();
        benchmark::DoNotOptimize(p);
        if ( p == nullptr )
            a.reset(); // reset when full
    }
}

static void BM_StackAllocator_SmallAllocs(benchmark::State& state)
{
    StackAllocator<1024 * 1024> a;
    for ( auto _ : state )
    {
        auto* p = a.allocate<int>();
        benchmark::DoNotOptimize(p);
        if ( p == nullptr )
            a.reset();
    }
}

BENCHMARK(BM_SystemAllocator_SmallAllocs);
BENCHMARK(BM_LinearAllocator_SmallAllocs);
BENCHMARK(BM_StackAllocator_SmallAllocs);

BENCHMARK_MAIN();