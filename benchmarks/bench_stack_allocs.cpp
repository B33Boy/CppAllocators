#include "linear_allocator.hpp"
#include "stack_allocator.hpp"

#include <benchmark/benchmark.h>

static void BM_LinearAllocator_Reset(benchmark::State& state)
{
    LinearAllocator<1024> a;
    for ( auto _ : state )
    {
        for ( int i = 0; i < state.range(0); i++ )
            a.allocate<int>();
        benchmark::DoNotOptimize(a);
        a.reset();
    }
}

static void BM_StackAllocator_Restore(benchmark::State& state)
{
    StackAllocator<1024> a;
    for ( auto _ : state )
    {
        size_t marker = a.save();
        for ( int i = 0; i < state.range(0); i++ )
            a.allocate<int>();
        benchmark::DoNotOptimize(a);
        a.restore(marker);
    }
}

BENCHMARK(BM_LinearAllocator_Reset)->Arg(1024)->Arg(1024 * 1024)->Arg(50 * 1024 * 1024);
BENCHMARK(BM_StackAllocator_Restore)->Arg(1024)->Arg(1024 * 1024)->Arg(50 * 1024 * 1024);
BENCHMARK_MAIN();