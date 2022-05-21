#include <benchmark/benchmark.h>
#include <fmt/core.h>

#include <OAC/cache/matrix.hpp>
#include <memory>

using oac::cache::Matrix;

// {{{1 Matrix constructor
static void BM_Constructor(benchmark::State& state) {
  for (auto _ : state) {
    auto m = std::make_unique<Matrix<double>>(state.range(0), state.range(0));
  }
}
// }}}1

// {{{1 Matrix fill random
static void BM_FillRandom(benchmark::State& state) {
  for (auto _ : state) {
    state.PauseTiming();
    auto m = std::make_unique<Matrix<double>>(state.range(0), state.range(0));
    state.ResumeTiming();
    m->fillRandom(0, 1e3);
  }
}
// }}}1

// {{{1 Matrix transposition
static void BM_Transposition(benchmark::State& state) {
  for (auto _ : state) {
    state.PauseTiming();
    auto m = std::make_unique<Matrix<double>>(state.range(0), state.range(0));
    m->fillRandom(0, 1);
    state.ResumeTiming();

    Matrix<double> m2 = m->transpose();
  }
}
// }}}

// {{{1 Matrix multiplication
static void BM_Multiplication(benchmark::State& state) {
  for (auto _ : state) {
    state.PauseTiming();

    auto m1 = std::make_unique<Matrix<double>>(state.range(0), state.range(0));
    auto m2 = std::make_unique<Matrix<double>>(state.range(0), state.range(0));

    m1->fillRandom(0, 1e3);
    m2->fillRandom(0, 1e3);

    state.ResumeTiming();

    *m1** m2;
  }
}
// }}}

// {{{1 Matrix transposed multiplication
static void BM_TransposedMultiplication(benchmark::State& state) {
  for (auto _ : state) {
    state.PauseTiming();

    auto m1 = std::make_unique<Matrix<double>>(state.range(0), state.range(0));
    auto m2 = std::make_unique<Matrix<double>>(state.range(0), state.range(0));

    m1->fillRandom(0, 1e3);
    m2->fillRandom(0, 1e3);

    state.ResumeTiming();

    *m1 ^ m2->transpose();
  }
}
// }}}

static constexpr const uint32_t startAt = 200;
static constexpr const uint32_t endAt = 2e3 + startAt;
static constexpr const uint32_t incrementBy = 200;

BENCHMARK(BM_Constructor)->DenseRange(startAt, endAt, incrementBy);
BENCHMARK(BM_FillRandom)->DenseRange(startAt, endAt, incrementBy);
BENCHMARK(BM_Transposition)->DenseRange(startAt, endAt, incrementBy);
BENCHMARK(BM_Multiplication)->DenseRange(startAt, endAt, incrementBy);
BENCHMARK(BM_TransposedMultiplication)->DenseRange(startAt, endAt, incrementBy);

BENCHMARK_MAIN();

// vim: set foldmethod=marker:
