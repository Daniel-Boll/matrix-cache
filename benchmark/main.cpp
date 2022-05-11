#include <benchmark/benchmark.h>
#include <fmt/core.h>

#include <OAC/cache/matrix.hpp>

using oac::cache::Matrix;

// {{{1 Matrix constructor
static void BM_Constructor(benchmark::State& state) {
  for (auto _ : state) {
    Matrix<double>* m = new Matrix<double>(state.range(0), state.range(0));
  }
}
// }}}1

// {{{1 Matrix fill random
static void BM_FillRandom(benchmark::State& state) {
  for (auto _ : state) {
    state.PauseTiming();
    Matrix<double>* m = new Matrix<double>(state.range(0), state.range(0));
    state.ResumeTiming();
    m->fillRandom(0, 1e3);
  }
}
// }}}1

// {{{1 Matrix transposition
static void BM_Transposition(benchmark::State& state) {
  for (auto _ : state) {
    state.PauseTiming();
    Matrix<double>* m = new Matrix<double>(state.range(0), state.range(0));
    m->fillRandom(0, 1);
    state.ResumeTiming();

    m->transposeInPlace();
  }
}
// }}}

// {{{1 Matrix multiplication
static void BM_Multiplication(benchmark::State& state) {
  for (auto _ : state) {
    state.PauseTiming();

    Matrix<double>* m1 = new Matrix<double>(state.range(0), state.range(0));
    Matrix<double>* m2 = new Matrix<double>(state.range(0), state.range(0));

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

    Matrix<double>* m1 = new Matrix<double>(state.range(0), state.range(0));
    Matrix<double>* m2 = new Matrix<double>(state.range(0), state.range(0));

    m1->fillRandom(0, 1e3);
    m2->fillRandom(0, 1e3);

    state.ResumeTiming();

    *m1 ^ m2->transpose();
  }
}
// }}}

static constexpr const uint8_t startAt = 10;
static constexpr const uint8_t endAt = 30;
static constexpr const uint8_t incrementBy = 10;

BENCHMARK(BM_Constructor)->DenseRange(startAt, endAt, incrementBy);
BENCHMARK(BM_FillRandom)->DenseRange(startAt, endAt, incrementBy);
BENCHMARK(BM_Transposition)->DenseRange(startAt, endAt, incrementBy);
BENCHMARK(BM_Multiplication)->DenseRange(startAt, endAt, incrementBy);
BENCHMARK(BM_TransposedMultiplication)->DenseRange(startAt, endAt, incrementBy);

BENCHMARK_MAIN();

// vim: set foldmethod=marker:
