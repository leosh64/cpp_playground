#include "data_generator.h"
#include "max_element.h"
#include <algorithm>
#include <benchmark/benchmark.h>
#include <iostream>
#include <memory>

template <typename MaxElementImpl>
static void BM_SomeFunction(benchmark::State &state)
{
    // Perform setup here
    // const std::size_t n = state.range(0);

    const auto data = RandomIntegerArrayGenerator<500000U>::getInstance().getData();

    std::unique_ptr<IMaxElement<>> impl_p = std::make_unique<MaxElementImpl>();

    for (auto _ : state)
    {
        // This code gets timed
        const auto max_element = impl_p->Get(data);
        volatile auto max_value = *max_element;
    }
}

// Register the function as a benchmark
// BENCHMARK(BM_SomeFunction)->Args({100000})->Args({1000000})->Unit(benchmark::kMillisecond);
BENCHMARK_TEMPLATE1(BM_SomeFunction, StandardLibraryMaxElement<>)->Unit(benchmark::kMillisecond);
BENCHMARK_TEMPLATE1(BM_SomeFunction, HomebrewMaxElement<>)->Unit(benchmark::kMillisecond);
BENCHMARK_TEMPLATE1(BM_SomeFunction, ParallelMaxElement<>)->Unit(benchmark::kMillisecond);

// Run the benchmark
BENCHMARK_MAIN();
