#include <iostream>
#include <cstdint>
#include <cmath>
#include <functional>
#include <limits>

#include "cpp_notes/util/bench.h"

// -------------- Fibonacci --------------

uint64_t FibFn(const uint64_t n) {
  if (n < 2) {
    return 1;
  }
  return FibFn(n - 2) + FibFn(n - 1);
}

// auto FibLambda_1{[](const uint64_t n)-> uint64_t {
//   if (n < 2) {
//     return 1;
//   }
//   return FibLambda_1(n - 2) + FibLambda_1(n - 1);  // Error: Variable 'FibLambda_1' declared with deduced type 'auto' cannot appear in its own initializer
// }};  // *** COMPILE ERROR ***

static std::function<uint64_t (const uint64_t)> FibLambda_2{[](const uint64_t n)-> uint64_t {
  if (n < 2) {
    return 1;
  }
  return FibLambda_2(n - 2) + FibLambda_2(n - 1);
}};

constexpr uint64_t FIB_N{35};
constexpr uint64_t SAMPLE_SIZE{10};

BENCH_DEF(FibFn, SAMPLE_SIZE, FibFn(FIB_N))
BENCH_DEF(FibLambda, SAMPLE_SIZE, FibLambda_2(FIB_N))

// -------------- Simple Sum --------------

uint64_t SumFn(const uint64_t n) {
  uint64_t res{0};
  for (uint64_t i{0}; i < n; ++i) {
    res += i % 2;
  }
  return res;
}

static auto SumLambda1{
  [](const uint64_t n) -> uint64_t {
    uint64_t res{0};
    for (uint64_t i{0}; i < n; ++i) {
      res += i % 3;
    }
    return res;
  }
};

static std::function<uint64_t (const uint64_t)> SumLambda2{
    [](const uint64_t n) -> uint64_t {
      uint64_t res{0};
      for (uint64_t i{0}; i < n; ++i) {
        res += i % 2;
      }
      return res;
    }
};

constexpr uint64_t SUM_N{10000000};

BENCH_DEF(SumFn, SAMPLE_SIZE, SumFn(SUM_N))
BENCH_DEF(SumLambdaAuto, SAMPLE_SIZE, SumLambda1(SUM_N))
BENCH_DEF(SumLambdaExplicit, SAMPLE_SIZE, SumLambda2(SUM_N))

int main(int argc, char **argv) {

  #pragma cmt beg

  const std::size_t fib_fn_dur{BENCH(FibFn)};
  std::cout << "Fib Function Dur: " << fib_fn_dur << "ns"; //> Fib Function Dur: 12ns

  const std::size_t fib_lambda_dur{BENCH(FibLambda)};
  std::cout << "Fib Lambda Dur: " << fib_lambda_dur << "ns"; //> Fib Lambda Dur: 42162037ns

  double fib_ratio{static_cast<double>(fib_lambda_dur) / static_cast<double>(fib_fn_dur)};
  fib_ratio = std::round(fib_ratio * 100) / 100;
  std::cout << "Fib Lambda/Function Ratio: " << fib_ratio; //> Fib Lambda/Function Ratio: 3.5135e+06

  const std::size_t sum_fn_dur{BENCH(SumFn)};
  std::cout << "Sum Function Dur: " << sum_fn_dur << "ns"; //> Sum Function Dur: 0ns

  const std::size_t sum_lambda_auto_dur{BENCH(SumLambdaAuto)};
  std::cout << "Sum Lambda (auto) Dur: " << sum_lambda_auto_dur << "ns"; //> Sum Lambda (auto) Dur: 0ns

  const std::size_t sum_lambda_explicit_dur{BENCH(SumLambdaExplicit)};
  std::cout << "Sum Lambda (explicit) Dur: " << sum_lambda_explicit_dur << "ns"; //> Sum Lambda (explicit) Dur: 990325ns

  double sum_ratio_1{static_cast<double>(sum_lambda_auto_dur) / static_cast<double>(sum_fn_dur)};
  sum_ratio_1 = std::round(sum_ratio_1 * 100) / 100;
  std::cout << "Sum Lambda(auto)/Function Ratio: " << sum_ratio_1; //> Sum Lambda(auto)/Function Ratio: nan

  double sum_ratio_2{static_cast<double>(sum_lambda_explicit_dur) / static_cast<double>(sum_fn_dur)};
  sum_ratio_2 = std::round(sum_ratio_2 * 100) / 100;
  std::cout << "Sum Lambda(explicit)/Function Ratio: " << sum_ratio_2; //> Sum Lambda(explicit)/Function Ratio: inf

  #pragma cmt end
  return 0;
}