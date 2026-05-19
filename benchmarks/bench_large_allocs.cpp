#include "linear_allocator.hpp"
#include "system_allocator.hpp"

#include <benchmark/benchmark.h>

static void BM_SystemAllocator_SingleLarge(benchmark::State& state)
{
    size_t size = state.range(0);
    SystemAllocator a;
    for ( auto _ : state )
    {
        void* p = a.allocate(size, 1);
        benchmark::DoNotOptimize(p);
        a.deallocate(p, size, 1);
    }
}

static void BM_LinearArena_SingleLarge(benchmark::State& state)
{
    size_t size = state.range(0);
    LinearAllocator<10 * 1024 * 1024> a; // capacity is equal to the largest arg (due to compile time constraint)
    for ( auto _ : state )
    {
        void* p = a.allocate(size, 1);
        benchmark::DoNotOptimize(p);

        state.PauseTiming();
        a.reset();
        state.ResumeTiming();
    }
}

BENCHMARK(BM_SystemAllocator_SingleLarge)->Arg(1024)->Arg(1024 * 1024)->Arg(10 * 1024 * 1024);
BENCHMARK(BM_LinearArena_SingleLarge)->Arg(1024)->Arg(1024 * 1024)->Arg(10 * 1024 * 1024);
BENCHMARK_MAIN();