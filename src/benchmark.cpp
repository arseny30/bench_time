#include <absl/time/clock.h>
#include <benchmark/benchmark.h>
#include <td/utils/port/Clocks.h>

#include <chrono>

#include "precise-time.h"

static void BM_StringCreation(benchmark::State &state) {
  for (auto _ : state)
    std::string empty_string;
}
BENCHMARK(BM_StringCreation);

static void BM_chrono_steady_clock(benchmark::State &state) {
  for (auto _ : state) {
    auto duration = std::chrono::steady_clock::now().time_since_epoch();
    auto nano =
        std::chrono::duration_cast<std::chrono::nanoseconds>(duration).count();
    benchmark::DoNotOptimize(nano);
  }
}
BENCHMARK(BM_chrono_steady_clock);

static void BM_chrono_system_clock(benchmark::State &state) {
  for (auto _ : state) {
    auto duration = std::chrono::system_clock::now().time_since_epoch();
    auto nano =
        std::chrono::duration_cast<std::chrono::nanoseconds>(duration).count();
    benchmark::DoNotOptimize(nano);
  }
}
BENCHMARK(BM_chrono_system_clock);

static void BM_abseil_now(benchmark::State &state) {
  for (auto _ : state) {
    auto nano = absl::GetCurrentTimeNanos();
    benchmark::DoNotOptimize(nano);
  }
}
BENCHMARK(BM_abseil_now);

static void BM_get_utime_monotonic(benchmark::State &state) {
  for (auto _ : state) {
    auto nano = get_utime_monotonic();
    benchmark::DoNotOptimize(nano);
  }
}
BENCHMARK(BM_get_utime_monotonic);

static void BM_get_double_time(benchmark::State &state) {
  for (auto _ : state) {
    auto nano = get_double_time();
    benchmark::DoNotOptimize(nano);
  }
}
BENCHMARK(BM_get_double_time);

static void BM_get_precise_time_1000000(benchmark::State &state) {
  for (auto _ : state) {
    auto nano = get_precise_time(1000000);
    benchmark::DoNotOptimize(nano);
  }
}
BENCHMARK(BM_get_precise_time_1000000);

BENCHMARK_MAIN();
