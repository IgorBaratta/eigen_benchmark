#include <benchmark/benchmark.h>
#include "ndVector.hpp"
#include <complex>

static void CustomArguments(benchmark::internal::Benchmark *b)
{
    std::vector<long> rows{10'000, 10'000'000};
    std::vector<long> cols{3, 5};
    for (auto r : rows)
        for (auto c : cols)
            b->Args({r, c});
}

template <typename T>
static void allocate_data(benchmark::State &state)
{
    for (auto _ : state)
    {
        ndVector<T> vec(state.range(0), state.range(1));
        benchmark::DoNotOptimize(vec);
    }
}

template <typename T>
static void loop_and_assign(benchmark::State &state)
{
    ndVector<T> vec(state.range(0), state.range(1));
    for (auto _ : state)
    {
        for (std::size_t i = 0; i < vec.rows(); i++)
            for (std::size_t j = 0; j < vec.cols(); j++)
                vec(i, j) = i + j;
        benchmark::DoNotOptimize(vec);
    }
}

BENCHMARK_TEMPLATE(allocate_data, double)->Apply(CustomArguments);
BENCHMARK_TEMPLATE(allocate_data, std::complex<double>)->Apply(CustomArguments);
BENCHMARK_TEMPLATE(allocate_data, std::int64_t)->Apply(CustomArguments);

BENCHMARK_TEMPLATE(loop_and_assign, double)->Apply(CustomArguments);
BENCHMARK_TEMPLATE(loop_and_assign, std::complex<double>)->Apply(CustomArguments);
BENCHMARK_TEMPLATE(loop_and_assign, std::int64_t)->Apply(CustomArguments);

BENCHMARK_MAIN();