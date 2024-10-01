//g++ *.cpp -std=c++11 -isystem ~/benchmark/include -L ~/benchmark/build/src -lbenchmark -lpthread -o bm
#include <benchmark/benchmark.h>
#include "1.h"

static void BM_find_marker1(benchmark::State& state){
    for (auto _ : state)
        find_marker1(input);
}

static void BM_find_marker1_14(benchmark::State& state){
    for (auto _ : state)
        find_marker1_14(input);
}

static void BM_find_marker1_u(benchmark::State& state){
    for (auto _ : state)
        find_marker1_u(input);
}

static void BM_find_marker1_u_14(benchmark::State& state){
    for (auto _ : state)
        find_marker1_u_14(input);
}
static void BM_find_marker11(benchmark::State& state){
    for (auto _ : state)
        find_marker11(input);
}

static void BM_find_marker11_2(benchmark::State& state){
    for (auto _ : state)
        find_marker11_2(input);
}

static void BM_find_marker2(benchmark::State& state){
    for (auto _ : state)
        find_marker2(input);
}

static void BM_find_marker3(benchmark::State& state){
    for (auto _ : state)
        find_marker3(input);
}

static void BM_find_marker4(benchmark::State& state){
    for (auto _ : state)
        find_marker4(input);
}

static void BM_find_marker4_2(benchmark::State& state){
    for (auto _ : state)
        find_marker4_2(input);
}

static void BM_find_marker4_2_14(benchmark::State& state){
    for (auto _ : state)
        find_marker4_2_14(input);
}

static void BM_find_marker4_21(benchmark::State& state){
    for (auto _ : state)
        find_marker4_21(input);
}

static void BM_find_marker4_21_14(benchmark::State& state){
    for (auto _ : state)
        find_marker4_21_14(input);
}

static void BM_find_marker4_3(benchmark::State& state){
    for (auto _ : state)
        find_marker4_3(input);
}

static void BM_find_marker4_3_14(benchmark::State& state){
    for (auto _ : state)
        find_marker4_3_14(input);
}

static void BM_find_marker4_4(benchmark::State& state){
    for (auto _ : state)
        find_marker4_4(input);
}

static void BM_find_marker4_4_14(benchmark::State& state){
    for (auto _ : state)
        find_marker4_4_14(input);
}
static void BM_find_marker5(benchmark::State& state){
    for (auto _ : state)
        find_marker5(input);
}

static void BM_find_marker6(benchmark::State& state){
    for (auto _ : state)
        find_marker6(input);
}

static void BM_find_marker6_2(benchmark::State& state){
    for (auto _ : state)
        find_marker6_2(input);
}

static void BM_find_marker7(benchmark::State& state){
    for (auto _ : state)
        find_marker7(input);
}

static void BM_find_marker7_2(benchmark::State& state){
    for (auto _ : state)
        find_marker7_2(input);
}

static void BM_find_marker7_3(benchmark::State& state){
    for (auto _ : state)
        find_marker7_3(input);
}

static void BM_find_marker7_4(benchmark::State& state){
    for (auto _ : state)
        find_marker7_4(input);
}

static void BM_find_marker7_4_14(benchmark::State& state){
    for (auto _ : state)
        find_marker7_4_14(input);
}

static void BM_find_marker8(benchmark::State& state){
    for (auto _ : state)
        find_marker8(input);
}

static void BM_find_marker9(benchmark::State& state){
    for (auto _ : state)
        find_marker9(input);
}
static void BM_find_marker9_14(benchmark::State& state){
    for (auto _ : state)
        find_marker9_14(input);
}

BENCHMARK(BM_find_marker1);
BENCHMARK(BM_find_marker1_14);
BENCHMARK(BM_find_marker1_u);
BENCHMARK(BM_find_marker1_u_14);
BENCHMARK(BM_find_marker11);
BENCHMARK(BM_find_marker11_2);
BENCHMARK(BM_find_marker2);
BENCHMARK(BM_find_marker3);
BENCHMARK(BM_find_marker4);
BENCHMARK(BM_find_marker4_2);
BENCHMARK(BM_find_marker4_2_14);
BENCHMARK(BM_find_marker4_21);
BENCHMARK(BM_find_marker4_21_14);
BENCHMARK(BM_find_marker4_3);
BENCHMARK(BM_find_marker4_3_14);
BENCHMARK(BM_find_marker4_4);
BENCHMARK(BM_find_marker4_4_14);
BENCHMARK(BM_find_marker5);
BENCHMARK(BM_find_marker6);
BENCHMARK(BM_find_marker6_2);
BENCHMARK(BM_find_marker7);
BENCHMARK(BM_find_marker7_2);
BENCHMARK(BM_find_marker7_3);
BENCHMARK(BM_find_marker7_4);
BENCHMARK(BM_find_marker7_4_14);
BENCHMARK(BM_find_marker8);
BENCHMARK(BM_find_marker9);
BENCHMARK(BM_find_marker9_14);

BENCHMARK_MAIN();