#include "data_generator.h"
#include "max_element.h"
#include <benchmark/benchmark.h>

template <typename F>
static void BenchmarkMaxElement(benchmark::State &state, F func)
{
    // Perform setup here
    // const std::size_t n = state.range(0);

    const auto data = RandomIntegerArrayGenerator<500000U>::getInstance().getData();

    double max_value = 0;

    for (auto _ : state)
    {
        // This code gets timed
        const auto max_element = func(std::cbegin(data), std::cend(data));
        benchmark::DoNotOptimize(max_value = *max_element);
    }
}

/// TODO: Avoid specifying here, use either from data_generator or via decltype
using iterator_t = std::vector<int>::const_iterator;

// Register the function as a benchmark
// BENCHMARK(BenchmarkMaxElement)->Args({100000})->Args({1000000})->Unit(benchmark::kMillisecond);
BENCHMARK_CAPTURE(BenchmarkMaxElement, std::max_element, std::max_element<iterator_t>)->Unit(benchmark::kMillisecond);
BENCHMARK_CAPTURE(BenchmarkMaxElement, max_element_homebrew, max_element_homebrew<iterator_t>)->Unit(benchmark::kMillisecond);
BENCHMARK_CAPTURE(BenchmarkMaxElement, max_element_parallel, max_element_parallel<iterator_t>)->Unit(benchmark::kMillisecond);
BENCHMARK_CAPTURE(BenchmarkMaxElement, max_element_divide_and_conquer, max_element_divide_and_conquer<iterator_t>)->Unit(benchmark::kMillisecond);

// Run the benchmark
BENCHMARK_MAIN();
