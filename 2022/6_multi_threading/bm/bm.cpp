//g++ *.cpp -std=c++11 -isystem ~/benchmark/include -L ~/benchmark/build/src -lbenchmark -lpthread -o bm
#include <benchmark/benchmark.h>
#include "functions.h"

static void BM_find_marker(benchmark::State& state){
    for (auto _ : state)
        find_marker(input);
}

static void BM_find_marker_using_threads(benchmark::State& state){
    for (auto _ : state)
        find_marker_using_threads(input, 8);
}

BENCHMARK(BM_find_marker);
BENCHMARK(BM_find_marker_using_threads);

BENCHMARK_MAIN();