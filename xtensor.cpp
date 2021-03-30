#define EIGEN_NO_DEBUG
#include <complex>
#include <benchmark/benchmark.h>
#include <xtensor/xtensor.hpp>

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
        xt::xtensor<T, 2> vec({state.range(0), state.range(1)});
        vec.fill(0);
        benchmark::DoNotOptimize(vec);
    }
}

template <typename T>
static void loop_and_assign(benchmark::State &state)
{
    xt::xtensor<T, 2> vec({state.range(0), state.range(1)});
    for (auto _ : state)
    {
        for (std::size_t i = 0; i < vec.shape(0); i++)
            for (std::size_t j = 0; j < vec.shape(1); j++)
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